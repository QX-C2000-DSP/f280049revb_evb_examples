// #############################################################################
//
//  FILE:   i2c_ex2_eeprom.c
//
//  TITLE:  I2C EEPROM
//
//! \addtogroup driver_example_list
//! <I2C EEPROM>
//!
//! This program will write 1-14 words to EEPROM and read them back. The data
//! written and the EEPROM address written to are contained in the message
//! structure, i2cMsgOut. The data read back will be contained in the message
//! structure i2cMsgIn.
//!
//! \b External \b Connections on Control card\n
//!  - Connect external I2C EEPROM at address 0x50
//!  - Connect GPIO0/SDAA on controlCARD to external EEPROM SDA (serial data) pin
//!  - Connect GPIO1/SCLA on controlCARD to external EEPROM SCL (serial clock) pin
//!
//! \b Watch \b Variables \n
//!  - \b i2cMsgOut - Message containing data to write to EEPROM
//!  - \b i2cMsgIn - Message containing data read from EEPROM
//!
//
// #############################################################################

//
// Included Files
//
#include "device.h"
#include "driverlib.h"
#include <stdio.h>

volatile struct SCI_REGS *dbg_uart; // 调试使用的串口

// 用户层重载putchar回调函数
int putchar(int c)
{
    while (!dbg_uart->SCICTL2.bit.TXEMPTY)
        ;
    dbg_uart->SCITXBUF.all = c;
    while (!dbg_uart->SCICTL2.bit.TXEMPTY)
        ;

    return c;
}

// 使用打印SCI的串口初始化流程
void StdOutInit(volatile struct SCI_REGS *sci, int baudrate, uint32_t pin, uint32_t pin_mux)
{
    dbg_uart = sci;

    if (sci == &SciaRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    else if (sci == &ScibRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    else if (sci == &ScicRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIC);

    float tmp = (float)DEVICE_LSPCLK_FREQ / 8 / baudrate;
    if ((tmp - (int)tmp) >= 0.5)
        tmp = tmp + 1;
    int val = (int)tmp - 1;

    sci->SCICCR.bit.SCICHAR  = 7;
    sci->SCILBAUD.all        = val & 0xFF;
    sci->SCIHBAUD.all        = val >> 8;
    sci->SCICTL1.bit.SWRESET = 1;
    sci->SCICTL1.bit.TXENA   = 1;

    GPIO_setPinConfig(pin_mux);
    GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
}

/*----------------------------------------------------------*/
#define USE_DEBUG_PRINTF

#ifdef USE_DEBUG_PRINTF
#define DEBUG_LOG(fmt, ...)            \
    do                                 \
    {                                  \
        printf("" fmt, ##__VA_ARGS__); \
    } while (0)
#else
#define DEBUG_LOG(fmt, ...)
#endif

/*----------------------------------------------------------*/
// 读写数据大小不能超过eeprom 1 page size, 注意: 写完1page需要等待eeprom ACK polling, about 5ms
// AT24C02： 256   字节 (2K位),  每页8字节,  32页
// AT24C04： 512   字节 (4K位),  每页16字节, 32页
// AT24C08： 1024  字节 (8K位),  每页16字节, 64页
// AT24C16： 2048  字节 (16K位), 每页16字节, 128页
// AT24C32： 4096  字节 (32K位), 每页32字节, 128页
// AT24C64： 8192  字节 (64K位), 每页32字节, 256页
// AT24C256：32768 字节(256K位), 每页64字节, 512页
#define EEPROM_PAGE_SIZE    8
#define EEPROM_MEMORY_SIZE  0x100

#define MAX_WTRD_SIZE       8

#define I2C_FIFO_LEVEL      8
#define TARGET_ADDRESS      0x50
#define MAX_BUFFER_SIZE     64

#define I2C_WRITE           0
#define I2C_READ            1

#define MAX_TIMEOUT         0x100000
#define MAX_7_BIT_ADDRESS   0x7F

//
// Error messages for read and write functions
//
#define I2C_SUCCESS            0x0000
#define ERROR_BUS_BUSY         0x1000
#define ERROR_NACK_RECEIVED    0x2000
#define ERROR_ARBITRATION_LOST 0x3000
#define ERROR_STOP_NOT_READY   0x5555

/*----------------------------------------------------------*/
struct I2CHandle
{
    uint32_t base;
    uint16_t status;
    uint16_t targetAddr;    // Target address tied to the message.
    uint32_t *pControlAddr; // MSB
    uint16_t NumOfAddrBytes;
    uint16_t NumOfDataBytes; // Number of valid bytes in message.
    uint16_t *pTX_MsgBuffer; // Pointer to TX message buffer
    uint16_t *pRX_MsgBuffer; // Pointer to RX message buffer
    struct I2CHandle *currentHandlePtr;

    uint16_t numofHasTransBytes; // has transmitted bytes
    uint16_t numofHasRecvBytes;  // has Receive bytes

    uint16_t numofFifoLevel; // number of I2C_FIFO_LEVEL
    uint16_t remainingBytes; // remaining Bytes

    uint32_t WriteCycleTime_in_us; //  Target write cycle time. Depends on target.
                                   //  Please check target device datasheet
};

struct I2CHandle EEPROM;
struct I2CHandle *currentResponderPtr; // Used in interrupt
uint32_t ControlAddr;

uint16_t TX_MsgBuffer[MAX_BUFFER_SIZE];
uint16_t RX_MsgBuffer[MAX_BUFFER_SIZE];

__interrupt void i2cFIFO_isr(void);
__interrupt void i2caISR(void);
/*--------------------------------------------------------------------*/
#define __I2C_PIN_MUX_INIT(i2c_base, sda, scl)        \
    {                                                 \
        .sda_pin     = sda,                           \
        .sda_pin_mux = GPIO_##sda##_##i2c_base##_SDA, \
        .scl_pin     = scl,                           \
        .scl_pin_mux = GPIO_##scl##_##i2c_base##_SCL, \
    }

enum i2c_bus_id_e
{
    I2C_BUS_0,
    I2C_BUS_1,
    I2C_BUS_2,
};

typedef struct __i2c_gpio_config_t
{
    uint32_t sda_pin;
    uint32_t sda_pin_mux;
    uint32_t scl_pin;
    uint32_t scl_pin_mux;
} i2c_gpio_t;

static i2c_gpio_t i2c_gpio[] = {
    // ----------------------------- base  sda  scl
    [I2C_BUS_0] = __I2C_PIN_MUX_INIT(I2CA, 0, 1),
    [I2C_BUS_1] = __I2C_PIN_MUX_INIT(I2CA, 32, 33),
    [I2C_BUS_2] = __I2C_PIN_MUX_INIT(I2CA, 10, 8),
};

void I2C_gpioInit(uint8_t bus_id)
{
    i2c_gpio_t *pgpio = &i2c_gpio[bus_id];

    DEBUG_LOG("I2C Bus_id[%d]: sda=%d, scl=%d \r\n", bus_id, pgpio->sda_pin, pgpio->scl_pin);

    GPIO_setPadConfig(pgpio->sda_pin, GPIO_PIN_TYPE_OD);
    GPIO_setQualificationMode(pgpio->sda_pin, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(pgpio->sda_pin_mux);

    GPIO_setPadConfig(pgpio->scl_pin, GPIO_PIN_TYPE_OD);
    GPIO_setQualificationMode(pgpio->scl_pin, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(pgpio->scl_pin_mux);
}

//
// Function to configure I2CA Interrupt in FIFO mode.
//
void I2C_init(uint32_t base, uint32_t speed)
{
    DEBUG_LOG("I2C init: Speed=%d \r\n", speed);

    if (I2CA_BASE == base)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    }
    else
    {
        return;
    }

    I2C_disableModule(base);
    I2C_disableLoopback(base);
    I2C_initController(base, DEVICE_SYSCLK_FREQ, speed, I2C_DUTYCYCLE_50);
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);
    I2C_setBitCount(base, I2C_BITCOUNT_8);
    I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);

    // FIFO
    I2C_disableFIFO(base);
    I2C_clearInterruptStatus(base, I2C_INT_RXFF | I2C_INT_TXFF);

    I2C_enableFIFO(I2CA_BASE);
    I2C_setFIFOInterruptLevel(I2CA_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RX1);

    // Interrupt
    I2C_clearInterruptStatus(
        base, I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION | I2C_INT_REG_ACCESS_RDY);

    I2C_enableModule(base);
}

uint16_t checkBusStatus(uint32_t base)
{
    if (I2C_isBusBusy(base))
    {
        return ERROR_BUS_BUSY;
    }

    if (I2C_getStopConditionStatus(base))
    {
        return ERROR_STOP_NOT_READY;
    }

    return I2C_SUCCESS;
}

/**
 *  Start  -> Target address -> Reg_addr(Memory address)
 */
uint16_t I2C_TransmitSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params)
{
    int16_t i;
    uint16_t status;
    uint32_t reg_addr;
    uint32_t timeout = MAX_TIMEOUT;
    uint32_t base    = I2C_Params->base;

    status = checkBusStatus(base);
    if (status)
    {
        return status;
    }

    I2C_disableFIFO(base);

    // Send start as controller transmitter, Repeat Mode
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);

    if (I2C_Params->targetAddr > MAX_7_BIT_ADDRESS)
    {
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS); // 10-bit addressing
    }

    // Setup target address
    I2C_setTargetAddress(base, I2C_Params->targetAddr);

    I2C_enableFIFO(base);

    reg_addr = *(I2C_Params->pControlAddr);

    for (i = I2C_Params->NumOfAddrBytes; i > 0; i--)
    {
        I2C_putData(base, (reg_addr >> ((i - 1) * 8)) & 0xFF); // Memory address
    }

    I2C_sendStartCondition(base);

    return I2C_SUCCESS;
}

uint16_t I2C_ControllerTransmitter(struct I2CHandle *I2C_Params)
{
    int16_t i;
    uint16_t status;
    uint32_t timeout  = MAX_TIMEOUT;
    uint32_t base     = I2C_Params->base;
    uint32_t reg_addr = *(I2C_Params->pControlAddr);

    ASSERT(I2C_Params->NumOfDataBytes <= MAX_BUFFER_SIZE);

    I2C_Params->status             = I2C_WRITE;
    I2C_Params->numofHasTransBytes = 0; // 清零和重置已发送数据的计数

    I2C_Params->numofFifoLevel = I2C_Params->NumOfDataBytes / I2C_FIFO_LEVEL;
    I2C_Params->remainingBytes = I2C_Params->NumOfDataBytes % I2C_FIFO_LEVEL;

    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);
    if (status)
    {
        return status;
    }

    /*--------------------------------------------------------*/
    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    I2C_disableFIFO(base);
    I2C_clearInterruptStatus(base, I2C_INT_TXFF | I2C_INT_RXFF);
    I2C_enableFIFO(base);

    I2C_enableInterrupt(base, (I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    I2C_enableInterrupt(base, I2C_INT_TXFF);

    return I2C_SUCCESS;
}

uint16_t I2C_ControllerReceiver(struct I2CHandle *I2C_Params)
{
    int16_t i;
    uint16_t status;
    uint32_t base = I2C_Params->base;

    ASSERT(I2C_Params->NumOfDataBytes <= I2C_FIFO_RXFULL);

    I2C_Params->status            = I2C_READ;
    I2C_Params->numofHasRecvBytes = 0; // 清零和重置已接收数据的计数

    I2C_Params->numofFifoLevel = (I2C_Params->NumOfDataBytes) / I2C_FIFO_RXFULL;
    I2C_Params->remainingBytes = (I2C_Params->NumOfDataBytes) % I2C_FIFO_RXFULL;

    I2C_disableInterrupt(base, I2C_INT_TXFF | I2C_INT_RXFF);
    I2C_clearInterruptStatus(base, (I2C_INT_REG_ACCESS_RDY | I2C_INT_TXFF | I2C_INT_RXFF));
    I2C_disableFIFO(base);
    I2C_clearInterruptStatus(base, I2C_INT_TXFF | I2C_INT_RXFF);

    I2C_enableFIFO(base);

    I2C_enableInterrupt(base, I2C_INT_REG_ACCESS_RDY);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);
    if (status)
    {
        return status;
    }

    /*--------------------------------------------------------*/
    I2C_enableInterrupt(base, (I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));

    return I2C_SUCCESS;
}

void handleI2C_ErrorCondition(struct I2CHandle *I2C_Params)
{
    uint32_t base = I2C_Params->base;
    uint32_t interruptEnabled;
    I2C_InterruptSource intSource = I2C_getInterruptSource(base);

    switch (intSource)
    {
        case I2C_INTSRC_ARB_LOST: // 1

            // DEBUG_LOG("i2c_isr: Arbitration lost failure \r\n");

            // Report Arbitration lost failure
            I2C_clearStatus(base, I2C_STS_ARB_LOST);

            I2C_disableInterrupt(base, I2C_INT_TXFF | I2C_INT_RXFF);

            I2C_disableFIFO(base);
            I2C_clearInterruptStatus(base, I2C_INT_TXFF | I2C_INT_RXFF);
            I2C_enableFIFO(base);

            break;

        case I2C_INTSRC_NO_ACK: // 2
            // Clear NACK flag and generate STOP condition on a NACK condition

            // DEBUG_LOG("i2c_isr: NACK \r\n");

            I2C_clearStatus(base, I2C_STS_NO_ACK);
            I2C_sendStopCondition(base);
            break;

        case I2C_INTSRC_REG_ACCESS_RDY: // 3
            interruptEnabled = HWREGH(base + I2C_O_IER) & I2C_IER_ARDY;

            if (interruptEnabled)
            {
                // DEBUG_LOG("i2c_isr: REG_ACCESS_RDY \r\n");

                I2C_disableInterrupt(base, I2C_INT_REG_ACCESS_RDY);
                I2C_disableInterrupt(base, I2C_INT_TXFF);

                I2C_disableFIFO(base);
                I2C_clearInterruptStatus(base, I2C_INT_TXFF | I2C_INT_RXFF);
                I2C_enableFIFO(base);

                // Restart -> Read Data
                I2C_setConfig(base, (I2C_CONTROLLER_RECEIVE_MODE));

                if (I2C_Params->numofFifoLevel)
                {
                    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);
                    I2C_setDataCount(base, I2C_FIFO_RXFULL);
                }
                else
                {
                    I2C_setFIFOInterruptLevel(
                        base, I2C_FIFO_TXEMPTY, (I2C_RxFIFOLevel)I2C_Params->remainingBytes);
                    I2C_setDataCount(base, I2C_Params->remainingBytes);
                }

                I2C_sendStartCondition(base);
                I2C_enableInterrupt(base, I2C_INT_RXFF);
            }
            break;

        case I2C_INTSRC_RX_DATA_RDY: // 4
            break;

        case I2C_INTSRC_TX_DATA_RDY: // 5
            break;

        case I2C_INTSRC_STOP_CONDITION: // 6
            // DEBUG_LOG("i2c_isr: STOP \r\n");
            I2C_disableInterrupt(base, (I2C_INT_TXFF | I2C_INT_RXFF));
            I2C_Params->pTX_MsgBuffer = TX_MsgBuffer;
            I2C_Params->pRX_MsgBuffer = RX_MsgBuffer;
            // I2C_disableFIFO(base);
            break;

        case I2C_INTSRC_ADDR_SLAVE: // 7
            // DEBUG_LOG("i2c_isr: Slave Addr \r\n");
            // Set TX / RX FIFO Level
            I2C_setFIFOInterruptLevel(
                base, I2C_FIFO_TXEMPTY, (I2C_RxFIFOLevel)(I2C_Params->NumOfAddrBytes));

            if ((I2C_getStatus(base) & I2C_STS_SLAVE_DIR))
            {
                // Target Transmitter (SDIR = 1)
                I2C_setConfig(base, I2C_SLAVE_SEND_MODE);
                // Enable TX FIFO interrupt and disable RXFF interrupt
                I2C_enableInterrupt(base, I2C_INT_TXFF);
                I2C_disableInterrupt(base, I2C_INT_RXFF);
                I2C_clearInterruptStatus(base, (I2C_INT_TXFF | I2C_INT_RXFF));
            }
            else
            {
                // Target Receiver (SDIR = 0)
                I2C_setConfig(base, I2C_SLAVE_RECEIVE_MODE);
                // Fill dummy data in Transmit FIFO to clear pending FIFO interrupt flag
                // I2C_putData(base, 0xAA);
                // I2C_putData(base, 0x55);

                // Enable RX FIFO interrupt and disable TXFF interrupt
                I2C_disableInterrupt(base, I2C_INT_TXFF);
                I2C_enableInterrupt(base, I2C_INT_RXFF);
                I2C_clearInterruptStatus(base, (I2C_INT_TXFF | I2C_INT_RXFF));
            }
            break;

        case I2C_INTSRC_NONE: // 0: No interrupt pending
            break;
        default:
            break;
    }
}

void Write_Read_TX_RX_FIFO(struct I2CHandle *I2C_Params)
{
    int16_t i;
    uint32_t base           = I2C_Params->base;
    uint16_t numofFifoLevel = I2C_Params->numofFifoLevel;
    uint16_t remainingBytes = I2C_Params->remainingBytes;

    struct I2CHandle *currentPtr = I2C_Params->currentHandlePtr;

    uint32_t txFIFOinterruptenabled = HWREGH(base + I2C_O_FFTX) & I2C_FFTX_TXFFIENA;
    uint32_t rxFIFOinterruptenabled = HWREGH(base + I2C_O_FFRX) & I2C_FFRX_RXFFIENA;
    uint32_t intSource              = (uint32_t)I2C_getInterruptStatus(base);

    if ((intSource & I2C_INT_RXFF) && (rxFIFOinterruptenabled))
    {
        I2C_disableInterrupt(base, I2C_INT_RXFF);

        for (i = 0; i < I2C_Params->NumOfDataBytes; i++)
        {
            *(currentPtr->pRX_MsgBuffer++) = I2C_getData(base);
        }

        I2C_sendStopCondition(base);

        I2C_disableInterrupt(base, I2C_INT_RXFF);

        I2C_disableFIFO(base);
        I2C_clearInterruptStatus(base, I2C_INT_RXFF);
        I2C_enableFIFO(base);
        return;
    }
    else
    {
        if ((intSource & I2C_INT_TXFF) && (txFIFOinterruptenabled))
        {
            // 关闭 TX FIFO Level 中断
            I2C_disableInterrupt(base, I2C_INT_TXFF);

            // 检查是否还有剩余数据未发送, 等于0则表示已经发送完成
            if (I2C_Params->numofHasTransBytes == I2C_Params->NumOfDataBytes)
            {
                // Master主模式
                if (HWREGH(EEPROM.base + I2C_O_MDR) & I2C_MDR_MST)
                {
                    I2C_disableInterrupt(base, I2C_INT_TXFF);

                    I2C_disableFIFO(base);
                    I2C_clearInterruptStatus(base, I2C_INT_TXFF);
                    I2C_enableFIFO(base);

                    I2C_sendStopCondition(base);
                    return;
                }
            }
            else
            {
                // 先按预设的 I2C_FIFO_LEVEL 深度发送数据
                if (I2C_Params->numofFifoLevel)
                {

                    for (i = 0; i < I2C_FIFO_LEVEL; i++)
                    {
                        I2C_putData(base, *(currentPtr->pTX_MsgBuffer));
                        currentPtr->pTX_MsgBuffer++;
                    }

                    I2C_Params->numofFifoLevel--;
                    I2C_Params->numofHasTransBytes += I2C_FIFO_LEVEL;
                }
                else
                {
                    // remaining 剩余数据部分
                    for (i = 0; i < I2C_Params->remainingBytes; i++)
                    {
                        I2C_putData(base, *(currentPtr->pTX_MsgBuffer));
                        currentPtr->pTX_MsgBuffer++;
                    }

                    I2C_Params->numofHasTransBytes += I2C_Params->remainingBytes;
                }

                I2C_disableFIFO(base);
                I2C_clearInterruptStatus(base, I2C_INT_TXFF);
                I2C_enableFIFO(base);

                I2C_enableInterrupt(base, I2C_INT_TXFF);
            }
        }
    }
}

__interrupt void i2cFIFO_isr(void)
{
    Write_Read_TX_RX_FIFO(currentResponderPtr);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

__interrupt void i2caISR(void)
{
    uint16_t ControllerTarget = HWREGH(currentResponderPtr->base + I2C_O_MDR);

    handleI2C_ErrorCondition(currentResponderPtr);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

void verifyEEPROMRead(void)
{
    uint16_t i;
    uint32_t timeout = MAX_TIMEOUT;

    while ((I2C_getStatus(EEPROM.base) & I2C_STS_BUS_BUSY) && timeout--);

#if 0
    DEBUG_LOG("--------------------------------\r\n");

    DEBUG_LOG("Tx ");
    for (i = 0; i < EEPROM.NumOfDataBytes; i++) {
        DEBUG_LOG(" %x ", TX_MsgBuffer[i]);
    }
    DEBUG_LOG("\r\n");

    DEBUG_LOG("Rx ");
    for (i = 0; i < EEPROM.NumOfDataBytes; i++) {
        DEBUG_LOG(" %x ", RX_MsgBuffer[i]);
    }
    DEBUG_LOG("\r\n");
#endif

    for (i = 0; i < EEPROM.NumOfDataBytes; i++)
    {
        if (RX_MsgBuffer[i] != TX_MsgBuffer[i])
        {
            // Transmitted data doesn't match received data
            // Fail condition. PC shouldn't reach here
            // ESTOP0;
            DEBUG_LOG("verify EEPROM Read Fail: i=%d,  Rx[0x%x] != Tx[0x%x] !!! \r\n", i, RX_MsgBuffer[i], TX_MsgBuffer[i]);
        }
    }
}


int main(void)
{
    uint16_t i = 0, j = 0;

    // in order for interrupts to have a default entry port,
    // do not run away when interrupt is not registered
    Interrupt_initVectorTable();
    Device_init();

    StdOutInit(&ScibRegs, 921600, 12, GPIO_12_SCIB_TX);

    DEBUG_LOG("I2C Interrupt Count(FIFO) Test \r\n");

    I2C_gpioInit(I2C_BUS_0);
    I2C_init(I2CA_BASE, 400000);

    Interrupt_register(INT_I2CA_FIFO, &i2cFIFO_isr);
    Interrupt_enable(INT_I2CA_FIFO);

    Interrupt_register(INT_I2CA, &i2caISR);
    Interrupt_enable(INT_I2CA);

    currentResponderPtr = &EEPROM;

    EEPROM.currentHandlePtr     = &EEPROM;
    EEPROM.targetAddr           = TARGET_ADDRESS;
    EEPROM.WriteCycleTime_in_us = 6 * 1000; // 6ms for EEPROM this code was tested
    EEPROM.base                 = I2CA_BASE;
    ControlAddr                 = 0x0000; // EEPROM address to write
    EEPROM.pControlAddr         = &ControlAddr;

    while (1)
    {
        // Example 5: EEPROM Continuous write
        // Program address = data pattern from address 64

        for (i = 0; i < MAX_BUFFER_SIZE; i++)
        {
            TX_MsgBuffer[i] = (i + j);
        }

        j++;
        if (100 == j) j = 0;

        EEPROM.NumOfAddrBytes = 2;
        EEPROM.pControlAddr   = &ControlAddr;
        EEPROM.NumOfDataBytes = MAX_WTRD_SIZE;
        EEPROM.pTX_MsgBuffer  = TX_MsgBuffer;
        EEPROM.status         = I2C_ControllerTransmitter(&EEPROM);

        // Wait for EEPROM write cycle time
        // This delay is not mandatory. User can run their application code instead.
        // It is however important to wait for EEPROM write cycle time before you initiate
        // another read / write transaction
        DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

        // Example 6: EEPROM Continuous read
        EEPROM.NumOfAddrBytes = 2;
        EEPROM.pControlAddr   = &ControlAddr;
        EEPROM.NumOfDataBytes = MAX_WTRD_SIZE;
        EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
        EEPROM.status         = I2C_ControllerReceiver(&EEPROM);
        DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

        verifyEEPROMRead();

        // EEPROM (AT24C02) has 32 pages, each page is 8 bytes
        ControlAddr += EEPROM_PAGE_SIZE;
        if (EEPROM_MEMORY_SIZE == ControlAddr) ControlAddr = 0;
    }

    return 0;
}

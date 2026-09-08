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
#define EEPROM_PAGE_SIZE            8
#define EEPROM_MEMORY_SIZE          0x100
#define MAX_WTRD_SIZE               8       // 最大支持FIFO深度15, 一次读或写 不能超过 1 page size

#define I2C_FIFO_LEVEL              8
#define TARGET_ADDRESS              0x50
#define MAX_BUFFER_SIZE             64

#define MAX_TIMEOUT                 0x100000
#define MAX_7_BIT_ADDRESS           0x7F

//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY         0x1000
#define ERROR_NACK_RECEIVED    0x2000
#define ERROR_ARBITRATION_LOST 0x3000
#define ERROR_STOP_NOT_READY   0x5555
#define I2C_SUCCESS            0x0000

struct I2CHandle
{
    uint32_t base;
    uint16_t targetAddr;    // Target address tied to the message.
    uint32_t *pControlAddr; // MSB

    uint16_t NumOfAddrBytes;
    uint16_t NumOfDataBytes; // Number of valid bytes in message.

    uint16_t *pTX_MsgBuffer; // Pointer to TX message buffer
    uint16_t *pRX_MsgBuffer; // Pointer to RX message buffer

    uint16_t numofSixteenByte;
    uint16_t remainingBytes;

    uint16_t WriteCycleTime_in_us; //  Target write cycle time. Depends on target.
                                   //  Please check target device datasheet
};

struct I2CHandle EEPROM;
uint32_t ControlAddr;
uint16_t status;

uint16_t TX_MsgBuffer[MAX_BUFFER_SIZE];
uint16_t RX_MsgBuffer[MAX_BUFFER_SIZE];

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
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE);
    I2C_setBitCount(base, I2C_BITCOUNT_8);
    I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);

    // FIFO
    I2C_disableFIFO(base);
    I2C_enableFIFO(base);
    I2C_setFIFOInterruptLevel(I2CA_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RX2);

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

uint16_t handleNACK(uint32_t base)
{
    if (I2C_getStatus(base) & I2C_STS_NO_ACK)
    {
        I2C_clearStatus(base, I2C_STS_NO_ACK);
        I2C_sendStopCondition(base);

        return ERROR_NACK_RECEIVED;
    }

    return I2C_SUCCESS;
}

/**
 *  Start  -> Target address -> Reg_addr(Memory address)
 */
uint16_t I2C_TransmitSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params)
{
    int16_t i, status;
    uint32_t timeout = MAX_TIMEOUT;
    uint32_t reg_addr;
    uint32_t base = I2C_Params->base;

    status = checkBusStatus(base);
    if (status)
    {
        return status;
    }

    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    /*--------------------------------------------------------*/
    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    // Send start as controller transmitter, Non repeat
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE);

    // Send tartget address: 0x7F(max 7bit tartget address)
    if (I2C_Params->targetAddr > MAX_7_BIT_ADDRESS)
    {
        // 10-bit addressing
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    }
    I2C_setTargetAddress(base, I2C_Params->targetAddr);

    // Setup number of bytes to send memory address(2)
    I2C_setDataCount(base, I2C_Params->NumOfAddrBytes + I2C_Params->NumOfDataBytes);

    reg_addr = *(I2C_Params->pControlAddr);

    for (i = I2C_Params->NumOfAddrBytes; i > 0; i--)
    {
        I2C_putData(base, (reg_addr >> ((i - 1) * 8)) & 0xFF);
    }

    I2C_sendStartCondition(base);

    timeout = MAX_TIMEOUT;
    while (I2C_getTxFIFOStatus(base) && timeout--)
        ;

    return I2C_SUCCESS;
}

uint16_t I2C_ControllerTransmitter(struct I2CHandle *I2C_Params)
{
    int16_t i, status;
    uint32_t timeout = MAX_TIMEOUT;
    uint32_t reg_addr;
    uint32_t base = I2C_Params->base;

    // Wait until the STP bit is cleared from any previous controller communication.
    if (I2C_getStopConditionStatus(base))
    {
        return ERROR_STOP_NOT_READY;
    }

    // Check bus free idle
    if (I2C_isBusBusy(base))
    {
        return (ERROR_BUS_BUSY);
    }

    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);
    if (status)
    {
        return status;
    }

    /*--------------------------------------------------------*/
    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    uint16_t numofSixteenByte = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    uint16_t remainingBytes   = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    uint16_t count = 0, buff_pos = 0;

    while (count < numofSixteenByte)
    {
        for (i = 1; i <= I2C_FIFO_LEVEL; i++)
        {
            I2C_putData(base, I2C_Params->pTX_MsgBuffer[buff_pos++]);
        }

        timeout = MAX_TIMEOUT;
        while (I2C_getTxFIFOStatus(base) && timeout--)
        {
            status = handleNACK(base);
            if (status)
            {
                return status;
            }
        }

        count++;
    }

    for (i = 0; i < remainingBytes; i++)
    {
        I2C_putData(base, I2C_Params->pTX_MsgBuffer[buff_pos++]);
    }

    timeout = MAX_TIMEOUT;
    while (I2C_getTxFIFOStatus(base) && timeout--)
    {
        status = handleNACK(base);
        if (status)
        {
            return status;
        }
    }

    I2C_sendStopCondition(base);

    return I2C_SUCCESS;
}

uint16_t I2C_ControllerReceiver(struct I2CHandle *I2C_Params)
{
    int16_t i, status;
    uint32_t timeout = MAX_TIMEOUT;
    uint32_t reg_addr;
    uint32_t base = I2C_Params->base;

    if (I2C_getStopConditionStatus(base))
    {
        return ERROR_STOP_NOT_READY;
    }

    // Check bus free idle
    if (I2C_isBusBusy(base))
    {
        return (ERROR_BUS_BUSY);
    }

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);
    if (status)
    {
        return status;
    }

    /*---------------------------------------------*/
    // Send data to setup EEPROM address
    //
    I2C_setConfig(base, I2C_CONTROLLER_RECEIVE_MODE);

    //
    // Address setup phase has completed. Now setup how many bytes expected
    // and send restart as controller-receiver.
    //
    I2C_setDataCount(base, I2C_Params->NumOfDataBytes);
    I2C_sendStartCondition(base);

    for (i = 0; i < I2C_Params->NumOfDataBytes; i++)
    {
        timeout = MAX_TIMEOUT;
        while ((!(I2C_getStatus(base) & I2C_STS_RX_DATA_RDY)) && timeout--)
            ;

        I2C_Params->pRX_MsgBuffer[i] = I2C_getData(base);

        I2C_clearStatus(base, I2C_STS_RX_DATA_RDY);
    }

    // Generate Stop signal, end communication
    I2C_sendStopCondition(base);

    return I2C_SUCCESS;
}

void verifyEEPROMRead(void)
{
    uint16_t i;
    uint32_t timeout = MAX_TIMEOUT;

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
            // while(1);
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

    DEBUG_LOG("I2C Polling(FIFO) Test \r\n");

    I2C_gpioInit(I2C_BUS_0);
    I2C_init(I2CA_BASE, 400000);

    EEPROM.targetAddr           = TARGET_ADDRESS;
    EEPROM.WriteCycleTime_in_us = 6 * 1000;         // 6ms for EEPROM this code was tested
    EEPROM.base                 = I2CA_BASE;
    ControlAddr                 = 0x0000;           // EEPROM address to write
    EEPROM.pControlAddr         = &ControlAddr;

    while (1)
    {
        for (i = 0; i < MAX_BUFFER_SIZE; i++)
        {
            TX_MsgBuffer[i] = (i + j);
        }

        j++;
        if (100 == j) j = 0;

        // Example 1: EEPROM Byte Write
        EEPROM.NumOfAddrBytes = 2;
        EEPROM.NumOfDataBytes = MAX_WTRD_SIZE;
        EEPROM.pTX_MsgBuffer  = TX_MsgBuffer;
        status                = I2C_ControllerTransmitter(&EEPROM);

        // Wait for EEPROM write cycle time
        // This delay is not mandatory. User can run their application code instead.
        // It is however important to wait for EEPROM write cycle time before you initiate
        // another read / write transaction
        DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

        // Example 2: EEPROM Byte Read
        EEPROM.NumOfAddrBytes = 2;
        EEPROM.NumOfDataBytes = MAX_WTRD_SIZE;
        EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
        status                = I2C_ControllerReceiver(&EEPROM);
        DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

        verifyEEPROMRead();

        // EEPROM (AT24C02) has 32 pages, each page is 8 bytes
        ControlAddr += EEPROM_PAGE_SIZE;
        if (EEPROM_MEMORY_SIZE == ControlAddr) ControlAddr = 0;
    }

    return 0;
}

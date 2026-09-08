#include "device.h"
#include "driverlib.h"
#include "bsp_spi.h"

#define mySPI_BASE          SPIB_BASE
#define GPIO_PIN_SPIB_STE   15

/**
 * @brief SPIB
 *
 */
static void SPI_gpioInit(void)
{
    GPIO_MuxConfig(6, GPIO_6_SPIB_SOMI, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(7, GPIO_7_SPIB_SIMO, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(26, GPIO_26_SPIB_CLK, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_15_GPIO15);
    GPIO_setPadConfig(GPIO_PIN_SPIB_STE, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(GPIO_PIN_SPIB_STE, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(GPIO_PIN_SPIB_STE, GPIO_DIR_MODE_OUT);
}

static int SPI_drvInit(uint32_t base, uint32_t baudRate)
{
    if (SPIA_BASE == base)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    }
    else if (SPIB_BASE == base)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    }
    else
    {
        return -1;
    }

    SPI_disableModule(base);
    SPI_disableLoopback(base);
    SPI_disableFIFO(base);
    SPI_setConfig(base, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0, SPI_MODE_CONTROLLER, baudRate, 8);
    // SPI_setPTESignalPolarity(base, SPI_PTE_ACTIVE_LOW);
    // SPI_enableFIFO(base);
    // SPI_setEmulationMode(base, SPI_EMULATION_FREE_RUN);
    SPI_enableModule(base);

    return 0;
}

void SPI_init(void)
{
    EALLOW;

    SPI_gpioInit();
    SPI_drvInit(mySPI_BASE, 1 * 1000000); // 1Mbps

    EDIS;
}

/*--------------------------------------------------------------*/
void SPI_CS_HIGH(void)
{
    GPIO_writePin(GPIO_PIN_SPIB_STE, 1);
}

void SPI_CS_LOW(void)
{
    GPIO_writePin(GPIO_PIN_SPIB_STE, 0);
}

/*--------------------------------------------------------------*/
#define MAX_TIMEOUT (uint32_t)0x0000FFFF

/**
 * @brief spi read and write One Byte.
 * 
 * @param data single Byte
 * @return
 */
uint8_t SPIB_rxTxByte(uint8_t data)
{
    uint32_t timeout = MAX_TIMEOUT;
    uint16_t rx_data;

    while ((SPI_getTxFIFOStatus(mySPI_BASE) != SPI_FIFO_TXEMPTY) && (timeout--));
    SPI_writeDataNonBlocking(mySPI_BASE, data);

    timeout = MAX_TIMEOUT;
    while ((SPI_getRxFIFOStatus(mySPI_BASE) == SPI_FIFO_RXEMPTY) && (timeout--));
    rx_data = SPI_readDataNonBlocking(mySPI_BASE);

    // printf("write: 0x%x, read: 0x%x \r\n", data, rx_data);

    return rx_data;
}

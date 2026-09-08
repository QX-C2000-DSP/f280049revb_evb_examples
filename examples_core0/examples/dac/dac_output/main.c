#include "device.h"
#include "driverlib.h"

static void dac_drv_init(uint32_t base, DAC_ReferenceVoltage source, DAC_GainMode mode,
    DAC_LoadMode loadmode, DAC_SyncSel sync)
{
    DAC_setReferenceVoltage(base, source);
    DAC_setGainMode(base, mode);
    DAC_setLoadMode(base, loadmode);

    if (loadmode)
        DAC_setPWMSyncSignal(base, sync);

    DAC_enableOutput(base);
}

/**
 * @brief DACA-GPIOA0
 *
 */
void DAC_init(void)
{
    // 由于DAC需要不超过5MHz的时钟，所以在开启DAC时钟前需要先分频DAC的时钟到5M以下
    DacaRegs.DACCTL.bit.PRESCALE = 60;
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);

    // 测试DAC数据 Pin-GPIO: A0
    dac_drv_init(DACA_BASE, DAC_REF_ADC_VREFHI, DAC_GAIN_ONE, DAC_LOAD_SYSCLK, 0);

    // delay 1ms
    DEVICE_DELAY_US(1 * 1000);

    // set DAC output 0V
    DAC_setShadowValue(DACA_BASE, 0x0);
}

/**
 * @brief value is the 12-bit code to be loaded into the active value register
 * 
 * @param value 
 */
void DAC_setOutputVal(uint16_t value)
{
    DAC_setShadowValue(DACA_BASE, value);
}

int main(void)
{
    /* in order for interrupts to have a default entry port,
        do not run away when interrupt is not registered */
    Interrupt_initVectorTable();
    Device_init();

    DAC_init();

    while (1)
    {
        DAC_setOutputVal(0x4D9); // 1V
        DEVICE_DELAY_US(1000000);

        DAC_setOutputVal(0x9B2); // 2V
        DEVICE_DELAY_US(1000000);

        DAC_setOutputVal(0xE8B); // 3V
        DEVICE_DELAY_US(1000000);
    }

    return 0;
}

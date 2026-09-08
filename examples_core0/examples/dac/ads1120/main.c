#include "device.h"
#include "driverlib.h"
#include "user_inc.h"
#include "bsp_dac.h"
#include "bsp_spi.h"
#include "ads1220.h"
#include <stdio.h>

/*--------------------------------------------------------------------------------------------*/
#define ADS_S_SELECT_CH     0
#define ADS_S_DATA_READ     1

/* max read_data times */
#define MAX_TIME_CNT        9

typedef struct __ads_task_t
{
    uint8_t status;
    uint8_t ads_ch;
    uint16_t dac_val;
    uint16_t cnt;
    uint16_t res;
    uint32_t inverval;
    timer_sw_t timer;
} ads_task_t;

static ads_task_t ads_task = {
    .status   = ADS_S_SELECT_CH,
    .ads_ch   = 0,
    .dac_val  = 0,
    .inverval = 25, // sample period: 25ms
};

static uint32_t adc_code[10];

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

void ADS_task(void)
{
    int i;
    float sample_voltage;
    uint32_t ads_result;
    uint32_t sum_data;
    ads_task_t *pads = &ads_task;

    switch (pads->status)
    {
        case ADS_S_SELECT_CH:

            /* select ADS sample channel */         
            ADS1220_SelCh(pads->ads_ch);

            /* set DAC output value */  
            // DAC_setOutputVal(1241); // 测试DAC输出固定 1V = 1241
            DAC_setOutputVal(pads->dac_val);

            printf("----------------------------------------\n");
            printf("DAC Code_Value: %d, 0x%x \n", pads->dac_val, pads->dac_val);

            /* DAC output value add 1, bus DAC sampling resolution is 12bit. 
                when DAC value > 0xFFF, need to restart 0 */
            pads->dac_val += 1;
            if (pads->dac_val >= 0x1000)
            {
                pads->dac_val = 0;
            }

            pads->cnt    = 0;
            pads->status = ADS_S_DATA_READ;

            timer_set(&pads->timer, pads->inverval);
            break;

        case ADS_S_DATA_READ:
            if (timer_expired(&pads->timer))
            {
                timer_restart(&pads->timer);

                /* read data: ADS conversion result */
                ads_result = ADS1220ReadData();
                adc_code[pads->cnt] = ads_result;

                // sample_voltage = (float)(ads_result * 3.30) / 32767.00;
                // printf("ads_result: 0x%x  %d, voltage = %f \r\n", ads_result, ads_result, sample_voltage);

                /* check whether beyond MAX_TIME_CNT */
                pads->cnt++;
                if (pads->cnt > MAX_TIME_CNT)
                {
                    /* set sum_data default vaule to 0,  
                    start from i = 4, Calculate the average value 5 times. */
                    sum_data = 0;
                    for (i = 4; i < 9; i++)
                    {
                        sum_data += adc_code[i];
                    }
                    sum_data /= 5;

                    /* Ref = 3.3V: ADS1220_VREF_SUPPLY, ADS1220_VREF_EX_DED */
                    sample_voltage = (float)(sum_data * 3.30) / 32767.00;
                    printf("Average:  Raw_ADS: %d 0x%x, Voltage: %f, ads_result: 0x%x  %d\n",
                        sum_data, sum_data, sample_voltage, ads_result, ads_result);

                    pads->cnt    = 0;
                    pads->status = ADS_S_SELECT_CH;
                }
            }
            break;

        default:
            break;
    }
}

int main(void)
{
    /* in order for interrupts to have a default entry port,
        do not run away when interrupt is not registered */
    Interrupt_initVectorTable();
    Device_init();

    /* remap printf */
    StdOutInit(&ScibRegs, 115200, 12, GPIO_12_SCIB_TX);

    DAC_init();
    SPI_init();
    TIMER0_init();

    /* config ADS1220 */ 
    ADS1220Init();
    ADS1220Config();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while (1)
    {
        ADS_task();
    };

    return 0;
}

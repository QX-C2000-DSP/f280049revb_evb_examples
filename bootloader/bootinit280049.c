#include "driverlib.h"

_Pragma("clang section text=\".text.qxbootinit\"")

static inline void copied_DCC_setCounterSeeds(
    uint32_t base, uint32_t counter0, uint32_t validCounter0, uint32_t counter1);
static bool copied_SysCtl_setClock(uint32_t config);

//
// Input : GR4 = xtalfreq in integer
// Output: GR2 = maximum imult value in integer
//   = 160MHz * 4.0 / GR4
//
__attribute__((naked)) static uint32_t calc_value_4_mask(uint32_t xtalfreq)
{
    // GR3 <= 640.0f
    asm("movigh gr3 0x4420||");
    asm("movigl gr3 0x0000||");
    asm("fcvtus gr4 gr4||");
    asm("fsdiv  gr2 gr3 gr4||");
    asm("fcvtsu gr2 gr2||");
    asm("ret||");
    asm("nop||");
    asm("nop||");
}

static void boot_init_clock()
{
    //
    // enable PLL, and PLLRAWCLK = XTAL * 40 / 4
    // support XTAL frequency within [10MHz, 20MHz]
    //
    HWREG(0x01001300) = 0xFFFFFFFF;
    HWREG(0x01001304) = 0xFFFFFFFF;
    HWREG(0x01001308) = 0xFFFFFFFF;
    copied_SysCtl_setClock(0x90042801);

    // clear DCCSTATUS, ERR and DONE
    HWREGH(DCC0_BASE + DCC_O_STATUS) |= DCC_STATUS_ERR | DCC_STATUS_DONE;

    // disable DCC and its interrupt generation
    HWREGH(DCC0_BASE + DCC_O_GCTRL) = 0x5555;

    //
    // counter0 source: DCC_COUNT0SRC_INTOSC2 as reference clock and is 10MHz
    // counter1 source: to measure its frequency, can only be DCC_COUNT1SRC_PLL in 2024 NTO 280049
    // chip
    //
    HWREGH(DCC0_BASE + DCC_O_CLKSRC0)
        = (HWREGH(DCC0_BASE + DCC_O_CLKSRC0) & ~(DCC_CLKSRC0_CLKSRC0_M)) | DCC_COUNT0SRC_INTOSC2;
    HWREGH(DCC0_BASE + DCC_O_CLKSRC1)
        = (HWREGH(DCC0_BASE + DCC_O_CLKSRC1) & (DCC_REG_BYTE_MASK << 4U))
          | ((DCC_ENABLE_VALUE << 12U) | DCC_COUNT1SRC_PLL);

    //
    // counter0 + valid0 = 0x7FF0 + 0x10 = 0x8000
    // counter1          = 0xFFFFF
    //
    copied_DCC_setCounterSeeds(DCC0_BASE, 0x7FF0, 0x10, 0xFFFFF);
    // enable single shot mode and DCC
    HWREGH(DCC0_BASE + DCC_O_GCTRL)
        = (HWREGH(DCC0_BASE + DCC_O_GCTRL) & ~(DCC_GCTRL_SINGLESHOT_M | DCC_GCTRL_DCCENA_M))
          | (DCC_MODE_COUNTER_ZERO | DCC_ENABLE_VALUE);

    //
    // wait until counter0 and valid0 both reach zero
    //
    while (!(((HWREGH(DCC0_BASE + DCC_O_STATUS) & DCC_STATUS_DONE) == DCC_STATUS_DONE)
             || ((HWREGH(DCC0_BASE + DCC_O_STATUS) & DCC_STATUS_ERR) == DCC_STATUS_ERR)))
    { }

    //
    // get counter1 decremented value and calculate XTAL measured frequency
    // XTAL_freq (MHz) = (10.0 * count1dec) / 0x8000 / 10.0
    // NOTE: use integer calculation to avoid using data section, while bootloader doesn't have
    //
    uint32_t xtalfreq = (0xFFFFF - HWREG(DCC0_BASE + DCC_O_CNT1)) >> 15;

    //
    // reset and disable DCC
    //
    HWREGH(DCC0_BASE + DCC_O_STATUS) |= DCC_STATUS_ERR | DCC_STATUS_DONE;
    HWREGH(DCC0_BASE + DCC_O_GCTRL) = 0x5555;

    //
    // constrain maximum of IMULT_VAL to maximult
    //
    uint32_t maximult   = calc_value_4_mask(xtalfreq);
    uint32_t imultmask0 = 0xFFFFFFFF;
    uint32_t imultmask1 = 0x0;
    if (maximult > 31)
    {
        maximult -= 31;
        for (int i = 0; i < maximult; ++i)
        {
            imultmask1 |= 0x1 << i;
        }
    }
    else
    {
        imultmask0 = 0x0;
        for (int i = 0; i < maximult; ++i)
        {
            imultmask0 |= 0x1 << i;
        }
    }
    HWREG(0x01001300) = imultmask0;
    HWREG(0x01001304) = imultmask1;

    //
    // constrain minimum of ODIV_VAL to 4, [4, 15] are allowed
    //
    HWREG(0x01001308) = 0xFFFFFFF0;
}

__attribute__((naked)) static void boot_init_delay(uint32_t count)
{
    asm("addi gr4 gr4 0xffffffff||");
    asm("nop||");
    asm("nop||");
    asm("lei gr4 0||");
    asm("jnc boot_init_delay||");
    asm("nop||");
    asm("nop||");
    asm("ret||");
    asm("nop||");
    asm("nop||");
}

void boot_init_280049(void)
{
#if 0
    EALLOW;

    // do nothing if X1 not ready
    boot_init_delay(2000);
    if (!ClkCfgRegs.CLKSTATUS.bit.X1READLY)
        return;

    boot_init_clock();

    // disable PLL and set sysclk to OSC2 (10MHz)
    copied_SysCtl_setClock(0x10101);

    EDIS;
#endif
}

//
// copy required driverlib function below, so that this file is self-contained
//
static inline void copied_DCC_setCounterSeeds(
    uint32_t base, uint32_t counter0, uint32_t validCounter0, uint32_t counter1)
{
    //
    // Check the arguments.
    //
    ASSERT(DCC_isBaseValid(base));
    ASSERT(validCounter0 >= DCC_VALIDSEED_MIN);
    ASSERT(counter0 >= DCC_COUNTSEED_MIN);
    ASSERT(counter1 >= DCC_COUNTSEED_MIN);
    ASSERT(validCounter0 <= DCC_VALIDSEED_MAX);
    ASSERT(counter0 <= DCC_COUNTSEED_MAX);
    ASSERT(counter1 <= DCC_COUNTSEED_MAX);

    // EALLOW;

    //
    // Set Counter 0 Seed
    //
    HWREGH(base + DCC_O_CNTSEED0)      = counter0 & DCC_REG_WORD_MASK;
    HWREGH(base + DCC_O_CNTSEED0 + 2U) = (HWREGH(base + DCC_O_CNTSEED0 + 2U) & DCC_SEED_REG_MASK)
                                         | ((uint32_t)(counter0 & DCC_SEED_CNT_MASK) >> 16U);

    //
    // Set Valid Duration Counter 0 Seed
    //
    HWREGH(base + DCC_O_VALIDSEED0) = validCounter0;

    //
    // Set Counter 1 Seed
    //
    HWREGH(base + DCC_O_CNTSEED1)      = counter1 & DCC_REG_WORD_MASK;
    HWREGH(base + DCC_O_CNTSEED1 + 2U) = (HWREGH(base + DCC_O_CNTSEED1 + 2U) & DCC_SEED_REG_MASK)
                                         | ((uint32_t)(counter1 & DCC_SEED_CNT_MASK) >> 16U);

    // EDIS;
}

static bool copied_SysCtl_pollX1Counter(void)
{
    uint16_t loopCount    = 0U;
    uint32_t localCounter = 0U;
    bool status           = false;

    //
    // Delay for 1 ms while the XTAL powers up
    //
    // 2000 loops, 5 cycles per loop + 9 cycles overhead = 10009 cycles
    //
    boot_init_delay(2000);

    //
    // Clear and saturate X1CNT 4 times to guarantee operation
    //
    do
    {
        //
        // Keep clearing the counter until it is no longer saturated
        //
        while (HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) > 0x1FFU)
        {
            HWREG(CLKCFG_BASE + SYSCTL_O_X1CNT) |= SYSCTL_X1CNT_CLR;
        }

        //
        // Wait for the X1 clock to saturate
        //
        while (HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) != SYSCTL_X1CNT_X1CNT_M)
        {
            //
            // If your application is stuck in this loop, please check if the
            // input clock source is valid.
            //
            localCounter++;
            if (localCounter > 2500000U)
            {
                if (loopCount == 3U)
                {
                    status = false;
                }
                break;
            }
        }

        if (loopCount == 3U && (HWREGH(CLKCFG_BASE + SYSCTL_O_X1CNT) == SYSCTL_X1CNT_X1CNT_M))
        {
            status = true;
        }
        //
        // Increment the counter
        //
        loopCount++;
        localCounter = 0U;
    } while (loopCount < 4U);

    return status;
}

static void copied_SysCtl_selectXTAL(void)
{
    bool status        = false;
    uint16_t loopCount = 0U;

    // EALLOW;

    //
    // Turn on XTAL and select crystal mode
    //
    ClkCfgRegs.XTALCR.bit.OSCOFF = 0;
    boot_init_delay(100);
    ClkCfgRegs.XTALCR.bit.SE = 0;
    boot_init_delay(100);
    // EDIS;

    // Wait for the X1 clock readly
    while (1)
    {
        if (ClkCfgRegs.CLKSTATUS.bit.X1READLY)
            break;
    }

    //
    // Wait for the X1 clock to saturate
    //
    status = copied_SysCtl_pollX1Counter();

    //
    // Select XTAL as the oscillator source
    //
    // EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    boot_init_delay(100);
    // EDIS;

    //
    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    //
    while (((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) != 0U)
           && (status == FALSE) && (loopCount < 4U))
    {
        //
        // Clear the MCD failure
        //
        // EALLOW;
        HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) |= SYSCTL_MCDCR_MCLKCLR;
        // EDIS;

        //
        // Wait for the X1 clock to saturate
        //
        status = copied_SysCtl_pollX1Counter();

        //
        // Select XTAL as the oscillator source
        //
        // EALLOW;
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1)
            = ((HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) & (~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M))
                | (SYSCTL_OSCSRC_XTAL >> SYSCTL_OSCSRC_S));
        // EDIS;
        loopCount++;
    }
    while (status == FALSE)
    {
        // If code is stuck here, it means crystal has not started.
        // Replace crystal or update code below to take necessary actions if
        // crystal is bad
        while (1)
            ;
    }
}

static void copied_SysCtl_selectOscSource(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC1) || (oscSource == SYSCTL_OSCSRC_OSC2)
           || (oscSource == SYSCTL_OSCSRC_XTAL));

    //
    // Select the specified source.
    //
    // EALLOW;
    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Turn on INTOSC2
            //
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF = 0;   // Turn on INTOSC2
            boot_init_delay(120);                       // Delay
            ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // Clk Src = INTOSC2
            ClkCfgRegs.XTALCR.bit.OSCOFF           = 1; // Trun off XTAL
            break;
        case SYSCTL_OSCSRC_XTAL:
        case SYSCTL_OSCSRC_XTAL_SE:
            //
            // Select XTAL in crystal mode and wait for it to power up
            //
            copied_SysCtl_selectXTAL();
            break;
        case SYSCTL_OSCSRC_OSC1:
            //
            // Clk Src = INTOSC1
            //
            ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // Clk Src = INTOSC1
            ClkCfgRegs.XTALCR.bit.OSCOFF           = 1; // Trun off XTAL
            break;
        default:
            //
            // Do nothing. Not a valid oscSource value.
            //
            break;
    }
    // EDIS;
}

static bool copied_SysCtl_setClock(uint32_t config)
{
    uint16_t pllLockStatus, imult;
    uint32_t oscSource, timeout;

    // Don't proceed to the PLL initialization if an MCD failure is detected.
    // OSCCLKSRC2 failure detected. Returning false. You'll need to clear the MCD error.
    if ((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) != 0U)
        return false;

    // Configure oscillator source Bypass PLL
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;

    oscSource = config & SYSCTL_OSCSRC_M;
    copied_SysCtl_selectOscSource(oscSource);

    // Configure PLL if enabled
    if ((config & SYSCTL_PLL_ENABLE) == SYSCTL_PLL_ENABLE)
    {
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1; // Turn on PLL

        ClkCfgRegs.SYSPLLMULT.bit.RST  = 0; // enter reset mode
        ClkCfgRegs.SYSPLLMULT.bit.IDIV = (config & SYSCTL_IDIV_M) >> SYSCTL_IDIV_S;
        imult                          = (config & SYSCTL_IMULT_M) >> SYSCTL_IMULT_S;
        if (imult < 32)
        {
            ClkCfgRegs.SYSPLL_IMULT_L = 1 << imult;
            ClkCfgRegs.SYSPLL_IMULT_H = 0;
        }
        else
        {
            ClkCfgRegs.SYSPLL_IMULT_L = 0;
            ClkCfgRegs.SYSPLL_IMULT_H = 1 << (imult - 32);
        }
        ClkCfgRegs.SYSPLL_ODIV        = 1 << ((config & SYSCTL_ODIV_M) >> SYSCTL_ODIV_S);
        ClkCfgRegs.SYSPLLMULT.bit.RST = 1; // enter normal mode

        // Wait for the SYSPLL lock counter or a timeout
        timeout       = SYSCTL_PLLLOCK_TIMEOUT;
        pllLockStatus = ClkCfgRegs.SYSPLLSTS.bit.LOCKS;
        while ((pllLockStatus != 1U) && (timeout != 0U))
        {
            pllLockStatus = ClkCfgRegs.SYSPLLSTS.bit.LOCKS;
            timeout--;
        }

        // Check PLL Frequency using DCC
        // if (!SysCtl_isPLLValid(
        //         oscSource, (config & (SYSCTL_IMULT_M | SYSCTL_IDIV_M | SYSCTL_ODIV_M))))
        //     return false;

        // Check DCC Status, if no error break the loop
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1; // Enable PLLSYSCLK is fed from system PLL clock
        boot_init_delay(100);
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = (config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
    }
    else
    {
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0; // disable PLLSYSCLK
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN    = 0; // Turn off PLL
        boot_init_delay(100);
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = (config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
    }

    return true;
}

_Pragma("clang section text=\"\"")

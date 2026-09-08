#include "sysctl.h"
#include "dcc.h"

//*****************************************************************************
//
// SysCtl_pollX1Counter()
//
//*****************************************************************************
static bool SysCtl_pollX1Counter(void)
{
    uint16_t loopCount    = 0U;
    uint32_t localCounter = 0U;
    bool status           = false;

    //
    // Delay for 1 ms while the XTAL powers up
    //
    // 2000 loops, 5 cycles per loop + 9 cycles overhead = 10009 cycles
    //
    SysCtl_delay(2000);

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

//*****************************************************************************
//
// SysCtl_getClock()
//
//*****************************************************************************
uint32_t SysCtl_getClock(uint32_t clockInHz)
{
    uint32_t i = 0, temp = 0, imult = 0, idiv = 0, odiv = 0;
    uint32_t oscSource;
    uint32_t clockOut;

    //
    // Don't proceed if an MCD failure is detected.
    //
    if (SysCtl_isMCDClockFailureDetected())
    {
        //
        // OSCCLKSRC2 failure detected. Returning the INTOSC1 rate. You need
        // to handle the MCD and clear the failure.
        //
        clockOut = SYSCTL_DEFAULT_OSC_FREQ;
    }
    else
    {
        //
        // If one of the internal oscillators is being used, start from the
        // known default frequency.  Otherwise, use clockInHz parameter.
        //
        oscSource = ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL;
        if (oscSource == 0 || oscSource == 2)
            clockOut = SYSCTL_DEFAULT_OSC_FREQ;
        else
            clockOut = clockInHz;

        if (ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN == 1 && ClkCfgRegs.SYSPLLCTL1.bit.PLLEN == 1)
        {
            temp = ClkCfgRegs.SYSPLL_IMULT_L;
            if (temp)
            {
                for (i = 0; i < 32; i++)
                {
                    if (temp & (1 << i))
                    {
                        imult = i;
                        break;
                    }
                }
            }
            else
            {
                temp = ClkCfgRegs.SYSPLL_IMULT_H;
                if (temp)
                {
                    for (i = 0; i < 32; i++)
                    {
                        if (temp & (1 << i))
                        {
                            imult = i + 32;
                            break;
                        }
                    }
                }
            }
            if (imult != 0)
                clockOut = clockOut * imult;

            idiv = ClkCfgRegs.SYSPLLMULT.bit.IDIV;
            if (idiv != 0)
                clockOut /= idiv;

            temp = ClkCfgRegs.SYSPLL_ODIV;
            if (temp)
            {
                for (i = 0; i < 32; i++)
                {
                    if (temp & (1 << i))
                    {
                        odiv = i;
                        break;
                    }
                }
            }

            if (odiv != 0)
                clockOut /= odiv;
        }

        temp = ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV;
        if (temp != 0)
            clockOut /= (2 * temp);
    }

    return (clockOut);
}

//*****************************************************************************
//
// SysCtl_setClock()
//
//*****************************************************************************
bool SysCtl_setClock(uint32_t config)
{
    uint16_t pllLockStatus, imult;
    uint32_t retries = 0U, oscSource;
    uint32_t timeout;
    bool status = false;

    // Don't proceed to the PLL initialization if an MCD failure is detected.
    if (SysCtl_isMCDClockFailureDetected())
    {
        // OSCCLKSRC2 failure detected. Returning false. You'll need to clear
        // the MCD error.
        return false;
    }

    // Bypass PLL
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
    SysCtl_delay(11U);

    // Configure oscillator source
    oscSource = config & SYSCTL_OSCSRC_M;
    SysCtl_selectOscSource(oscSource);

    // Configure PLL if enabled
    if ((config & SYSCTL_PLL_ENABLE) == SYSCTL_PLL_ENABLE)
    {
        // Loop to retry locking the PLL should the DCC module
        // indicate that it was not successful.
        //
        // If a maximum retry count is required at the system level
        // it can be added here according to the maximum system allowed
        // time for PLL locking.  In this case there should be an error
        // handler at the system level for PLL lock failure. The largest
        // possible timeout should be used.
        // Uncomment the while loop to have a limit for retry count and
        // comment the for loop.
        // while(retries < SYSCTL_PLL_RETRIES)
        for (;;)
        {
            // Turn off PLL
            ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
            // Delay of at least 100 OSCCLK cycles required between
            // powerdown to powerup of PLL
            SysCtl_delay(100);
            // Turn on PLL
            ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;

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
#if 1
            // Check PLL Frequency using DCC
            status = SysCtl_isPLLValid(
                oscSource, (config & (SYSCTL_IMULT_M | SYSCTL_IDIV_M | SYSCTL_ODIV_M)));
            // Check DCC Status, if no error break the loop
#else
            status = (1 == pllLockStatus);
#endif
            if (status)
            {
                break;
            }

            retries++;
        }

        // Enable PLLSYSCLK is fed from system PLL clock
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;
        // ~100 PLLSYSCLK delay to allow voltage regulator to stabilize
        // prior to increasing entire system clock frequency.
        SysCtl_delay(100);
        // Set the divider to user value
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = (config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
    }
    else
    {
        // disable PLLSYSCLK
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
        // Turn off PLL
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
        SysCtl_delay(100);
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = (config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
    }

    return true;
}

//*****************************************************************************
//
// SysCtl_selectXTAL()
//
//*****************************************************************************
void SysCtl_selectXTAL(void)
{
    bool status        = false;
    uint16_t loopCount = 0U;

    EALLOW;

    //
    // Turn on XTAL and select crystal mode
    //
    ClkCfgRegs.XTALCR.bit.OSCOFF = 0;
    SysCtl_delay(100);
    ClkCfgRegs.XTALCR.bit.SE = 0;
    SysCtl_delay(100);
    EDIS;

    // Wait for the X1 clock readly
    while (1)
    {
        if (ClkCfgRegs.CLKSTATUS.bit.X1READLY)
            break;
    }

    //
    // Wait for the X1 clock to saturate
    //
    status = SysCtl_pollX1Counter();

    //
    // Select XTAL as the oscillator source
    //
    EALLOW;
    ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1;
    SysCtl_delay(100);
    EDIS;

    //
    // If a missing clock failure was detected, try waiting for the X1 counter
    // to saturate again. Consider modifying this code to add a 10ms timeout.
    //
    while (SysCtl_isMCDClockFailureDetected() && (status == FALSE) && (loopCount < 4U))
    {
        //
        // Clear the MCD failure
        //
        SysCtl_resetMCD();

        //
        // Wait for the X1 clock to saturate
        //
        status = SysCtl_pollX1Counter();

        //
        // Select XTAL as the oscillator source
        //
        EALLOW;
        HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1)
            = ((HWREGH(CLKCFG_BASE + SYSCTL_O_CLKSRCCTL1) & (~SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M))
                | (SYSCTL_OSCSRC_XTAL >> SYSCTL_OSCSRC_S));
        EDIS;
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

//*****************************************************************************
//
// SysCtl_selectOscSource()
//
//*****************************************************************************
void SysCtl_selectOscSource(uint32_t oscSource)
{
    ASSERT((oscSource == SYSCTL_OSCSRC_OSC1) || (oscSource == SYSCTL_OSCSRC_OSC2)
           || (oscSource == SYSCTL_OSCSRC_XTAL));

    //
    // Select the specified source.
    //
    EALLOW;
    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Turn on INTOSC2
            //
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF = 0;   // Turn on INTOSC2
            SysCtl_delay(120);                          // Delay
            ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // Clk Src = INTOSC2
            ClkCfgRegs.XTALCR.bit.OSCOFF           = 1; // Trun off XTAL
            break;
        case SYSCTL_OSCSRC_XTAL:
        case SYSCTL_OSCSRC_XTAL_SE:
            //
            // Select XTAL in crystal mode and wait for it to power up
            //
            SysCtl_selectXTAL();
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
    EDIS;
}

//*****************************************************************************
//
// SysCtl_getLowSpeedClock()
//
//*****************************************************************************
uint32_t SysCtl_getLowSpeedClock(uint32_t clockInHz)
{
    uint32_t clockOut;

    //
    // Get the main system clock
    //
    clockOut = SysCtl_getClock(clockInHz);

    //
    // Apply the divider to the main clock
    //
    if (ClkCfgRegs.LOSPCP.bit.LSPCLKDIV != 0U)
        clockOut /= (2U * ClkCfgRegs.LOSPCP.bit.LSPCLKDIV);
    return (clockOut);
}

//*****************************************************************************
//*****************************************************************************
//
// SysCtl_isPLLValid()
//
//*****************************************************************************
bool SysCtl_isPLLValid(uint32_t oscSource, uint32_t pllMultDiv)
{
    uint32_t imult, idiv, odiv, base;

    DCC_Count0ClockSource dccClkSrc0;
    DCC_Count1ClockSource dccClkSrc1;
    uint32_t dccCounterSeed0, dccCounterSeed1, dccValidSeed0;

    switch (oscSource)
    {
        case SYSCTL_OSCSRC_OSC2:
            //
            // Select DCC Clk Src0 as INTOSC2
            //
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC2;
            break;
        case SYSCTL_OSCSRC_XTAL:
        case SYSCTL_OSCSRC_XTAL_SE:
            //
            // Select DCC Clk Src0 as XTAL
            //
            dccClkSrc0 = DCC_COUNT0SRC_XTAL;
            break;
        case SYSCTL_OSCSRC_OSC1:
            //
            // Select DCC Clk Src0 as INTOSC1
            //
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC1;
            break;
        default:
            //
            // Select DCC Clk Src0 as INTOSC1
            //
            dccClkSrc0 = DCC_COUNT0SRC_INTOSC1;
            break;
    }

    //
    // Setting Counter0 & Valid Seed Value with +/-12% tolerance
    //
    dccCounterSeed0 = (uint32_t)SYSCTL_DCC_COUNTER0_WINDOW - 12U;
    dccValidSeed0   = 24U;

    //
    // Select DCC0 for PLL validation
    //
    base = DCC0_BASE;

    //
    // Select DCC Clk Src1 as SYSPLL
    //
    dccClkSrc1 = DCC_COUNT1SRC_PLL;

    imult = (pllMultDiv & SYSCTL_IMULT_M) >> SYSCTL_IMULT_S;
    idiv  = (pllMultDiv & SYSCTL_IDIV_M) >> SYSCTL_IDIV_S;
    odiv  = (pllMultDiv & SYSCTL_ODIV_M) >> SYSCTL_ODIV_S;

    //
    // Multiplying Counter-0 window with PLL Integer Multiplier
    //
    dccCounterSeed1 = SYSCTL_DCC_COUNTER0_WINDOW * imult / idiv / odiv;

    //
    // Clear Error & Done Flag
    //
    DCC_clearErrorFlag(base);
    DCC_clearDoneFlag(base);

    //
    // Disable DCC
    //
    DCC_disableModule(base);

    //
    // Disable Error Signal
    //
    DCC_disableErrorSignal(base);

    //
    // Disable Done Signal
    //
    DCC_disableDoneSignal(base);

    //
    // Configure Clock Source0 to whatever set as a clock source for PLL
    //
    DCC_setCounter0ClkSource(base, dccClkSrc0);

    //
    // Configure Clock Source1 to PLL
    //
    DCC_setCounter1ClkSource(base, dccClkSrc1);

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    DCC_setCounterSeeds(base, dccCounterSeed0, dccValidSeed0, dccCounterSeed1);

    //
    // Enable Single Shot mode
    //
    DCC_enableSingleShotMode(base, DCC_MODE_COUNTER_ZERO);

    //
    // Enable Error Signal
    //
    DCC_enableErrorSignal(base);

    //
    // Enable Done Signal
    //
    DCC_enableDoneSignal(base);

    //
    // Enable DCC to start counting
    //
    DCC_enableModule(base);

    //
    // Timeout for the loop
    //
    uint32_t timeout = dccCounterSeed1;

    //
    // Wait until Error or Done Flag is generated
    //

    while (((HWREGH(base + DCC_O_STATUS) & (DCC_STATUS_ERR | DCC_STATUS_DONE)) == 0U)
           && (timeout != 0U))
    {
        timeout--;
    }

    //
    // Returns true if DCC completes without error
    //

    return (((HWREGH(base + DCC_O_STATUS) & (DCC_STATUS_ERR | DCC_STATUS_DONE)) == DCC_STATUS_DONE)
            && (HWREGH(base + DCC_O_CNT0) == 0U) && (HWREGH(base + DCC_O_VALID0) == 0U)
            && (HWREGH(base + DCC_O_CNT1) == 0U));
}

#include "adc.h"

//
// The following macro calculates the INL trim location in OTP memory
// required to calibrate the ADC linearity.  Use this in the
// ADC_setMode() function only.
//
#define ADC_getINLTrimOTPLoc(offset) ((uint32_t *)(0x72070U + (0xCU * offset)))

//
// This macro calculates the ADC offset trim location in OTP memory required
// to calibrate ADC offset. Use this in the ADC_setMode() function only.
//
#define ADC_getOffsetTrimOTPLoc(offset) ((uint16_t *)(0x72064U + offset))

//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY (0x5A5AU)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY (HWREGH(0x72062UL))

//*****************************************************************************
//
// ADC_setMode
//
//*****************************************************************************
// void ADC_setMode(uint32_t base, ADC_Resolution resolution, ADC_SignalMode signalMode)
//{
//    //
//    // Check the arguments.
//    //
//    ASSERT(ADC_isBaseValid(base));
//
//    //
//    // Apply the resolution and signalMode to the specified ADC.
//    //
//    EALLOW;
//    HWREGH(base + ADC_O_CTL2)
//        = (HWREGH(base + ADC_O_CTL2) & ~(ADC_CTL2_RESOLUTION | ADC_CTL2_SIGNALMODE))
//          | (((uint16_t)resolution << 6) | ((uint16_t)signalMode << 7));
//    EDIS;
//
//    //
//    // Apply INL and offset trims
//    //
//    ADC_setINLTrim(base);
//    ADC_setOffsetTrim(base);
//}

//*****************************************************************************
//
// ADC_setVREF
//
//*****************************************************************************
void ADC_setVREF(uint32_t base, ADC_ReferenceMode refMode, ADC_ReferenceVoltage refVoltage)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    uint16_t moduleShiftVal;

    //
    // Assign a shift amount corresponding to which ADC module is being
    // configured.
    //
    switch (base)
    {
        case ADCA_BASE:
            moduleShiftVal = 1U;
            break;
        case ADCB_BASE:
            moduleShiftVal = 0U;
            break;
        case ADCC_BASE:
            moduleShiftVal = 0U;
            break;
        default:
            //
            // Invalid base address!!
            //
            moduleShiftVal = 0U;
            break;
    }

    EALLOW;
    //
    // Configure the reference mode (internal or external).
    //

    if (refMode == ADC_REFERENCE_INTERNAL)
    {
        if (base == ADCA_BASE)
        {
            AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_A    = 0;
            AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_A = 1;
        }
        else
        {
            AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_BC    = 0;
            AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_BC = 1;
        }
    }
    else
    {
        if (base == ADCA_BASE)
        {
            AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_A    = 1;
            AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_A = 0;
        }
        else
        {
            AnalogSubsysRegs.ANAREFCTL.bit.EN_HIZ_BC    = 1;
            AnalogSubsysRegs.ANAREFCTL.bit.EN_VREFBI_BC = 0;
        }
    }

    //
    // Configure the reference voltage
    //
    if (moduleShiftVal)
        AnalogSubsysRegs.ANAREFCTL.bit.SEL_VREFBIBI_A = refVoltage;
    else
        AnalogSubsysRegs.ANAREFCTL.bit.SEL_VREFBIBI_BC = refVoltage;
    EDIS;
}
//*****************************************************************************
//
// ADC_setOffsetTrim
//
//*****************************************************************************
// void ADC_setOffsetTrim(uint32_t base)
//{
//    //
//    // Selecting the individual offset trim mode wherein offset trim will be
//    // supplied from individual registers already programmed by device_cal api.
//    //
//    ADC_selectOffsetTrimMode(base, ADC_OFFSET_TRIM_INDIVIDUAL);
//}

//*****************************************************************************
//
// ADC_setPPBTripLimits
//
//*****************************************************************************
void ADC_setPPBTripLimits(
    uint32_t base, ADC_PPBNumber ppbNumber, int32_t tripHiLimit, int32_t tripLoLimit)
{
    uint32_t ppbHiOffset;
    uint32_t ppbLoOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((tripHiLimit <= 8388607) && (tripHiLimit >= -8388607));
    ASSERT((tripLoLimit <= 8388607) && (tripLoLimit >= -8388607));

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbHiOffset = (ADC_PPBxTRIPHI_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1TRIPHI;
    //
    // Enable extended low limit
    //
    ppbLoOffset = (ADC_PPBxTRIPLO_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1TRIPLO;

    EALLOW;

    //
    // Set the trip high limit.
    //
    HWREG(base + ppbHiOffset) = (HWREG(base + ppbHiOffset) & ~ADC_PPBTRIP_MASK)
                                | ((uint32_t)tripHiLimit & ADC_PPBTRIP_MASK);

    //
    // Set the trip low limit.
    //
    HWREG(base + ppbLoOffset) = (HWREG(base + ppbLoOffset) & ~ADC_PPBTRIP_MASK)
                                | ((uint32_t)tripLoLimit & ADC_PPBTRIP_MASK);

    EDIS;
}

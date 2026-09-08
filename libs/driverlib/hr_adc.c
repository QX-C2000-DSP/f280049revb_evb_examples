#include "hr_adc.h"

//*****************************************************************************
//
// HR ADC_setPPBTripLimits
//
//*****************************************************************************
void HR_ADC_setPPBTripLimits(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, int32_t tripHiLimit, int32_t tripLoLimit)
{
    uint32_t ppbHiOffset;
    uint32_t ppbLoOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((tripHiLimit <= 65535) && (tripHiLimit >= -65536));
    ASSERT((tripLoLimit <= 65535) && (tripLoLimit >= -65536));

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbHiOffset = 0x98U + (int16_t)ppbNumber * 0x18U;
    ppbLoOffset = 0x9cU + (int16_t)ppbNumber * 0x18U;

    EALLOW;

    //
    // Set the trip high limit.
    //
    ((union HR_ADCPPBTRIPHI_REG *)(base + ppbHiOffset))->all = tripHiLimit;

    //
    // Set the trip low limit.
    //
    ((union HR_ADCPPBTRIPLO_REG *)(base + ppbLoOffset))->all = tripLoLimit;

    EDIS;
}

//
// The following macro calculates the INL trim location in OTP memory
// required to calibrate the HR_ADC linearity.  Use this in the
// HR_ADC_setMode() function only.
//
#define HR_ADC_getINLTrimOTPLoc(offset) ((uint32_t *)(0x72070U + (0xCU * offset)))

//
// This macro calculates the HR_ADC offset trim location in OTP memory required
// to calibrate HR_ADC offset. Use this in the HR_ADC_setMode() function only.
//
#define HR_ADC_getOffsetTrimOTPLoc(offset) ((uint16_t *)(0x72064U + offset))

//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY (0x5A5AU)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY (HWREGH(0x72062UL))

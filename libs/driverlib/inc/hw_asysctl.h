#ifndef HW_ASYSCTL_H
#define HW_ASYSCTL_H

//*************************************************************************************************
//
// The following are defines for the ASYSCTL register offsets
//
//*************************************************************************************************
#define ASYSCTL_O_TSNSCTL    0x04U // Temperature Sensor Control Register
#define ASYSCTL_O_ANAREFCTL  0x08U // Analog Reference Control Register
#define ASYSCTL_O_VMONCTL    0x0CU // Voltage Monitor Control Register
#define ASYSCTL_O_DCDCCTL    0x10U // DC-DC control register.
#define ASYSCTL_O_DCDCSTS    0x14U // DC-DC status register.
#define ASYSCTL_O_CMPHPMXSEL 0x18U // Bits to select one of the many sources on CopmHP inputs.
#define ASYSCTL_O_CMPLPMXSEL 0x1CU // Bits to select one of the many sources on CopmLP inputs.
#define ASYSCTL_O_CMPHNMXSEL 0x20U // Bits to select one of the many sources on CopmHN inputs.
#define ASYSCTL_O_CMPLNMXSEL 0x24U // Bits to select one of the many sources on CopmLN inputs.
#define ASYSCTL_O_AGPIOCTRL  0x30U // AGPIO mode control register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TSNSCTL register
//
//*************************************************************************************************
#define ASYSCTL_TSNSCTL_ENABLE 0x1U // Temperature Sensor Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the ANAREFCTL register
//
//*************************************************************************************************
#define ASYSCTL_ANAREFCTL_EN_HIZ_A        0x2U  // Analog Internal Reference A connect Hiz
#define ASYSCTL_ANAREFCTL_EN_HIZ_BC       0x4U  // Analog Internal Reference B/C connect Hiz
#define ASYSCTL_ANAREFCTL_EN_VREFBI_A     0x8U  // Analog Internal Reference A enable
#define ASYSCTL_ANAREFCTL_EN_VREFBI_BC    0x10U // Analog Internal Reference B/C enable
#define ASYSCTL_ANAREFCTL_SEL_VREFBI_A_S  5U
#define ASYSCTL_ANAREFCTL_SEL_VREFBI_A_M  0x60U // Analog Reference A Select
#define ASYSCTL_ANAREFCTL_SEL_VREFBI_BC_S 7U
#define ASYSCTL_ANAREFCTL_SEL_VREFBI_BC_M 0x180U // Analog Reference B/C Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the VMONCTL register
//
//*************************************************************************************************
#define ASYSCTL_VMONCTL_BORLVMONEN 0x100U // enable BORL(ow) feature on VDDIO

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCDCCTL register
//
//*************************************************************************************************
#define ASYSCTL_DCDCCTL_DCDCEN     0x1U // DCDC Enable
#define ASYSCTL_DCDCCTL_MD_LXDET_S 14U
#define ASYSCTL_DCDCCTL_MD_LXDET_M 0xC000U // DCDC External inductance detect type

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCDCSTS register
//
//*************************************************************************************************
#define ASYSCTL_DCDCSTS_INDDETECT 0x1U // Inductor Detected
#define ASYSCTL_DCDCSTS_SWSEQDONE 0x2U // Switch sequence to DC-DC done.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHPMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_S 0U
#define ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M 0x7U // CMP1HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_S 3U
#define ASYSCTL_CMPHPMXSEL_CMP2HPMXSEL_M 0x38U // CMP2HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_S 6U
#define ASYSCTL_CMPHPMXSEL_CMP3HPMXSEL_M 0x1C0U // CMP3HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_S 9U
#define ASYSCTL_CMPHPMXSEL_CMP4HPMXSEL_M 0xE00U // CMP4HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP5HPMXSEL_S 12U
#define ASYSCTL_CMPHPMXSEL_CMP5HPMXSEL_M 0x7000U // CMP5HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP6HPMXSEL_S 16U
#define ASYSCTL_CMPHPMXSEL_CMP6HPMXSEL_M 0x70000U // CMP6HPMXSEL bits
#define ASYSCTL_CMPHPMXSEL_CMP7HPMXSEL_S 19U
#define ASYSCTL_CMPHPMXSEL_CMP7HPMXSEL_M 0x380000U // CMP7HPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLPMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_S 0U
#define ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M 0x7U // CMP1LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_S 3U
#define ASYSCTL_CMPLPMXSEL_CMP2LPMXSEL_M 0x38U // CMP2LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_S 6U
#define ASYSCTL_CMPLPMXSEL_CMP3LPMXSEL_M 0x1C0U // CMP3LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_S 9U
#define ASYSCTL_CMPLPMXSEL_CMP4LPMXSEL_M 0xE00U // CMP4LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP5LPMXSEL_S 12U
#define ASYSCTL_CMPLPMXSEL_CMP5LPMXSEL_M 0x7000U // CMP5LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP6LPMXSEL_S 16U
#define ASYSCTL_CMPLPMXSEL_CMP6LPMXSEL_M 0x70000U // CMP6LPMXSEL bits
#define ASYSCTL_CMPLPMXSEL_CMP7LPMXSEL_S 19U
#define ASYSCTL_CMPLPMXSEL_CMP7LPMXSEL_M 0x380000U // CMP7LPMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPHNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPHNMXSEL_CMP1HNMXSEL_S 0U
#define ASYSCTL_CMPHNMXSEL_CMP1HNMXSEL_M 0x3U // CMP1HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP2HNMXSEL_S 2U
#define ASYSCTL_CMPHNMXSEL_CMP2HNMXSEL_M 0xCU // CMP2HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP3HNMXSEL_S 4U
#define ASYSCTL_CMPHNMXSEL_CMP3HNMXSEL_M 0x30U // CMP3HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP4HNMXSEL_S 6U
#define ASYSCTL_CMPHNMXSEL_CMP4HNMXSEL_M 0xC0U // CMP4HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP5HNMXSEL_S 8U
#define ASYSCTL_CMPHNMXSEL_CMP5HNMXSEL_M 0x300U // CMP5HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP6HNMXSEL_S 10U
#define ASYSCTL_CMPHNMXSEL_CMP6HNMXSEL_M 0xC00U // CMP6HNMXSEL bits
#define ASYSCTL_CMPHNMXSEL_CMP7HNMXSEL_S 12U
#define ASYSCTL_CMPHNMXSEL_CMP7HNMXSEL_M 0x3000U // CMP7HNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPLNMXSEL register
//
//*************************************************************************************************
#define ASYSCTL_CMPLNMXSEL_CMP1LNMXSEL_S 0U
#define ASYSCTL_CMPLNMXSEL_CMP1LNMXSEL_M 0x3U // CMP1LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP2LNMXSEL_S 2U
#define ASYSCTL_CMPLNMXSEL_CMP2LNMXSEL_M 0xCU // CMP2LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP3LNMXSEL_S 4U
#define ASYSCTL_CMPLNMXSEL_CMP3LNMXSEL_M 0x30U // CMP3LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP4LNMXSEL_S 6U
#define ASYSCTL_CMPLNMXSEL_CMP4LNMXSEL_M 0xC0U // CMP4LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP5LNMXSEL_S 8U
#define ASYSCTL_CMPLNMXSEL_CMP5LNMXSEL_M 0x300U // CMP5LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP6LNMXSEL_S 10U
#define ASYSCTL_CMPLNMXSEL_CMP6LNMXSEL_M 0xC00U // CMP6LNMXSEL bits
#define ASYSCTL_CMPLNMXSEL_CMP7LNMXSEL_S 12U
#define ASYSCTL_CMPLNMXSEL_CMP7LNMXSEL_M 0x3000U // CMP7LNMXSEL bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the AGPIOCTRL register
//
//*************************************************************************************************
#define ASYSCTL_AGPIOCTRL_GPIO224 0x1U      // GPIO224 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO225 0x2U      // GPIO225 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO226 0x4U      // GPIO226 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO227 0x8U      // GPIO227 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO228 0x10U     // GPIO228 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO229 0x20U     // GPIO229 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO230 0x40U     // GPIO230 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO231 0x80U     // GPIO231 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO232 0x100U    // GPIO232 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO233 0x200U    // GPIO233 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO234 0x400U    // GPIO234 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO235 0x800U    // GPIO235 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO236 0x1000U   // GPIO236 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO237 0x2000U   // GPIO237 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO238 0x4000U   // GPIO238 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO239 0x8000U   // GPIO239 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO240 0x10000U  // GPIO240 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO241 0x20000U  // GPIO241 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO242 0x40000U  // GPIO242 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO243 0x80000U  // GPIO243 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO244 0x100000U // GPIO244 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO245 0x200000U // GPIO245 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO246 0x400000U // GPIO246 AGPO mode enable
#define ASYSCTL_AGPIOCTRL_GPIO247 0x800000U // GPIO248 AGPO mode enable

#endif

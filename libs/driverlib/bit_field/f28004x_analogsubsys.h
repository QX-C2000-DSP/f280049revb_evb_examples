#ifndef F28004X_ANALOGSUBSYS_H
#define F28004X_ANALOGSUBSYS_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// ANALOGSUBSYS Individual Register Bit Definitions:

struct TSNSCTL_BITS
{                       // bits description
    Uint32 ENABLE : 1;  // 0 Temperature Sensor Enable
    Uint32 rsvd1  : 15; // 15:1 Reserved
};

union TSNSCTL_REG
{
    Uint32 all;
    struct TSNSCTL_BITS bit;
};

struct ANAREFCTL_BITS
{                               // bits description
    Uint32 rsvd1    : 1;        // 0 Reserved (EN_VR_EX)
    Uint32 EN_HIZ_A : 1;        // 1 Control signal for enabling high-impedance state when built-in
                                // reference is disabled
    Uint32 EN_HIZ_BC : 1;       // 2 Control signal for enabling high-impedance state when built-in
                                // reference is disabled
    Uint32 EN_VREFBI_A     : 1; // 3 built-in reference voltage A enable signal
    Uint32 EN_VREFBI_BC    : 1; // 4 built-in reference voltage B or C enable signal
    Uint32 SEL_VREFBIBI_A  : 2; // 6:5 built-in reference A output voltage selected signal
    Uint32 SEL_VREFBIBI_BC : 2; // 8:7 built-in reference B or C output voltage selected signal
};

union ANAREFCTL_REG
{
    Uint32 all;
    struct ANAREFCTL_BITS bit;
};

struct VMONCTL_BITS
{                          // bits description
    Uint32 rsvd1      : 3; // 2:0 Reserved (ADJ_PVD)
    Uint32 rsvd2      : 5; // 7:3 Reserved
    Uint32 BORLVMONEN : 1; // 8 Enable BORL on VDDIO
};

union VMONCTL_REG
{
    Uint32 all;
    struct VMONCTL_BITS bit;
};

struct DCDCCTL_BITS
{                        // bits description
    Uint32 DCDCEN   : 1; // 0 enable DC-DC
    Uint32 rsvd1    : 2; // 2:1
    Uint32 rsvd2    : 2; // 4:3
    Uint32 rsvd3    : 2; // 6:5
    Uint32 rsvd4    : 2; // 8:7
    Uint32 rsvd5    : 4; // 12:9
    Uint32 rsvd6    : 1; // 13
    Uint32 MD_LXDET : 2; // 15:14 LX Detect
};

union DCDCCTL_REG
{
    Uint32 all;
    struct DCDCCTL_BITS bit;
};

struct DCDCSTS_BITS
{                          // bits description
    Uint32 INDDETECT : 1;  // 0 Inductor Detected
    Uint32 SWSEQDONE : 1;  // 1 Switch sequence to DC-DC done.
    Uint32 rsvd1     : 1;  // 2 Reserved
    Uint32 rsvd2     : 13; // 15:3 Reserved
};

union DCDCSTS_REG
{
    Uint32 all;
    struct DCDCSTS_BITS bit;
};

struct CMPHPMXSEL_BITS
{                            // bits description
    Uint32 CMP1HPMXSEL : 3;  // 2:0 CMP1HPMXSEL bits
    Uint32 CMP2HPMXSEL : 3;  // 5:3 CMP2HPMXSEL bits
    Uint32 CMP3HPMXSEL : 3;  // 8:6 CMP3HPMXSEL bits
    Uint32 CMP4HPMXSEL : 3;  // 11:9 CMP4HPMXSEL bits
    Uint32 CMP5HPMXSEL : 3;  // 14:12 CMP5HPMXSEL bits
    Uint32 rsvd1       : 1;  // 15 Reserved
    Uint32 CMP6HPMXSEL : 3;  // 18:16 CMP6HPMXSEL bits
    Uint32 CMP7HPMXSEL : 3;  // 21:19 CMP7HPMXSEL bits
    Uint32 rsvd2       : 10; // 31:22 Reserved
};

union CMPHPMXSEL_REG
{
    Uint32 all;
    struct CMPHPMXSEL_BITS bit;
};

struct CMPLPMXSEL_BITS
{                            // bits description
    Uint32 CMP1LPMXSEL : 3;  // 2:0 CMP1LPMXSEL bits
    Uint32 CMP2LPMXSEL : 3;  // 5:3 CMP2LPMXSEL bits
    Uint32 CMP3LPMXSEL : 3;  // 8:6 CMP3LPMXSEL bits
    Uint32 CMP4LPMXSEL : 3;  // 11:9 CMP4LPMXSEL bits
    Uint32 CMP5LPMXSEL : 3;  // 14:12 CMP5LPMXSEL bits
    Uint32 rsvd1       : 1;  // 15 Reserved
    Uint32 CMP6LPMXSEL : 3;  // 18:16 CMP6LPMXSEL bits
    Uint32 CMP7LPMXSEL : 3;  // 21:19 CMP7LPMXSEL bits
    Uint32 rsvd2       : 10; // 31:22 Reserved
};

union CMPLPMXSEL_REG
{
    Uint32 all;
    struct CMPLPMXSEL_BITS bit;
};

struct CMPHNMXSEL_BITS
{
    Uint32 CMP1HNMXSEL : 2; // 1:0 CMP-1HNMXSEL bit
    Uint32 CMP2HNMXSEL : 2; // 3:2 CMP-2HNMXSEL bit
    Uint32 CMP3HNMXSEL : 2; // 5:4 CMP-3HNMXSEL bit
    Uint32 CMP4HNMXSEL : 2; // 7:6 CMP-4HNMXSEL bit
    Uint32 CMP5HNMXSEL : 2; // 9:8 CMP-5HNMXSEL bit
    Uint32 CMP6HNMXSEL : 2; // 11:10 CMP-6HNMXSEL bit
    Uint32 CMP7HNMXSEL : 2; // 13:12 CMP-7HNMXSEL bit
};

union CMPHNMXSEL_REG
{
    Uint32 all;
    struct CMPHNMXSEL_BITS bit;
};

struct CMPLNMXSEL_BITS
{
    Uint32 CMP1LNMXSEL : 2; // 1:0  CMP-1LNMXSEL bit
    Uint32 CMP2LNMXSEL : 2; // 3:2  CMP-2LNMXSEL bit
    Uint32 CMP3LNMXSEL : 2; // 5:4  CMP-3LNMXSEL bit
    Uint32 CMP4LNMXSEL : 2; // 7:6  CMP-4LNMXSEL bit
    Uint32 CMP5LNMXSEL : 2; // 9:8  CMP-5LNMXSEL bit
    Uint32 CMP6LNMXSEL : 2; // 11:10 CMP-6LNMXSEL bit
    Uint32 CMP7LNMXSEL : 2; // 13:12 CMP-7LNMXSEL bit
};

union CMPLNMXSEL_REG
{
    Uint32 all;
    struct CMPLNMXSEL_BITS bit;
};

struct AGPIOCTRLH_BITS
{
    Uint32 GPIO224 : 1; // 0 Enable AGPIO funtction on GPIO224
    Uint32 GPIO225 : 1; // 1 Enable AGPIO funtction on GPIO225
    Uint32 GPIO226 : 1; // 2 Enable AGPIO funtction on GPIO226
    Uint32 GPIO227 : 1; // 3 Enable AGPIO funtction on GPIO227
    Uint32 GPIO228 : 1; // 4 Enable AGPIO funtction on GPIO228
    Uint32 GPIO229 : 1; // 5 Enable AGPIO funtction on GPIO229
    Uint32 GPIO230 : 1; // 6 Enable AGPIO funtction on GPIO230
    Uint32 GPIO231 : 1; // 7 Enable AGPIO funtction on GPIO231
    Uint32 GPIO232 : 1; // 8 Enable AGPIO funtction on GPIO232
    Uint32 GPIO233 : 1; // 9 Enable AGPIO funtction on GPIO233
    Uint32 GPIO234 : 1; // 10 Enable AGPIO funtction on GPIO234
    Uint32 GPIO235 : 1; // 11 Enable AGPIO funtction on GPIO235
    Uint32 GPIO236 : 1; // 12 Enable AGPIO funtction on GPIO236
    Uint32 GPIO237 : 1; // 13 Enable AGPIO funtction on GPIO237
    Uint32 GPIO238 : 1; // 14 Enable AGPIO funtction on GPIO238
    Uint32 GPIO239 : 1; // 15 Enable AGPIO funtction on GPIO239
    Uint32 GPIO240 : 1; // 16 Enable AGPIO funtction on GPIO240
    Uint32 GPIO241 : 1; // 17 Enable AGPIO funtction on GPIO241
    Uint32 GPIO242 : 1; // 18 Enable AGPIO funtction on GPIO242
    Uint32 GPIO243 : 1; // 19 Enable AGPIO funtction on GPIO243
    Uint32 GPIO244 : 1; // 20 Enable AGPIO funtction on GPIO244
    Uint32 GPIO245 : 1; // 21 Enable AGPIO funtction on GPIO245
    Uint32 GPIO246 : 1; // 22 Enable AGPIO funtction on GPIO246
    Uint32 GPIO247 : 1; // 23 Enable AGPIO funtction on GPIO247
};

union AGPIOCTRLH_REG
{
    Uint32 all;
    struct AGPIOCTRLH_BITS bit;
};

struct ANATEST_TOP_BITS
{
    Uint32 ANATESTSEL : 3;  // 2:0 Analog system test select
    Uint32 ANATESTEN  : 1;  // 3 Analog system test enable
    Uint32 rsv        : 28; // 31:4 rsv
};

union ANATEST_TOP_REG
{
    Uint32 all;
    struct ANATEST_TOP_BITS bit;
};

struct ANALOG_SUBSYS_REGS
{
    Uint32 rsv1;                       // Reserved
    union TSNSCTL_REG TSNSCTL;         // Temperature Sensor Control Register
    union ANAREFCTL_REG ANAREFCTL;     // Analog Reference Control Register
    union VMONCTL_REG VMONCTL;         // Voltage Monitor Control Register
    union DCDCCTL_REG DCDCCTL;         // DC-DC control register
    union DCDCSTS_REG DCDCSTS;         // DC-DC status register
    union CMPHPMXSEL_REG CMPHPMXSEL;   // Bits to select one of the many sources on CopmHP inputs.
                                       // Refer to Pimux diagram for details.
    union CMPLPMXSEL_REG CMPLPMXSEL;   // Bits to select one of the many sources on CopmLP inputs.
                                       // Refer to Pimux diagram for details.
    union CMPHNMXSEL_REG CMPHNMXSEL;   // Bits to select one of the many sources on CopmHN inputs.
                                       // Refer to Pimux diagram for details.
    union CMPLNMXSEL_REG CMPLNMXSEL;   // Bits to select one of the many sources on CopmLN inputs.
                                       // Refer to Pimux diagram for details.
    Uint32 rsv2[2];                    // 0x28-0x2C
    union AGPIOCTRLH_REG AGPIOCTRLH;   // AGPIO Control register
    union ANATEST_TOP_REG ANATEST_TOP; // Analog system test control top register
};

//---------------------------------------------------------------------------
// ANALOGSUBSYS External References & Function Declarations:
//
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================

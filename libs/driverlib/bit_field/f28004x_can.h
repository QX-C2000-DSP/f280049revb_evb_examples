#ifndef F28004X_CAN_H
#define F28004X_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// CAN Register Bit Definitions:

struct CANFD_CFGSTAT_BIT
{
    Uint8 BUSOFF  : 1; /* [0] */
    Uint8 TACTIVE : 1; /* [1] */
    Uint8 RACTIVE : 1; /* [2] */
    Uint8 TSSS    : 1; /* [3] */
    Uint8 TPSS    : 1; /* [4] */
    Uint8 LBMI    : 1; /* [5] */
    Uint8 LBME    : 1; /* [6] */
    Uint8 RESET   : 1; /* [7] */
};

union CANFD_CFGSTAT_REG
{
    Uint8 all;
    struct CANFD_CFGSTAT_BIT bit;
};

struct CANFD_TCMD_BIT
{
    Uint8 TSA   : 1; /* [0] */
    Uint8 TSALL : 1; /* [1] */
    Uint8 TSONE : 1; /* [2] */
    Uint8 TPA   : 1; /* [3] */
    Uint8 TPE   : 1; /* [4] */
    Uint8 STBY  : 1; /* [5] */
    Uint8 LOM   : 1; /* [6] */
    Uint8 TBSEL : 1; /* [7] */
};

union CANFD_TCMD_REG
{
    Uint8 all;
    struct CANFD_TCMD_BIT bit;
};

struct CANFD_TCTRL_BIT
{
    Uint8 TSSTAT : 2; /* [1:0] */
    Uint8 rsvd1  : 2; /* [3:2] Reserved */
    Uint8 TTTBM  : 1; /* [4] */
    Uint8 TSMODE : 1; /* [5] */
    Uint8 TSNEXT : 1; /* [6] */
    Uint8 FD_ISO : 1; /* [7] */
};

union CANFD_TCTRL_REG
{
    Uint8 all;
    struct CANFD_TCTRL_BIT bit;
};

struct CANFD_RCTRL_BIT
{
    Uint8 RSTAT : 2; /* [1:0] */
    Uint8 rsvd1 : 1; /* [2] Reserved */
    Uint8 RBALL : 1; /* [3] */
    Uint8 RREL  : 1; /* [4] */
    Uint8 ROV   : 1; /* [5] */
    Uint8 ROM   : 1; /* [6] */
    Uint8 SACK  : 1; /* [7] */
};

union CANFD_RCTRL_REG
{
    Uint8 all;
    struct CANFD_RCTRL_BIT bit;
};

struct CANFD_RTIE_BIT
{
    Uint8 TSFF  : 1; /* [0] */
    Uint8 EIE   : 1; /* [1] */
    Uint8 TSIE  : 1; /* [2] */
    Uint8 TPIE  : 1; /* [3] */
    Uint8 RAFIE : 1; /* [4] */
    Uint8 RFIE  : 1; /* [5] */
    Uint8 ROIE  : 1; /* [6] */
    Uint8 RIE   : 1; /* [7] */
};

union CANFD_RTIE_REG
{
    Uint8 all;
    struct CANFD_RTIE_BIT bit;
};

struct CANFD_RTIF_BIT
{
    Uint8 AIF   : 1; /* [0] */
    Uint8 EIF   : 1; /* [1] */
    Uint8 TSIF  : 1; /* [2] */
    Uint8 TPIF  : 1; /* [3] */
    Uint8 RAFIF : 1; /* [4] */
    Uint8 RFIF  : 1; /* [5] */
    Uint8 ROIF  : 1; /* [6] */
    Uint8 RIF   : 1; /* [7] */
};

union CANFD_RTIF_REG
{
    Uint8 all;
    struct CANFD_RTIF_BIT bit;
};

struct CANFD_ERRINT_BIT
{
    Uint8 BEIF  : 1; /* [0] */
    Uint8 BEIE  : 1; /* [1] */
    Uint8 ALIF  : 1; /* [2] */
    Uint8 ALIE  : 1; /* [3] */
    Uint8 EPIF  : 1; /* [4] */
    Uint8 EPIE  : 1; /* [5] */
    Uint8 EPASS : 1; /* [6] */
    Uint8 EWARN : 1; /* [7] */
};

union CANFD_ERRINT_REG
{
    Uint8 all;
    struct CANFD_ERRINT_BIT bit;
};

struct CANFD_LIMIT_BIT
{
    Uint8 EWL  : 4; /* [3:0] */
    Uint8 AFWL : 4; /* [7:4] */
};

union CANFD_LIMIT_REG
{
    Uint8 all;
    struct CANFD_LIMIT_BIT bit;
};

struct CANFD_SSeg1_BIT
{
    Uint8 SSeg1 : 8; /* [7:0] */
};

union CANFD_SSeg1_REG
{
    Uint8 all;
    struct CANFD_SSeg1_BIT bit;
};

struct CANFD_SSeg2_BIT
{
    Uint8 SSeg2 : 7; /* [6:0] */
    Uint8 rsvd1 : 1; /* [7] Reserved */
};

union CANFD_SSeg2_REG
{
    Uint8 all;
    struct CANFD_SSeg2_BIT bit;
};

struct CANFD_SSJW_BIT
{
    Uint8 SSJW  : 7; /* [6:0] */
    Uint8 rsvd1 : 1; /* [7] Reserved */
};

union CANFD_SSJW_REG
{
    Uint8 all;
    struct CANFD_SSJW_BIT bit;
};

struct CANFD_SPRESC_BIT
{
    Uint8 SPRESC : 8; /* [7:0] */
};

union CANFD_SPRESC_REG
{
    Uint8 all;
    struct CANFD_SPRESC_BIT bit;
};

struct CANFD_FSeg1_BIT
{
    Uint8 FSeg1 : 5; /* [4:0] */
    Uint8 rsvd1 : 3; /* [7:5] Reserved */
};

union CANFD_FSeg1_REG
{
    Uint8 all;
    struct CANFD_FSeg1_BIT bit;
};

struct CANFD_FSeg2_BIT
{
    Uint8 FSeg2 : 4; /* [3:0] */
    Uint8 rsvd1 : 4; /* [7:4] Reserved */
};

union CANFD_FSeg2_REG
{
    Uint8 all;
    struct CANFD_FSeg2_BIT bit;
};

struct CANFD_FSJW_BIT
{
    Uint8 FSJW  : 4; /* [3:0] */
    Uint8 rsvd1 : 4; /* [7:4] Reserved */
};

union CANFD_FSJW_REG
{
    Uint8 all;
    struct CANFD_FSJW_BIT bit;
};

struct CANFD_FPRESC_BIT
{
    Uint8 FPRESC : 8; /* [7:0] */
};

union CANFD_FPRESC_REG
{
    Uint8 all;
    struct CANFD_FPRESC_BIT bit;
};

struct CANFD_EALCAP_BIT
{
    Uint8 ALC  : 5; /* [4:0] */
    Uint8 KOER : 3; /* [7:5] */
};

union CANFD_EALCAP_REG
{
    Uint8 all;
    struct CANFD_EALCAP_BIT bit;
};

struct CANFD_TDC_BIT
{
    Uint8 SSPOFF : 7; /* [6:0] */
    Uint8 TDCEN  : 1; /* [7] */
};

union CANFD_TDC_REG
{
    Uint8 all;
    struct CANFD_TDC_BIT bit;
};

struct CANFD_RECNT_BIT
{
    Uint8 RECNT : 8; /* [7:0] */
};

union CANFD_RECNT_REG
{
    Uint8 all;
    struct CANFD_RECNT_BIT bit;
};

struct CANFD_TECNT_BIT
{
    Uint8 TECNT : 8; /* [7:0] */
};

union CANFD_TECNT_REG
{
    Uint8 all;
    struct CANFD_TECNT_BIT bit;
};

struct CANFD_ACFCTRL_BIT
{
    Uint8 ACFADR  : 4; /* [3:0] */
    Uint8 rsvd1   : 1; /* [4] Reserved */
    Uint8 SELMASK : 1; /* [5] */
    Uint8 rsvd2   : 2; /* [7:6] Reserved */
};

union CANFD_ACFCTRL_REG
{
    Uint8 all;
    struct CANFD_ACFCTRL_BIT bit;
};

struct CANFD_TIMECFG_BIT
{
    Uint8 TIMEEN  : 1; /* [0] */
    Uint8 TIMEPOS : 1; /* [1] */
    Uint8 rsvd1   : 6; /* [7:2] Reserved */
};

union CANFD_TIMECFG_REG
{
    Uint8 all;
    struct CANFD_TIMECFG_BIT bit;
};

struct CANFD_ACFEN0_BIT
{
    Uint8 AE_0 : 1; /* [0] */
    Uint8 AE_1 : 1; /* [1] */
    Uint8 AE_2 : 1; /* [2] */
    Uint8 AE_3 : 1; /* [3] */
    Uint8 AE_4 : 1; /* [4] */
    Uint8 AE_5 : 1; /* [5] */
    Uint8 AE_6 : 1; /* [6] */
    Uint8 AE_7 : 1; /* [7] */
};

union CANFD_ACFEN0_REG
{
    Uint8 all;
    struct CANFD_ACFEN0_BIT bit;
};

struct CANFD_ACFEN1_BIT
{
    Uint8 AE_8  : 1; /* [0] */
    Uint8 AE_9  : 1; /* [1] */
    Uint8 AE_10 : 1; /* [2] */
    Uint8 AE_11 : 1; /* [3] */
    Uint8 AE_12 : 1; /* [4] */
    Uint8 AE_13 : 1; /* [5] */
    Uint8 AE_14 : 1; /* [6] */
    Uint8 AE_15 : 1; /* [7] */
};

union CANFD_ACFEN1_REG
{
    Uint8 all;
    struct CANFD_ACFEN1_BIT bit;
};

struct CANFD_ACODE_BIT
{
    Uint8 ACODE0 : 8; /* [7:0] */
    Uint8 ACODE1 : 8; /* [15:8] */
    Uint8 ACODE2 : 8; /* [23:16] */
    Uint8 ACODE3 : 5; /* [28:24] */
    Uint8 rsvd1  : 3; /* [31:29] Reserved */
};

struct CANFD_AMASK_BIT
{
    Uint8 AMASK0 : 8; /* [7:0] */
    Uint8 AMASK1 : 8; /* [15:8] */
    Uint8 AMASK2 : 8; /* [23:16] */
    Uint8 AMASK3 : 5; /* [28:24] */
    Uint8 AIDE   : 1; /* [29] */
    Uint8 AIDEE  : 1; /* [30] */
    Uint8 rsvd1  : 1; /* [31] Reserved */
};

union CANFD_ACF_REG
{
    Uint32 all;
    struct CANFD_ACODE_BIT ACODE;
    struct CANFD_AMASK_BIT AMASK;
};

struct CANFD_VER0_BIT
{
    Uint8 VERSION_L : 8; /* [7:0] */
};

union CANFD_VER0_REG
{
    Uint8 all;
    struct CANFD_VER0_BIT bit;
};

struct CANFD_VER1_BIT
{
    Uint8 VERSION_H : 8; /* [7:0] */
};

union CANFD_VER1_REG
{
    Uint8 all;
    struct CANFD_VER1_BIT bit;
};

struct CANFD_TBSLOT_BIT
{
    Uint8 TBPTR : 6; /* [5:0] */
    Uint8 TBF   : 1; /* [6] */
    Uint8 TBE   : 1; /* [7] */
};

union CANFD_TBSLOT_REG
{
    Uint8 all;
    struct CANFD_TBSLOT_BIT bit;
};

struct CANFD_TTCFG_BIT
{
    Uint8 TTEN    : 1; /* [0] */
    Uint8 T_PRESC : 2; /* [2:0] */
    Uint8 TTIF    : 1; /* [3] */
    Uint8 TTIE    : 1; /* [4] */
    Uint8 TEIF    : 1; /* [5] */
    Uint8 WTIF    : 1; /* [6] */
    Uint8 WTIE    : 1; /* [7] */
};

union CANFD_TTCFG_REG
{
    Uint8 all;
    struct CANFD_TTCFG_BIT bit;
};

struct CANFD_REFMSG0_BIT
{
    Uint8 REF_ID0 : 8; /* [7:0] */
};

union CANFD_REFMSG0_REG
{
    Uint8 all;
    struct CANFD_REFMSG0_BIT bit;
};

struct CANFD_REFMSG1_BIT
{
    Uint8 REF_ID1 : 8; /* [7:0] */
};

union CANFD_REFMSG1_REG
{
    Uint8 all;
    struct CANFD_REFMSG1_BIT bit;
};

struct CANFD_REFMSG2_BIT
{
    Uint8 REF_ID2 : 8; /* [7:0] */
};

union CANFD_REFMSG2_REG
{
    Uint8 all;
    struct CANFD_REFMSG2_BIT bit;
};

struct CANFD_REFMSG3_BIT
{
    Uint8 REF_ID3 : 5; /* [4:0] */
    Uint8 rsvd1   : 2; /* [6:5] Reserved */
    Uint8 REF_IDE : 1; /* [7] */
};

union CANFD_REFMSG3_REG
{
    Uint8 all;
    struct CANFD_REFMSG3_BIT bit;
};

struct CANFD_TRIGCFG0_BIT
{
    Uint8 TTPTR : 6; /* [5:0] */
    Uint8 rsvd1 : 2; /* [7:6] Reserved */
};

union CANFD_TRIGCFG0_REG
{
    Uint8 all;
    struct CANFD_TRIGCFG0_BIT bit;
};

struct CANFD_TRIGCFG1_BIT
{
    Uint8 TTYPE : 3; /* [2:0] */
    Uint8 rsvd1 : 1; /* [3] Reserved */
    Uint8 TEW   : 4; /* [7:4] */
};

union CANFD_TRIGCFG1_REG
{
    Uint8 all;
    struct CANFD_TRIGCFG1_BIT bit;
};

struct CANFD_TTTRIG0_BIT
{
    Uint8 TT_TRIG0 : 8; /* [7:0] */
};

union CANFD_TTTRIG0_REG
{
    Uint8 all;
    struct CANFD_TTTRIG0_BIT bit;
};

struct CANFD_TTTRIG1_BIT
{
    Uint8 TT_TRIG1 : 8; /* [7:0] */
};

union CANFD_TTTRIG1_REG
{
    Uint8 all;
    struct CANFD_TTTRIG1_BIT bit;
};

struct CANFD_TTWTRIG0_BIT
{
    Uint8 TT_WTRIG0 : 8; /* [7:0] */
};

union CANFD_TTWTRIG0_REG
{
    Uint8 all;
    struct CANFD_TTWTRIG0_BIT bit;
};

struct CANFD_TTWTRIG1_BIT
{
    Uint8 TT_WTRIG1 : 8; /* [7:0] */
};

union CANFD_TTWTRIG1_REG
{
    Uint8 all;
    struct CANFD_TTWTRIG1_BIT bit;
};

struct CAN_REGS
{
    Uint32 RBUF[20];                     /* offset: 0x00-0x4f */
    Uint32 TBUF[18];                     /* offset: 0x50-0x97 */
    Uint8 TTS[8];                        /* offset: 0x98-0x9f */
    union CANFD_CFGSTAT_REG CFGSTAT;     /* offset: 0xa0 */
    union CANFD_TCMD_REG TCMD;           /* offset: 0xa1 */
    union CANFD_TCTRL_REG TCTRL;         /* offset: 0xa2 */
    union CANFD_RCTRL_REG RCTRL;         /* offset: 0xa3 */
    union CANFD_RTIE_REG RTIE;           /* offset: 0xa4 */
    union CANFD_RTIF_REG RTIF;           /* offset: 0xa5 */
    union CANFD_ERRINT_REG ERRINT;       /* offset: 0xa6 */
    union CANFD_LIMIT_REG LIMIT;         /* offset: 0xa7 */
    union CANFD_SSeg1_REG S_Seg_1;       /* offset: 0xa8 */
    union CANFD_SSeg2_REG S_Seg_2;       /* offset: 0xa9 */
    union CANFD_SSJW_REG S_SJW;          /* offset: 0xaa */
    union CANFD_SPRESC_REG S_PRESC;      /* offset: 0xab */
    union CANFD_FSeg1_REG F_Seg_1;       /* offset: 0xac */
    union CANFD_FSeg2_REG F_Seg_2;       /* offset: 0xad */
    union CANFD_FSJW_REG F_SJW;          /* offset: 0xae */
    union CANFD_FPRESC_REG F_PRESC;      /* offset: 0xaf */
    union CANFD_EALCAP_REG EALCAP;       /* offset: 0xb0 */
    union CANFD_TDC_REG TDC;             /* offset: 0xb1 */
    union CANFD_RECNT_REG RECNT;         /* offset: 0xb2 */
    union CANFD_TECNT_REG TECNT;         /* offset: 0xb3 */
    union CANFD_ACFCTRL_REG ACFCTRL;     /* offset: 0xb4 */
    union CANFD_TIMECFG_REG TIMECFG;     /* offset: 0xb5 */
    union CANFD_ACFEN0_REG ACF_EN_0;     /* offset: 0xb6 */
    union CANFD_ACFEN1_REG ACF_EN_1;     /* offset: 0xb7 */
    union CANFD_ACF_REG ACF;             /* offset: 0xb8-0xbb */
    union CANFD_VER0_REG VER_0;          /* offset: 0xbc */
    union CANFD_VER1_REG VER_1;          /* offset: 0xbd */
    union CANFD_TBSLOT_REG TBSLOT;       /* offset: 0xbe */
    union CANFD_TTCFG_REG TTCFG;         /* offset: 0xbf */
    union CANFD_REFMSG0_REG REF_MSG_0;   /* offset: 0xc0 */
    union CANFD_REFMSG1_REG REF_MSG_1;   /* offset: 0xc1 */
    union CANFD_REFMSG2_REG REF_MSG_2;   /* offset: 0xc2 */
    union CANFD_REFMSG3_REG REF_MSG_3;   /* offset: 0xc3 */
    union CANFD_TRIGCFG0_REG TRIG_CFG_0; /* offset: 0xc4 */
    union CANFD_TRIGCFG1_REG TRIG_CFG_1; /* offset: 0xc5 */
    union CANFD_TTTRIG0_REG TT_TRIG_0;   /* offset: 0xc6 */
    union CANFD_TTTRIG1_REG TT_TRIG_1;   /* offset: 0xc7 */
    union CANFD_TTWTRIG0_REG TT_WTRIG_0; /* offset: 0xc8 */
    union CANFD_TTWTRIG1_REG TT_WTRIG_1; /* offset: 0xc9 */
    Uint8 rsvd1;                         /* offset: 0xca */
    Uint8 rsvd2;                         /* offset: 0xcb */
};

extern volatile struct CAN_REGS CanaRegs;
extern volatile struct CAN_REGS CanbRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

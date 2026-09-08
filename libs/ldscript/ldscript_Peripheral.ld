MEMORY
{
  PIECTRL       : ORIGIN = 0x007F0100, LENGTH = 0x100
  PIEVECTTABLE0 : ORIGIN = 0x0000FC00, LENGTH = 0x400
  PIEVECTTABLE1 : ORIGIN = 0x00077C00, LENGTH = 0x400
  DEBUG         : ORIGIN = 0x007F0200, LENGTH = 0x100
  CPUTIMER0     : ORIGIN = 0x007F0300, LENGTH = 0x20
  CPUTIMER1     : ORIGIN = 0x007F0320, LENGTH = 0x20
  CPUTIMER2     : ORIGIN = 0x007F0340, LENGTH = 0x20
  CR            : ORIGIN = 0x007F0400, LENGTH = 0x100
  GR            : ORIGIN = 0x007F0500, LENGTH = 0x100
  MOB           : ORIGIN = 0x007F0600, LENGTH = 0x100
  EXP           : ORIGIN = 0x007F0700, LENGTH = 0x100
  WD            : ORIGIN = 0x007F0800, LENGTH = 0x100
  IPCEVENT      : ORIGIN = 0x007F0900, LENGTH = 0x100
  IPCCMD        : ORIGIN = 0x007F0A00, LENGTH = 0x100
  VCU           : ORIGIN = 0x007F0B00, LENGTH = 0x100
  TRACE_BUFFER  : ORIGIN = 0x007F0C00, LENGTH = 0x100
  WATCH_POINT   : ORIGIN = 0x007F0D00, LENGTH = 0x100
  ECC           : ORIGIN = 0x007F0E00, LENGTH = 0x100
  ERADGLOBAL    : ORIGIN = 0x007F0F00, LENGTH = 0x100
  ERADHWBP1     : ORIGIN = 0x007F1000, LENGTH = 0x100
  ERADHWBP2     : ORIGIN = 0x007F1100, LENGTH = 0x100
  ERADHWBP3     : ORIGIN = 0x007F1200, LENGTH = 0x100
  ERADHWBP4     : ORIGIN = 0x007F1300, LENGTH = 0x100
  ERADHWBP5     : ORIGIN = 0x007F1400, LENGTH = 0x100
  ERADHWBP6     : ORIGIN = 0x007F1500, LENGTH = 0x100
  ERADHWBP7     : ORIGIN = 0x007F1600, LENGTH = 0x100
  ERADHWBP8     : ORIGIN = 0x007F1700, LENGTH = 0x100
  ERADCOUNTER1  : ORIGIN = 0x007F1800, LENGTH = 0x100
  ERADCOUNTER2  : ORIGIN = 0x007F1900, LENGTH = 0x100
  ERADCOUNTER3  : ORIGIN = 0x007F1A00, LENGTH = 0x100
  ERADCOUNTER4  : ORIGIN = 0x007F1B00, LENGTH = 0x100
  CLKCFG        : ORIGIN = 0x01000000, LENGTH = 0x200
  CPUSYS        : ORIGIN = 0x01001000, LENGTH = 0x400
  DEVCFG        : ORIGIN = 0x01001000, LENGTH = 0x400
  XINT          : ORIGIN = 0x010011B0, LENGTH = 0x50
  NMIINTRUPT    : ORIGIN = 0x01001200, LENGTH = 0x100
  DCC0          : ORIGIN = 0x01002000, LENGTH = 0x1000
  DMA           : ORIGIN = 0x01003000, LENGTH = 0x1000
  DMACH1        : ORIGIN = 0x01003100, LENGTH = 0x100
  DMACH2        : ORIGIN = 0x01003200, LENGTH = 0x100
  DMACH3        : ORIGIN = 0x01003300, LENGTH = 0x100
  DMACH4        : ORIGIN = 0x01003400, LENGTH = 0x100
  DMACH5        : ORIGIN = 0x01003500, LENGTH = 0x100
  DMACH6        : ORIGIN = 0x01003600, LENGTH = 0x100
  ANALOGSUBSYS  : ORIGIN = 0x01004000, LENGTH = 0x1000
  REGFILE       : ORIGIN = 0x01005000, LENGTH = 0x1000
  DCSMBANK0Z1   : ORIGIN = 0x01006000, LENGTH = 0x800
  DCSMBANK0Z2   : ORIGIN = 0x01006800, LENGTH = 0x800
  DCSMCOMMON    : ORIGIN = 0x01007000, LENGTH = 0x1000
  DCSMBANK1Z1   : ORIGIN = 0x01008000, LENGTH = 0x800
  DCSMBANK1Z2   : ORIGIN = 0x01008800, LENGTH = 0x800
  ECAP1         : ORIGIN = 0x01010000, LENGTH = 0x80
  ECAP2         : ORIGIN = 0x01010080, LENGTH = 0x80
  ECAP3         : ORIGIN = 0x01010100, LENGTH = 0x80
  ECAP4         : ORIGIN = 0x01010180, LENGTH = 0x80
  ECAP5         : ORIGIN = 0x01010200, LENGTH = 0x80
  ECAP6         : ORIGIN = 0x01010280, LENGTH = 0x40
  HRCAP6        : ORIGIN = 0x010102C0, LENGTH = 0x40
  ECAP7         : ORIGIN = 0x01010300, LENGTH = 0x40
  HRCAP7        : ORIGIN = 0x01010340, LENGTH = 0x40
  SYNCSOC       : ORIGIN = 0x01010380, LENGTH = 0x80
  SFO           : ORIGIN = 0x01010400, LENGTH = 0x80
  SFOHHR        : ORIGIN = 0x01010480, LENGTH = 0x80
  EPWM1         : ORIGIN = 0x01012000, LENGTH = 0x200
  EPWM2         : ORIGIN = 0x01012200, LENGTH = 0x200
  EPWM3         : ORIGIN = 0x01012400, LENGTH = 0x200
  EPWM4         : ORIGIN = 0x01012600, LENGTH = 0x200
  EPWM5         : ORIGIN = 0x01012800, LENGTH = 0x200
  EPWM6         : ORIGIN = 0x01012A00, LENGTH = 0x200
  EPWM7         : ORIGIN = 0x01012C00, LENGTH = 0x200
  EPWM8         : ORIGIN = 0x01012E00, LENGTH = 0x200
  EPWM9         : ORIGIN = 0x01013000, LENGTH = 0x200
  EPWM10        : ORIGIN = 0x01013200, LENGTH = 0x200
  EPWM11        : ORIGIN = 0x01013400, LENGTH = 0x200
  EPWM12        : ORIGIN = 0x01013600, LENGTH = 0x200
  EQEP1         : ORIGIN = 0x01014000, LENGTH = 0x800
  EQEP2         : ORIGIN = 0x01014800, LENGTH = 0x800
  PGA1          : ORIGIN = 0x01016000, LENGTH = 0x20
  PGA2          : ORIGIN = 0x01016020, LENGTH = 0x20
  PGA3          : ORIGIN = 0x01016040, LENGTH = 0x20
  PGA4          : ORIGIN = 0x01016060, LENGTH = 0x20
  PGA5          : ORIGIN = 0x01016080, LENGTH = 0x20
  PGA6          : ORIGIN = 0x010160A0, LENGTH = 0x20
  PGA7          : ORIGIN = 0x010160C0, LENGTH = 0x20
  DAC_A         : ORIGIN = 0x01018000, LENGTH = 0x40
  DAC_B         : ORIGIN = 0x01018040, LENGTH = 0x40
  CMPSS1        : ORIGIN = 0x0101A000, LENGTH = 0x100
  CMPSS2        : ORIGIN = 0x0101A100, LENGTH = 0x100
  CMPSS3        : ORIGIN = 0x0101A200, LENGTH = 0x100
  CMPSS4        : ORIGIN = 0x0101A300, LENGTH = 0x100
  CMPSS5        : ORIGIN = 0x0101A400, LENGTH = 0x100
  CMPSS6        : ORIGIN = 0x0101A500, LENGTH = 0x100
  CMPSS7        : ORIGIN = 0x0101A600, LENGTH = 0x100
  ADCARESULT    : ORIGIN = 0x01020110, LENGTH = 0x200
  ADCBRESULT    : ORIGIN = 0x01020310, LENGTH = 0x200
  ADCCRESULT    : ORIGIN = 0x01020510, LENGTH = 0x200
  ADCGRESULT    : ORIGIN = 0x01020710, LENGTH = 0x200
  ADCHRESULT    : ORIGIN = 0x01020910, LENGTH = 0x200
  HRADCARESULT  : ORIGIN = 0x01022100, LENGTH = 0x400
  HRADCBRESULT  : ORIGIN = 0x01022500, LENGTH = 0x400
  HRADCCRESULT  : ORIGIN = 0x01022900, LENGTH = 0x400
  ADC_A         : ORIGIN = 0x01030000, LENGTH = 0x200
  ADC_B         : ORIGIN = 0x01030200, LENGTH = 0x200
  ADC_C         : ORIGIN = 0x01030400, LENGTH = 0x200
  ADC_G         : ORIGIN = 0x01030600, LENGTH = 0x200
  ADC_H         : ORIGIN = 0x01030800, LENGTH = 0x200
  HRADC_A       : ORIGIN = 0x01032000, LENGTH = 0x200
  HRADC_B       : ORIGIN = 0x01032400, LENGTH = 0x200
  HRADC_C       : ORIGIN = 0x01032800, LENGTH = 0x200
  GPIODATA      : ORIGIN = 0x01040000, LENGTH = 0x1000
  GPIOCTRL      : ORIGIN = 0x01050000, LENGTH = 0x1000
  INPUTXBAR     : ORIGIN = 0x01051000, LENGTH = 0x1000
  OUTPUTXBAR    : ORIGIN = 0x01052000, LENGTH = 0x1000
  EPWMXBAR      : ORIGIN = 0x01053000, LENGTH = 0x1000
  XBAR          : ORIGIN = 0x01054000, LENGTH = 0x1000
  SPIA          : ORIGIN = 0x01060000, LENGTH = 0x1000
  SPIB          : ORIGIN = 0x01061000, LENGTH = 0x1000
  PMBUSA        : ORIGIN = 0x01062000, LENGTH = 0x1000
  FSIRXA        : ORIGIN = 0x01063000, LENGTH = 0x1000
  FSITXA        : ORIGIN = 0x01064000, LENGTH = 0x1000
  LINA          : ORIGIN = 0x01070000, LENGTH = 0x1000
  SCIC          : ORIGIN = 0x01070000, LENGTH = 0x1000
  SCIA          : ORIGIN = 0x01080000, LENGTH = 0x1000
  SCIB          : ORIGIN = 0x01081000, LENGTH = 0x1000
  I2CA          : ORIGIN = 0x01082000, LENGTH = 0x1000
  CANA          : ORIGIN = 0x01090000, LENGTH = 0x1000
  CANB          : ORIGIN = 0x01091000, LENGTH = 0x1000
  SDFM          : ORIGIN = 0x010A0000, LENGTH = 0x1000
  XINTFA        : ORIGIN = 0x20000000, LENGTH = 0x1000
  IPCCPU1RAM    : ORIGIN = 0x00100000, LENGTH = 0x1000
  IPCCPU2RAM    : ORIGIN = 0x00101000, LENGTH = 0x1000
  FLASH0CTRL    : ORIGIN = 0x010B0000, LENGTH = 0x1000
}

SECTIONS
{
    PieCtrlRegsFile(NOLOAD)       : { KEEP(*(PieCtrlRegsFile)) }       > PIECTRL
    PieVectTable0File(NOLOAD)     : { KEEP(*(PieVectTable0File)) }     > PIEVECTTABLE0
    PieVectTable1File(NOLOAD)     : { KEEP(*(PieVectTable1File)) }     > PIEVECTTABLE1
    CpuTimer0RegsFile(NOLOAD)     : { KEEP(*(CpuTimer0RegsFile)) }     > CPUTIMER0
    CpuTimer1RegsFile(NOLOAD)     : { KEEP(*(CpuTimer1RegsFile)) }     > CPUTIMER1
    CpuTimer2RegsFile(NOLOAD)     : { KEEP(*(CpuTimer2RegsFile)) }     > CPUTIMER2
    ExpRegsFile(NOLOAD)           : { KEEP(*(ExpRegsFile)) }           > EXP
    WdRegsFile(NOLOAD)            : { KEEP(*(WdRegsFile)) }            > WD
    IpcEventRegsFile(NOLOAD)      : { KEEP(*(IpcEventRegsFile)) }      > IPCEVENT
    IpcCmdRegsFile(NOLOAD)        : { KEEP(*(IpcCmdRegsFile)) }        > IPCCMD
    TraceBufferRegsFile(NOLOAD)   : { KEEP(*(TraceBufferRegsFile)) }   > TRACE_BUFFER
    WatchPointRegsFile(NOLOAD)    : { KEEP(*(WatchPointRegsFile)) }    > WATCH_POINT
    EccRegsFile(NOLOAD)           : { KEEP(*(EccRegsFile)) }           > ECC
    EradGlobalRegsFile(NOLOAD)    : { KEEP(*(EradGlobalRegsFile)) }    > ERADGLOBAL
    EradHWBP1RegsFile(NOLOAD)     : { KEEP(*(EradHWBP1RegsFile)) }     > ERADHWBP1
    EradHWBP2RegsFile(NOLOAD)     : { KEEP(*(EradHWBP2RegsFile)) }     > ERADHWBP2
    EradHWBP3RegsFile(NOLOAD)     : { KEEP(*(EradHWBP3RegsFile)) }     > ERADHWBP3
    EradHWBP4RegsFile(NOLOAD)     : { KEEP(*(EradHWBP4RegsFile)) }     > ERADHWBP4
    EradHWBP5RegsFile(NOLOAD)     : { KEEP(*(EradHWBP5RegsFile)) }     > ERADHWBP5
    EradHWBP6RegsFile(NOLOAD)     : { KEEP(*(EradHWBP6RegsFile)) }     > ERADHWBP6
    EradHWBP7RegsFile(NOLOAD)     : { KEEP(*(EradHWBP7RegsFile)) }     > ERADHWBP7
    EradHWBP8RegsFile(NOLOAD)     : { KEEP(*(EradHWBP8RegsFile)) }     > ERADHWBP8
    EradCounter1RegsFile(NOLOAD)  : { KEEP(*(EradCounter1RegsFile)) }  > ERADCOUNTER1
    EradCounter2RegsFile(NOLOAD)  : { KEEP(*(EradCounter2RegsFile)) }  > ERADCOUNTER2
    EradCounter3RegsFile(NOLOAD)  : { KEEP(*(EradCounter3RegsFile)) }  > ERADCOUNTER3
    EradCounter4RegsFile(NOLOAD)  : { KEEP(*(EradCounter4RegsFile)) }  > ERADCOUNTER4
    ClkCfgRegsFile(NOLOAD)        : { KEEP(*(ClkCfgRegsFile)) }        > CLKCFG
    CpuSysRegsFile(NOLOAD)        : { KEEP(*(CpuSysRegsFile)) }        > CPUSYS
    DevCfgRegsFile(NOLOAD)        : { KEEP(*(DevCfgRegsFile)) }        > DEVCFG
    XintRegsFile(NOLOAD)          : { KEEP(*(XintRegsFile)) }          > XINT
    NmiIntruptRegsFile(NOLOAD)    : { KEEP(*(NmiIntruptRegsFile)) }    > NMIINTRUPT
    Dcc0RegsFile(NOLOAD)          : { KEEP(*(Dcc0RegsFile)) }          > DCC0
    DmaRegsFile(NOLOAD)           : { KEEP(*(DmaRegsFile)) }           > DMA
    DmaCh1RegsFile(NOLOAD)        : { KEEP(*(DmaCH1RegsFile)) }        > DMACH1
    DmaCh2RegsFile(NOLOAD)        : { KEEP(*(DmaCH2RegsFile)) }        > DMACH2
    DmaCh3RegsFile(NOLOAD)        : { KEEP(*(DmaCH3RegsFile)) }        > DMACH3
    DmaCh4RegsFile(NOLOAD)        : { KEEP(*(DmaCH4RegsFile)) }        > DMACH4
    DmaCh5RegsFile(NOLOAD)        : { KEEP(*(DmaCH5RegsFile)) }        > DMACH5
    DmaCh6RegsFile(NOLOAD)        : { KEEP(*(DmaCH6RegsFile)) }        > DMACH6
    AnalogSubsysRegsFile(NOLOAD)  : { KEEP(*(AnalogSubsysRegsFile)) }  > ANALOGSUBSYS
    DcsmBank0Z1RegsFile(NOLOAD)   : { KEEP(*(DcsmBank0Z1RegsFile)) }   > DCSMBANK0Z1
    DcsmBank0Z2RegsFile(NOLOAD)   : { KEEP(*(DcsmBank0Z2RegsFile)) }   > DCSMBANK0Z2
    DcsmCommonRegsFile(NOLOAD)    : { KEEP(*(DcsmCommonRegs)) }        > DCSMCOMMON
    DcsmBank1Z1RegsFile(NOLOAD)   : { KEEP(*(DcsmBank1Z1RegsFile)) }   > DCSMBANK1Z1
    DcsmBank1Z2RegsFile(NOLOAD)   : { KEEP(*(DcsmBank1Z2RegsFile)) }   > DCSMBANK1Z2
    ECap1RegsFile(NOLOAD)         : { KEEP(*(ECap1RegsFile)) }         > ECAP1
    ECap2RegsFile(NOLOAD)         : { KEEP(*(ECap2RegsFile)) }         > ECAP2
    ECap3RegsFile(NOLOAD)         : { KEEP(*(ECap3RegsFile)) }         > ECAP3
    ECap4RegsFile(NOLOAD)         : { KEEP(*(ECap4RegsFile)) }         > ECAP4
    ECap5RegsFile(NOLOAD)         : { KEEP(*(ECap5RegsFile)) }         > ECAP5
    ECap6RegsFile(NOLOAD)         : { KEEP(*(ECap6RegsFile)) }         > ECAP6
    HRCap6RegsFile(NOLOAD)        : { KEEP(*(HRCap6RegsFile)) }        > HRCAP6
    ECap7RegsFile(NOLOAD)         : { KEEP(*(ECap7RegsFile)) }         > ECAP7
    HRCap7RegsFile(NOLOAD)        : { KEEP(*(HRCap7RegsFile)) }        > HRCAP7
    SyncSocRegsFile(NOLOAD)       : { KEEP(*(SyncSocRegsFile)) }       > SYNCSOC
    SFORegsFile(NOLOAD)           : { KEEP(*(SFORegsFile)) }           > SFO
    SFOHHRRegsFile(NOLOAD)        : { KEEP(*(SFOHHRRegsFile)) }        > SFOHHR
    EPwm1RegsFile(NOLOAD)         : { KEEP(*(EPwm1RegsFile)) }         > EPWM1
    EPwm2RegsFile(NOLOAD)         : { KEEP(*(EPwm2RegsFile)) }         > EPWM2
    EPwm3RegsFile(NOLOAD)         : { KEEP(*(EPwm3RegsFile)) }         > EPWM3
    EPwm4RegsFile(NOLOAD)         : { KEEP(*(EPwm4RegsFile)) }         > EPWM4
    EPwm5RegsFile(NOLOAD)         : { KEEP(*(EPwm5RegsFile)) }         > EPWM5
    EPwm6RegsFile(NOLOAD)         : { KEEP(*(EPwm6RegsFile)) }         > EPWM6
    EPwm7RegsFile(NOLOAD)         : { KEEP(*(EPwm7RegsFile)) }         > EPWM7
    EPwm8RegsFile(NOLOAD)         : { KEEP(*(EPwm8RegsFile)) }         > EPWM8
    EPwm9RegsFile(NOLOAD)         : { KEEP(*(EPwm9RegsFile)) }         > EPWM9
    EPwm10RegsFile(NOLOAD)        : { KEEP(*(EPwm10RegsFile)) }        > EPWM10
    EPwm11RegsFile(NOLOAD)        : { KEEP(*(EPwm11RegsFile)) }        > EPWM11
    EPwm12RegsFile(NOLOAD)        : { KEEP(*(EPwm12RegsFile)) }        > EPWM12
    EQep1RegsFile(NOLOAD)         : { KEEP(*(EQep1RegsFile)) }         > EQEP1
    EQep2RegsFile(NOLOAD)         : { KEEP(*(EQep2RegsFile)) }         > EQEP2
    Pga1RegsFile(NOLOAD)          : { KEEP(*(Pga1RegsFile)) }          > PGA1
    Pga2RegsFile(NOLOAD)          : { KEEP(*(Pga2RegsFile)) }          > PGA2
    Pga3RegsFile(NOLOAD)          : { KEEP(*(Pga3RegsFile)) }          > PGA3
    Pga4RegsFile(NOLOAD)          : { KEEP(*(Pga4RegsFile)) }          > PGA4
    Pga5RegsFile(NOLOAD)          : { KEEP(*(Pga5RegsFile)) }          > PGA5
    Pga6RegsFile(NOLOAD)          : { KEEP(*(Pga6RegsFile)) }          > PGA6
    Pga7RegsFile(NOLOAD)          : { KEEP(*(Pga7RegsFile)) }          > PGA7
    DacaRegsFile(NOLOAD)          : { KEEP(*(DacaRegsFile)) }          > DAC_A
    DacbRegsFile(NOLOAD)          : { KEEP(*(DacbRegsFile)) }          > DAC_B
    Cmpss1RegsFile(NOLOAD)        : { KEEP(*(Cmpss1RegsFile)) }        > CMPSS1
    Cmpss2RegsFile(NOLOAD)        : { KEEP(*(Cmpss2RegsFile)) }        > CMPSS2
    Cmpss3RegsFile(NOLOAD)        : { KEEP(*(Cmpss3RegsFile)) }        > CMPSS3
    Cmpss4RegsFile(NOLOAD)        : { KEEP(*(Cmpss4RegsFile)) }        > CMPSS4
    Cmpss5RegsFile(NOLOAD)        : { KEEP(*(Cmpss5RegsFile)) }        > CMPSS5
    Cmpss6RegsFile(NOLOAD)        : { KEEP(*(Cmpss6RegsFile)) }        > CMPSS6
    Cmpss7RegsFile(NOLOAD)        : { KEEP(*(Cmpss7RegsFile)) }        > CMPSS7
    AdcbResultRegsFile(NOLOAD)    : { KEEP(*(AdcbResultRegsFile)) }    > ADCBRESULT
    AdcaResultRegsFile(NOLOAD)    : { KEEP(*(AdcaResultRegsFile)) }    > ADCARESULT
    AdccResultRegsFile(NOLOAD)    : { KEEP(*(AdccResultRegsFile)) }    > ADCCRESULT
    AdcgResultRegsFile(NOLOAD)    : { KEEP(*(AdcgResultRegsFile)) }    > ADCGRESULT
    AdchResultRegsFile(NOLOAD)    : { KEEP(*(AdchResultRegsFile)) }    > ADCHRESULT
    HrAdcaResultRegsFile(NOLOAD)  : { KEEP(*(HrAdcaResultRegsFile)) }  > HRADCARESULT
    HrAdcbResultRegsFile(NOLOAD)  : { KEEP(*(HrAdcbResultRegsFile)) }  > HRADCBRESULT
    HrAdccResultRegsFile(NOLOAD)  : { KEEP(*(HrAdccResultRegsFile)) }  > HRADCCRESULT
    AdcaRegsFile(NOLOAD)          : { KEEP(*(AdcaRegsFile)) }          > ADC_A
    AdcbRegsFile(NOLOAD)          : { KEEP(*(AdcbRegsFile)) }          > ADC_B
    AdccRegsFile(NOLOAD)          : { KEEP(*(AdccRegsFile)) }          > ADC_C
    AdcgRegsFile(NOLOAD)          : { KEEP(*(AdcgRegsFile)) }          > ADC_G
    AdchRegsFile(NOLOAD)          : { KEEP(*(AdchRegsFile)) }          > ADC_H
    HrAdcaRegsFile(NOLOAD)        : { KEEP(*(HrAdcaRegsFile)) }        > HRADC_A
    HrAdcbRegsFile(NOLOAD)        : { KEEP(*(HrAdcbRegsFile)) }        > HRADC_B
    HrAdccRegsFile(NOLOAD)        : { KEEP(*(HrAdccRegsFile)) }        > HRADC_C
    GpioDataRegsFile(NOLOAD)      : { KEEP(*(GpioDataRegsFile)) }      > GPIODATA
    GpioCtrlRegsFile(NOLOAD)      : { KEEP(*(GpioCtrlRegsFile)) }      > GPIOCTRL
    InputXbarRegsFile(NOLOAD)     : { KEEP(*(InputXbarRegsFile)) }     > INPUTXBAR
    OutputXbarRegsFile(NOLOAD)    : { KEEP(*(OutputXbarRegsFile)) }    > OUTPUTXBAR
    EPwmXbarRegsFile(NOLOAD)      : { KEEP(*(EPwmXbarRegsFile)) }      > EPWMXBAR
    XbarRegsFile(NOLOAD)          : { KEEP(*(XbarRegsFile)) }          > XBAR
    SpiaRegsFile(NOLOAD)          : { KEEP(*(SpiaRegsFile)) }          > SPIA
    SpibRegsFile(NOLOAD)          : { KEEP(*(SpibRegsFile)) }          > SPIB
    PmbusaRegsFile(NOLOAD)        : { KEEP(*(PmbusaRegsFile)) }        > PMBUSA
    FsiRxaRegsFile(NOLOAD)        : { KEEP(*(FsiRxaRegsFile)) }        > FSIRXA
    FsiTxaRegsFile(NOLOAD)        : { KEEP(*(FsiTxaRegsFile)) }        > FSITXA
    LinaRegsFile(NOLOAD)          : { KEEP(*(LinaRegsFile)) }          > LINA
    SciaRegsFile(NOLOAD)          : { KEEP(*(SciaRegsFile)) }          > SCIA
    ScibRegsFile(NOLOAD)          : { KEEP(*(ScibRegsFile)) }          > SCIB
    ScicRegsFile(NOLOAD)          : { KEEP(*(ScicRegsFile)) }          > SCIC
    I2caRegsFile(NOLOAD)          : { KEEP(*(I2caRegsFile)) }          > I2CA
    CanaRegsFile(NOLOAD)          : { KEEP(*(CanaRegsFile)) }          > CANA
    CanbRegsFile(NOLOAD)          : { KEEP(*(CanbRegsFile)) }          > CANB
    Sdfm1RegsFile(NOLOAD)         : { KEEP(*(Sdfm1RegsFile)) }         > SDFM
    XintfaRegsFile(NOLOAD)        : { KEEP(*(XintfaRegsFile)) }        > XINTFA
    MsgRamCpu1ToCpu2File(NOLOAD)  : { KEEP(*(MsgRamCpu1ToCpu2File)) }  > IPCCPU1RAM
    MsgRamCpu2ToCpu1File(NOLOAD)  : { KEEP(*(MsgRamCpu2ToCpu1File)) }  > IPCCPU2RAM
    Flash0CtrlRegsFile(NOLOAD)    : { KEEP(*(Flash0CtrlRegsFile)) }    > FLASH0CTRL
}

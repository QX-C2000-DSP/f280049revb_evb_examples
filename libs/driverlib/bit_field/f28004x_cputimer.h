#ifndef F28004X_CPUTIMER_H
#define F28004X_CPUTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// CPUTIMER Individual Register Bit Definitions:

struct TIM_BITS
{                    // bits description
    Uint32 LSW : 16; // 15:0 CPU-Timer Counter Registers
    Uint32 MSW : 16; // 31:16 CPU-Timer Counter Registers High
};

union TIM_REG
{
    Uint32 all;
    struct TIM_BITS bit;
};

struct PRD_BITS
{                    // bits description
    Uint32 LSW : 16; // 15:0 CPU-Timer Period Registers
    Uint32 MSW : 16; // 31:16 CPU-Timer Period Registers High
};

union PRD_REG
{
    Uint32 all;
    struct PRD_BITS bit;
};

struct TCR_BITS
{                     // bits description
    Uint32 rsvd1 : 4; // 3:0 Reserved
    Uint32 TSS   : 1; // 4 CPU-Timer stop status bit.
    Uint32 TRB   : 1; // 5 Timer reload
    Uint32 rsvd2 : 4; // 9:6 Reserved
    Uint32 SOFT  : 1; // 10 Emulation modes
    Uint32 FREE  : 1; // 11 Emulation modes
    Uint32 rsvd3 : 2; // 13:12 Reserved
    Uint32 TIE   : 1; // 14 CPU-Timer Interrupt Enable.
    Uint32 TIF   : 1; // 15 CPU-Timer Interrupt Flag.
};

union TCR_REG
{
    Uint32 all;
    struct TCR_BITS bit;
};

struct TPR_BITS
{                    // bits description
    Uint32 TDDR : 8; // 7:0 CPU-Timer Divide-Down.
    Uint32 PSC  : 8; // 15:8 CPU-Timer Prescale Counter.
};

union TPR_REG
{
    Uint32 all;
    struct TPR_BITS bit;
};

struct TPRH_BITS
{                     // bits description
    Uint32 TDDRH : 8; // 7:0 CPU-Timer Divide-Down.
    Uint32 PSCH  : 8; // 15:8 CPU-Timer Prescale Counter.
};

union TPRH_REG
{
    Uint32 all;
    struct TPRH_BITS bit;
};

struct CPUTIMER_REGS
{
    union TIM_REG TIM;   // CPU-Timer, Counter Register
    union PRD_REG PRD;   // CPU-Timer, Period Register
    union TCR_REG TCR;   // CPU-Timer, Control Register
    union TPR_REG TPR;   // CPU-Timer, Prescale Register
    union TPRH_REG TPRH; // CPU-Timer, Prescale Register High
};

//---------------------------------------------------------------------------
// CPUTIMER External References & Function Declarations:
//
extern volatile struct CPUTIMER_REGS CpuTimer0Regs;
extern volatile struct CPUTIMER_REGS CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS CpuTimer2Regs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================

#ifndef F28004X_INPUT_XBAR_H
#define F28004X_INPUT_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// INPUT_XBAR Individual Register Bit Definitions:

struct INPUTSELECTLOCK_BITS
{                              // bits description
    Uint32 INPUT1SELECT  : 1;  // 0 Lock bit for INPUT1SELECT Register
    Uint32 INPUT2SELECT  : 1;  // 1 Lock bit for INPUT2SELECT Register
    Uint32 INPUT3SELECT  : 1;  // 2 Lock bit for INPUT3SELECT Register
    Uint32 INPUT4SELECT  : 1;  // 3 Lock bit for INPUT4SELECT Register
    Uint32 INPUT5SELECT  : 1;  // 4 Lock bit for INPUT5SELECT Register
    Uint32 INPUT6SELECT  : 1;  // 5 Lock bit for INPUT6SELECT Register
    Uint32 INPUT7SELECT  : 1;  // 6 Lock bit for INPUT7SELECT Register
    Uint32 INPUT8SELECT  : 1;  // 7 Lock bit for INPUT8SELECT Register
    Uint32 INPUT9SELECT  : 1;  // 8 Lock bit for INPUT9SELECT Register
    Uint32 INPUT10SELECT : 1;  // 9 Lock bit for INPUT10SELECT Register
    Uint32 INPUT11SELECT : 1;  // 10 Lock bit for INPUT11SELECT Register
    Uint32 INPUT12SELECT : 1;  // 11 Lock bit for INPUT12SELECT Register
    Uint32 INPUT13SELECT : 1;  // 12 Lock bit for INPUT13SELECT Register
    Uint32 INPUT14SELECT : 1;  // 13 Lock bit for INPUT14SELECT Register
    Uint32 INPUT15SELECT : 1;  // 14 Lock bit for INPUT15SELECT Register
    Uint32 INPUT16SELECT : 1;  // 15 Lock bit for INPUT16SELECT Register
    Uint32 rsvd1         : 16; // 31:16 Reserved
};

union INPUTSELECTLOCK_REG
{
    Uint32 all;
    struct INPUTSELECTLOCK_BITS bit;
};

struct INPUT_XBAR_REGS
{
    Uint32 INPUT1SELECT;                       // INPUT1 Input Select Register (GPIO0 to x)
    Uint32 INPUT2SELECT;                       // INPUT2 Input Select Register (GPIO0 to x)
    Uint32 INPUT3SELECT;                       // INPUT3 Input Select Register (GPIO0 to x)
    Uint32 INPUT4SELECT;                       // INPUT4 Input Select Register (GPIO0 to x)
    Uint32 INPUT5SELECT;                       // INPUT5 Input Select Register (GPIO0 to x)
    Uint32 INPUT6SELECT;                       // INPUT6 Input Select Register (GPIO0 to x)
    Uint32 INPUT7SELECT;                       // INPUT7 Input Select Register (GPIO0 to x)
    Uint32 INPUT8SELECT;                       // INPUT8 Input Select Register (GPIO0 to x)
    Uint32 INPUT9SELECT;                       // INPUT9 Input Select Register (GPIO0 to x)
    Uint32 INPUT10SELECT;                      // INPUT10 Input Select Register (GPIO0 to x)
    Uint32 INPUT11SELECT;                      // INPUT11 Input Select Register (GPIO0 to x)
    Uint32 INPUT12SELECT;                      // INPUT12 Input Select Register (GPIO0 to x)
    Uint32 INPUT13SELECT;                      // INPUT13 Input Select Register (GPIO0 to x)
    Uint32 INPUT14SELECT;                      // INPUT14 Input Select Register (GPIO0 to x)
    Uint32 INPUT15SELECT;                      // INPUT15 Input Select Register (GPIO0 to x)
    Uint32 INPUT16SELECT;                      // INPUT16 Input Select Register (GPIO0 to x)
    union INPUTSELECTLOCK_REG INPUTSELECTLOCK; // Input Select Lock Register
};

//---------------------------------------------------------------------------
// INPUT_XBAR External References & Function Declarations:
//
extern volatile struct INPUT_XBAR_REGS InputXbarRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================

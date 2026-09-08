#ifndef BOARD_H_
#define BOARD_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CAN Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init();
void CAN_init();
void INTERRUPT_init();
void PinMux_init();
void CAN_setBusTimingSlow(uint32_t base, u32 s_prescale, u32 s_sjw, u32 s_seg1, u32 s_seg2);
void verify_data_byte(void *buf1, void *buf2, u32 len);
void simple_delay(u32 count);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif


#endif /* BOARD_H_ */

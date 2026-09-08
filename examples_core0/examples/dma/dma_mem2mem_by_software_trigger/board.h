#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

void Board_init();
void INTERRUPT_init();
void DMA_init();

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */

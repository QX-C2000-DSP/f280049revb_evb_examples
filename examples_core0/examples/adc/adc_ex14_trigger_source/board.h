/*
 * bspcomm.h
 *
 *  Created on: 2024 Aug 22
 *      Author: QX2000
 */

#ifndef BSP_BSPCOMM_H_
#define BSP_BSPCOMM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "device.h"

// #define     ADCSOCSOFTWARE
// #define     ADCSOCTIMER
#define ADCSOCEPWM

#define ADCTIMERPERIOD (40000 - 1)
#define ADCEPWMPERIOD  (20000 - 1)

void AdcInitial(void);

#ifdef __cplusplus
}
#endif

#endif /* BSP_BSPCOMM_H_ */

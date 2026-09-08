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

//
//SCI config
//

//基地址
#define SCI_BASE SCIB_BASE

//管脚
#define SCI_TX_PIN_NUM 12
#define SCI_RX_PIN_NUM 13

//波特率
#define SCI_BAUD_RATE 115200

//数据位，校验位和停止位
#define SCI_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define SCI_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define SCI_CONFIG_PAR  SCI_CONFIG_PAR_NONE

#if (SCI_BASE == SCIA_BASE)

#define _SERIAL_TX_GPIO_CONFIG(x) GPIO_##x##_SCIA_TX
#define _SERIAL_RX_GPIO_CONFIG(x) GPIO_##x##_SCIA_RX

#elif (SCI_BASE == SCIB_BASE)

#define _SERIAL_TX_GPIO_CONFIG(x) GPIO_##x##_SCIB_TX
#define _SERIAL_RX_GPIO_CONFIG(x) GPIO_##x##_SCIB_RX

#elif (SCI_BASE == SCIC_BASE)

#define _SERIAL_TX_GPIO_CONFIG(x) GPIO_##x##_SCIC_TX
#define _SERIAL_RX_GPIO_CONFIG(x) GPIO_##x##_SCIC_RX

#endif

#define SERIAL_TX_GPIO_CONFIG(x) _SERIAL_TX_GPIO_CONFIG(x)
#define SERIAL_RX_GPIO_CONFIG(x) _SERIAL_RX_GPIO_CONFIG(x)

void Board_init();
void PinMux_init();
void INTERRUPT_init();
void SCI_init();

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */

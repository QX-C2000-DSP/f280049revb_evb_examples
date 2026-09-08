/*
 * main.c
 *
 *  Created on: 2025 Jun 11
 *      Author: 00001
 */


//
// Included Files
//
#include "driverlib.h"
#include "device.h"


// 定义 LED 连接的引脚
const int ledPins[] = {5, 9}; //LED对应的GPIO
const int numLeds = 2; // LED 的数量


void setup_led() {
    // 初始化所有 LED 引脚为输出模式
    GPIO_setPinConfig(GPIO_5_GPIO5);
    GPIO_setPinConfig(GPIO_9_GPIO9);
    for (int i = 0; i < numLeds; i++) {
      GPIO_setDirectionMode(ledPins[i], GPIO_DIR_MODE_OUT);
    }
}

//
// Main
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Set up LED
    //
    setup_led();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while (1)
    {
        // 从左到右依次点亮 LED
        for (int i = 0; i < numLeds; i++) {

            GPIO_writePin(ledPins[i], 1);
            DEVICE_DELAY_US(200000);
            GPIO_writePin(ledPins[i], 0);
        }

        // 从右到左依次点亮 LED
        for (int i = numLeds - 1; i >= 0; i--) {

            GPIO_writePin(ledPins[i], 1);
            DEVICE_DELAY_US(200000);
            GPIO_writePin(ledPins[i], 0);
        }
    }
}

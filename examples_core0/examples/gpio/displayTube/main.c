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


// 定义 74HC164 的引脚
const int dataPin = 16;  // 串行数据引脚
const int clockPin = 32; // 时钟引脚
// 定义 FJ3461AH 的位选引脚
const int digitPins[] = {3, 2, 33, 11}; // 位选引脚
const int numDigits = 4; // 数码管的位数

int numDisplay = 1234;


// 初始化函数
void setup_display() {
  // 初始化 74HC164 的引脚
  GPIO_setDirectionMode(dataPin, GPIO_DIR_MODE_OUT);
  GPIO_setDirectionMode(clockPin, GPIO_DIR_MODE_OUT);
  GPIO_MuxConfig(clockPin, GPIO_32_GPIO32, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
  GPIO_MuxConfig(dataPin, GPIO_16_GPIO16, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

  // 初始化 FJ3461AH 的位选引脚
  for (int i = 0; i < numDigits; i++) {
    GPIO_setDirectionMode(digitPins[i], GPIO_DIR_MODE_OUT);
    GPIO_writePin(digitPins[i], 0);// 默认关闭所有位选
  }
}

// 定义数字 0-9 的段选编码（共阳极）
const char digitCode[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// 自定义 shiftOut 函数
void shiftOut(int dataPin, int clockPin, char value) {
  for (int i = 0; i < 8; i++) {
        GPIO_writePin(dataPin, !!(value & (1 << (7 - i)))); // 从最低位开始发送
        // 产生时钟上升沿
        GPIO_writePin(clockPin, 1);
        GPIO_writePin(clockPin, 0);
  }
}

// 显示数字函数
void displayNumber(int number) {
  int digits[numDigits];
  // 分离每一位数字
  digits[0] = number / 1000;       // 千位
  digits[1] = (number / 100) % 10; // 百位
  digits[2] = (number / 10) % 10;  // 十位
  digits[3] = number % 10;         // 个位

  // 依次显示每一位
  for (int i = 0; i < numDigits; i++) {
    // 关闭所有位选
    for (int j = 0; j < numDigits; j++) {
        GPIO_writePin(digitPins[j], 0);
    }
    // 设置段选
    shiftOut(dataPin, clockPin, digitCode[digits[i]]);
    // 打开当前位选
    GPIO_writePin(digitPins[i], 1);
    // 延时一段时间
   DEVICE_DELAY_US(20);
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
    // Set up display
    //
    setup_display();

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
        // 显示数字 1234
        displayNumber(numDisplay);
    }
}

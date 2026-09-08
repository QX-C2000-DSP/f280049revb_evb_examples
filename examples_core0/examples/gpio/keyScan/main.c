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


// 按键映射表（根据实际布局修改）
const char KeyMap[2][2] = {
    {'1','3'},
    {'2','4'},
};


char last_key = 0;

// 初始化函数
void Keypad_Init(void) {


    // 配置行线（推挽输出）
    GPIO_MuxConfig(4, GPIO_4_GPIO4, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);
    GPIO_MuxConfig(24, GPIO_24_GPIO24, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_OUT);

    // 配置列线（上拉输入）
    GPIO_MuxConfig(8, GPIO_8_GPIO8, GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(8, GPIO_DIR_MODE_IN);
    GPIO_MuxConfig(17, GPIO_17_GPIO17, GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(17, GPIO_DIR_MODE_IN);
}

// 按键扫描函数
char Keypad_Scan(void) {
    uint8_t row, col;
    static uint8_t last_key = 0;
    uint8_t col_state = 0;

    // 扫描所有行
    for(row=0; row<2; row++) {
        // 设置当前行为低电平
        if(row % 2)
        {
            GPIO_writePin(24, 0);
        }
        else
        {
            GPIO_writePin(4, 0);
        }


        // 等待电平稳定
        DEVICE_DELAY_US(10);

        // 读取列状态
        uint8_t col_state = GPIO_readPin(8) << 0 | GPIO_readPin(17) << 1;


        // 检测有效列
        if(col_state != 3) {
            // 去抖动延时
            DEVICE_DELAY_US(10000);

            // 再次检测
            if(col_state != 3) {
                // 确定列位置
                switch(col_state) {
                    case 2 : col=0; break;
                    case 1 : col=1; break;
                    default: return 0;
                }

                // 等待按键释放
                while(!(GPIO_readPin(8) & GPIO_readPin(17)));

                // 返回对应键值
                return KeyMap[row][col];
            }
        }

        // 恢复当前行高电平
        if(row % 2)
        {
            GPIO_writePin(24, 1);
        }
        else
        {
            GPIO_writePin(4, 1);
        }
    }
    return 0;
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
    Keypad_Init();

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
        char key = Keypad_Scan();
        if (key != 0)
        {
            last_key = key;
        }
        DEVICE_DELAY_US(1000);
    }
}

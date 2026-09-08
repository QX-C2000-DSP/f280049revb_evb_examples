// ###########################################################################
//
//  FILE:   ipc_ex1_asin.c
//
//  TITLE:  ipc Arcsine Example
//
//! \addtogroup driver_example_list
//! <h1>CLA \f$arcsine(x)\f$ using a lookup table (cla_asin_cpu01)</h1>
//!
//! In this example, Task  of the cpu2 will calculate the arcsine of
//! an input argument in the range (-1.0 to 1.0) using a lookup table.
//!
//! \b Memory \b Allocation \n
//!  - CPU2 Math Tables
//!    - CLAasinTable - Lookup table
//!  - CPU2 to CPU1 Message RAM
//!    - fResult - Result of the lookup algorithm
//!  - CPU1 to CPU2 Message RAM
//!    - fVal - Sample input to the lookup algorithm
//!
//! \b Watch \b Variables \n
//!  - fVal - Argument to CPU2 task
//!  - fResult - Result of \f$arcsin(fVal)\f$
//!
//
// ###########################################################################
// $Copyright:
// Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
// ###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include <math.h>

//
// Defines
//
#define BUFFER_SIZE    64
#define TABLE_SIZE     64
#define TABLE_SIZE_M_1 TABLE_SIZE - 1
#define PIBYTWO        1.570796327
#define PI             3.141592653589
#define INV2PI         0.159154943

#define SYNC_FLAG IPC_FLAG31

//
// Globals
//

uint8_t Cpu2DoneCnt = 0;

__shared_var_CPU1toCPU2(0) float fVal;     // 定义为CPU1读写，CPU2读的变量
__shared_var_CPU1toCPU2(1) float fVal2;    // 定义为CPU1读写，CPU2读的变量
__shared_var_CPU1toCPU2(2) float fVal3;    // 定义为CPU1读写，CPU2读的变量
__shared_var_CPU1toCPU2(3) float fVal4;    // 定义为CPU1读写，CPU2读的变量
__shared_var_CPU2toCPU1(0) float fResult;  // 定义为CPU2读写，CPU1读的变量
__shared_var_CPU2toCPU1(1) float fResult2; // 定义为CPU2读写，CPU1读的变量
__shared_var_CPU2toCPU1(2) float fResult3; // 定义为CPU2读写，CPU1读的变量
__shared_var_CPU2toCPU1(3) float fResult4; // 定义为CPU2读写，CPU1读的变量

float y[BUFFER_SIZE];

//
// Common (C) Variables
// The Exponential table
//

float asin_expected[BUFFER_SIZE]
    = { 1.570796, 1.393789, 1.320141, 1.263401, 1.215375, 1.172892, 1.134327, 1.098718, 1.065436,
          1.034046, 1.004232, 0.9757544, 0.9484279, 0.9221048, 0.8966658, 0.8720123, 0.8480621,
          0.8247454, 0.8020028, 0.7797828, 0.7580408, 0.7367374, 0.7158381, 0.6953120, 0.6751316,
          0.6552721, 0.6357113, 0.6164289, 0.5974064, 0.5786270, 0.5600753, 0.5417370, 0.5235988,
          0.5056486, 0.4878751, 0.4702678, 0.4528166, 0.4355124, 0.4183464, 0.4013104, 0.3843968,
          0.3675981, 0.3509074, 0.3343180, 0.3178237, 0.3014185, 0.2850964, 0.2688521, 0.2526802,
          0.2365756, 0.2205333, 0.2045484, 0.1886164, 0.1727327, 0.1568929, 0.1410927, 0.1253278,
          0.1095943, 0.09388787, 0.07820469, 0.06254076, 0.04689218, 0.03125509, 0.01562564 };

uint16_t pass = 0;
uint16_t fail = 0;

//
// Function Prototypes
//
void Cpu2_runTest(void);
__interrupt void Cpu2DoneIsr();

//
// Main
//
int main(void)
{

    //
    // Intialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    // Device_initGPIO(); //skipped for this example

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    // Turn on core 2 clock, enable core 2
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU2);

    // Break point debugging here
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, SYNC_FLAG);

    // Interrupt Settings for IPC_0
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_IPC0, &Cpu2DoneIsr);
    Interrupt_enable(INT_IPC0);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Run the test
    //
    Cpu2_runTest();

    for (;;)
    { }
}

//
// Cpu2_runTest
//
void Cpu2_runTest(void)
{
    int16_t i;
    float error;

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        fVal = (float)(BUFFER_SIZE - i) / (float)BUFFER_SIZE;
        IPC_setFlagLtoR(
            IPC_CPU1_L_CPU2_R, IPC_FLAG0); // 触发CPU2中的IPC中断执行，等同于TI触发CLA task执行
        //
        // Wait for acknowledgment
        //
        IPC_waitForAck(IPC_CPU1_L_CPU2_R, IPC_FLAG0); // 等待CPU2 task计算完成
        y[i]  = fResult;
        error = fabsf(asin_expected[i] - y[i]);

        if (error < 0.1f)
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }
}

//
// Cpu2DoneIsr1 （CPU2 task完成中断）
//
__interrupt void Cpu2DoneIsr()
{

    Cpu2DoneCnt++;
    //
    // Acknowledge the flag
    //
    IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG0);
}

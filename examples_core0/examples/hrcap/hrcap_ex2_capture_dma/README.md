# hrcap_ex2_capture_dma.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的hrcap测量结果由DMA来搬运的示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何使用hrcap模块测量hrpwm的频率和占空比，测量结果通过DMA来搬运到RAM中
- 控制pwm1输出频率喝占空比可调的hrpwm波,通过改变freqFine的值来调整pwm的频率，单位为kHZ，通过改变dutyFine的值来调整pwm的占空比，单位为百分比
- 使用hrcap来测量hrpwm的频率和占空比，为了避免频繁进出中断对CPU性能的消耗，hrcap每捕获完一次，触发DMA将结果寄存器中的值搬运到cap3Count和cap4Count中
- 每搬运20次会触发一次DMA done中断，在DMA中断中将dmaDoneFlag置起，可根据此标志位的状态对捕获结果进行处理，处理完成之后再次重启DMA搬运
- SFO校准函数通过定时器中断每10s调用一次
- inputFreqkHz和inputDuty分别为测量的频率和占空比结果

### 外部连接：
- GPIO0 hrPWM1A
- GPIO16 hrcap
- 连接GPIO0和GPIO16
# epwm_ex11_configure_signal.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的控制epwm输出各类波形的示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何对ePWM模块的输出进行配置。
- pwmSignal为epwm输出配置结构体，结构体各元素的定义如下
- freqInHz为pwm频率，单位hz
- dutyValA为ePWMxA的占空比
- dutyValB为ePWMxB的占空比
- invertSignalB控制ePWMxB是否进行翻转
- sysClkInHz 为系统时钟
- tbCtrMode为计数模式
- tbClkDiv为PWM时钟分频
- tbHSClkDiv为PWM时钟分频
- 例程中的默认配置为ePWMxA & ePWMxB输出频率为10khz，占空比为50%的波形，并且对ePWMxB进行翻转，使ePWMxA & ePWMxB形成互补输出
- EPWM2相较于EPWM1移相120度，EPWM3相较于EPWM1移相240度，

### 外部连接：
- GPIO0 EPWM1A
- GPIO1 EPWM1B
- GPIO2 EPWM2A
- GPIO3 EPWM2B
- GPIO4 EPWM3A
- GPIO5 EPWM3B
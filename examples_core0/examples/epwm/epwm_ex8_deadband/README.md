# epwm_ex8_deadband.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的ePWM死区控制示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何使用ePWM模块的DB子模块。
- EPWM1为参考信号，EPWM1未进行任何死区配置，在测试中可以以EPWM1作为参考对比
- 本例中死区输出波形上升下降延迟的来源都来自于EPWMx_A

- EPWM2_A相较于EPWM1_A的输出上升沿延迟时间RED = 400 * TTBCLK(TTBCLK为PWM时基时钟周期)
- EPWM2_B相较于EPWM1_A的输出下降沿延迟时间RED = 200 * TTBCLK
- EPWM2最终输出设置为高有效模式（AH）,EPWM2_A和EPWM2_B均不进行翻转

- EPWM3_A相较于EPWM1_A的输出上升沿延迟时间RED = 400 * TTBCLK(TTBCLK为PWM时基时钟周期)
- EPWM3_B相较于EPWM1_A的输出下降沿延迟时间RED = 200 * TTBCLK
- EPWM3最终输出设置为低有效模式（AL）,EPWM3_A和EPWM3_B均进行翻转

- EPWM4_A相较于EPWM1_A的输出上升沿延迟时间RED = 400 * TTBCLK(TTBCLK为PWM时基时钟周期)
- EPWM4_B相较于EPWM1_A的输出下降沿延迟时间RED = 200 * TTBCLK
- EPWM4最终输出设置为高有效互补模式（AHC）,EPWM4_B进行翻转

- EPWM5_A相较于EPWM1_A的输出上升沿延迟时间RED = 400 * TTBCLK(TTBCLK为PWM时基时钟周期)
- EPWM5_B相较于EPWM1_A的输出下降沿延迟时间RED = 200 * TTBCLK
- EPWM5最终输出设置为低有效互补模式（ALC）,EPWM5_A进行翻转

- EPWM6最终输出设置为EPWM6_A和EPWM6_B输出互换
- EPWM6_A和EPWM1_B相同
- EPWM6_B和EPWM1_A相同

### 外部连接：
- GPIO0 EPWM1A
- GPIO1 EPWM1B
- GPIO2 EPWM2A
- GPIO3 EPWM2B
- GPIO4 EPWM3A
- GPIO5 EPWM3B
- GPIO6 EPWM4A
- GPIO7 EPWM4B
- GPIO8 EPWM5A
- GPIO9 EPWM5B
- GPIO10 EPWM6A
- GPIO11 EPWM6B
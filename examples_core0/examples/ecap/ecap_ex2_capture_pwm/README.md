# ecap_capture_pwm.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的eCAP模块的捕获功能示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何使用eCAP模块的捕获功能。
- 控制EPWM3输出频率变化的PWM波形，使用ecap对波形进行捕获，在ecap中断中校验测得的PWM周期值和期望值是否相等，相等情况下ecap1IntCount
- 和ecap1PassCount会持续累加，在ecap中断中不断改变PWM的频率
- GPIO4配置为EPWM_A的输出，GPIO16配置为ECAP1的输入
- 将GPIO4和GPIO16相连接可完成对PWM波形的捕获，调试器观测ecap1IntCount，ecap1PassCount变量来判断有无错误
### 外部连接：
- GPIO4配置为EPWM_A的输出，GPIO16配置为ECAP1的输入，将GPIO4和GPIO16相连接
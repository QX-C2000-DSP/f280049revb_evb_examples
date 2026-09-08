# hrpwm_ex3_prd_updown_sfo.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的hrPWM 动态调整高精度周期的示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何使用hrPWM模块。
- 控制pwm1,2,3,4输出高精度周期动态变化的pwm波
- 并加入了SFO校准，来校准更新mep比例因子

### 外部连接：
- GPIO0 hrPWM1A
- GPIO1 hrPWM1B
- GPIO2 hrPWM2A
- GPIO3 hrPWM2B
- GPIO4 hrPWM3A
- GPIO5 hrPWM3B
- GPIO6 hrPWM4A
- GPIO7 hrPWM4B
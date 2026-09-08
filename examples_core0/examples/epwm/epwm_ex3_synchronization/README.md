# epwm_ex3_synchronization.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的ePWM 同步相移的示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何实现各路PWM之间进行同步。
- 本例程EPWM1作为同步源，EPWM2相较于EPWM1相移54°，EPWM3相较于EPWM1相移108°，EPWM4相较于EPWM1相移162°
- 计算相移的公式 ：Desired Phase Degree = TBPHS * 360° / TBPRD

### 外部连接：
- GPIO0为ePWM1_A的输出，GPIO1为ePWM1_B的输出，GPIO2为ePWM2_A的输出，GPIO3为ePWM2_B的输出，GPIO4为ePWM3_A的输出，GPIO5为ePWM3_B的输出
- GPIO6为ePWM4_A的输出，GPIO7为ePWM4_B的输出
# cmpss_ex1_asynch.c

## 文件所有
本文适用于QXS320F28XXX系列芯片的cmpss触发EPWM跳闸示例例程。

## 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任。

## 使用说明
- 本例展示了如何使用CMPSS模块的输出经过EPWM的DC子模块进一步将跳闸信号馈送到TZ子模块触发EPWM跳闸。
- GPIO14为CMPSS的比较输出，CMPSS的高侧比较器的负端由内部DAC输入，正端由A2引脚输入。
- CMPSS的比较输出经过EPWMXBAR的TRIP4输入到EPWM的DC
- GPIO15为EPWM8_B的输出，当A2接地时，CMPSS输出低，GPIO15输出EPWM8_B的波形，当A2拉高，CMPSS输出高，触发EPWM跳闸，EPWM8_B恒高

### 外部连接：
- GPIO14为CMPSS1的输出，GPIO15为EPWM8_B的输出，A2为CMPSS1的正端输入
#### 文件所有
本文适用于QXS320F28XXX系列芯片的 LIN_SEND AS MASTER 的示例例程
* * *

#### 版权说明
目前的固件只是为了给使用者提供指导，目的是向客户提供有关产品的代码信息，
与使用者的产品信息和代码无关。因此，对于因此类固件内容和（或）客户使用此
处包含的与其产品相关的编码信息而引起的任何索赔，合肥乾芯科技有限公司
不承担任何直接、间接或后果性损害赔偿责任
* * *

#### 使用说明
* 本例展示了如何配置 寄存器 控制到 LIN 模块的应用:
* 本例将本芯片作为主机发送十个不同ID的LIN报文以及每帧八个数据：
* 在使用LIN模块的时候根据下列设置相应引脚连接TX和RX到LIN收发器的相应引脚；
*   GPIO_MuxConfig(28, GPIO_28_LINA_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
*   GPIO_MuxConfig(29, GPIO_29_LINA_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
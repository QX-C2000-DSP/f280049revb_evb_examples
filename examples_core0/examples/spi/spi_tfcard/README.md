# SPI读写TF卡示例

## 文件概述
本文档适用于QXS320F28XXX系列芯片，并提供了SPI读写TF卡（SD卡）的示例代码。

---

## 版权说明
提供的固件仅作为用户的参考指南，旨在为客户提供有关产品的代码信息，并与用户的产品信息或代码无关。因此，合肥乾芯科技有限公司对于因使用此固件内容及/或与其产品相关的编码信息所引发的任何索赔或损失，不承担任何直接、间接或后果性损害赔偿责任。

---

## 使用说明
* 本示例展示了如何使用SPI读写TF卡（SD卡）。
* 提供了基本的TF卡操作，包括读、写等功能。
* SPI驱动提供与TF卡的通信接口，支持多字节读写操作，并优化了传输效率。

## 硬件
* **SPI_B 引脚定义：**
  * MISO: GPIO_6
  * MOSI: GPIO_7
  * CLK : GPIO_28
  * CS  : GPIO_29

---

## SPI读写TF卡

本示例展示了如何通过SPI接口与TF卡进行通信，实现基本的读写操作。以下是配置和使用SPI接口与TF卡进行操作的步骤：

### 1. 硬件设置

确保以下SPI引脚已经正确连接到微控制器，并正确配置：

* **MISO (主设备输入从设备输出)**：连接到SD卡的MISO引脚（GPIO_6）
* **MOSI (主设备输出从设备输入)**：连接到SD卡的MOSI引脚（GPIO_7）
* **SCK (串行时钟)**：连接到SD卡的SCK引脚（GPIO_28）
* **CS (片选)**：连接到SD卡的CS引脚（GPIO_29）

确保TF卡已正确供电，并且SPI通信线路已正确连接。

### 2. 初始化

在使用TF卡之前，需要初始化SPI外设，配置为主模式，并设置适当的时钟极性和相位来与TF卡进行通信。

```c
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SPI_disableModule(mySPI1_BASE);
    SPI_setConfig(mySPI1_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0, SPI_MODE_CONTROLLER,
        mySPI1_BITRATE, mySPI1_DATAWIDTH);
    SPI_enableModule(mySPI1_BASE);
    SPI_CS_HIGH();
```

### 3. TF卡初始化

在使用TF卡之前，需要初始化它并检查其状态。通常通过SD_init函数来检查卡是否准备好进行通信。

```c
uint8_t sd_initflag = SD_init();
if (sd_initflag != 0)
{
    printf("TF卡初始化失败，请确保TF卡正确接入开发板。\n");
}
else
{
    printf("TF卡初始化成功！\n");
}
```

### 4. 读写数据

一旦TF卡初始化成功，你可以使用提供的函数来进行读写操作。例如，读取一个数据块可以通过以下函数实现：

```c
uint8_t SD_ReadDisk(uint8_t *buf, uint32_t sector, uint8_t cnt)
{
    uint8_t r1;
    if (cnt == 1)
    {
        r1 = SD_sendcmd(CMD17, sector, 0X01); // 读命令
        if (r1 == 0)  // 指令发送成功
        {
            r1 = SD_ReceiveData(buf, 512); // 接收512字节的数据
        }
    }
    return r1;
}
```

同样，写入数据到TF卡可以使用以下代码：

```c
uint8_t SD_WriteDisk(uint8_t *buf, uint32_t sector, uint8_t cnt)
{
    uint8_t r1;
    if (cnt == 1)
    {
        r1 = SD_sendcmd(CMD24, sector, 0X01); // 写命令
        if (r1 == 0)  // 指令发送成功
        {
            r1 = SD_SendBlock(buf, 0xFE); // 写入512字节的数据
        }
    }
    return r1;
}
```


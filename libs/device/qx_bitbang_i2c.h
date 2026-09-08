#ifndef QX_BSP_BITBANG_I2C_H
#define QX_BSP_BITBANG_I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <device.h>
#include "qx_config_board.h"

// ----------------------------------------------------------------------------
// I2C 实例配置与强制内联接口 (可读性极佳且零开销)
// ----------------------------------------------------------------------------

typedef struct
{
    uint16_t scl_pin;
    uint16_t sda_pin;
} bb_i2c_t;

// I2C总线 GPIO 引脚定义, 支持多总线定义和使用
#define IIC_SCL_BUS_1 33
#define IIC_SDA_BUS_1 32

#define IIC_SCL_BUS_2 23
#define IIC_SDA_BUS_2 22

// 预定义实例配置
static const bb_i2c_t BB_I2C_BUS1 = { IIC_SCL_BUS_1, IIC_SDA_BUS_1 };
static const bb_i2c_t BB_I2C_BUS2 = { IIC_SCL_BUS_2, IIC_SDA_BUS_2 };

// ----------------------------------------------------------------------------
// 底层寄存器操作抽象 (使用三元运算符确保常量折叠，不依赖优化等级)
// ----------------------------------------------------------------------------

#define GPIO_SET_H_GPA(bit)   (GpioDataRegs.GPASET.all = (1UL << (bit)))
#define GPIO_SET_L_GPA(bit)   (GpioDataRegs.GPACLEAR.all = (1UL << (bit)))
#define GPIO_GET_DAT_GPA(bit) ((GpioDataRegs.GPADAT.all >> (bit)) & 1UL)

#define GPIO_SET_H_GPB(bit)   (GpioDataRegs.GPBSET.all = (1UL << ((bit) - 32)))
#define GPIO_SET_L_GPB(bit)   (GpioDataRegs.GPBCLEAR.all = (1UL << ((bit) - 32)))
#define GPIO_GET_DAT_GPB(bit) ((GpioDataRegs.GPBDAT.all >> ((bit) - 32)) & 1UL)

#define GPIO_SET_H_GPH(bit)   (GpioDataRegs.GPHSET.all = (1UL << ((bit) - 224)))
#define GPIO_SET_L_GPH(bit)   (GpioDataRegs.GPHCLEAR.all = (1UL << ((bit) - 224)))
#define GPIO_GET_DAT_GPH(bit) ((GpioDataRegs.GPHDAT.all >> ((bit) - 224)) & 1UL)

#define GPIO_SET_H(pin)   ((pin < 32) ? GPIO_SET_H_GPA(pin) : ((pin < 64) ? GPIO_SET_H_GPB(pin) : GPIO_SET_H_GPH(pin)))
#define GPIO_SET_L(pin)   ((pin < 32) ? GPIO_SET_L_GPA(pin) : ((pin < 64) ? GPIO_SET_L_GPB(pin) : GPIO_SET_L_GPH(pin)))
#define GPIO_GET_DAT(pin) ((pin < 32) ? GPIO_GET_DAT_GPA(pin) : ((pin < 64) ? GPIO_GET_DAT_GPB(pin) : GPIO_GET_DAT_GPH(pin)))

static inline void bb_i2c_delay(void)
{
    // 性能估算(适用于乾芯C2000系列芯片):
    // 完全注释掉循环NOP时达到最大速率, 此时100Mhz主频+O1优化时约800Khz, 优化等级提高到O3时达到1Mhz+
    // 如果希望降低I2C速度, 通过解开下面的NOP循环, 修改循环计数值即可实现调节I2C通信速率
    // for (volatile int i= 0; i < 100; i++)
    //     __asm("NOP||");
}

static inline bool bb_i2c_wait_scl_high(const bb_i2c_t *bus)
{
    uint16_t n = 50u;
    while ((GPIO_GET_DAT(bus->scl_pin) == 0u) && (n-- != 0u))
        ;
    return (GPIO_GET_DAT(bus->scl_pin) != 0u);
}

static inline bool bb_i2c_stop(const bb_i2c_t *bus)
{
    // 产生 STOP 信号: SCL 为高时，SDA 由低变高
    GPIO_SET_L(bus->sda_pin);
    bb_i2c_delay();
    GPIO_SET_H(bus->scl_pin);
    if (!bb_i2c_wait_scl_high(bus))
        return false;
    bb_i2c_delay();
    GPIO_SET_H(bus->sda_pin);
    bb_i2c_delay();
    return true;
}

static inline void bb_i2c_recover_bus(const bb_i2c_t *bus)
{
    uint16_t i;

    // 强制释放总线逻辑：
    // 如果 SDA 被从机拉死（例如从机在传输中复位），可以通过 SCL 的 9 个脉冲恢复
    GPIO_SET_H(bus->sda_pin);
    for (i = 0; i < 9; i++)
    {
        GPIO_SET_L(bus->scl_pin);
        bb_i2c_delay();
        GPIO_SET_H(bus->scl_pin);
        (void)bb_i2c_wait_scl_high(bus);
        bb_i2c_delay();
        // 如果 SDA 变高了，说明从机已释放总线
        if (GPIO_GET_DAT(bus->sda_pin))
            break;
    }

    // 产生 STOP 信号确保进入空闲状态
    (void)bb_i2c_stop(bus);
}

static inline bool bb_i2c_start(const bb_i2c_t *bus)
{
    // 在产生 START 信号前，确保总线空闲
    // 释放 SDA 为输入/高阻态，释放 SCL
    GPIO_SET_H(bus->sda_pin);
    bb_i2c_delay();
    GPIO_SET_H(bus->scl_pin);
    if (!bb_i2c_wait_scl_high(bus))
        return false;
    bb_i2c_delay();

    // 检查总线是否真的空闲 (SDA 应该为高)
    if (GPIO_GET_DAT(bus->sda_pin) == 0u)
        return false;

    // 产生 START 信号: SCL 为高时，SDA 由高变低
    GPIO_SET_L(bus->sda_pin);
    bb_i2c_delay();
    GPIO_SET_L(bus->scl_pin);
    bb_i2c_delay();
    return true;
}

static inline bool bb_i2c_write_byte(const bb_i2c_t *bus, uint8_t byte)
{
    uint16_t i;
    for (i = 0; i < 8; i++)
    {
        if (byte & 0x80)
            GPIO_SET_H(bus->sda_pin);
        else
            GPIO_SET_L(bus->sda_pin);
        byte <<= 1;

        GPIO_SET_H(bus->scl_pin);
        bb_i2c_delay();
        GPIO_SET_L(bus->scl_pin);
        bb_i2c_delay();
    }

    GPIO_SET_H(bus->sda_pin);
    GPIO_SET_H(bus->scl_pin);
    bb_i2c_delay();
    bool ack = (GPIO_GET_DAT(bus->sda_pin) == 0);
    GPIO_SET_L(bus->scl_pin);
    bb_i2c_delay();

    return ack;
}

static inline uint8_t bb_i2c_read_byte(const bb_i2c_t *bus, bool ack)
{
    uint8_t byte = 0;
    uint16_t i;

    GPIO_SET_H(bus->sda_pin);

    for (i = 0; i < 8; i++)
    {
        byte <<= 1;
        GPIO_SET_H(bus->scl_pin);
        bb_i2c_delay();
        if (GPIO_GET_DAT(bus->sda_pin))
            byte |= 0x01;
        GPIO_SET_L(bus->scl_pin);
        bb_i2c_delay();
    }

    if (ack)
        GPIO_SET_L(bus->sda_pin);
    else
        GPIO_SET_H(bus->sda_pin);

    GPIO_SET_H(bus->scl_pin);
    bb_i2c_delay();
    GPIO_SET_L(bus->scl_pin);
    bb_i2c_delay();
    GPIO_SET_H(bus->sda_pin);

    return byte;
}

static inline bool bb_i2c_write_reg(
    const bb_i2c_t *bus, uint8_t dev7, uint8_t reg, const uint8_t *data, uint16_t len)
{
    if (!bb_i2c_start(bus))
    {
        bb_i2c_recover_bus(bus);
        if (!bb_i2c_start(bus))
            return false;
    }
    if (!bb_i2c_write_byte(bus, (uint8_t)((dev7 << 1) | 0)))
    {
        (void)bb_i2c_stop(bus);
        return false;
    }
    if (!bb_i2c_write_byte(bus, reg))
    {
        (void)bb_i2c_stop(bus);
        return false;
    }
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        if (!bb_i2c_write_byte(bus, data[i]))
        {
            (void)bb_i2c_stop(bus);
            return false;
        }
    }
    return bb_i2c_stop(bus);
}

static inline bool bb_i2c_read_reg(
    const bb_i2c_t *bus, uint8_t dev7, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (!bb_i2c_start(bus))
    {
        bb_i2c_recover_bus(bus);
        if (!bb_i2c_start(bus))
            return false;
    }
    if (!bb_i2c_write_byte(bus, (uint8_t)((dev7 << 1) | 0)))
    {
        (void)bb_i2c_stop(bus);
        return false;
    }
    if (!bb_i2c_write_byte(bus, reg))
    {
        (void)bb_i2c_stop(bus);
        return false;
    }

    // 采用 Stop + Start 模式以适应某些严格的从机
    (void)bb_i2c_stop(bus);
    uint16_t delay_count = 3;  // 优化：从10减少到3，减少约70ns延迟
    while(delay_count--) bb_i2c_delay(); // 确保 Bus Free Time (tBUF)

    if (!bb_i2c_start(bus))
        return false;

    if (!bb_i2c_write_byte(bus, (uint8_t)((dev7 << 1) | 1)))
    {
        (void)bb_i2c_stop(bus);
        return false;
    }
    uint16_t i;
    if (len > 0)
    {
        for (i = 0; i < (len - 1); i++)
        {
            data[i] = bb_i2c_read_byte(bus, true);
        }
        data[len - 1] = bb_i2c_read_byte(bus, false);
    }
    return bb_i2c_stop(bus);
}

#endif

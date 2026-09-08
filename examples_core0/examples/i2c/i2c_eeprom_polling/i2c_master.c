#include "device.h"
#include "driverlib.h"
#include <stdio.h>

// wait timeout
#define MAX_TIMEOUT 0xFFFF

void i2c_init(uint32_t speed)
{
    uint32_t base = I2CA_BASE;

    /* 开启i2c外设时钟 */
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);

    I2C_disableModule(base);
    I2C_disableLoopback(base);
    I2C_initController(base, DEVICE_SYSCLK_FREQ, speed, I2C_DUTYCYCLE_50);  // 50% 占空比
    I2C_setBitCount(base, I2C_BITCOUNT_8);                                  // 8 bit 数据位
    I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);                          // 默认从机目标地址7bit模式
    I2C_disableFIFO(base);                                                  // 禁用i2c模块FIFO
    I2C_enableModule(base);
}

int i2c_read_reg8(uint16_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t length)
{
    uint32_t base = I2CA_BASE;
    uint32_t timeout = MAX_TIMEOUT;

    /* 检查i2c总线是否空闲,以及停止状态是否准备好 */
    if (I2C_isBusBusy(base) || (I2C_getStopConditionStatus(base))) {
        return -1;
    }

    /*------------------------------------------------------------------------*/
    /* 设置i2c为主机发送模式 */
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);

    /* 根据从机目标地址设置地址模式(7bit地址最大支持0x7F) */
    if (slave_addr > 0x7F) {
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    } else {
        I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);
    }

    /* 设置从机目标地址 */
    I2C_setTargetAddress(base, slave_addr);

    /* 发送Start信号 */
    I2C_sendStartCondition(base);

    /* 发送 1 Byte寄存器地址, 并等待tx_data从DXR寄存器复制到移位寄存器 */
    timeout = MAX_TIMEOUT;
    I2C_putData(base, reg_addr);
    while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
        ;

    /*-------------------------------------------------------*/
    /* 设置I2C为主机接收模式 */
    I2C_setConfig(base, I2C_CONTROLLER_RECEIVE_MODE);

    /* 设置想要读取的数据长度 */
    I2C_setDataCount(base, length);

    /* 发送Restart信号 */
    I2C_sendStartCondition(base);

    for (uint8_t i = 0; i < length; i++) {
        timeout = MAX_TIMEOUT;
        /* 等待Rx数据准备好 */
        while ((!(I2C_getStatus(base) & I2C_STS_RX_DATA_RDY)) && timeout--)
            ;

        data[i] = I2C_getData(base);
    
        /* 清除接收数据就绪状态 */
        I2C_clearStatus(base, I2C_STS_RX_DATA_RDY);
    }

    /* 发送Stop信号, 终止通信 */
    I2C_sendStopCondition(base);

    return 0;
}

int i2c_write_reg8(uint16_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t length)
{
    uint32_t base = I2CA_BASE;
    uint32_t timeout = MAX_TIMEOUT;

    /* 检查i2c总线是否空闲,以及停止状态是否准备好 */
    if (I2C_isBusBusy(base) || (I2C_getStopConditionStatus(base))) {
        return -1;
    }

    /*------------------------------------------------------------------------*/
    /* 设置i2c为主机发送模式 */
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);

    /* 根据从机目标地址设置地址模式(7bit地址最大支持0x7F) */
    if (slave_addr > 0x7F) {
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    } else {
        I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);
    }

    /* 设置从机目标地址 */
    I2C_setTargetAddress(base, slave_addr);

    /* 发送Start信号 */
    I2C_sendStartCondition(base);

    /* 发送 1 Byte寄存器地址, 并等待tx_data从DXR寄存器复制到移位寄存器 */
    timeout = MAX_TIMEOUT;
    I2C_putData(base, reg_addr);
    while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
        ;

    /* 写入 length 字节数据, 并等待tx_data从DXR寄存器复制到移位寄存器 */
    for (uint8_t i = 0; i < length; i++) {
        timeout = MAX_TIMEOUT;
        I2C_putData(base, data[i]);
        while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
            ;
    }

    /* 发送Stop信号, 终止通信 */
    I2C_sendStopCondition(base);

    return 0;
}


int i2c_read_reg16(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data, uint8_t length)
{
    uint32_t base = I2CA_BASE;
    uint32_t timeout = MAX_TIMEOUT;

    /* 检查i2c总线是否空闲,以及停止状态是否准备好 */
    if (I2C_isBusBusy(base) || (I2C_getStopConditionStatus(base))) {
        return -1;
    }

    /*------------------------------------------------------------------------*/
    /* 设置i2c为主机发送模式 */
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);

    /* 根据从机目标地址设置地址模式(7bit地址最大支持0x7F) */
    if (slave_addr > 0x7F) {
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    } else {
        I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);
    }

    /* 设置从机目标地址 */
    I2C_setTargetAddress(base, slave_addr);

    /* 发送Start信号 */
    I2C_sendStartCondition(base);

    /* 发送 2 Byte寄存器地址, 并等待tx_data从DXR寄存器复制到移位寄存器 */
    timeout = MAX_TIMEOUT;
    I2C_putData(base, ((reg_addr >> 8) & 0xFF));  // 发送高字节 msb
    while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
        ;

    timeout = MAX_TIMEOUT;
    I2C_putData(base, (reg_addr & 0xFF));         // 发送低字节 lsb
    while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
        ;

    /*-------------------------------------------------------*/
    /* 设置I2C为主机接收模式 */
    I2C_setConfig(base, I2C_CONTROLLER_RECEIVE_MODE);

    /* 设置想要读取的数据长度 */
    I2C_setDataCount(base, length);

    /* 发送Restart信号 */
    I2C_sendStartCondition(base);

    for (uint8_t i = 0; i < length; i++) {
        timeout = MAX_TIMEOUT;
        /* 等待Rx数据准备好 */
        while ((!(I2C_getStatus(base) & I2C_STS_RX_DATA_RDY)) && timeout--)
            ;

        data[i] = I2C_getData(base);
    
        /* 清除接收数据就绪状态 */
        I2C_clearStatus(base, I2C_STS_RX_DATA_RDY);
    }

    /* 发送Stop信号, 终止通信 */
    I2C_sendStopCondition(base);

    return 0;
}

int i2c_write_reg16(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data, uint8_t length)
{
    uint32_t base = I2CA_BASE;
    uint32_t timeout = MAX_TIMEOUT;

    /* 检查i2c总线是否空闲,以及停止状态是否准备好 */
    if (I2C_isBusBusy(base) || (I2C_getStopConditionStatus(base))) {
        return -1;
    }

    /*------------------------------------------------------------------------*/
    /* 设置i2c为主机发送模式, repeat模式当发送完后产生STOP信号 */
    I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE | I2C_REPEAT_MODE);

    /* 根据从机目标地址设置地址模式(7bit地址最大支持0x7F) */
    if (slave_addr > 0x7F) {
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    } else {
        I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS);
    }

    /* 设置从机目标地址 */
    I2C_setTargetAddress(base, slave_addr);

    /* 发送Start信号 */
    I2C_sendStartCondition(base);

    /* 发送 2 Byte寄存器地址, 并等待tx_data从DXR寄存器复制到移位寄存器 */
    timeout = MAX_TIMEOUT;
    I2C_putData(base, ((reg_addr >> 8) & 0xFF));  // 发送高字节 msb
    while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
        ;

    timeout = MAX_TIMEOUT;
    I2C_putData(base, (reg_addr & 0xFF));         // 发送低字节 lsb
    while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
        ;

    /* 写入 length 字节数据, 并等待tx_data从DXR寄存器复制到移位寄存器 */
    for (uint8_t i = 0; i < length; i++) {
        timeout = MAX_TIMEOUT;
        I2C_putData(base, data[i]);
        while (((I2C_getStatus(base) & I2C_STS_TX_DATA_RDY)) && timeout--)
            ;
    }

    /* 发送Stop信号, 终止通信 */
    I2C_sendStopCondition(base);

    return 0;
}

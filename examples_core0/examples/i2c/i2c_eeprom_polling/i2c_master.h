#ifndef __I2C_MASTER_H__
#define __I2C_MASTER_H__


/**
 * @brief 初始化I2C外设
 * @param speed I2C时钟频率:100000 或 400000
 */
void i2c_init(uint32_t speed);

/**
 * @brief 读取8位寄存器地址的数据
 * @param slave_addr 从机地址(注意是7bit或10bit地址,不是左移1位后的地址)
 * @param reg_addr 8bit 寄存器地址
 * @param data 数据缓冲区指针
 * @param length 读取数据长度
 * @return 0-成功, -1失败
 */
int i2c_read_reg8(uint16_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t length);
int i2c_write_reg8(uint16_t slave_addr, uint8_t reg_addr, uint8_t *data, uint8_t length);

/**
 * @brief 读取16位寄存器地址的数据
 * @param slave_addr 从机地址(注意是7bit或10bit地址,不是左移1位后的地址)
 * @param reg_addr 16bit 寄存器地址, 默认先发送msb
 * @param data 数据缓冲区指针
 * @param length 读取数据长度
 * @return 0-成功, -1失败
 */
int i2c_read_reg16(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data, uint8_t length);
int i2c_write_reg16(uint16_t slave_addr, uint16_t reg_addr, uint8_t *data, uint8_t length);


#endif // __I2C_MASTER_H__

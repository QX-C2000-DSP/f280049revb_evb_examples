// #############################################################################
//
//  FILE:   i2c_ex2_eeprom.c
//
//  TITLE:  I2C EEPROM
//
//! \addtogroup driver_example_list
//! <I2C EEPROM>
//!
//! This program will write 1-14 words to EEPROM and read them back. The data
//! written and the EEPROM address written to are contained in the message
//! structure, i2cMsgOut. The data read back will be contained in the message
//! structure i2cMsgIn.
//!
//! \b External \b Connections on Control card\n
//!  - Connect external I2C EEPROM at address 0x50
//!  - Connect GPIO0/SDAA on controlCARD to external EEPROM SDA (serial data) pin
//!  - Connect GPIO1/SCLA on controlCARD to external EEPROM SCL (serial clock) pin
//!
// #############################################################################

//
// Included Files
//
#include "device.h"
#include "driverlib.h"
#include <stdio.h>

#include "i2c_master.h"

uint8_t rx_data[64];
uint8_t tx_data[64];

/*----------------------------------------------------------*/
/**
 *  读写数据大小不能超过eeprom 1 page size
 *  注意: 写完1page需要等待eeprom ACK polling, about 5ms
 *  AT24C02： 256   字节 (2K位),   每页8字节,  32页
 *  AT24C04： 512   字节 (4K位),   每页16字节, 32页
 *  AT24C08： 1024  字节 (8K位),   每页16字节, 64页
 *  AT24C16： 2048  字节 (16K位),  每页16字节, 128页
 *  AT24C32： 4096  字节 (32K位),  每页32字节, 128页
 *  AT24C64： 8192  字节 (64K位),  每页32字节, 256页
 *  AT24C128：16384 字节 (128K位), 每页64字节, 256页
 *  AT24C256：32768 字节 (256K位), 每页64字节, 512页
*/
#define TARGET_ADDRESS  0x50

/*----------------------------------------------------------*/

#define __I2C_PIN_MUX_INIT(i2c_base, sda, scl)        \
    {                                                 \
        .sda_pin     = sda,                           \
        .sda_pin_mux = GPIO_##sda##_##i2c_base##_SDA, \
        .scl_pin     = scl,                           \
        .scl_pin_mux = GPIO_##scl##_##i2c_base##_SCL, \
    }

enum i2c_bus_id_e
{
    I2C_BUS_0,
    I2C_BUS_1,
    I2C_BUS_2,
};

typedef struct __i2c_gpio_config_t
{
    uint32_t sda_pin;
    uint32_t sda_pin_mux;
    uint32_t scl_pin;
    uint32_t scl_pin_mux;
} i2c_gpio_t;

static i2c_gpio_t i2c_gpio[] = {
    // ----------------------------- base  sda  scl
    [I2C_BUS_0] = __I2C_PIN_MUX_INIT(I2CA, 0, 1),
    [I2C_BUS_1] = __I2C_PIN_MUX_INIT(I2CA, 32, 33),
    [I2C_BUS_2] = __I2C_PIN_MUX_INIT(I2CA, 10, 8),
};

void i2c_gpio_init(uint8_t index)
{
    i2c_gpio_t *pgpio = &i2c_gpio[index];

    GPIO_setPadConfig(pgpio->sda_pin, GPIO_PIN_TYPE_OD);
    GPIO_setQualificationMode(pgpio->sda_pin, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(pgpio->sda_pin_mux);

    GPIO_setPadConfig(pgpio->scl_pin, GPIO_PIN_TYPE_OD);
    GPIO_setQualificationMode(pgpio->scl_pin, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(pgpio->scl_pin_mux);
}

int main(void)
{
    int i;
    Interrupt_initVectorTable();
    Device_init();

    /* 初始化i2c总线0: gpio0(sda), gpio1(scl), 设置为开漏OD */
    i2c_gpio_init(I2C_BUS_0);

    /* 初始化i2c外设模块: 400kHz 速率 */
    i2c_init(400000);

    while (1) {
        /* 准备写入的测试数据 */
        for (i = 0; i < sizeof(tx_data); i++) {
            tx_data[i] = (i + 1);
        }

        static uint16_t reg_addr = 0x0000;

        i2c_write_reg16(TARGET_ADDRESS, reg_addr, tx_data, 8);
        DEVICE_DELAY_US(5 * 1000); /* 等待ACK,至少5ms */

        i2c_read_reg16(TARGET_ADDRESS, reg_addr, rx_data, 8);
        DEVICE_DELAY_US(5 * 1000);

        /* 比较读写数据 */
        for (i = 0; i < 8; i++) {
            if (rx_data[i] != tx_data[i]) {
                // Error
                while (1)
                    ;
            }
        }

        /* AT24C128 1page大小64字节, 总共256页 */
        reg_addr += 8;
        if (reg_addr >= 8*256) {
            reg_addr = 0;
        }
    }

    return 0;
}

/*
 *   Copyright (c) STARRYSTONETECH - http://www.starrystonetech.com/
 *   All rights reserved.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
*   @file    w25q64.c
*   @brief   
*   @details
*
*/

#ifdef __cplusplus
extern "C"{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "device.h"
#include "w25q64.h"
#include "board.h"

#define FLASH_SECTOR_SIZE       (0x00001000)
#define FLASH_PAGE_SIZE         (0x00000100)


#define DUMMY_DATA 0
#define NO_DELAY   0

typedef struct
{
	uint8_t *send_cmd;
	uint32_t send_cmd_len;
	uint8_t *send_data;
	uint32_t send_data_len;
	uint8_t *rcv_data;
	uint32_t rcv_data_len;
} TRANSFER_INFO;


/*******************************************************************************
 * 函数名：SPI_sendByte
 * 描述  ：SPI读取数据
 * 输入  ：data
 * 输出  ：Outdata
 * 调用  ：内部调用
 * 备注  ：通过发送一个字节的数据并同时接收一个字节的数据，实现了数据的读取操作。
 *******************************************************************************/
uint8_t SPI_sendByte(uint8_t data)
{
    uint32_t timeout = MAX_TIMEOUT;

    while ((SPI_getTxFIFOStatus(SPIB_BASE) != SPI_FIFO_TXEMPTY) && (timeout--))
        ;

    SPI_writeDataNonBlocking(SPIB_BASE, data);

    timeout = MAX_TIMEOUT;
    while ((SPI_getRxFIFOStatus(SPIB_BASE) != SPI_FIFO_RX1) && (timeout--))
        ;

    return SPI_readDataBlockingFIFO(SPIB_BASE);
}

void w25q64_polling_transfer(uint32_t base, TRANSFER_INFO *transfer_info)
{
	uint16_t tx_data = 0;
    uint32_t tx_len = transfer_info->send_cmd_len + transfer_info->send_data_len;
    uint32_t rx_len = transfer_info->rcv_data_len;
	uint32_t i,j;

    CS_LOW;

	for(i=0; i<tx_len; i++)
	{
		if(i <= (transfer_info->send_cmd_len - 1))
			tx_data = transfer_info->send_cmd[i];
		else
			tx_data = transfer_info->send_data[i-transfer_info->send_cmd_len];
		
//	    SPI_transmitByte(base, tx_data);
		SPI_sendByte(tx_data);

		if(i >= (transfer_info->send_cmd_len - 1))
		{
			if(rx_len > 0)
			{
				for(j=0; j<rx_len; j++)
				{
					transfer_info->rcv_data[j] = SPI_sendByte(W25Q64_DUMMY_BYTE);
				}
//				SPI_receiveNBytes(base, transfer_info->rcv_data, rx_len+1, NO_DELAY);
			}
		}
	}
	
    CS_HIGH;
}


uint32_t w25q64_write_reg(uint32_t base, uint8_t reg, uint8_t *data, uint32_t len)
{
	TRANSFER_INFO transfer_info = {0};
    uint8_t send_cmd[1] = {0};

    send_cmd[0] = reg;
    transfer_info.send_cmd = send_cmd;
    transfer_info.send_cmd_len = sizeof(send_cmd);

    transfer_info.send_data = data;
    transfer_info.send_data_len = len;

    w25q64_polling_transfer(base, &transfer_info);

    return 0;
}

uint32_t w25q64_read_reg(uint32_t base, uint8_t reg, uint16_t *data, uint32_t len)
{
	TRANSFER_INFO transfer_info = {0};
    uint8_t send_cmd[1] = {0};

    send_cmd[0] = reg;
    transfer_info.send_cmd = send_cmd;
    transfer_info.send_cmd_len = sizeof(send_cmd);

    transfer_info.rcv_data = data;
    transfer_info.rcv_data_len = len;

    w25q64_polling_transfer(base, &transfer_info);

    return 0;
}

uint32_t w25q64_read_jedec_id(void)
{
    uint8_t rcv_data[3] = {0};

#if 0
    CS_LOW;
    SPI_sendByte(READ_JEDEC_ID);         // 读ID号指令

    rcv_data[0] = SPI_sendByte(W25Q64_DUMMY_BYTE); // 厂商ID，默认为0xEF
    rcv_data[1] = SPI_sendByte(W25Q64_DUMMY_BYTE); // 设备ID，表示存储类型，默认为0x40
    rcv_data[2] = SPI_sendByte(W25Q64_DUMMY_BYTE); // 设备ID，表示容量，默认为0x17

    CS_HIGH;
#else
    w25q64_read_reg(SPIB_BASE, READ_JEDEC_ID, rcv_data, sizeof(rcv_data));
#endif

    return (rcv_data[0] << 16 | rcv_data[1] << 8 | rcv_data[2]) & 0x00ffffff;
}

uint32_t w25q64_read_device_id(uint32_t base)
{
	TRANSFER_INFO transfer_info = {0};
    uint8_t send_cmd[4] = {0x90, 0x00, 0x00, 0x00};
    uint8_t rcv_data[2] = {0};

    transfer_info.send_cmd = send_cmd;
    transfer_info.send_cmd_len = sizeof(send_cmd);

    transfer_info.rcv_data = rcv_data;
    transfer_info.rcv_data_len = sizeof(rcv_data);

    w25q64_polling_transfer(base, &transfer_info);

    return (rcv_data[0] << 8 | rcv_data[1]) & 0x0000ffff;
}

int32_t w25q64_wait_ready(uint32_t base)
{
    uint32_t status = 0;
    uint8_t r_data = 0;

    do
    {
        w25q64_read_reg(base, READ_STATUS_REG1, &r_data, 1);
    } while (r_data & 0x01);// Status Register 1 Bit 0

    return 0;
}



int32_t w25q64_write_enable(uint32_t dev)
{
    uint32_t status = 0;
    uint8_t w_data[8] = {0};
	uint8_t r_data = 0;

    do
    {
        w25q64_write_reg(dev, WRITE_ENABLE, (uint8_t *)&w_data, 0);

        w25q64_read_reg(dev, READ_STATUS_REG1, &r_data, 1);

        // clear protection bits
        //  Write Protect. and Write Enable.
        if ((r_data & 0xfc) && (r_data & 0x02))
        {
            w_data[1] = 0;

            w25q64_write_reg(dev, WRITE_STATUS_REG, (uint8_t *)&w_data, 1);

            r_data = 0;
        }
    } while (r_data != 0x02);

    return 0;
}

int32_t w25q64_write_disable(uint32_t dev)
{
    uint32_t status = 0;
    uint8_t w_data[8], r_data = 0;

    do
    {
        w25q64_write_reg(dev, WRITE_DISABLE, (uint8_t *)&w_data, 0);

        w25q64_read_reg(dev, READ_STATUS_REG1, &r_data, 1);

    } while (r_data & 0x02);// Status Register 1 Bit 1

    return 0;

}

int32_t w25q64_erase(uint32_t spi_base, uint32_t address, uint32_t size)
{
    uint32_t last_address;
    uint32_t earse_sector_counts = 0;
    uint8_t cmd[4] = {0};
	TRANSFER_INFO transfer_info = {0};

    // start address of last sector
    last_address = (address + size) & (~(FLASH_SECTOR_SIZE - 1));

    // start address of first sector
    address &= ~(FLASH_SECTOR_SIZE - 1);

    do 
    {
        if (w25q64_write_enable(spi_base) != 0)
        {
            return -1;
        }

        if (w25q64_wait_ready(spi_base) != 0)
        {
            return -1;
        }

        cmd[0] = SECTOR_ERASE;
        cmd[1] = (address >> 16) & 0xff;
        cmd[2] = (address >> 8) & 0xff;
        cmd[3] =  address & 0xff;

        transfer_info.send_cmd = cmd;
        transfer_info.send_cmd_len = sizeof(cmd);

        w25q64_polling_transfer(spi_base, &transfer_info);

        address += FLASH_SECTOR_SIZE;
        earse_sector_counts++;
    } while (address <= last_address);

    if (w25q64_wait_ready(spi_base) != 0)
    {
        return -1;
    }

    if (w25q64_write_disable(spi_base) != 0)
    {
        return -1;
    }

    return earse_sector_counts;
}

int32_t w25q64_write(uint32_t dev, uint32_t address, uint32_t size, const void *data)
{
    uint8_t cmd[4] = {0};
    uint32_t next_write_data_len = 0;
    TRANSFER_INFO transfer_info = {0};

    if (w25q64_wait_ready(dev) != 0)
    {
        return -1;
    }

    next_write_data_len = FLASH_PAGE_SIZE - (address & (FLASH_PAGE_SIZE - 1));

    do
    {
        // send write enable command to flash
        if (w25q64_write_enable(dev) != 0)
        {
            return -1;
        }
        if (w25q64_wait_ready(dev) != 0)
        {
            return -1;
        }

        next_write_data_len = next_write_data_len < size ? next_write_data_len : size;

        cmd[0] = PAGE_PROGRAM;
        cmd[1] = (address >> 16) & 0xff;
        cmd[2] = (address >> 8) & 0xff;
        cmd[3] = address  & 0xff;

        transfer_info.send_cmd = cmd;
        transfer_info.send_cmd_len = sizeof(cmd);

        transfer_info.send_data = (uint8_t *)data;
        transfer_info.send_data_len = next_write_data_len;

        w25q64_polling_transfer(dev, &transfer_info);

        size -= next_write_data_len;
        address += next_write_data_len;
        data += next_write_data_len;
        next_write_data_len = FLASH_PAGE_SIZE;

    } while (size);

    if (w25q64_wait_ready(dev) != 0)
    {
        return -1;
    }

    if (w25q64_write_disable(dev) != 0)
    {
        return -1;
    }

    return 0;
}

int32_t w25q64_read(uint32_t dev, uint32_t address, uint32_t size, void *data)
{
    TRANSFER_INFO stSend = {0};
    TRANSFER_INFO stCmd = {0};
    TRANSFER_INFO stRecv = {0};
    uint8_t cmd[4] = {0};

    uint32_t next_read_len = 0;
    uint32_t size_orig = size;
    TRANSFER_INFO transfer_info = {0};

    next_read_len = FLASH_PAGE_SIZE - (address & (FLASH_PAGE_SIZE - 1));

    do
    {
        if (w25q64_wait_ready(dev) != 0)
        {
            return -1;
        }

        next_read_len = next_read_len < size ? next_read_len : size;

        cmd[0] = READ_DATA;
        cmd[1] = (address >> 16) & 0xff;
        cmd[2] = (address >> 8) & 0xff;
        cmd[3] = address  & 0xff;

        transfer_info.send_cmd = cmd;
        transfer_info.send_cmd_len = sizeof(cmd);

        transfer_info.rcv_data = (uint8_t *)data;
        transfer_info.rcv_data_len = next_read_len;

        w25q64_polling_transfer(dev, &transfer_info);

        size -= next_read_len;
        address += next_read_len;
        data += next_read_len;
        next_read_len = FLASH_PAGE_SIZE;

    } while (size);

    return 0;
}
#ifdef __cplusplus
}
#endif


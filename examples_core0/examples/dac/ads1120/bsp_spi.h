#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

void SPI_init(void);
void SPI_CS_HIGH(void);
void SPI_CS_LOW(void);

uint8_t SPIB_rxTxByte(uint8_t data);

#endif

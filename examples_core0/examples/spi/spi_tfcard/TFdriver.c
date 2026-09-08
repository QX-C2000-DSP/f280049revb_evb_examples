#include "TFdriver.h"
#include "board.h"
#include "sci_printf.h"
#include "TFdriver.h"

/* Private define ------------------------------------------------------------*/
#define BLOCK_SIZE 512 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS  10 /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE (BLOCK_SIZE * NUMBER_OF_BLOCKS)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Buffer_Block_Tx[BLOCK_SIZE], Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[MULTI_BUFFER_SIZE], Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;

uint8_t DFF = 0xFF;
uint8_t test;
uint8_t SD_TYPE = 0x00;
MSD_CARDINFO SD0_CardInfo;

// 记录卡的类型
uint8_t SD_Type = 4;    // 存储卡的类型
SD_CardInfo SDCardInfo; // 用于存储卡的信息

/**
 * @brief  Sets the SPI Chip Select (CS) pin to high.
 * @note   This function is used to deactivate the SPI slave device
 *         by setting the Chip Select (CS) signal high.
 * @retval None
 */
void SPI_CS_HIGH(void)
{
    GPIO_writePin(GPIO_PIN_SPIB_STE, 1);
}

/**
 * @brief  Sets the SPI Chip Select (CS) pin to low.
 * @note   This function is used to activate the SPI slave device
 *         by setting the Chip Select (CS) signal low.
 * @retval None
 */
void SPI_CS_LOW(void)
{
    GPIO_writePin(GPIO_PIN_SPIB_STE, 0);
}

/**
 * @brief  Sends a single byte via SPI and receives the response byte.
 * @param  data: The byte to be transmitted via SPI.
 * @note   This function waits until the SPI transmit FIFO is empty before
 *         sending the data and waits until a byte is received in the receive
 *         FIFO before reading the response.
 * @retval The byte received from the SPI slave device.
 */
uint8_t SPI_SendByte(uint8_t data)
{
    // Wait until the TX FIFO is empty
    while (SPI_getTxFIFOStatus(mySPI1_BASE) != SPI_FIFO_TXEMPTY)
        ;

    // Send the data
    SPI_writeDataBlockingFIFO(mySPI1_BASE, data);

    // Wait until there is a byte in the RX FIFO
    while (SPI_getRxFIFOStatus(mySPI1_BASE) != SPI_FIFO_RX1)
        ;

    // Return the received byte
    return SPI_readDataBlockingFIFO(mySPI1_BASE);
}

/**
 * @brief  Controls the Chip Select (CS) pin for the SD card.
 * @param  p: Specifies the state of the CS pin.
 *            - 0: Sets the CS pin high to deactivate the SD card.
 *            - 1: Sets the CS pin low to activate the SD card.
 * @note   This function uses SPI_CS_HIGH() and SPI_CS_LOW() to manage
 *         the state of the CS pin.
 * @retval None
 */
void SD_CS(uint8_t p)
{
    if (p == 0)
    {
        SPI_CS_HIGH();
    }
    else
    {
        SPI_CS_LOW();
    }
}

/**
 * @brief  Sends a command to the SD card and retrieves the response.
 * @param  cmd: The command index to be sent to the SD card.
 *              The command index should be provided without the start bit (0x40) as it is added
 * internally.
 * @param  arg: The 32-bit argument for the command.
 * @param  crc: The CRC value for the command.
 *              This is required for certain commands, especially in SPI mode.
 * @note   This function performs the following steps:
 *         - Toggles the CS pin to ensure proper communication.
 *         - Sends the command with its arguments and CRC.
 *         - Handles special conditions for CMD12 (STOP_TRANSMISSION).
 *         - Waits for a valid response from the SD card.
 * @retval The R1 response from the SD card:
 *         - A value with the MSB cleared indicates a valid response.
 *         - The MSB set indicates that the card is still processing.
 */
int SD_sendcmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t r1;
    uint8_t retry;

    // Toggle CS pin to reset SD communication
    SD_CS(0);
    DEVICE_DELAY_US(20);
    SD_CS(1);

    // Wait until the SD card is ready (0xFF)
    do
    {
        retry = SPI_SendByte(DFF);
    } while (retry != 0xFF);

    // Send command
    SPI_SendByte(cmd | 0x40); // Send command index with start bit
    SPI_SendByte(arg >> 24);  // Send argument's MSB
    SPI_SendByte(arg >> 16);  // Send argument
    SPI_SendByte(arg >> 8);   // Send argument
    SPI_SendByte(arg);        // Send argument's LSB
    SPI_SendByte(crc);        // Send CRC

    // Send an additional byte for CMD12
    if (cmd == CMD12)
        SPI_SendByte(DFF);

    // Wait for the response with MSB cleared
    do
    {
        r1 = SPI_SendByte(0xFF);
    } while (r1 & 0x80);

    return r1; // Return the R1 response
}

/**
 * @brief  Initializes the SD card and identifies its type.
 * @note   This function performs the following steps:
 *         - Sends multiple dummy clocks to wake up the SD card.
 *         - Puts the SD card into idle state using CMD0.
 *         - Sends CMD8 to check voltage range compatibility and identify SD version.
 *         - Identifies the card type (SDSC, SDHC, or MMC).
 *         - Configures the block size to 512 bytes if the initialization is successful.
 * @retval Initialization status:
 *         - 0: SD card initialized successfully.
 *         - 1: SD card initialization failed.
 */
uint8_t SD_init(void)
{
    uint8_t r1;
    uint8_t buff[6] = { 0 }; // Buffer for OCR or R7 response
    uint16_t retry;
    uint8_t i;

    // Send dummy clocks to initialize the SD card
    SD_CS(0);
    for (retry = 0; retry < 10; retry++)
    {
        SPI_SendByte(DFF);
    }

    // Put SD card into IDLE state using CMD0
    do
    {
        r1 = SD_sendcmd(CMD0, 0, 0x95);
    } while (r1 != 0x01);

    // Check SD card type
    SD_TYPE = 0;
    r1      = SD_sendcmd(CMD8, 0x1AA, 0x87);
    if (r1 == 0x01)
    {
        for (i = 0; i < 4; i++)
            buff[i] = SPI_SendByte(DFF);        // Retrieve R7 response
        if (buff[2] == 0x01 && buff[3] == 0xAA) // Check voltage range
        {
            retry = 0xFFFE;
            do
            {
                SD_sendcmd(CMD55, 0, 0x01);               // Send CMD55
                r1 = SD_sendcmd(CMD41, 0x40000000, 0x01); // Send CMD41
            } while (r1 && retry--);
            if (retry && SD_sendcmd(CMD58, 0, 0x01) == 0) // Check OCR for SDHC/SDXC
            {
                for (i = 0; i < 4; i++)
                    buff[i] = SPI_SendByte(0xFF); // Retrieve OCR
                if (buff[0] & 0x40)
                {
                    SD_TYPE = V2HC; // SDHC/SDXC
                }
                else
                {
                    SD_TYPE = V2; // SDSC V2.0
                }
            }
        }
    }
    else
    {
        // Handle SDSC V1.0 or MMC
        SD_sendcmd(CMD55, 0, 0x01);      // Send CMD55
        r1 = SD_sendcmd(CMD41, 0, 0x01); // Send CMD41
        if (r1 <= 1)
        {
            SD_TYPE = V1; // SDSC V1.0
            retry   = 0xFFFE;
            do
            {
                SD_sendcmd(CMD55, 0, 0x01);      // Send CMD55
                r1 = SD_sendcmd(CMD41, 0, 0x01); // Send CMD41
            } while (r1 && retry--);
        }
        else
        {
            SD_TYPE = MMC; // MMC V3
            retry   = 0xFFFE;
            do
            {
                r1 = SD_sendcmd(CMD1, 0, 0x01); // Send CMD1
            } while (r1 && retry--);
        }
        if (retry == 0 || SD_sendcmd(CMD16, 512, 0x01) != 0)
        {
            SD_TYPE = ERR; // Invalid card
        }
    }

    SD_CS(0); // Deselect SD card

    // Return initialization status
    if (SD_TYPE)
        return 0; // Initialization successful
    else
        return 1; // Initialization failed
}

/**
 * @brief  Receives a block of data from the SD card.
 * @param  data: Pointer to the buffer where the received data will be stored.
 * @param  len: Length of the data block to be received in bytes.
 * @note   This function waits for a start token (0xFE) from the SD card to
 *         indicate the beginning of data transmission. It then reads the
 *         specified number of bytes into the provided buffer and sends
 *         two additional dummy bytes as CRC.
 * @retval 0: Data received successfully.
 */
uint8_t SD_ReceiveData(uint8_t *data, uint16_t len)
{
    uint8_t r1;

    // Activate the SD card by pulling CS low
    SD_CS(1);

    // Wait for the start token (0xFE)
    do
    {
        r1 = SPI_SendByte(0xFF);
        DEVICE_DELAY_US(100); // Add a delay between retries
    } while (r1 != 0xFE);

    // Read the specified number of bytes
    while (len--)
    {
        *data = SPI_SendByte(0xFF);
        data++;
    }

    // Send two dummy bytes for CRC
    SPI_SendByte(0xFF);
    SPI_SendByte(0xFF);

    return 0; // Data received successfully
}

/**
 * @brief  Sends a data block to the SD card.
 * @param  buf: Pointer to the data buffer containing the block to be sent.
 * @param  cmd: Command token indicating the type of operation.
 *              - 0xFD: Stop transmission command.
 *              - Other values: Write data block.
 * @note   This function waits until the SD card is ready to accept a new block,
 *         then transmits the block, ignoring CRC. The function also checks the
 *         response from the SD card after transmission to ensure successful write.
 * @retval Status:
 *         - 0: Block sent successfully.
 *         - 2: Response error or block not accepted by the SD card.
 */
uint8_t SD_SendBlock(uint8_t *buf, uint8_t cmd)
{
    uint16_t t;
    uint8_t r1;

    // Wait until the SD card is ready (0xFF)
    do
    {
        r1 = SPI_SendByte(0xFF);
    } while (r1 != 0xFF);

    // Send the command token
    SPI_SendByte(cmd);

    // If not a stop transmission command, send the data block
    if (cmd != 0xFD)
    {
        // Transmit the 512-byte data block
        for (t = 0; t < 512; t++)
            SPI_SendByte(buf[t]);

        // Send dummy CRC (not used in SPI mode)
        SPI_SendByte(0xFF);
        SPI_SendByte(0xFF);

        // Read the response token
        t = SPI_SendByte(0xFF);
        if ((t & 0x1F) != 0x05)
            return 2; // Response error
    }

    return 0; // Block sent successfully
}

/**
 * @brief  Retrieves the CID (Card Identification) data from the SD card.
 * @param  cid_data: Pointer to the buffer where the CID data will be stored.
 * @note   This function sends the CMD10 to the SD card to read the CID register,
 *         and then receives the 16-byte CID data from the SD card into the provided buffer.
 * @retval Status:
 *         - 0: CID data retrieved successfully.
 *         - 1: Error in retrieving CID data.
 */
uint8_t SD_GETCID(uint8_t *cid_data)
{
    uint8_t r1;

    // Send CMD10 to read the CID register
    r1 = SD_sendcmd(CMD10, 0, 0x01);
    if (r1 == 0x00)
    {
        // Receive the 16-byte CID data
        r1 = SD_ReceiveData(cid_data, 16);
    }

    // Deselect SD card
    SD_CS(0);

    // Return status based on result
    if (r1)
        return 1; // Error
    else
        return 0; // Success
}

/**
 * @brief  Retrieves the CSD (Card Specific Data) from the SD card.
 * @param  csd_data: Pointer to the buffer where the CSD data will be stored.
 * @note   This function sends the CMD9 to the SD card to read the CSD register,
 *         and then receives the 16-byte CSD data from the SD card into the provided buffer.
 * @retval Status:
 *         - 0: CSD data retrieved successfully.
 *         - 1: Error in retrieving CSD data.
 */
uint8_t SD_GETCSD(uint8_t *csd_data)
{
    uint8_t r1;

    // Send CMD9 to read the CSD register
    r1 = SD_sendcmd(CMD9, 0, 0x01);
    if (r1 == 0)
    {
        // Receive the 16-byte CSD data
        r1 = SD_ReceiveData(csd_data, 16);
    }

    // Deselect SD card
    SD_CS(0);

    // Return status based on result
    if (r1)
        return 1; // Error
    else
        return 0; // Success
}

/**
 * @brief  Retrieves the total number of sectors of the SD card.
 * @note   This function reads the CSD register from the SD card to determine its capacity.
 *         The calculation depends on whether the card is a V1.XX or V2.00 card, as the
 *         method for computing the number of sectors differs.
 * @retval The number of sectors on the SD card, or 0 if an error occurs while retrieving CSD data.
 */
uint32_t SD_GetSectorCount(void)
{
    uint8_t csd[16];
    uint32_t Capacity;
    uint8_t n;
    uint16_t csize;

    // Retrieve CSD data from the SD card
    if (SD_GETCSD(csd) != 0)
        return 0; // Error in reading CSD data

    // If it's an SDHC card (V2.00), calculate sector count based on CSD values
    if ((csd[0] & 0xC0) == 0x40) // SDHC card (V2.00)
    {
        csize    = csd[9] + ((uint16_t)csd[8] << 8) + 1;
        Capacity = (uint32_t)csize << 10; // Calculate sector count
    }
    else // If it's an SD card (V1.XX), calculate sector count differently
    {
        n        = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
        csize    = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
        Capacity = (uint32_t)csize << (n - 9); // Calculate sector count
    }

    return Capacity; // Return total number of sectors
}

/**
 * @brief  Retrieves basic information of the SD card, including the content of CSD and CID
 * registers.
 * @param  SD0_CardInfo: A pointer to an SD_CARDINFO structure where the card information will be
 * stored.
 * @retval Return value:
 *         - 0: Success
 *         - 1: Failed to receive CSD data
 *         - 2: Failed to receive CID data
 *         - Other: Error code if command execution fails
 *
 * @note   This function first sends CMD9 to read the CSD register, then sends CMD10 to read the CID
 * register. The received data is stored in the SD0_CardInfo structure in corresponding fields. The
 * CSD and CID contents are parsed into individual fields for further usage. If the card type is
 * V2HC, additional device size processing is performed.
 */
int MSD0_GetCardInfo(PMSD_CARDINFO SD0_CardInfo)
{
    uint8_t r1;
    uint8_t CSD_Tab[16];
    uint8_t CID_Tab[16];

    /* Send CMD9 to read CSD register */
    r1 = SD_sendcmd(CMD9, 0, 0xFF);
    if (r1 != 0x00)
    {
        return r1; /* Return error code if command fails */
    }

    if (SD_ReceiveData(CSD_Tab, 16)) /* Receive CSD data */
    {
        return 1; /* Return 1 if receiving data fails */
    }

    /* Send CMD10 to read CID register */
    r1 = SD_sendcmd(CMD10, 0, 0xFF);
    if (r1 != 0x00)
    {
        return r1; /* Return error code if command fails */
    }

    if (SD_ReceiveData(CID_Tab, 16)) /* Receive CID data */
    {
        return 2; /* Return 2 if receiving data fails */
    }

    /* Parse the CSD register fields */
    SD0_CardInfo->CSD.CSDStruct       = (CSD_Tab[0] & 0xC0) >> 6;
    SD0_CardInfo->CSD.SysSpecVersion  = (CSD_Tab[0] & 0x3C) >> 2;
    SD0_CardInfo->CSD.Reserved1       = CSD_Tab[0] & 0x03;
    SD0_CardInfo->CSD.TAAC            = CSD_Tab[1];
    SD0_CardInfo->CSD.NSAC            = CSD_Tab[2];
    SD0_CardInfo->CSD.MaxBusClkFrec   = CSD_Tab[3];
    SD0_CardInfo->CSD.CardComdClasses = CSD_Tab[4] << 4;
    SD0_CardInfo->CSD.CardComdClasses |= (CSD_Tab[5] & 0xF0) >> 4;
    SD0_CardInfo->CSD.RdBlockLen      = CSD_Tab[5] & 0x0F;
    SD0_CardInfo->CSD.PartBlockRead   = (CSD_Tab[6] & 0x80) >> 7;
    SD0_CardInfo->CSD.WrBlockMisalign = (CSD_Tab[6] & 0x40) >> 6;
    SD0_CardInfo->CSD.RdBlockMisalign = (CSD_Tab[6] & 0x20) >> 5;
    SD0_CardInfo->CSD.DSRImpl         = (CSD_Tab[6] & 0x10) >> 4;
    SD0_CardInfo->CSD.Reserved2       = 0; /* Reserved */
    SD0_CardInfo->CSD.DeviceSize      = (CSD_Tab[6] & 0x03) << 10;
    SD0_CardInfo->CSD.DeviceSize |= (CSD_Tab[7]) << 2;
    SD0_CardInfo->CSD.DeviceSize |= (CSD_Tab[8] & 0xC0) >> 6;
    SD0_CardInfo->CSD.MaxRdCurrentVDDMin = (CSD_Tab[8] & 0x38) >> 3;
    SD0_CardInfo->CSD.MaxRdCurrentVDDMax = (CSD_Tab[8] & 0x07);
    SD0_CardInfo->CSD.MaxWrCurrentVDDMin = (CSD_Tab[9] & 0xE0) >> 5;
    SD0_CardInfo->CSD.MaxWrCurrentVDDMax = (CSD_Tab[9] & 0x1C) >> 2;
    SD0_CardInfo->CSD.DeviceSizeMul      = (CSD_Tab[9] & 0x03) << 1;
    SD0_CardInfo->CSD.DeviceSizeMul |= (CSD_Tab[10] & 0x80) >> 7;
    SD0_CardInfo->CSD.EraseGrSize = (CSD_Tab[10] & 0x7C) >> 2;
    SD0_CardInfo->CSD.EraseGrMul  = (CSD_Tab[10] & 0x03) << 3;
    SD0_CardInfo->CSD.EraseGrMul |= (CSD_Tab[11] & 0xE0) >> 5;
    SD0_CardInfo->CSD.WrProtectGrSize   = (CSD_Tab[11] & 0x1F);
    SD0_CardInfo->CSD.WrProtectGrEnable = (CSD_Tab[12] & 0x80) >> 7;
    SD0_CardInfo->CSD.ManDeflECC        = (CSD_Tab[12] & 0x60) >> 5;
    SD0_CardInfo->CSD.WrSpeedFact       = (CSD_Tab[12] & 0x1C) >> 2;
    SD0_CardInfo->CSD.MaxWrBlockLen     = (CSD_Tab[12] & 0x03) << 2;
    SD0_CardInfo->CSD.MaxWrBlockLen |= (CSD_Tab[13] & 0xc0) >> 6;
    SD0_CardInfo->CSD.WriteBlockPaPartial = (CSD_Tab[13] & 0x20) >> 5;
    SD0_CardInfo->CSD.Reserved3           = 0;
    SD0_CardInfo->CSD.ContentProtectAppli = (CSD_Tab[13] & 0x01);
    SD0_CardInfo->CSD.FileFormatGrouop    = (CSD_Tab[14] & 0x80) >> 7;
    SD0_CardInfo->CSD.CopyFlag            = (CSD_Tab[14] & 0x40) >> 6;
    SD0_CardInfo->CSD.PermWrProtect       = (CSD_Tab[14] & 0x20) >> 5;
    SD0_CardInfo->CSD.TempWrProtect       = (CSD_Tab[14] & 0x10) >> 4;
    SD0_CardInfo->CSD.FileFormat          = (CSD_Tab[14] & 0x0C) >> 2;
    SD0_CardInfo->CSD.ECC                 = (CSD_Tab[14] & 0x03);
    SD0_CardInfo->CSD.CSD_CRC             = (CSD_Tab[15] & 0xFE) >> 1;
    SD0_CardInfo->CSD.Reserved4           = 1;

    /* If it's a V2HC card, perform additional device size processing */
    if (SD0_CardInfo->CardType == V2HC)
    {
        SD0_CardInfo->CSD.DeviceSize = (uint16_t)(CSD_Tab[8]) * 256;
        SD0_CardInfo->CSD.DeviceSize += CSD_Tab[9];
    }

    /* Calculate the card's capacity and block size */
    SD0_CardInfo->Capacity  = SD0_CardInfo->CSD.DeviceSize * MSD_BLOCKSIZE * 1024;
    SD0_CardInfo->BlockSize = MSD_BLOCKSIZE;

    /* Parse the CID register fields */
    SD0_CardInfo->CID.ManufacturerID = CID_Tab[0];
    SD0_CardInfo->CID.OEM_AppliID    = CID_Tab[1] << 8;
    SD0_CardInfo->CID.OEM_AppliID |= CID_Tab[2];
    SD0_CardInfo->CID.ProdName1 = CID_Tab[3] << 24;
    SD0_CardInfo->CID.ProdName1 |= CID_Tab[4] << 16;
    SD0_CardInfo->CID.ProdName1 |= CID_Tab[5] << 8;
    SD0_CardInfo->CID.ProdName1 |= CID_Tab[6];
    SD0_CardInfo->CID.ProdName2 = CID_Tab[7];
    SD0_CardInfo->CID.ProdRev   = CID_Tab[8];
    SD0_CardInfo->CID.ProdSN    = CID_Tab[9] << 24;
    SD0_CardInfo->CID.ProdSN |= CID_Tab[10] << 16;
    SD0_CardInfo->CID.ProdSN |= CID_Tab[11] << 8;
    SD0_CardInfo->CID.ProdSN |= CID_Tab[12];
    SD0_CardInfo->CID.Reserved1 |= (CID_Tab[13] & 0xF0) >> 4;
    SD0_CardInfo->CID.CID_CRC = (CID_Tab[13] & 0x0F);
    return 0;
}

/**
 * @brief  Writes data to the SD card.
 * @param  buf: Pointer to the buffer containing the data to be written.
 * @param  sector: The sector number to write data to.
 * @param  cnt: The number of 512-byte blocks to write.
 * @retval Return value:
 *         - 0: Success
 *         - Non-zero: Error code
 *
 * @note   If the SD card type is not V2HC, the sector address is multiplied by 512 to convert it to
 * byte address. CMD24 is used for writing a single block, while CMD25 is used for writing multiple
 * blocks.
 */
uint8_t SD_WriteDisk(uint8_t *buf, uint32_t sector, uint8_t cnt)
{
    uint8_t r1;

    /* If the card is not V2HC, convert sector to byte address */
    if (SD_TYPE != V2HC)
        sector *= 512;

    if (cnt == 1)
    {
        /* Send CMD24 to write a single block */
        r1 = SD_sendcmd(CMD24, sector, 0X01);
        if (r1 == 0) // Command sent successfully
        {
            /* Send the block of data */
            r1 = SD_SendBlock(buf, 0xFE); // Write 512 bytes
        }
    }
    else
    {
        /* For non-MMC cards, send CMD55 and CMD23 */
        if (SD_TYPE != MMC)
        {
            SD_sendcmd(CMD55, 0, 0X01);
            SD_sendcmd(CMD23, cnt, 0X01); // Set block count for continuous write
        }

        /* Send CMD25 to start writing multiple blocks */
        r1 = SD_sendcmd(CMD25, sector, 0X01);
        if (r1 == 0)
        {
            do
            {
                /* Send each block of data */
                r1 = SD_SendBlock(buf, 0xFC); // Write 512 bytes
                buf += 512;                   // Move to the next block
            } while (--cnt && r1 == 0);

            /* Send last block with end signal */
            r1 = SD_SendBlock(0, 0xFD); // Write 512 bytes and send stop command
        }
    }

    /* Deactivate chip select */
    SD_CS(0);
    return r1; // Return the result of the operation
}

/**
 * @brief  Reads data from the SD card.
 * @param  buf: Pointer to the buffer where the read data will be stored.
 * @param  sector: The sector number to start reading from.
 * @param  cnt: The number of 512-byte blocks to read.
 * @retval Return value:
 *         - 0: Success
 *         - Non-zero: Error code
 *
 * @note   If the SD card type is not V2HC, the sector address is shifted left by 9 to convert it to
 * byte address. CMD17 is used for reading a single block, while CMD18 is used for reading multiple
 * blocks.
 */
uint8_t SD_ReadDisk(uint8_t *buf, uint32_t sector, uint8_t cnt)
{
    uint8_t r1;

    /* If the card is not V2HC, convert sector to byte address */
    if (SD_TYPE != V2HC)
        sector <<= 9; // Shift left by 9 to convert to byte address

    if (cnt == 1)
    {
        /* Send CMD17 to read a single block */
        r1 = SD_sendcmd(CMD17, sector, 0X01);
        if (r1 == 0) // Command sent successfully
        {
            /* Receive the block of data */
            r1 = SD_ReceiveData(buf, 512); // Read 512 bytes
        }
    }
    else
    {
        /* Send CMD18 to start reading multiple blocks */
        r1 = SD_sendcmd(CMD18, sector, 0X01);
        do
        {
            /* Receive each block of data */
            r1 = SD_ReceiveData(buf, 512); // Read 512 bytes
            buf += 512;                    // Move to the next block
        } while (--cnt && r1 == 0);

        /* Send CMD12 to stop the multiple block read operation */
        SD_sendcmd(CMD12, 0, 0X01); // Send stop command
    }

    /* Deactivate chip select */
    SD_CS(0);
    return r1; // Return the result of the operation
}

/**
 * @brief  Performs a single block read/write test on the SD card.
 * @retval None
 *
 * @note   This function writes a single block of data to the SD card, reads it back,
 *         and compares the written and read data to verify the integrity of the operation.
 */
void SD_SingleBlockTest(void)
{
    uint8_t tx_flag, rx_flag;

    /*------------------- Block Read/Write --------------------------*/
    /* Fill the buffer with test data to send */
    Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320F);

    /* Write the data to the SD card */
    tx_flag = SD_WriteDisk(Buffer_Block_Tx, 0x00, 1);
    if (tx_flag == 0)
    {
        printf("Single block write successful\n"); // Print success message for write
    }
    else
    {
        printf("Single block write failed\n"); // Print failure message for write
    }

    /* Read the data back from the SD card */
    rx_flag = SD_ReadDisk(Buffer_Block_Rx, 0x00, 1);
    if (rx_flag == 0)
    {
        printf("Single block read successful\n"); // Print success message for read
    }
    else
    {
        printf("Single block read failed\n"); // Print failure message for read
    }

    /* Compare the written and read data */
    TransferStatus1 = Buffercmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);

    if (TransferStatus1 == PASSED)
    {
        printf("Single block test passed!\n"); // Print success message for test
    }
    else
    {
        printf("Single block test failed. Please ensure the SD card is correctly connected to the "
               "development board or try a different SD card!\n"); // Print failure message for test
    }
}

/**
 * @brief  Performs a multiple block read/write test on the SD card.
 * @retval None
 *
 * @note   This function writes multiple blocks of data to the SD card, reads them back,
 *         and compares the written and read data to verify the integrity of the operation.
 */
void SD_MultiBlockTest(void)
{
    uint8_t tx_flag, rx_flag;

    /*--------------- Multiple Block Read/Write ---------------------*/
    /* Fill the buffer with test data to send */
    Fill_Buffer(Buffer_MultiBlock_Tx, MULTI_BUFFER_SIZE, 0x0);

    /* Write multiple blocks of data to the SD card */
    tx_flag = SD_WriteDisk(Buffer_MultiBlock_Tx, 0x00, NUMBER_OF_BLOCKS);
    //    tx_flag = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

    if (tx_flag == 0)
    {
        printf("Multi block write successful\n"); // Print success message for write
    }
    else
    {
        printf("Multi block write failed\n"); // Print failure message for write
    }

    /* Read multiple blocks of data from the SD card */
    rx_flag = SD_ReadDisk(Buffer_MultiBlock_Rx, 0x00, NUMBER_OF_BLOCKS);
    //    rx_flag = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);

    if (rx_flag == 0)
    {
        printf("Multi block read successful\n"); // Print success message for read
    }
    else
    {
        printf("Multi block read failed\n"); // Print failure message for read
    }

    /* Compare the written and read data */
    TransferStatus2 = Buffercmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, MULTI_BUFFER_SIZE);

    if (TransferStatus2 == PASSED)
    {
        printf("Multi block test passed!\n"); // Print success message for test
    }
    else
    {
        printf("Multi block test failed. Please ensure the SD card is correctly connected to the "
               "development board or try a different SD card!\n"); // Print failure message for test
    }
}

/**
 * @brief  Fills a buffer with sequential data starting from a specified offset.
 * @param  pBuffer: Pointer to the buffer to be filled.
 * @param  BufferLength: The length of the buffer to be filled.
 * @param  Offset: The starting value to be added to each buffer element.
 * @retval None
 *
 * @note   This function fills the buffer with sequential values starting from the given offset.
 *         Each element in the buffer will have a value equal to its index + the offset.
 */
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset)
{
    uint16_t index = 0;

    /* Fill the buffer with sequential values, starting from the offset */
    for (index = 0; index < BufferLength; index++)
    {
        pBuffer[index] = index + Offset;
    }
}

/**
 * @brief  Compares two buffers byte by byte.
 * @param  pBuffer1: Pointer to the first buffer.
 * @param  pBuffer2: Pointer to the second buffer.
 * @param  BufferLength: The length of the buffers to compare.
 * @retval TestStatus: Result of the comparison (PASSED or FAILED).
 *
 * @note   This function compares two buffers of the same length byte by byte.
 *         If any byte differs between the two buffers, the function returns FAILED.
 *         If all bytes are the same, it returns PASSED.
 */
TestStatus Buffercmp(uint8_t *pBuffer1, uint8_t *pBuffer2, uint32_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED; // Return FAILED if any byte is different
        }

        pBuffer1++; // Move to the next byte in the first buffer
        pBuffer2++; // Move to the next byte in the second buffer
    }

    return PASSED; // Return PASSED if all bytes are the same
}

/**
 * @brief  SD card test function to initialize the SD card and perform read/write tests.
 * @retval None
 *
 * This function initializes the SD card and runs both single-block and multi-block read/write
 * tests. If initialization fails, it outputs an error message. If initialization is successful, it
 * proceeds to test the read/write operations for both single and multiple blocks.
 */
void SD_Test(void)
{
    uint8_t sd_initflag = 1;

    /* SD Initialization */
    sd_initflag = SD_init();

    if (sd_initflag != 0)
    {
        printf("SD card initialization failed. Please ensure the SD card is properly connected to "
               "the development board, or try a different SD card.\n");
    }
    else
    {
        printf("SD card initialization successful!\n");
    }

    if (sd_initflag == 0)
    {
        /* Single block read/write test */
        SD_SingleBlockTest();

        /* Multi-block read/write test */
        SD_MultiBlockTest();
    }
}

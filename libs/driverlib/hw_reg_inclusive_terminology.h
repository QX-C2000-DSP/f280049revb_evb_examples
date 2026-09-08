#ifndef HW_REG_INCLUSIVE_TERMINOLOGY_H
#define HW_REG_INCLUSIVE_TERMINOLOGY_H

//*****************************************************************************
// FSI
//*****************************************************************************
#define FSI_O_TX_MAIN_CTRL FSI_O_TX_MASTER_CTRL
#define FSI_O_RX_MAIN_CTRL FSI_O_RX_MASTER_CTRL

#define FSI_TX_MAIN_CTRL_CORE_RST FSI_TX_MASTER_CTRL_CORE_RST
#define FSI_TX_MAIN_CTRL_FLUSH    FSI_TX_MASTER_CTRL_FLUSH
#define FSI_TX_MAIN_CTRL_KEY_S    FSI_TX_MASTER_CTRL_KEY_S
#define FSI_TX_MAIN_CTRL_KEY_M    FSI_TX_MASTER_CTRL_KEY_M

#define FSI_RX_MAIN_CTRL_CORE_RST       FSI_RX_MASTER_CTRL_CORE_RST
#define FSI_RX_MAIN_CTRL_INT_LOOPBACK   FSI_RX_MASTER_CTRL_INT_LOOPBACK
#define FSI_RX_MAIN_CTRL_SPI_PAIRING    FSI_RX_MASTER_CTRL_SPI_PAIRING
#define FSI_RX_MAIN_CTRL_INPUT_ISOLATE  FSI_RX_MASTER_CTRL_INPUT_ISOLATE
#define FSI_RX_MAIN_CTRL_DATA_FILTER_EN FSI_RX_MASTER_CTRL_DATA_FILTER_EN
#define FSI_RX_MAIN_CTRL_KEY_S          FSI_RX_MASTER_CTRL_KEY_S
#define FSI_RX_MAIN_CTRL_KEY_M          FSI_RX_MASTER_CTRL_KEY_M

//*****************************************************************************
// SPI
//*****************************************************************************
#define SPI_CTL_CONTROLLER_PERIPHERAL SPI_CTL_MASTER_SLAVE
#define SPI_PRI_PTEINV                SPI_PRI_STEINV

//*****************************************************************************
// I2C
//*****************************************************************************
#define I2C_O_TAR I2C_O_SAR

#define I2C_TAR_TAR_S I2C_SAR_SAR_S
#define I2C_TAR_TAR_M I2C_SAR_SAR_M

#define I2C_IER_AAT I2C_IER_AAS

#define I2C_STR_AAT  I2C_STR_AAS
#define I2C_STR_TDIR I2C_STR_SDIR

#define I2C_MDR_CNT I2C_MDR_MST

#endif // HW_REG_INCLUSIVE_TERMINOLOGY_H

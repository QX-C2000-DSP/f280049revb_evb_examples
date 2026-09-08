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
*   @file    w25q64.h
*   @brief   
*
*/

#ifndef _W25Q64_H_
#define _W25Q64_H_

#ifdef __cplusplus
extern "C"{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "inc/hw_types.h"



#define READ_JEDEC_ID    0x9F            /*!<read chip ID */
#define READ_STATUS_REG1   0x05            /*!< read status register-1 */
#define WRITE_STATUS_REG   0x01            /*!< write status registe-1 */
#define READ_STATUS_REG2   0x35            /*!< read status register-2 */
#define WRITE_ENABLE    0x06            /*!< write enablewaitDeviceReady */
#define WRITE_DISABLE    0x04            /*!< write disable */
#define READ_DATA    0x03            /*!< read data bytes */
#define SECTOR_ERASE              0x20    /*!< sector erase */
#define PAGE_PROGRAM              0x02    /*!< page program */

#define W25Q64_DUMMY_BYTE 0xFF

#define MAX_TIMEOUT (uint32_t)0x0000FFFF


int32_t w25q64_init(uint32_t spi_base);
int32_t w25q64_write_enable(uint32_t dev);
int32_t w25q64_write_disable(uint32_t dev);
int32_t w25q64_erase(uint32_t dev, uint32_t address, uint32_t size);
int32_t w25q64_write(uint32_t dev, uint32_t address, uint32_t size, const void *data);
extern int32_t w25q64_read(uint32_t dev, uint32_t address, uint32_t size, void *data);
extern uint32_t w25q64_read_jedec_id(void);
extern uint32_t w25q64_read_device_id(uint32_t base);

#ifdef __cplusplus
}
#endif


#endif /* _W25Q64_H_ */

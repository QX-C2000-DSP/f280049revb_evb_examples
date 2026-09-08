#ifndef BOARD_H_
#define BOARD_H_

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"
//*****************************************************************************
//
// DCSM Configurations
//
//*****************************************************************************

#define B0Z1_link1         0x80000000
#define B0Z1_link2         0x80000001
#define B0Z1_link3         0x80000002
#define B0Z1_gpreg1        0x80000003
#define B0Z1_gpreg2        0x80000004
#define B0Z1_pswdlock      0x80000005
#define B0Z1_crclock       0x80000006
#define B0Z1_jtaglock      0x80000007
#define B0Z1_gpreg3        0x80000008
#define B0Z1_bootctrl      0x80000009
#define B0Z1_exeonlyram    0x8000000A
#define B0Z1_exeonlysect   0x8000000B
#define B0Z1_grabram       0x8000000C
#define B0Z1_grabsect      0x8000000D
#define B0Z1_csmpswd0      0x8000000E
#define B0Z1_csmpswd1      0x8000000F
#define B0Z1_csmpswd2      0x80000010
#define B0Z1_csmpswd3      0x80000011
#define B0Z1_csmkey0       0x80000012
#define B0Z1_csmkey1       0x80000013
#define B0Z1_csmkey2       0x80000014
#define B0Z1_csmkey3       0x80000015

#define B0Z2_link1         0xA0000000
#define B0Z2_link2         0xA0000001
#define B0Z2_link3         0xA0000002
#define B0Z2_pswdlock      0xA0000005
#define B0Z2_crclock       0xA0000006
#define B0Z2_jtaglock      0xA0000007
#define B0Z2_exeonlyram    0xA000000A
#define B0Z2_exeonlysect   0xA000000B
#define B0Z2_grabram       0xA000000C
#define B0Z2_grabsect      0xA000000D
#define B0Z2_csmpswd0      0xA000000E
#define B0Z2_csmpswd1      0xA000000F
#define B0Z2_csmpswd2      0xA0000010
#define B0Z2_csmpswd3      0xA0000011
#define B0Z2_csmkey0       0xA0000012
#define B0Z2_csmkey1       0xA0000013
#define B0Z2_csmkey2       0xA0000014
#define B0Z2_csmkey3       0xA0000015

#define B1Z1_link1         0xC0000000
#define B1Z1_link2         0xC0000001
#define B1Z1_link3         0xC0000002
#define B1Z1_jtaglock      0xC0000007
#define B1Z1_exeonlysect   0xC000000B
#define B1Z1_grabsect      0xC000000D

#define B1Z2_link1         0xE0000000
#define B1Z2_link2         0xE0000001
#define B1Z2_link3         0xE0000002
#define B1Z2_jtaglock      0xE0000007
#define B1Z2_exeonlysect   0xE000000B
#define B1Z2_grabsect      0xE000000D

#define DCSM_LINK_LOCATION         0x30004000
#define DCSM_GRABSECT_LOCATION     0x3000404C
#define UNCONFIGURED_LINK_VALUE    0xFFFFFFFF
#define CONFIGURED_LINK_VALUE      0xFFFFFFFE
#define CONFIGURED_GARBSECT_ONE    0xFFFFFFFD

uint32_t read_flash(u32 flash_addr);
void DCSM_unlockZone1(const DCSM_CSMPasswordKey * const psCMDKey);
void DCSM_lockZone1(void) ;
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif


#endif /* BOARD_H_ */

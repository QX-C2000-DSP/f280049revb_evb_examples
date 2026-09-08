.global _dsp_boot0_start
.global _dsp_boot1_start
.global _dsp_boot_jmp_to_core
.extern qx_bootloader_main

.section .text.qxboot0
_dsp_boot0_start:
# Core0Boot_AcquireAllSRAM
movigh gr3 0x0100||
movigl gr3 0x1000||
moviglz gr2 0x0||
||store32 gr2 gr3 0xc8
||store32 gr2 gr3 0xc9

movigh GR30 %hi16(_BOOT_LOADER_SP)||
movigl GR30 %lo16(_BOOT_LOADER_SP)||
jmp qx_bootloader_main||
nop||
nop||

.section .text.qxboot1
_dsp_boot1_start:
movigh GR30 %hi16(_BOOT_LOADER_SP)||
movigl GR30 %lo16(_BOOT_LOADER_SP)||
jmp qx_bootloader_main||
nop||
nop||

.section .text.qxboot
_dsp_boot_jmp_to_core:
jmpr GR4||
nop||
nop||

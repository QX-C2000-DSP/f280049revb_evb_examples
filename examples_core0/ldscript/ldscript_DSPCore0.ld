OUTPUT_FORMAT("elf32-dsp")

ENTRY(_dsp_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __data_start__ = ORIGIN(GS_RAM_RESERVED);
  . = __data_start__;
  .fill   : { LONG(0xDEADBEEF)        } > GS_RAM_RESERVED
  .rodata : { *(.rodata) *(.rodata.*) } > GS_RAM_CORE0_DATA
  .data   : { *(.data)   *(.data.*)   } > GS_RAM_CORE0_DATA
  .sdata  : { *(.sdata)  *(.sdata.*)  } > GS_RAM_CORE0_DATA
  __bss_start = .;
  .sbss   : { *(.sbss) *(.sbss.*) *(.scommon) } > GS_RAM_CORE0_DATA
  .bss    : { *(.bss)  *(.bss.*)  *(COMMON)   } > GS_RAM_CORE0_DATA
  __data_end__ = .;

  /* let .noinit_data out of FLASH image range, and align to 0x100 (256B)
   * to fit bootloader copy FLASH to SRAM DMA config.
   */
  .noinit_data(NOLOAD) : {
    . = ALIGN(0x100);
    *(.noinit_data)
  } > GS_RAM_CORE0_DATA

  /* for fake bootloader when debugging on RAM */
  .text.qxbootdebug : {
    KEEP(*(.text.qxboot0debug))
    *(.text.qxbootinit)
    . = ALIGN(0x10);
  } > BOOT_RAM_CORE0 =0x00000080
  
  .shared_var_CPU1toCPU2(NOLOAD) : {
    KEEP(*(.shared_var_CPU1toCPU2_sec0))
    KEEP(*(.shared_var_CPU1toCPU2_sec1))
    KEEP(*(.shared_var_CPU1toCPU2_sec2))
    KEEP(*(.shared_var_CPU1toCPU2_sec3))
  } > IPC_CPU0_RAM
  
  .shared_var_CPU2toCPU1(NOLOAD) : {
    KEEP(*(.shared_var_CPU2toCPU1_sec0))
    KEEP(*(.shared_var_CPU2toCPU1_sec1))
    KEEP(*(.shared_var_CPU2toCPU1_sec2))
    KEEP(*(.shared_var_CPU2toCPU1_sec3))
  } > IPC_CPU1_RAM
  
  __text_start__ = ORIGIN(GS_RAM_CORE0_INST);
  . = __text_start__;
  .text : {
    KEEP(*(.text.interrupt.vector))
    KEEP(*(.text.interrupt.routine))
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > GS_RAM_CORE0_INST =0x00000080
  __text_end__ = .;
  
  /*
   * XINTF instruction and data
   */
  __xintf_data_start__ = ORIGIN(XINTF_Zone6);
  . = __xintf_data_start__;
  .xintf.rodata : { *(.xintf_rodata) *(.xintf_rodata.*) } > XINTF_Zone6
  .xintf.data   : { *(.xintf_data)   *(.xintf_data.*)   } > XINTF_Zone6
  __xintf_bss_start = .;
  .xintf.bss    : { *(.xintf_bss)    *(.xintf_bss.*)    } > XINTF_Zone6
  __xintf_data_end__ = .;
  
  . = ALIGN(0x10);
  
  __xintf_text_start__ = .;
  . = __xintf_text_start__;
  .xintf.text   : {
    *(.xintf_text)
    *(.xintf_text.*)
    . = ALIGN(0x10);
  } > XINTF_Zone6 =0x00000080
  __xintf_text_end__ = .;

  PIEVECTTABLE_BASE = ORIGIN(GS_RAM_CORE0_IVEC);

  PROVIDE(_DSP_STACK_TOP = ORIGIN(GS_RAM_CORE0_DATA) + LENGTH(GS_RAM_CORE0_DATA));

  PROVIDE(_core0_exp_start = (ORIGIN(GS_RAM_CORE0_INST) >> 15) & 0xF);
  PROVIDE(_core1_exp_start = (ORIGIN(GS_RAM_CORE1_INST) >> 15) & 0xF);

  PROVIDE(_CORE0_IRAM_START = ORIGIN(GS_RAM_CORE0_INST));
  PROVIDE(_CORE1_IRAM_START = ORIGIN(GS_RAM_CORE1_INST));

  PROVIDE(__end = __data_end__);
  PROVIDE(__stack_end = ORIGIN(GS_RAM_CORE0_DATA) + LENGTH(GS_RAM_CORE0_DATA) - LENGTH(STACK_CORE0));
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"

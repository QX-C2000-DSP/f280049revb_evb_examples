OUTPUT_FORMAT("elf32-dsp")

ENTRY(_dsp_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __data_start__ = ORIGIN(GS_RAM_CORE1_DATA);
  . = __data_start__;
  .rodata : { *(.rodata) *(.rodata.*) } > GS_RAM_CORE1_DATA
  .data   : { *(.data)   *(.data.*)   } > GS_RAM_CORE1_DATA
  .sdata  : { *(.sdata)  *(.sdata.*)  } > GS_RAM_CORE1_DATA
  __bss_start = .;
  .sbss   : { *(.sbss) *(.sbss.*) *(.scommon) } > GS_RAM_CORE1_DATA
  .bss    : { *(.bss)  *(.bss.*)  *(COMMON)   } > GS_RAM_CORE1_DATA
  __data_end__ = .;

  /* let .noinit_data out of FLASH image range, and align to 0x100 (256B)
   * to fit bootloader copy FLASH to SRAM DMA config.
   */
  .noinit_data(NOLOAD) : {
    . = ALIGN(0x100);
    *(.noinit_data)
  } > GS_RAM_CORE1_DATA

  /* for fake bootloader when debugging on RAM */
  .text.qxbootdebug : {
    KEEP(*(.text.qxboot1debug))
    . = ALIGN(0x10);
  } > BOOT_RAM_CORE1 =0x00000080


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
  
  
  __text_start__ = ORIGIN(GS_RAM_CORE1_INST);
  . = __text_start__;
  .text : {
    KEEP(*(.text.interrupt.vector))
    KEEP(*(.text.interrupt.routine))
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > GS_RAM_CORE1_INST =0x00000080
  __text_end__ = .;


  PIEVECTTABLE_BASE = ORIGIN(GS_RAM_CORE1_IVEC);

  PROVIDE(_DSP_STACK_TOP = ORIGIN(GS_RAM_CORE1_DATA) + LENGTH(GS_RAM_CORE1_DATA));

  PROVIDE(_core0_exp_start = (ORIGIN(GS_RAM_CORE0_INST) >> 15) & 0xF);
  PROVIDE(_core1_exp_start = (ORIGIN(GS_RAM_CORE1_INST) >> 15) & 0xF);

  PROVIDE(__end = __data_end__);
  PROVIDE(__stack_end = ORIGIN(GS_RAM_CORE1_DATA) + LENGTH(GS_RAM_CORE1_DATA) - LENGTH(STACK_CORE1));
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"

OUTPUT_FORMAT("elf32-dsp")

ENTRY(_dsp_boot0_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __text_start__ = ORIGIN(BOOT_RAM_CORE0);
  .text : {
    *(.text.qxboot0)
    *(.text.qxboot)
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > BOOT_RAM_CORE0 =0x00000080
  __text_end__ = .;

  /* choose a SRAM defaults to core0 for its bootloader stack */
  PROVIDE(_BOOT_LOADER_SP = ORIGIN(GS_RAM_CORE0_DATA) + LENGTH(GS_RAM_CORE0_DATA) + LENGTH(GS_RAM_CORE0_IVEC));

  /* bootloader currently is not allowed to have data sections */
  /DISCARD/ : { *(.data)  }
  /DISCARD/ : { *(.bss)   }
  /DISCARD/ : { *(COMMON) }
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"

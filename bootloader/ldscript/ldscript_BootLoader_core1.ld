OUTPUT_FORMAT("elf32-dsp")

ENTRY(_dsp_boot1_start)

INCLUDE "ldscript_Memory.ld"

SECTIONS
{
  __text_start__ = ORIGIN(BOOT_RAM_CORE1);
  .text : {
    *(.text.qxboot1)
    *(.text.qxboot)
    *(.text)
    *(.text.*)
    . = ALIGN(0x10);
  } > BOOT_RAM_CORE1 =0x00000080
  __text_end__ = .;

  PROVIDE(_BOOT_LOADER_SP = ORIGIN(GS_RAM_CORE1_DATA) + LENGTH(GS_RAM_CORE1_DATA) + LENGTH(GS_RAM_CORE1_IVEC));

  /* bootloader currently is not allowed to have data sections */
  /DISCARD/ : { *(.data)  }
  /DISCARD/ : { *(.bss)   }
  /DISCARD/ : { *(COMMON) }
}

INCLUDE "ldscript_Peripheral.ld"
INCLUDE "ldscript_DebugInfo.ld"

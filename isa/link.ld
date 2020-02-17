OUTPUT_ARCH( "riscv" )
ENTRY(_start)

DONE = 0xFF000000;
SECTIONS
{
  . = 0x0;
  .text.init : { *(.text.init) }
  . = ALIGN(0x1000);
  .text : { *(.text) }
  . = ALIGN(0x1000);
  .data : { *(.data) }
  .bss : { *(.bss) }
  _end = .;
}


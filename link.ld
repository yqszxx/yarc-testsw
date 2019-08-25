SECTIONS
{
  . = 0;
  .text : {
    *(.text)
    PROVIDE(PRINT = 0xFFF8);
    PROVIDE(DONE  = 0xFFFC);
  }
/*  . = 0x1000;*/
  .data : { *(.data) }
  .bss : { *(.bss) }
}


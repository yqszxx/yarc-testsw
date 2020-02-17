DONE = 0xFFFFFFFF;
GPIO = 0xFE000000;
UART = 0xFD000000;

SECTIONS
{
  . = 0;
  .text : {
    *(.text)
  }
  . = 0x01000000;
  .data : { *(.data) }
  .bss : {
    *(.bss)
    PROVIDE(STACK = 0x1FF);
  }
}


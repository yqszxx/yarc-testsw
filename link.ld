OUTPUT_ARCH( "riscv" )

ENTRY( main )

MEMORY
{
  ram (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 16K
}

PHDRS
{
  ram PT_LOAD;
}

SECTIONS
{
  .text :
  {
    *(.text)
  } >ram AT>ram :ram

  .data :
  {
    *(.data)
  } >ram AT>ram :ram

  .bss :
  {
    *(.bss)
    . = ALIGN(4);
  } >ram AT>ram :ram
}


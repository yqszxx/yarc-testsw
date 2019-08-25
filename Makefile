TOOLCHAIN=/opt/riscv64-unknown-elf-gcc-8.2.0-2019.05.3-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-
EMULATOR=/mnt/hgfs/Exchange/go_build_main_go

build/sprog.o: sprog.s
	$(TOOLCHAIN)as -march=rv32i -mabi=ilp32 -o $@ $<

build/sprog: build/sprog.o link.ld
	$(TOOLCHAIN)ld -m elf32lriscv -o $@ -T link.ld $<

sdebug: build/sprog
	$(EMULATOR) $<

srun: build/sprog
	$(EMULATOR) $< 2>/dev/null

sdump: build/sprog
	$(TOOLCHAIN)objdump -d $<

build/cprog: cprog.c link.ld
	$(TOOLCHAIN)gcc -march=rv32i -mabi=ilp32 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -o $@ -T link.ld $<

cdebug: build/cprog
	$(EMULATOR) $<

crun: build/cprog
	$(EMULATOR) $< 2>/dev/null

cdump: build/cprog
	$(TOOLCHAIN)objdump -d $<

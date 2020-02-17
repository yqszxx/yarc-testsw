TOOLCHAIN=/opt/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-
EMULATOR=../yars.exe

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

build/cprog: cprog.c _start.s link.ld
	$(TOOLCHAIN)gcc -march=rv32i -mabi=ilp32 -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -o $@ -T link.ld _start.s $<

cdebug: build/cprog
	$(EMULATOR) $<

crun: build/cprog
	$(EMULATOR) $< 2>/dev/null

cdump: build/cprog
	$(EMULATOR) $< d

cdasm: build/cprog
	$(TOOLCHAIN)objdump -d $<

build/cprog.hex: build/cprog
	$(TOOLCHAIN)objcopy -O ihex $< $@

chex: build/cprog.hex
	cat build/cprog.hex


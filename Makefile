TOOLCHAIN=/opt/riscv64-unknown-elf-gcc-8.2.0-2019.05.3-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-

build/cprog: cprog.c link.ld
	$(TOOLCHAIN)gcc -O0 -march=rv32i -mabi=ilp32 -static -mcmodel=medany -fvisibility=hidden -fno-builtin -nostdlib -nostartfiles -o $@ -T link.ld $<

cdasm: build/cprog
	$(TOOLCHAIN)objdump -d $<

build/cprog.srec: build/cprog
	$(TOOLCHAIN)objcopy -O srec $< $@

upload: build/cprog.srec
	dd if=$< of=/dev/ttyUSB2

clear:
	rm build/*

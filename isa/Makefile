#=======================================================================
# Makefile for riscv-tests/isa
#-----------------------------------------------------------------------

src_dir := .

include $(src_dir)/rv32ui/Makefrag

default: all

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

RISCV_PREFIX ?= ./riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_GCC_OPTS ?= -static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
RISCV_SIM ?= ./yars_linux
YARC_RUN ?= (cd ../../ && exec sbt "test:runMain yarc.Main")

vpath %.S $(src_dir)

#------------------------------------------------------------
# Build assembly tests

%.dump: %
	$(RISCV_OBJDUMP) $< > $@

%.out32: %
	$(RISCV_SIM) $< 2> $@
	$(YARC_RUN)

define compile_template

$$($(1)_p_tests): $(1)-p-%: $(1)/%.S
	$$(RISCV_GCC) $(2) $$(RISCV_GCC_OPTS) -I$(src_dir)/include -T$(src_dir)/link.ld $$< -o $$@
$(1)_tests += $$($(1)_p_tests)

$(1)_tests_dump = $$(addsuffix .dump, $$($(1)_tests))

$(1): $$($(1)_tests_dump)

.PHONY: $(1)

tests += $$($(1)_tests)

endef

$(eval $(call compile_template,rv32ui,-march=rv32g -mabi=ilp32))

tests_dump = $(addsuffix .dump, $(tests))
tests_hex = $(addsuffix .hex, $(tests))
tests_out = $(addsuffix .out, $(spike_tests))
tests32_out = $(addsuffix .out32, $(spike32_tests))

run: $(tests32_out)

junk += $(tests) $(tests_dump) $(tests_hex) $(tests_out) $(tests32_out)

#------------------------------------------------------------
# Default

all: $(tests_dump)

#------------------------------------------------------------
# Clean up

clean:
	rm -rf $(junk)

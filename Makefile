CC=gcc
INSTALL_PREFIX=/opt/riscv/x86_64-pc-linux-gnu/
LIBS=-lopcodes -lbfd -liberty -lz -ldl 

all: disasm disasm-x86
disasm: disasm.c
	$(CC) $< -L$(INSTALL_PREFIX)/lib -I$(INSTALL_PREFIX)/include $(LIBS) -o $@
disasm-x86: disasm.c
	$(CC) $< $(LIBS) -o $@
test-riscv: disasm
	./disasm riscv32.elf elf32-littleriscv
test-x86: disasm-x86
	./disasm-x86 disasm-x86 elf64-x86-64
clean:
	rm disasm disasm-x86 -rf

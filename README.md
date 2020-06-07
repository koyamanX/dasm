# dasm
Sample project of disassembler using libbfd &amp; libopcodes.    
Disassembler for RISC-V however, can be any target architecture supported by BFD and opcodes library.   
This sample loads text section from given ELF, then disassemble them.    
It takes two argument, first one is the executable to disassemble, second one is the target architecture recognized by BFD.   
This code can be integrated into CPU simulator to enable disassembling features (not sure it is useful..)
# Dependencies
* libopcodes (binutils)
* libbfd	 (binuitls)
* liberty
* zlib1g
* libdl

# How to test
```bash
make test
```

#define PACKAGE "bfd"
#include <bfd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <dis-asm.h>
#include <assert.h>

int main(int argc, char** argv) {
	bfd *abfd;
	asection *section;
	struct disassemble_info disasm_info = {};
	disassembler_ftype disasm;
	uint32_t pc = 0;
	char *buf;
	int i;
	const char **targets;
	
	bfd_init();
	if(argc != 3) {
		fprintf(stderr, "%s takes exactly two arguments, but we got %d\n", argv[0], argc);	
		fprintf(stderr, "%s exeutable_file target\n", argv[0]);
		fprintf(stderr, "targets we support are following\n"); targets = bfd_target_list();
		while(*targets != NULL) {
			fprintf(stderr, "\t%s\n", *targets++);
		}
		exit(1);
	}
	/* does not check content of argv, so be careful */
	abfd = bfd_openr(argv[1], argv[2]);
	if(abfd == NULL) {
		fprintf(stderr, "Error: %s\n", bfd_errmsg(bfd_get_error()));
		exit(1);
	}
	if(!bfd_check_format(abfd, bfd_object)) {
		bfd_perror("bfd_check_format");
		exit(1);
	}
	section = bfd_get_section_by_name(abfd, ".text");
	assert(section != NULL);
	printf("section: %s\n", section->name);
	buf = malloc(sizeof(char)*section->size);
	assert(buf != NULL);
	bfd_get_section_contents(abfd, section, buf, 0, section->size);
	/*
	for(i = 0; i < section->size; i+=4) {
#define lsb(x) ((x) & 0xff)
		printf("%02x%02x%02x%02x\n", lsb(buf[i+3]), lsb(buf[i+2]), lsb(buf[i+1]), lsb(buf[i+0]));
	}
	*/
	
	init_disassemble_info(&disasm_info, stdout, (fprintf_ftype) fprintf);
	disasm_info.arch = bfd_get_arch(abfd); 
	disasm_info.mach = bfd_get_mach(abfd); 
	disasm_info.buffer_vma = section->vma;
	disasm_info.buffer_length = section->size;
	disasm_info.section = section;
	disasm_info.buffer = buf;
	disasm_info.read_memory_func = buffer_read_memory;
	disassemble_init_for_target(&disasm_info);
	disasm = disassembler(bfd_get_arch(abfd), false, bfd_get_mach(abfd), NULL);	
	if(disasm == NULL) {
		fprintf(stderr, "cannot find disassembler\n");
		exit(1);
	}
	pc = section->vma;
	while(pc < section->vma+section->size) {
		uint32_t insn_size;	
		insn_size = disasm(pc, &disasm_info);
		pc += insn_size;
		puts("");
	}
	puts("");
}

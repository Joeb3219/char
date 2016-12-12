#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "futil.h"
#include "cpu.h"
#include "emul.h"
#include "rom.h"

int main(int argc, char **argv){
	int i;
	char *fileName, *clockString, *tcodes;
	tcodes = "../rom/tcodes";
	clockString = "default";

	printf("===\tCHAR EMULATOR\t\t\t===\n");
	printf("===\tDEBUGGING INFO\t\t\t===\n");
	printf("===\tWORD SIZE: %d\t\t\t===\n", WORDSIZE);

	for(i = 1; i < argc; i ++){
		if(strcmp(argv[i], "-file") == 0) fileName = argv[++i];
		else if(strcmp(argv[i], "-clock") == 0) clockString = argv[++i];
	}

	if(fileName == 0){
		error(0, "File not specified.\nUsage: emul -file <filename>\nOther arguments: -clock <clockSpeed>, default: unspecified\n");
	}

	if(getFile(fileName) == 0){
		error(0, "File not found\n");
	}

	printf("===\tFILE: %s\t===\n",fileName);
	printf("===\tBEGIN PRGM\t\t\t===\n");

	Rom *rom_tcodes = loadROM(getFile(tcodes), 256);

	initialize();

	runCPU(parseClockSpeed(clockString));

	free(rom_tcodes);

	return 0;
}

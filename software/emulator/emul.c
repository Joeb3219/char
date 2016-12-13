#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "futil.h"
#include "cpu.h"
#include "emul.h"

int main(int argc, char **argv){
	int i;
	char *fileName, *clockString, *tcodes_1, *tcodes_2;
	tcodes_1 = "../rom/tcodes_1";
	tcodes_2 = "../rom/tcodes_2";
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

	printf("===\tFILE: %s\t===\n",fileName);
	printf("===\tBEGIN PRGM\t\t\t===\n");

	initialize();

	runCPU(getFile(fileName), getFile(tcodes_1), getFile(tcodes_2), parseClockSpeed(clockString));

	return 0;
}

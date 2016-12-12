#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "rom.h"

#define DATA_WIDTH 4

Rom* loadROM(FILE *file, int dataSize){
	int i = 0, j = 0;
	char c, buffer[5];
	Rom *rom = malloc(sizeof(Rom));
	rom->dataSize = dataSize;
	rom->data = calloc(dataSize, sizeof(double_byte));
	while( (c = fgetc(file)) != EOF){
		if(c == '\n' || j == 4){
			buffer[j] = '\0';
			rom->data[i] = (double_byte) strtol(buffer, NULL, 16);
			j = 0;
			i ++;
		}else if(c != ' '){
			buffer[j] = c;
			j ++;
		}
	}

	return rom;
}

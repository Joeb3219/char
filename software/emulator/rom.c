#include <stdio.h>
#include <stdlib.h>
#include "rom.h"
#include "futil.h"

#define DATA_WIDTH 4

Rom* loadROM(FILE *file, int dataSize){
	if(file == 0){
		error(0, "Nonexistant file loaded by ROM\n");
	}
	int i = 0, j = 0, commentStarted = 0;
	char c, buffer[5];
	Rom *rom = malloc(sizeof(Rom));
	rom->dataSize = dataSize;
	rom->data = calloc(dataSize, sizeof(double_byte));
	while( (c = fgetc(file)) != EOF){
		if(c == '#') commentStarted = 1;
		if(c == '\n' || j == 4){
			buffer[j] = '\0';
			rom->data[i] = (double_byte) strtol(buffer, NULL, 16);
			j = 0;
			i ++;
			commentStarted = 0;
		}else if(c != ' ' && commentStarted != 1){
			buffer[j] = c;
			j ++;
		}
	}

	return rom;
}

double_byte readROM(Rom *rom, int address){
	if(address < 0 || address > rom->dataSize) error(0, "ATTEMPTING TO ACCESS ROM ADDRESS OUT OF BOUNDS\n");
	return rom->data[address];
}

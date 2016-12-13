#include <stdio.h>
#include <stdlib.h>
#include "rom.h"
#include "futil.h"

Rom* loadROM(FILE *file, int size){
	if(file == 0){
		error(0, "Nonexistant file loaded by ROM\n");
	}
	int i = 0, j = 0, commentStarted = 0;
	char c, buffer[3];
	Rom *rom = malloc(sizeof(Rom));
	rom->dataSize = size;
	rom->data = calloc(size, sizeof(byte));
	while( (c = fgetc(file)) != EOF){
		if(c == '#') commentStarted = 1;
		if(c == '\n' || j == 2){
			if(j == 2){
				buffer[j] = '\0';
				rom->data[i] = (byte) strtol(buffer, NULL, 16);
				i ++;
			}
			j = 0;
			commentStarted = 0;
		}else if(c != ' ' && commentStarted != 1){
			buffer[j] = c;
			j ++;
		}
	}

	return rom;
}

byte readROM(Rom *rom, int address){
	if(address < 0 || address > rom->dataSize){
		error(0, "ATTEMPTING TO ACCESS ROM ADDRESS OUT OF BOUNDS\n");
	}
	return rom->data[address];
}

void printROM(Rom *rom){
	int i = 0;
	for(i = 0; i < rom->dataSize; i ++){
		if(i % 8 == 0) printf("%40x: ", i);
		printf("[%02X]", readROM(rom, i));
		if((i + 1) % 8 == 0) printf("\n");
	}
	printf("\n");
}

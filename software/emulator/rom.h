#ifndef _ROM_H_
#define _ROM_H_

typedef unsigned char byte;

typedef struct Rom{
	int dataSize;
	byte *data;
} Rom;

Rom* loadROM(FILE *file, int size);
byte readROM(Rom *rom, int address);
void printROM(Rom *rom);

#endif

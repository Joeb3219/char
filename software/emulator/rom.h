#ifndef _ROM_H_
#define _ROM_H_

typedef unsigned short double_byte;

typedef struct Rom{
	int dataSize;
	double_byte *data;
} Rom;

Rom* loadROM(FILE *file, int dataSize);
double_byte readROM(Rom *rom, int address);

#endif

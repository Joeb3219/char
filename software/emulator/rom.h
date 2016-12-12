#ifndef _ROM_H_
#define _ROM_H_

typedef struct Rom{
	int dataSize;
	double_byte *data;
} Rom;

Rom* loadROM(FILE *file, int dataSize);

#endif

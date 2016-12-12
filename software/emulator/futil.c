#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "futil.h"
#include "cpu.h"

void error(int level, char *message){
	printf("ERR [%d]: %s\n", level, message);
	if(level == 0){
		exit(1);
	}
}

// Gets a file if it exists, in read-only mode.
FILE* getFile(char *fileName){
        if(fileName == 0) return 0;
        return fopen(fileName, "r");
}

// Gets a file if it exists, or creates it otherwise, in read-write mode.
FILE* getFileOrCreate(char *fileName){
        if(fileName == 0) return 0;
        return fopen(fileName, "w+");
}

// Closes a file & frees memory.
int closeFile(FILE *file){
        if(file == 0) return 0;
        return fclose(file);
}

// Appends a character to a string.
void append(char *str, char c){
        char buffer[2];
        buffer[0] = c;
        buffer[1] = '\0';
        strcat(str, buffer);
}

int parseClockSpeed(char *str){
	if(str == 0 || strcmp(str, "default") == 0) return DEFAULT_CLOCKSPEED;
	if(strcmp(str, "manual") == 0) return -1;
	return 1;
}

#ifndef _FUTIL_H_
#define _FUTIL_H_

#define ERROR_DIE 0

void error(int level, char *message);
FILE* getFile(char *filename);
FILE* getFileOrCreate(char *filename);
int closeFile(FILE *file);
void append(char *str, char c);
char* getNextToken(FILE *file);
int parseClockSpeed(char *str);

#endif

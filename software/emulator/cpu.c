#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "alu.h"
#define add() tick_ALU(registers[REG_MA], registers[REG_MB], registers[REG_ALU], 1)
#define sub() tick_ALU(registers[REG_MA], registers[REG_MB], registers[REG_ALU], 2)
#define and() tick_ALU(registers[REG_MA], registers[REG_MB], registers[REG_ALU], 3)
#define or() tick_ALU(registers[REG_MA], registers[REG_MB], registers[REG_ALU], 4)
#define xor() tick_ALU(registers[REG_MA], registers[REG_MB], registers[REG_ALU], 5)
#define nor() tick_ALU(registers[REG_MA], registers[REG_MB], registers[REG_ALU], 6)

int status = STATUS_AOK;
byte *dataBus_devices;
reg **registers;

void readWriteCycle(){
	int i;
	byte valWritten = 0;
	for(i = 0; i < NUM_REGISTERS; i ++){
                if(registers[i]->dataRW == REGISTER_WRITE) valWritten = registers[i]->val;
	}

	for(i = 0; i < NUM_REGISTERS; i ++){
		if(registers[i]->dataRW == REGISTER_READ) registers[i]->val = valWritten;
	}

	printf("DATABUS: %d\n", valWritten);
}

void initialize(){
	int i;
	registers = calloc(NUM_REGISTERS, sizeof(void*));
	for(i = 0; i < NUM_REGISTERS; i ++){
		registers[i] = malloc(sizeof(reg));
		registers[i]->aluRW = registers[i]->dataRW = registers[i]->val = 0;
	}
	registers[REG_MA]->aluRW = registers[REG_MB]->aluRW = REGISTER_WRITE;
	registers[REG_ALU]->dataRW = REGISTER_WRITE;
	registers[REG_MA]->val = registers[REG_MB]->val = 1;
	registers[REG_MA]->dataRW = REGISTER_READ;
}

void runCPU(int clockSpeed){
	while(status != STATUS_HLT){
		readWriteCycle();
		status = STATUS_HLT;
	}
}

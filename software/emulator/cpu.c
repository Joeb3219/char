#include <stdio.h>
#include <stdlib.h>
#include "rom.h"
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

typedef void (*microcode_functions)(byte, int);

void printRegisters(){
	printf("+=A:%02X=+=B:%02X=+=C:%02X=+=D:%02X=+=MA:%02X=+=MB:%02X=+=AL:%02X=+\n", registers[REG_A]->val, registers[REG_B]->val, registers[REG_C]->val, registers[REG_D]->val,
		registers[REG_MA]->val, registers[REG_MB]->val, registers[REG_ALU]->val);
}

void micro_donothing(byte operands, int cleanup){}

void micro_halt(byte operands, int cleanup){
	status = STATUS_HLT;
}

void micro_read_first(byte operands, int cleanup){
	if(cleanup == CLEANUP_FALSE) registers[(operands & 0xF0) >> 4]->dataRW = REGISTER_READ;
	else registers[(operands & 0xF0) >> 4]->dataRW = 0;
}

void micro_read_last(byte operands, int cleanup){
	if(cleanup == CLEANUP_FALSE) registers[(operands & 0x0F)]->dataRW = REGISTER_READ;
        else registers[(operands & 0x0F)]->dataRW = 0;
}

void micro_write_first(byte operands, int cleanup){
	if(cleanup == CLEANUP_FALSE) registers[(operands & 0xF0) >> 4]->dataRW = REGISTER_WRITE;
        else registers[(operands & 0xF0) >> 4]->dataRW = 0;
}

void micro_write_last(byte operands, int cleanup){
	if(cleanup == CLEANUP_FALSE) registers[(operands & 0x0F)]->dataRW = REGISTER_WRITE;
        else registers[(operands & 0x0F)]->dataRW = 0;
}

void micro_read_write(byte operands, int cleanup){
	micro_write_first(operands, cleanup);
	micro_read_last(operands, cleanup);
}

void micro_read_write_ma(byte operands, int cleanup){
	micro_write_first(operands, cleanup);
	if(cleanup == CLEANUP_FALSE) registers[REG_MA]->dataRW = REGISTER_READ;
	else registers[REG_MA]->dataRW = 0;
}

void micro_read_write_mb(byte operands, int cleanup){
	micro_write_last(operands, cleanup);
        if(cleanup == CLEANUP_FALSE) registers[REG_MB]->dataRW = REGISTER_READ;
        else registers[REG_MB]->dataRW = 0;
}

void micro_store(byte operands, int cleanup){
	if(cleanup == CLEANUP_FALSE){
		printf("Moving %0X -> rA\n", operands);
		registers[REG_NONE]->dataRW = REGISTER_WRITE;
		registers[REG_NONE]->val = operands;
		registers[REG_A]->dataRW = REGISTER_READ;
	}else{
		registers[REG_NONE]->dataRW = registers[REG_A]->dataRW = 0;
	}
}

void micro_add(byte operands, int cleanup){
	add();
	micro_read_last(operands, cleanup);
	if(cleanup == CLEANUP_FALSE) registers[REG_ALU]->dataRW = REGISTER_WRITE;
	else registers[REG_ALU]->dataRW = 0;
}

void micro_sub(byte operands, int cleanup){

}

void micro_and(byte operands, int cleanup){

}

void micro_or(byte operands, int cleanup){

}

void micro_xor(byte operands, int cleanup){

}

void micro_nor(byte operands, int cleanup){

}

microcode_functions microcodes[16] = {micro_donothing, micro_halt, micro_read_first, micro_read_last,
	micro_write_first, micro_write_last, micro_read_write, micro_read_write_ma,
	micro_read_write_mb, micro_store, micro_add, micro_sub, micro_and, micro_or,
	micro_xor, micro_nor};

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
	registers[REG_ALU]->dataRW = 0;
}

byte getCurrentTcode(double_byte *count, byte *tcodeCount, Rom *tcodes, Rom *program, double_byte *instr){
	double_byte tcode;
	*instr = readROM(program, *count);
	tcode = (readROM(tcodes, (int) ((*instr) & 0xFF00) >> 8));
	if(*tcodeCount == 0) tcode = ((tcode & 0xF800) >> 11);	// LEFT 5 BITS: 1111 1000 0000 0000, >> 11
	else if(*tcodeCount == 1) tcode = ((tcode & 0x07A0) >> 6);	// NEXT 5 BITS: 0000 0111 1100 0000
	else tcode = ((tcode & 0x003E) >> 1);	// LAST 5 BITS: 0000 0000 0011 1110
	(*tcodeCount) ++;
	if((*tcodeCount) == 3){
		((*count) ++);
		(*tcodeCount) = 0;
	}
	return (byte) tcode;
}

void runCPU(FILE *program, FILE *tcodes, int clockSpeed){
	double_byte count = 0, instr = 0;
	byte tcodeCount = 0, tInstr, operands;
	Rom *rom_program, *rom_tcodes;

	rom_program = loadROM(program, 256);
	rom_tcodes = loadROM(tcodes, 256);

	fclose(program);
	fclose(tcodes);

	while(status == STATUS_AOK){
		tInstr = getCurrentTcode(&count, &tcodeCount, rom_tcodes, rom_program, &instr);
		if(tInstr == 0) continue;
		operands = (instr & 0x00FF);
		printf("CURRENT INSTR: %0X (%0X), TCODE: %0X\n", instr, operands, tInstr);
		microcodes[tInstr](operands, CLEANUP_FALSE);
		readWriteCycle();
		microcodes[tInstr](operands, CLEANUP_TRUE);
		printRegisters();
	}

	free(rom_program);
	free(rom_tcodes);
}

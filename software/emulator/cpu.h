#ifndef _CPU_H_
#define _CPU_H_

#define REG_NONE 0
#define REG_A 1
#define REG_B 2
#define REG_C 3
#define REG_D 4
#define REG_INST 5
#define REG_ADH 6
#define REG_ADL 7
#define	REG_MA 8
#define REG_MB 9
#define REG_ALU 10

#define STATUS_AOK 0
#define STATUS_HLT 1

#define NUM_REGISTERS 11
#define NUM_DEVICES 9

#define REGISTER_READ 1
#define REGISTER_WRITE 2

#define DEFAULT_CLOCKSPEED 1000

extern int dataBus, instrBus, cntrlBus, status;

typedef unsigned char byte;
typedef unsigned short double_byte;

typedef enum opcode{
	NOP = 0x00, HALT = 0x01,
	ADD = 0x10, SUB = 0x11, AND = 0x12, OR = 0x13, XOR = 0x14, NOR = 0x15,
	MVRR = 0x20, MVIR = 0x21
} Opcode;

typedef struct Register{
	byte val;
	byte dataRW, aluRW;
} reg;

void initialize();
void runCPU(int clockSpeed);
void readWriteCycle();

#endif

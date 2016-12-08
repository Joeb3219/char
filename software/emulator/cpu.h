#ifndef _CPU_H_
#define _CPU_H_

#define REG_A 1
#define REG_B 2
#define REG_C 3
#define REG_D 4
#define REG_INST 5
#define REG_E 6
#define REG_F 7

typedef enum opcode{
	NOP = 0x00, HALT = 0x01,
	ADD = 0x10, SUB = 0x11, AND = 0x12, OR = 0x13, XOR = 0x14, NOR = 0x15,
	MVRR = 0x20, MVIR = 0x21
} Opcode;

#endif

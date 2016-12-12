#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

byte add(byte a, byte b){
	return a + b;
}

byte sub(byte a, byte b){
	return a - b;
}

byte and(byte a, byte b){
	return a & b;
}

byte or(byte a, byte b){
	return a | b;
}

byte xor(byte a, byte b){
	return a ^ b;
}

byte nor(byte a){
	return ~(a);
}

void tick_ALU(reg *mA, reg *mB, reg *alu, byte operation){
	byte output;
	if(operation == 1) output = add(mA->val, mB->val);
	else if(operation == 2) output = sub(mA->val, mB->val);
	else if(operation == 3) output = and(mA->val, mB->val);
	else if(operation == 4) output = or(mA->val, mB->val);
	else if(operation == 5) output = xor(mA->val, mB->val);
	else if(operation == 6) output = nor(mA->val);
	else printf("Unspecified ALU operation: %d\n", operation);
	alu->val = output;
}

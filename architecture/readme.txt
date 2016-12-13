GENERAL OUTLINE:

-- REGISTERS
	-- 4 general purpose registers (A[0], B[1], C[2], D[3]).	[8 bit]
	-- PROGRAM Register (inside of program counter)	[6]		[8 bit]
	-- INSTRUCTION Register [7]					[16 bit]
		-- Splits into three pieces for most instructions
		-- INSTRUCTION						[8 bit]
		-- rA, rB						[8 bit, 8 bit]
		-- IMMEDIATE						[8 bit]
	-- TWO math registers (mA[4], mB[5])				[8 bit]
	-- 
-- ALU
	-- mA & mB Registers constantly output to ALU.
	-- All ALU components constantly compute on mA & mB.
		-- Perhaps this needs to be revised (division by zero?)
	-- Implementing subtraction and addition into same circuit
		-- Convert mB to -mB if subtracting, then add mA+mB.
	-- ALU operations:
		-- ADD, SUB, MULT, AND, OR, XOR, NOR
-- BUSSES
	-- DATA BUS							[8 bit]
	-- INSTRUCTION BUS						[16 bit]
		-- First 8 bits are the instruction
		-- Next 8 bits are either an immediate, or one/two regs
	-- ADDRESS BUS							[16 bit]
	-- COUNT BUS							[8 bit]
-- ROM
	-- Use a 2 256x8 ROM chips
		-- 3 steps each get 4 bits, ergo 2^4 (16) possible
			microcodes
		-- Tcodes 1 & 2 stored on chip 1, Tcode 3 on chip 2
		-- Possible expansion to a 4th Tcode for bigger instructions
	-- There are several operations that we define by a given value	[8 bit]
		of a ROM read
00000	-- x00: Do nothing
00001	-- x01: Halt
00010	-- x02: READ: register indicated by first 4 bits of operand
00011	-- x03: READ: register indicated by last 4 bits of operand
00100	-- x04: WRITE: register indicated by first 4 bits of operand
00101	-- x05: WRITE: register indicated by last 4 bits of operand
00110	-- x06: READ, WRITE: WRITE reg @ first 4 bits, READ reg @ second 4 bits
00111	-- x07: READ, WRITE: Write reg @ first 4 bits -> mA
01000	-- x08: READ, WRITE: Write reg @ last 4 bits -> mB
01001	-- x09: STORE: Move operand to rA
01010	-- x0A: ADD -> reg @ last 4 bits
01011	-- x0B: SUBTRACT -> reg @ last 4 bits
01100	-- x0C: AND -> reg @ last 4 bits
01101	-- x0D: OR -> reg @ last 4 bits
01110	-- x0E: XOR -> reg @ last 4 bits
01111	-- x0F: NOR -> reg @ last 4 bits
-- INSTRUCTIONS
	-- NOP:		0x00						[8 bit]
		-- 00, 00, 00	[000]
	-- HALT:	0x01						[8 bit]
		-- 01, 00, 00	[100]
	-- ALU FAMILY	(0x1x)
		-- ADD:		0x10	rA, rB	(src, dst)		[16 bit]
			-- 07, 08, 0A	[78A]
		-- SUB:		0x11	rA, rB	(src, dst)		[16 bit]
			-- 07, 08, 0B	[78B]
		-- AND:		0x12	rA, rB	(src, dst)		[16 bit]
			-- 07, 08, 0C	[78C]
		-- OR:		0x13	rA, rB	(src, dst)		[16 bit]
			-- 07, 08, 0D	[78D]
		-- XOR:		0x14	rA, rB	(src, dst)		[16 bit]
			-- 07, 08, 0E	[78E]
		-- NOR:		0x15	rA, rB	(src, dst)		[16 bit]
			-- 07, 08, 0F	[78F]
	-- MOVE FAMILY	(0x2x)
		-- MVRR:	0x20	rA, rB	(src, dst)		[16 bit]
			-- 06, 00, 00	[600]
		-- MVIR:	0x21	IMM	(IMM)			[16 bit]
			-- Moves into general register A.
			-- 09, 00, 00	[900]
		-- MVADH:	0x22	IMM	(IMM)			[16 bit]
		-- MVADL:	0x23	IMM	(IMM)			[16 bit]
		-- MVMR:	0x24	rA	(dst)			[12 bit?]
		-- MVRM:	0x25	rA	(src)			[12 bit?]

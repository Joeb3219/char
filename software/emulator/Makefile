CC := gcc

all: clean emul

emul: emul.c
	$(CC) -Wall -g -o emul emul.c cpu.c futil.c alu.c rom.c

clean:
	rm -rf emul emul.o

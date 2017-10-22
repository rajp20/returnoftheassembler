CC = g++
CFLAGS = -Wall -std=c++11

assembler: assembler.cpp
	${CC} ${CFLAGS} -o assembler assembler.cpp

clean:
	rm assembler

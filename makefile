#
#  File name: makefile
#
#  Author: AED - Grupo 66
#
#  Release date: 2018/11/16
#
#  Description: Makefile for the program tuktuk
#
#  Usage:
#     1) To generate the executable file for the program tuktuk,
#       run
#         $ make
#
#     2) To clean all object files and the executable file of
#        tuktuk, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -g -pedantic -std=c99 -O3

#  Sources
SOURCES = ficheiro.c struct.c oper.c acervo.c main.c

#  Objects
OBJECTS = ficheiro.o struct.o oper.o  acervo.o main.o

tuktuk: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

ficheiro.o: ficheiro.h struct.h oper.h ficheiro.c

oper.o: ficheiro.h struct.h oper.h oper.c

struct.o: ficheiro.h struct.h oper.h struct.c

acervo.o: acervo.h oper.h struct.h acervo.c 


clean::
	rm -f *.o core a.out tuktuk *~

# DO NOT DELETE

CC = gcc
CFLAGS = -Wall -pedantic -ansi

all: text.o main.o main
 
main: text.o
	$(CC) $(CFLAGS) main.o text.o -o main

main.o: main.c text.h
	$(CC) $(CFLAGS) -o main.o -c main.c

text.o: text.c text.h
	$(CC) $(CFLAGS) -o  text.o -c text.c

clean: 
	rm -f text.o main.o main
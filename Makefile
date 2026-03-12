CC = gcc
FLAGS = -g -Wall -Wextra
BUILD_DIR = build

build:$(BUILD_DIR)/javaMaker

$(BUILD_DIR)/javaMaker: javaMaker.o scanner.o
	mkdir -p build
	$(CC) $(FLAGS) -o $@ $^
	rm -rf *.o

javaMaker.o: javaMaker.c struc.h template.h scanner.h
scanner.o: scanner.c struc.h template.h scanner.h

%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf build/*
	rm -rf *.o
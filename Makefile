CC = gcc
FLAGS = -g -Wall -Wextra
BUILD_DIR = build

build:$(BUILD_DIR)/javaMaker

$(BUILD_DIR)/javaMaker: javaMaker.o scanner.o classWriter.o classCreator.o
	mkdir -p build
	$(CC) $(FLAGS) -o $@ $^
	rm -rf *.o

javaMaker.o: javaMaker.c struc.h template.h scanner.h writer.h
scanner.o: scanner.c struc.h template.h scanner.h
classWriter.o: classWriter.c struc.h template.h
classCreator.o: classCreator.c struc.h template.h

%.o:%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf build/*
	rm -rf *.o
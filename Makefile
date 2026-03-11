CC = gcc
FLAGS = -g -Wall -Wextra
BUILD_DIR = build


$(BUILD_DIR)/javaMaker: javaMaker.o
	$(CC) $(FLAGS) -o $@ $^
	rm -rf *.o

javaMaker.o: javaMaker.c struc.h template.h

%.o:%.c
	$(CC) $(FLAGS) -c $<


clean:
	rm -rf build/*
	rm -rf *.o
CC = gcc
FLAGS = -Wall -g -fPIC

all: cmp copy

cmp: maincmp.o cmp.o
	$(CC) $(FLAGS) cmp.o maincmp.o -o cmp
cmp.o: cmp.c cmp.h
	$(CC) $(FLAGS) -c cmp.c
maincmp.o: maincmp.c cmp.c cmp.h
	$(CC) $(FLAGS) -c maincmp.c

copy: maincopy.o copy.o
	$(CC) $(FLAGS) copy.o maincopy.o -o copy
copy.o: copy.c copy.h
	$(CC) $(FLAGS) -c copy.c
maincopy.o: maincopy.c copy.c copy.h
	$(CC) $(FLAGS) -c maincopy.c

.PHONY: clean all
clean: 
	rm -f  *.o cmp copy
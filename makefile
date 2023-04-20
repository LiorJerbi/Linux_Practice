CC = gcc
FLAGS = -Wall -g -fPIC

all: cmp copy encode decode stshell

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

encode:  encode.c libA libB
	gcc encode.c -fPIC -ldl -o encode
decode:  decode.c libA libB
	gcc decode.c -fPIC -ldl -o decode

libA: codecA.h codecA.c
	$(CC) -shared codecA.c -fPIC -o libcodecA.so

libB: codecB.h codecB.c
	$(CC) -shared codecB.c -fPIC -o libcodecB.so

stshell: basic_shell.c basic_shell.o
	$(CC) $(FLAGS) basic_shell.o -o stshell
stshell.o: basic_shell.c
	$(CC) $(FLAGS) -c basic_shell.c

.PHONY: clean all
clean: 
	rm -f *.so *.o cmp copy encode decode stshell
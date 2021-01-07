CC=gcc
CFLAGS=-Wall -g
CLINK=$(CC)

prog1.exe: linked-list.o grades.o main.o
	$(CLINK) linked-list.o grades.o -o prog1.exe 

linked-list.o: linked-list.h
liblinked-list.os:linked-list.h 
	$(CLINK) -shared linked-list.o -o liblinked-list.os

grades.o: linked-list.h grades.h grades.c


clean:
	rm -f *.o *.exe
CC=gcc
CFLAGS=-Wall -g -std=c99
CLINK=$(CC)
LD_LIBRARY_PATH=./
libgrades.so: grades.o 
	$(CLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: linked-list.h grades.h grades.c
	$(CLINK) $(CFLAGS) -c -fpic grades.c
clean:
	rm -f *.o 

#!/bin/bash
mdc: main.o mainmenu.o openfile.o compression.o decompression.o Masterarray.o unique.o bitlength.o comp4.c index.c getMasterarray.o find_char.o decomp4.o init.o comp3.o decomp3.o
	gcc -o mdc main.o mainmenu.o openfile.o compression.o decompression.o Masterarray.o unique.o bitlength.o comp4.c index.c getMasterarray.o find_char.o decomp4.o init.o comp3.o decomp3.o

comp3.o: comp3.c headers.h prototypes.h
	gcc -c comp3.c
decomp4.o: decomp4.c headers.h prototypes.h
	gcc -c decomp4.c
decomp3.o: decomp3.c headers.h prototypes.h
	gcc -c decomp3.c
init.o: init.c headers.h prototypes.h
	gcc -c init.c
find_char.o: find_char.c headers.h prototypes.h
	gcc -c find_char.c
comp4.o: comp4.c headers.h prototypes.h
	gcc -c comp4.c 
index.o: index.c headers.h prototypes.h
	gcc -c index.c 
Masterarry.o: Masterarray.c headers.h prototypes.h
	gcc -c Masterarray.c 
getMasterarry.o: getMasterarray.c headers.h prototypes.h
	gcc -c getMasterarray.c 
bitlength.o: bitlength.c headers.h prototypes.h
	gcc -c bitlength.c 
unique.o: unique.c headers.h prototypes.h
	gcc -c unique.c
compression.o: compression.c headers.h prototypes.h
	gcc -c compression.c
decompression.o: decompression.c headers.h prototypes.h
	gcc -c decompression.c
openfile.o: openfile.c headers.h prototypes.h
	gcc -c openfile.c
main.o:	main.c headers.h prototypes.h
	gcc -c main.c
mainmenu.o: mainmenu.c headers.h prototypes.h
	gcc -c mainmenu.c
	

clean:
	@rm -rf *.o

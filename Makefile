.PHONY = clean


all: base

base: main.o
	gcc obj/main.o -o Complex_prog  -l dl

main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -I include

clean:
	

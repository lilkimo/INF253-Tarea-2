all: programa
	./programa

programa: main.o heap.o
	gcc -o programa main.o heap.o -lm

main.o: main.c utilities.h
	gcc -c main.c

heap.o: heap.c heap.h
	gcc -c heap.c -o heap.o

clean:
	rm -f programa main.o heap.o
#gcc -Wall main.c -o main.out -lm && ./main.out
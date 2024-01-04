
output: heap.c heap.test.c
	gcc -Wall -pedantic -Werror -Wextra -c heap.test.c
	gcc -Wall -pedantic -Werror -Wextra -c heap.c
	gcc -o Heap heap.o heap.test.o
	gcc -g heap.c heap.test.c

debug: Heap
	gdb a.out

clean : 
	rm Heap heap.o heap.test.o a.out



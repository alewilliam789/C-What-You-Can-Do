test : heap.c heap.test.c
	gcc -isystem./include -Wall -pedantic -Werror -Wextra -g heap.c heap.test.c

library : heap.c
	gcc -isystem./include -c -Wall -pedantic -Werror -Wextra -fPIC heap.c
	gcc -shared -o libheap.so heap.o
	- rm heap.o
	mv ./libheap.so ./lib

json : heap.c heap.test.c 
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out

debug : a.out
	gdb a.out

clean : 
	- rm ./a.out
	- rm ./lib/*




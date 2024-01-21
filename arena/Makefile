test : arena.c arena.test.c 
	gcc -isystem./include -Wall -pedantic -Werror -Wextra -g arena.c arena.test.c

library : arena.c
	gcc -isystem./include -c -Wall -pedantic -Werror -Wextra -fPIC arena.c
	gcc -shared -o libarena.so arena.o
	- rm arena.o
	mv ./libarena.so ./lib

json : arena.c arena.test.c
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out

debug: a.out
	gdb a.out

clean : 
	- rm a.out
	- rm ./lib/*


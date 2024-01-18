test : hashtable.c hashtable.test.c 
	gcc -isystem./include -Wall -pedantic -Werror -Wextra -g hashtable.c hashtable.test.c

library : hashtable.c
	gcc -isystem./include -c -Wall -pedantic -Werror -Wextra -fPIC hashtable.c
	gcc -shared -o libhashtable.so hashtable.o
	- rm hashtable.o
	mv ./libhashtable.so ./lib

json : hashtable.c hashtable.test.c
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out

debug: a.out
	gdb a.out

clean : 
	- rm a.out
	- rm ./lib/*


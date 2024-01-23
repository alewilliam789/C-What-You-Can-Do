test : hashtable.c hashtable.test.c 
	gcc -isystem./include -isystem../../arena/include -Wall -pedantic -Werror -Wextra -g hashtable.c hashtable.test.c -L../../lib -larena

library : hashtable.c
	- rm ../../lib/libhashtable.so
	gcc -isystem./include -isystem../../arena/include -c -Wall -pedantic -Werror -Wextra -fPIC hashtable.c -L../lib -larena
	gcc -shared -o libhashtable.so hashtable.o
	- rm hashtable.o
	mv ./libhashtable.so ../../lib/

json : hashtable.c hashtable.test.c
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out

debug: a.out
	gdb a.out

clean : 
	- rm a.out


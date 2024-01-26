file_header = -isystem./include
library_headers = -isystem../../lib/include
libraries = -L../../lib


test : hashtable.c hashtable.test.c 
	gcc $(file_header) $(library_headers) -Wall -pedantic -Werror -Wextra -g hashtable.c hashtable.test.c $(libraries) -larena -lhash

library : hashtable.c
	- rm ../../lib/libhashtable.so
	gcc $(file_header) $(library_headers) -c -Wall -pedantic -Werror -Wextra -fPIC hashtable.c $(libraries) -larena -lhash
	gcc -shared -o libhashtable.so hashtable.o
	- rm hashtable.o
	mv ./libhashtable.so ../../lib/
	cp ./include/hashtable.h ../../lib/include

json : hashtable.c hashtable.test.c
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out

debug : a.out
	gdb a.out

clean : 
	- rm a.out


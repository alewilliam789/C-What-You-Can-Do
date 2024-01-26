test : hash.c hash.test.c 
	gcc -isystem./include -Wall -pedantic -Werror -Wextra -g hash.c hash.test.c

library : 
	- rm ../../lib/libhash.so
	-rm ../../lib/include/hash.h
	gcc -isystem./include -c -Wall -pedantic -Werror -Wextra -fPIC hash.c 
	gcc -shared -o libhash.so hash.o
	- rm hash.o
	mv ./libhash.so ../lib/
	cp ./include/hash.h ../lib/include/

json : hash.c 
	- rm compile_commands.json
	bear -- gcc -isystem./include -Wall -pedantic -Werror -Wextra -g hash.c
	- rm -r a.out

debug: a.out
	gdb a.out

clean : 
	- rm a.out


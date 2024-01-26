test : linkedlist.c linkedlist.test.c
	gcc -isystem./include -isystem../../arena/include -Wall -pedantic -Werror -Wextra -g linkedlist.test.c linkedlist.c -L../../lib -larena

library :
	- rm ../../lib/liblinkedlist.so
	- rm ../../lib/include/linkedlist.h
	gcc -isystem./include -isystem../../arena/include -c -Wall -pedantic -Werror -Wextra -fPIC linkedlist.c -L../../lib -larena
	gcc -shared -o liblinkedlist.so linkedlist.o
	- rm linkedlist.o
	mv ./liblinkedlist.so ../../lib/
	cp ./include/linkedlist.h ../../lib/include

json : linkedlist.c linkedlist.test.c
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out


debug : a.out
	gdb a.out

clean : 
	- rm a.out
	- rm ./lib/*

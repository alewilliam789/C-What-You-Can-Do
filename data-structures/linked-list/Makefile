test : linkedlist.c linkedlist.test.c
	gcc -isystem./include -Wall -pedantic -Werror -Wextra -g linkedlist.test.c linkedlist.c

library : 
	gcc -isystem./include -c -Wall -pedantic -Werror -Wextra -fPIC linkedlist.c
	gcc -shared -o liblinkedlist.so linkedlist.o
	- rm linkedlist.o
	mv ./liblinkedlist.so ./lib

json : linkedlist.c linkedlist.test.c
	- rm compile_commands.json
	bear -- make test
	- rm -r a.out


debug : a.out
	gdb a.out

clean : 
	- rm a.out
	- rm ./lib/*

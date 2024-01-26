binary-test : binarytree.c binarytree.test.c
	gcc -isystem./include -isystem../../arena/include -Wall -pedantic -Werror -Wextra -g binarytree.test.c binarytree.c -L../../lib -larena

binary-library : binarytree.c
	gcc -isystem./include -isystem../../arena/include -c -Wall -pedantic -Werror -Wextra -fPIC binarytree.c -L../../lib -larena
	gcc -shared -o libtree.so tree.o
	- rm tree.o
	mv ./libtree.so ../../lib/

binary-json : binarytree.c binarytree.test.c
	- rm compile_commands.json
	bear -- make binary-test
	- rm -r a.out


debug : a.out
	gdb a.out

clean : 
	- rm a.out
	- rm ./lib/*

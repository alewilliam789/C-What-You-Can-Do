json-parser: json-parser.c lexer.c
	gcc -g json-parser.c lexer.c

test: json-parser.test.c parser.c scanner.c
	gcc -isystem./include -isystem../lib/include -g json-parser.test.c parser.c scanner.c -L../lib -lhashtable -larena -llinkedlist -lhash

json: json-parser.test.c lexer.c
	bear -- make test
	- rm a.out

debug: a.out
	gdb a.out

clean: 
	rm a.out 

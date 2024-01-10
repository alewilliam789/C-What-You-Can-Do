json-parser: json-parser.c lexer.c
	gcc -g json-parser.c lexer.c

test: json-parser.test.c lexer.c
	gcc -g json-parser.test.c lexer.c
	
debug: a.out
	gdb a.out

clean: a.out
	rm a.out

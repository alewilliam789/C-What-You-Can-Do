file_header = -isystem./include
library_headers = -isystem../lib/include
library_path = -L../lib
libraries = -lhashtable -larena -llinkedlist -lhash 
base_flags = -Wall -pedantic -Werror -Wextra


json-parser: main.c scanner.c parser.c
	gcc $(file_header) $(library_headers) $(base_flags) -o json-parser main.c scanner.c parser.c $(library_path) $(libraries)
	
test: json-parser.test.c parser.c scanner.c
	gcc $(file_header) $(library_headers) $(base_flags) -g json-parser.test.c parser.c scanner.c $(library_path) $(libraries) 

json: json-parser.test.c scanner.c parser.c
	bear -- make json-parser
	- rm a.out

debug-parser: json-parser
	gcc $(file_header) $(library_headers) $(base_flags) -g main.c parser.c scanner.c $(library_path) $(libraries) 
	gdb a.out

debug-test: 
	- rm a.out
	make test
	gdb a.out

clean: 
	- rm a.out 
	- rm json-parser

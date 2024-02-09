base_flags = -Wall -Wextra -Werror -pedantic
headers = -isystem./include


test : 
	gcc $(headers) $(base_flags) -g -c test.c server.c request.c handler.c builder.c
	gcc -o a.out test.o server.o request.o handler.o builder.o

json :
	- rm compile_commands.json
	bear -- make test
	- rm a.out

debug : a.out
	gdb a.out

clean : 
	-rm *.o
	- rm a.out

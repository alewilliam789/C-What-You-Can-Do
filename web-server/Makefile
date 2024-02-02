base_flags = -Wall -Wextra -Werror -pedantic
headers = -I./include


test : 
	gcc $(headers) $(base_flags) -g test.c server.c request.c handler.c


json : 
	bear -- make test
	- rm a.out

debug : a.out
	gdb a.out

clean : a.out
	- rm a.out

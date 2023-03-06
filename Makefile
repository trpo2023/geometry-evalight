all: main

main: main.c
	g++ -o main main.c -Wall -Werror

clean:
	rm -f
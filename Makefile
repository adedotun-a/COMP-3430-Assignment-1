all: assignment1

assignment1: assignment1.c
	clang assignment1.c -Wall -Wpedantic -Wextra -Werror -pthread -o assignment1

clean:
	rm assignment1
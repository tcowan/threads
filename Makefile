all: threads

threads: threads.c
	gcc -Werror -Wall -ggdb -pthread -o threads threads.c

clean:
	rm -f threads

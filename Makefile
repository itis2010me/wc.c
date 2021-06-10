CC=gcc
FLAGS=-Wall -Werror

all: wc

wc: wc.c
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -f wc
	rm -f *.o

update:
	make clean
	make all

CC=gcc
FLAGS=-Wall -Werror

all: wc.o

wc.o: wc.c
	$(CC) $(FLAGS) -o wc wc.c

clean:
	rm -f wc

update:
	make clean
	make all

# wc.c
My own implementation of wc unix command in C.

Support muliple flags, even repeated.  

- -m for chars
- -w for words
- -l for lines

For Makefile,
- `make update` will clean and then compile.
- `make clean` and `make` still apply.\

## Example

```shell
$ make
gcc -Wall -Werror -o wc wc.c
$ ./wc bar.txt
bar.txt 43 1270 8048
$ ./wc -m bar.txt 
bar.txt 8048
$ ./wc -l foo.txt 
foo.txt 2 
$ cat foo.txt
Hi there
How are you
$
```


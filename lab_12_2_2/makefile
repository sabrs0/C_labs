CC=gcc
INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
UNITTESTSPATH=./unit/
CFLAGS= -std=c99 -fPIC -c
.PHONY: clean
make_lib: lib_funcs.c
	$(CC) $(CFLAGS) -o$ lib_funcs.o lib_funcs.c
	$(CC) -o libdyn.so -shared lib_funcs.o
clean:
	rm -fv *.exe
	rm -fv *.o
	rm -fv *.gcno

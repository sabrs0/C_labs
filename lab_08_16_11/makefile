CC=gcc
INCPATH=./inc/
OUTPATH=./out/
SRCPATH=./src/
UNITTESTSPATH=./unit_tests/
CFLAGS=-std=c99 -I$(INCPATH) -Wall -pedantic -c
.PHONY: clean
app.exe: $(OUTPATH) $(OUTPATH)main.o $(OUTPATH)funcs.o
	mkdir -p $(OUTPATH)
	$(CC) -o app.exe $(OUTPATH)main.o $(OUTPATH)funcs.o
unit_tests.exe: $(OUTPATH) $(OUTPATH)check_main.o $(OUTPATH)funcs.o
	mkdir -p $(OUTPATH)
	$(CC) -o unit_tests.exe $(OUTPATH)check_main.o $(OUTPATH)funcs.o -lcheck
$(OUTPATH)main.o: $(SRCPATH)main.c $(INCPATH)funcs.h
	$(CC) $(CFLAGS) -o$(OUTPATH)main.o $(SRCPATH)main.c
$(OUTPATH)funcs.o: $(SRCPATH)funcs.c $(INCPATH)funcs.h
	$(CC) $(CFLAGS) -o$(OUTPATH)funcs.o $(SRCPATH)funcs.c
$(OUTPATH)check_main.o: $(UNITTESTSPATH)check_main.c $(INCPATH)funcs.h
	$(CC) $(CFLAGS) -o$(OUTPATH)check_main.o $(UNITTESTSPATH)check_main.c
clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno


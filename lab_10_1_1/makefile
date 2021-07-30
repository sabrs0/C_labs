CC = gcc
CFLAGS= -I$(INCPATH) -Wall -Werror -std=c99 -pedantic -c
INCPATH=./inc/
SRCPATH=./src/
FUNCPATH=./func/
UNITTESTSPATH=./unit_tests/
OUTPATH=./out/
.PHONY: clean
app.exe: $(OUTPATH)main.o $(OUTPATH)funcs.o
	$(CC) -o app.exe $(OUTPATH)main.o $(OUTPATH)funcs.o
unit_tests.exe: $(OUTPATH)check_main.o $(OUTPATH)funcs.o
	$(CC) -o unit_tests.exe $(OUTPATH)check_main.o $(OUTPATH)funcs.o -lcheck -lpthread -lrt
$(OUTPATH)main.o: $(SRCPATH)main.c $(INCPATH)funcs.h
	mkdir -p $(OUTPATH)
	$(CC) $(CFLAGS) -o$(OUTPATH)main.o $(SRCPATH)main.c
$(OUTPATH)funcs.o: $(SRCPATH)funcs.c $(INCPATH)funcs.h
	mkdir -p $(OUTPATH)
	$(CC) $(CFLAGS) -o$(OUTPATH)funcs.o $(SRCPATH)funcs.c
$(OUTPATH)check_main.o: $(UNITTESTSPATH)check_main.c $(INCPATH)funcs.h
	mkdir -p $(OUTPATH)
	$(CC) $(CFLAGS) -o$(OUTPATH)check_main.o $(UNITTESTSPATH)check_main.c
clean:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno

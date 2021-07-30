CC=gcc
SRCPATH=./src/
OUTPATH=./out/
INCPATH=./inc/
UNITPATH=./unit/
FUNCPATH=./func/
CFLAGS= -Wall -Werror -std=c99 -I$(INCPATH) -c
.PHONY: clean
app.exe: $(OUTPATH) $(OUTPATH)main.o $(OUTPATH)funcs.o
	mkdir -p $(OUTPATH)
	$(CC) -o app.exe $(OUTPATH)main.o $(OUTPATH)funcs.o
unit_tests.exe: $(OUTPATH) $(OUTPATH)check_main.o $(OUTPATH)funcs.o
	mkdir -p $(OUTPATH)
	$(CC) -o unit_tests.exe $(OUTPATH)check_main.o $(OUTPATH)funcs.o -lcheck
func_tests.exe: $(OUTPATH) $(OUTPATH)func_tests.o $(OUTPATH)funcs.o
	mkdir -p $(OUTPATH)
	$(CC) -o func_tests.exe $(OUTPATH)func_tests.o $(OUTPATH)funcs.o
$(OUTPATH)main.o: $(SRCPATH)main.c $(INCPATH)funcs.h
	 $(CC) $(CFLAGS) -o $(OUTPATH)main.o $(SRCPATH)main.c
$(OUTPATH)funcs.o: $(SRCPATH)funcs.c $(INCPATH)funcs.h
	 $(CC) $(CFLAGS) -o $(OUTPATH)funcs.o $(SRCPATH)funcs.c
$(OUTPATH)check_main.o: $(UNITPATH)check_main.c $(INCPATH)funcs.h
	 $(CC) $(CFLAGS) -o $(OUTPATH)check_main.o $(UNITPATH)check_main.c
$(OUTPATH)func_tests.o: $(FUNCPATH)func_tests.c $(INCPATH)funcs.h
	 $(CC) $(CFLAGS) -o$(OUTPATH)func_tests.o $(FUNCPATH)func_tests.c
clean:
	rm -fv *gcno
	rm -fv *exe
	rm -fv *o

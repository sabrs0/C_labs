INC = ./inc/
OUT = ./out/
SRC = ./src/
UNIT = ./unit/
CFLAGS = -w -c
.PHONY: clean
unit_tests.exe: $(OUT)check_main.o $(OUT)funcs.o
	gcc -o unit_tests.exe  $(OUT)check_main.o $(OUT)funcs.o -lcheck
$(OUT)check_main.o: $(UNIT)check_main.c $(INC)funcs.h
	mkdir -p $(OUT)
	gcc $(CFLAGS) -o $(OUT)check_main.o $(UNIT)check_main.c
$(OUT)funcs.o: $(SRC)my_snprintf.c $(INC)funcs.h
	mkdir -p $(OUT)
	gcc $(CFLAGS) -o $(OUT)funcs.o $(SRC)my_snprintf.c
clean:
	rm -fv *.exe
	rm -fv *.o
	rm -fv *.gcno

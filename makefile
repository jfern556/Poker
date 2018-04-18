
CC = gcc
FILES =  cards.c functions.c 
OUT_EXE =  stud_poker.out

build: $(FILES)
	$(CC) $(FILES)-o $(OUT_EXE)

clean: 
	rm -rf *o $(OUT_EXE)

rebuild: clean build 

all: tic-tac-toe.o

tic-tac-toe.o: tic-tac-toe.c ../header_files/interface.h
$(CC) -I../header_files -c tic-tac-toe.c

main.o: main.c ../bee/parse.h
$(CC) -I../bee -c main.c

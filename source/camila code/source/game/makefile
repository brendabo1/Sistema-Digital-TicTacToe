all: tic-tac-toe-threads.o

tic-tac-toe.o: tic-tac-toe-threads.c ../header_files/interface.h
	$(CC) -I../header_files -c tic-tac-toe-threads.c

main.o: main.c ../bee/parse.h
	$(CC) -I../bee -c main.c

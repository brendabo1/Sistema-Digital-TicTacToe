all: tic-tac-toe

tic-tac-toe: tic-tac-toe.o interface.o mouseHandler.o posTranslate.o
	gcc -o tic-tac-toe tic-tac-toe-threads.o interface.o mouseHandler.o posTranslate.o -pthread -std=c99

tic-tac-toe.o: game/tic-tac-toe-threads.c
	gcc -c game/tic-tac-toe-threads.c -pthread -std=c99

interface.o: header_files/interface.c header_files/interface.h header_files/mouseHandler.h header_files/posTranslate.h
	gcc -c header_files/interface.c -std=c99

mouseHandler.o: header_files/mouseHandler.c header_files/mouseHandler.h
	gcc -c header_files/mouseHandler.c -std=c99

posTranslate.o: header_files/posTranslate.c header_files/posTranslate.h
	gcc -c header_files/posTranslate.c -std=c99

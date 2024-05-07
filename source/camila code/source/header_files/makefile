OBJ = ../game/tic-tac-toe-threads.o interface.o
all: prog
prog: $(OBJ)
	$(CC) -o $@ $(OBJ)

interface.o: interface.c interface.h mouseHandler.h posTranslate.h
	gcc -c interface.c mouseHandler.h posTranslate.h

mouseHandler.o: mouseHandler.c mouseHandler.h
	gcc -c mouseHandler.c

posTranslate.o: posTranslate.c posTranslate.h
	gcc -c posTranslate.c

clean:
	rm -f *.o

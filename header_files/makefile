
all: test

test: main.o interface.o mouseHandler.o posTranslate.o
	gcc -o teste main.o interface.o  mouseHandler.o posTranslate.o

main.o: main.c interface.o mouseHandler.o posTranslate.o
	gcc -c main.c interface.o mouseHandler.o posTranslate.o

interface.o: interface.c interface.h mouseHandler.h posTranslate.h
	gcc -c interface.c mouseHandler.h posTranslate.h

mouseHandler.o: mouseHandler.c mouseHandler.h
	gcc -c mouseHandler.c

posTranslate.o: posTranslate.c posTranslate.h
	gcc -c posTranslate.c

clean:
	rm -f *.o

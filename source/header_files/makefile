all: exec

exec: arquivo.c interface.o mouseHandler.o posTranslate.o
	gcc -o exec arquivo.c interface.o mouseHandler.o posTranslate.o -pthread -std=c99

interface.o: interface.c interface.h
	gcc -c interface.c -std=c99

mouseHandler.o: mouseHandler.c mouseHandler.h
	gcc -c mouseHandler.c -std=c99

posTranslate.o: posTranslate.c posTranslate.h
	gcc -c posTranslate.c -std=c99

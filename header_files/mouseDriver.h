#ifndef MOUSE_DRIVER
#define MOUSE_DRIVER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MOUSE   "/dev/input/event12"

#define EVENT_SIZE sizeof(struct input_event)

#define B_READONLY "rb"

/*consts for mouse move events*/
#define MOVE_EVENT 1
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

/*consts for mouse keys*/
#define CLICK_EVENT 2
#define LEFT_CLICK 'l'
#define RIGHT_CLICK 'r'
#define MIDDLE_CLICK 'm'

/*data format in array*/
#define TYPE 0
#define CODE 1
#define VALUE 2

/*consts for global use*/
#define ERROR 0
#define SUCCESS 1


/*input struct for mouse events bits*/
struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

 
/**
 * @param data vetor de inteiros com 3 posicoes sendo o type, code e value
 * @return inteiro 1 se deu certo 0 se houve alguem erro
*/
int getMouseEvent(int *data);

/**
 * @param ev ponteiro pra um char que recebe o valor do evento detectado
 * @return inteiro 1 se for movimento 2 se for clique e 0 se houve alguem erro
*/
int getMousePos(char * ev);


#endif 
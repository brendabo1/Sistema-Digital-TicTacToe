/*
Este é o arquivo cabeçalho do mouseHandler.c e provem o cabeçalho das funções assim como constantes e structs utilizadas no codigo

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#ifndef MOUSE_HANDLER
#define MOUSE_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Definição de constantes*/

#define MOUSE   "/dev/input/event0"  /* caminho do mouse*/

#define EVENT_SIZE sizeof(struct input_event) /* quantidade de bits de um evento do mouse*/

#define B_READONLY "rb" /* constante para o tipo de leitura binaria*/

/* constantes de eventos de movimento*/
#define MOVE_EVENT 1
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

/*constante spara eventos de clique*/
#define CLICK_EVENT 2
#define LEFT_CLICK 'l'
#define RIGHT_CLICK 'r'
#define MIDDLE_CLICK 'm'

/*formato de dados da struct organizados no vetor*/
#define TYPE 0
#define CODE 1
#define VALUE 2

/*constantes de uso geral para valores de erros e acertos*/
#define ERROR 0
#define SUCCESS 1


/*struct para melhor organização dos eventos de entrada do mouse*/
struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

 
/** 
 * 
 * faz a leitura do mouse e atribui a um vetor os valores referentes ao tipo, codigo e valor do evento
 * data: vetor de inteiros com 3 posições que guardam os valores do evento realizado
 *      -> 0 é o tipo do evento
 *      -> 1 é o codigo do evento
 *      -> 2 é o valor do evento
 * Return: Retorna um inteiro correspondente se a operação foi bem sucedida ou não
 *      -> 1 se bem sucedida
 *      -> 0 se houve algum erro
*/
int getMouseEvent(int *data);

/**
 * função responsavel por converter a leitura dos valores do  mouse em um dado mais facil de trabalhar
 * ev: o ponteiro de um char que armazena um caracter correspondente a leitura realizada
 *      -> L caso seja realizado a leitura de um evento de deslocamento para a esquerda
 *      -> R caso seja realizado a leitura de um evento de deslocamento para a direita
 *      -> U caso seja realizado a leitura de um evento de deslocamento para cima
 *      -> D caso seja realizado a leitura de um evento de deslocamento para baixo
 *      -> l caso seja um evento de clique do botão esquerdo
 *      -> r caso seja um evento de clique do botão direito
 *      -> m caso seja um evento de clique do botão do meio
 * Return: um inteiro que que informa se house erro ou qual o tipo de evento ocorreu
 *      -> -1 caso não tenha ocorrido nenhum evento valido
 *      -> 0 caso ocorra algum erro de leitura
 *      -> 1 caso haja um evento de movimentação
 *      -> 2 caso haja um evento de clique
*/
int getMousePos(char * ev);


#endif 
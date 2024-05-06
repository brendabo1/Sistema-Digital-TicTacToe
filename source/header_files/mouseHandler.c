/*
Este arquivo implementa a logica do arquivo mouseHandler.h e tem como objetivo realizar a leitura dos eventos
emitidos pelo mouse ao SO e provem essas informações de maneira mais abstraida possibilitando um melhor
aproveitamento dos dados obtidos 

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mouseHandler.h"


/* variaveis globais de contagem para manipular melhor os eventos do mouse */
int count_to_x = 0;
int count_to_y = 0;
int count_click = 0;
//alterar o nome


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
int getMouseEvent(int *data) {

        struct input_event ev; /* struct que armazena um evento de entrada do mouse */

        FILE *pathFile; /* ponteiro para o arqivo do mouse */

        /* abre o arquivo do mouse no modo leitura binaria */
        pathFile = fopen(MOUSE, B_READONLY);
        /* caso não haja erro no momento da leitura atribui ao vetor de dados os dados armazenados na struct e retorna 1*/
        if (fread(&ev, sizeof(ev), 1, pathFile)) {
                data[TYPE] = ev.type;
                data[CODE] = ev.code;
                data[VALUE] = ev.value;
                //printf("type = %d\tcode = %d\tvalue = %d\ncount x = %d\tcount y = %d\tcount click = %d\n", ev.type, ev.code, ev.value, count_to_x, count_to_y, count_click);
                return SUCCESS;

        } 
        /* caso ocorra algum erro, retonar 0*/
        else{

                return ERROR;

        }

        /* realiza o fechamendo do arquivo */
        fclose(pathFile);
}


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
int getMousePos(char * ev) {

        int data[3]; /* vetor para guardar o retorno da função de leitura do mouse */

        /*caso mão haja nenhum erro*/
        if (getMouseEvent(data)) {

                        /*caso seja um evento do tipo movimentação e seja vertical*/
                        if(data[TYPE] == 2 && data[CODE] == 1){

                                /* filtragem de sensibilidade na leitura */
                                if (data[VALUE] < -6){
                                        count_to_y +=1;

                                        /* para limitar a quantidade de eventos enviados a interaface externa usa-se um contador
                                        que é incrementado a cada detecção de um evento valido e dentro da sensibilidade definida
                                        */
                                        if (count_to_y == 7){
                                                /*reset do contador e envio do evento capturado*/
                                                count_to_y = 0;
                                                count_to_x = 0;
                                                *ev = UP;
                                                return MOVE_EVENT;
                                        } 
                                        /*caso seja detecdtado um evento dentro da sensibilidade porem o contador ainda não tenha chegado
                                        ao valor pre-definido é retornado -1 informado que não foi detectado um evento valido e dentro do filtro*/
                                        else {
                                                return -1;
                                        }
                                        

                                } else if (data[VALUE] > 6) {
                                        count_to_y -=1;
                                        if(count_to_y == -7){
                                                count_to_y = 0;
                                                count_to_x = 0;

                                                *ev = DOWN;
                                                return MOVE_EVENT;
                                        } else {
                                                return -1;
                                        }

                                        
                                } else {
                                        return -1;
                                }

                        } 
                        /* caso seja um evento do movimentação e seja no eixo horizontal */
                        else  if (data[TYPE] == 2 && data[CODE] == 0) {

                                if (data[VALUE] < -6){
                                        count_to_x += 1;
                                        if (count_to_x == 7) {
                                                count_to_y = 0;
                                                count_to_x = 0;
                                                *ev = LEFT;
                                                return MOVE_EVENT;
                                        } else {
                                                return -1;
                                        }

                                } else if (data[VALUE] > 6) {
                                        count_to_x -= 1;
                                        if(count_to_x == -7){
                                                count_to_y = 0;
                                                count_to_x = 0;
                                                *ev = RIGHT;
                                                return MOVE_EVENT;
                                        }
                                        else {
                                                return -1;
                                        }
                                } else {
                                        return -1;
                                }

                        }
                        /*caso seja um evento de clique
                        */
                        else if (data[TYPE] == 4) {

                                data[VALUE] = data[VALUE] - 589553; /* redução de um valor de redundante para facilitar trabalhar com o valor */

                                if (data[VALUE] == 272) { /* 272 valor do clique esquerco */
                                        count_click +=1 ;
                                        /*como a ocorrencia do evento de clique é duplicada usa se um contado para impedir o envio de eventos d*/
                                        if (count_click == 2) {
                                                count_click = 0;
                                                *ev = LEFT_CLICK;
                                                return CLICK_EVENT;
                                        } else {
                                                return -1;
                                        }

                                } else if (data[VALUE] == 273) { /* 273 valor do clique direito */
                                        count_click +=1 ;
                                        if (count_click == 2) {
                                                count_click = 0;
                                                *ev = RIGHT_CLICK;
                                                return CLICK_EVENT;
                                        }else {
                                                return -1;
                                        }

                                } else if (data[VALUE] == 274) { /* 274  valor do clique do meio*/
                                        count_click +=1 ;
                                        if (count_click == 2) {
                                                count_click = 0;
                                                *ev = MIDDLE_CLICK;
                                                return CLICK_EVENT;
                                        }else {
                                                return -1;
                                        }
                                } 
                                /* caso haja leitura mas o contador não tenha chegado no valor de filtro, retorna -1 */
                                else {
                                        return -1;
                                }
                        }
                        
                } else { /* caso haja um erro, retorna 0*/

                        return ERROR;
                }
}

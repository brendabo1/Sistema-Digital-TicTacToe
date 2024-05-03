/* 
Este arquivo implementa a logica do arquivo interface.h e tem como objetivo prover uma interface de comunicação
entre o jogo e os arquivos de leitura do mouse e de tradução dos movimentos para coordenadas utilizadas no jogo.

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#include <stdio.h>
#include "interface.h"
#include "mouseHandler.h"
#include "posTranslate.h"


/**
 * função responsável pela leitura dos eventos do mouse e retornar um vetor com 3 posições
 * currentPos: vetor de inteiro com 3 posições onde 0 e 1 são os eixos Y e X e 2 é o valor correspondente ao botão pressionado
 * newPos:  vetor de inteiros com 3 posições onde 0 e 1 são as novas cordenadas Y e X e 2 é o valor correspondente ao botão pressionado
 * Return: Inteiro que indica se a operação ocorreu be sucedida ou não, 0 caso erro e 1 caso sucesso
*/
int readEvent(int currentPos[], int * newPos){

    char event = ' '; /* variavel que guarda que guarda o evento realizado pelo mouse */
    int response = 0; /* variavel responsavel por armazenar o retorno da função de leitura do mouse pra identificação de tipo de evento */

    /* Enquanto não houver um evento valido de mouse, o resto das operações ficam em espera ocupada aguardando um dado valido */
    do {
        response = getMousePos(&event);
    } while (response == -1);
    
    
    /* Verifica se o evento é um evento de movimento ou de click */
    if (response) {
            switch (response)
            {
            case MOVE_EVENT:
                    if (getnewpos(currentPos, event, newPos)){
                        newPos[CLICK] = -1; /* seta o espaço de click como -1, para indicar que foi um evento de clique */
                        return SUCCESS;
                    } else {
                        return ERROR;
                    }
                    break;
            case CLICK_EVENT:
                    /* identifica qual foi o botão pressionado, seta o valor de clique, e seta os valores de cordenadas para os anteriores */
                    switch (event)
                    {
                    case LEFT_CLICK:
                        newPos[CORD_X] = currentPos[CORD_X];
                        newPos[CORD_Y] = currentPos[CORD_Y];
                        newPos[CLICK] = 0;
                        return SUCCESS;
                        break;
                    case RIGHT_CLICK:
                        newPos[CORD_X] = currentPos[CORD_X];
                        newPos[CORD_Y] = currentPos[CORD_Y];
                        newPos[CLICK] = 1;
                        return SUCCESS;
                        break;
                    case MIDDLE_CLICK:
                        newPos[CORD_X] = currentPos[CORD_X];
                        newPos[CORD_Y] = currentPos[CORD_Y];
                        newPos[CLICK] = 2;
                        return SUCCESS;
                        break;
                    }
                    break;
            
                }
    } 
    /* caso não tenha sido um evento valido retorna erro */
    else {
        return ERROR;
    }
    /* caso nenhum codigo seja executado retorna erro por padrão */
    return ERROR;
}


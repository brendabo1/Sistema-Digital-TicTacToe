/*
Este arquivo implementa a logica do arquivo posTranslate.h e tem como objetivo prover uma tradução de eventos para entradas do mouse

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "posTranslate.h"

/**
 * função que confere se mover pra direita é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetoright(int currentpos[]) {
    if(currentpos[CORD_X] != 2)
        return true;
    else   
        return false;
}

/**
 * função que confere se mover pra esquerda é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetoleft(int currentpos[]) {
    if(currentpos[CORD_X] != 0){
        return true;
    } else {
        return false;
    }
}

/**
 * função que confere se mover pra cima é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetoup(int currentpos[]) {
    if(currentpos[CORD_Y] != 0) {
        return true;
    } else{
        return false;
    }
}

/**
 * função que confere se mover pra baixo é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetodown(int currentpos[]) {
    if(currentpos[CORD_Y] != 2)
        return true;
    else 
        return false;
}

/**
 * função responsavel por agrupar as funções de validação de movimentos de acordo com as posições atuais 
 * e impedir a ocorrencia de movimentações invalidas
 * currentpos: vetor com 2 posições onde 0 é o eixo Y e 1 é o eixo X
 * move: o proximo movimento a ser realizado
 * newPos: um vetor com 2 posições para as novas cordenadas onde 0 é o eixo Y e 1 é o eixo X
 * Return: 1 se ocorreu movimentação
 *      0 se não foi possivel realizar movimentação
*/
int getnewpos(int currentpos[], char move, int* newPos) {
    switch (move)
    {
    case UP:
        /*caso seja um movimento valido*/
        if (movetoup(currentpos)) {
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y] - 1; /*decrementa 1 no eixo Y*/
            return 1;
        } else{ /*caso não, mantem as mesmas cordenadas*/
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        }
        break;
    case DOWN:
    /*caso seja um movimento valido*/
        if(movetodown(currentpos)) {
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y] + 1; /*incrementa um no eixo Y*/
            return 1;
        } else {
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        }
    break;
    case LEFT:
    /*caso seja um movimento valido*/
        if(movetoleft(currentpos)) {
            newPos[CORD_X] = currentpos[CORD_X] - 1; /*decrementa um no eixo X*/
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        } else {
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        }
    break;
    case RIGHT:
    /*caso seja um movimento valido*/
        if (movetoright(currentpos))
        {
            newPos[CORD_X] = currentpos[CORD_X] + 1; /*incrementa um no eixo X*/
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        } else{
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        }
    break;
    }
    return 0;

}
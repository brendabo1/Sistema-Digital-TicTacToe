/*
Este é o arquivo de cabeçalho do posTranslate.c e contem a definição de constantes e cabeçalho das funções implementadas

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#ifndef POSITION_TRANSLATE
#define POSITION_TRANSLATE

#include <stdbool.h>

/* definição de constantes */
/*constantes do valor dads cordenadas no vetor*/
#define CORD_X 1
#define CORD_Y 0

/*constantes para movimento*/
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

/**
 * função que confere se mover pra direita é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetoright(int currentpos[]);

/**
 * função que confere se mover pra esquerda é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetoleft(int currentpos[]);

/**
 * função que confere se mover pra cima é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetoup(int currentpos[]);

/**
 * função que confere se mover pra baixo é um movimento valido ou não
 * currenpos: é um vetor com 2 valores onde 0 é o eixo Y e 1 é o eixo X
 * Return: verdadeiro se é um movimento valido
 *      false se é um movimento invalido
*/
bool movetodown(int currentpos[]);

/**
 * função responsavel por agrupar as funções de validação de movimentos de acordo com as posições atuais 
 * e impedir a ocorrencia de movimentações invalidas
 * currentpos: vetor com 2 posições onde 0 é o eixo Y e 1 é o eixo X
 * move: o proximo movimento a ser realizado
 * newPos: um vetor com 2 posições para as novas cordenadas onde 0 é o eixo Y e 1 é o eixo X
 * Return: 1 se ocorreu movimentação
 *      0 se não foi possivel realizar movimentação
*/
int getnewpos(int currentpos[], char move, int* newPos);

#endif
/* 
Este é o arquivo cabecalho do interface.c e tem como objetivo informar de maneira breve o cabeçalho de chamada 
de cada função contida no arquivo .c para facilitar o desenvolvimento, utilização e entendimento de terceiros 

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#ifndef INTERFACE_MOUSE_JOGO
#define INTERFACE_MOUSE_JOGO
#include "mouseHandler.h"
#include "posTranslate.h"

/* Definição de constantes */

#define CLICK 2     /* posição do vetor relativa ao dado de clique*/
#define CORD_X 1    /* posição do vetor relativa a cordenada X */
#define CORD_Y 0    /* posição do vetor relativa a cordenado Y */


/* cabeçalhos de funções */

/**
 * função responsável pela leitura dos eventos do mouse e retornar um vetor com 3 posições
 * @param currentPos vetor de inteiro com 3 posições onde 0 e 1 são os eixos Y e X e 2 é o valor correspondente ao botão pressionado
 * @param newPos  vetor de inteiros com 3 posições onde 0 e 1 são as novas cordenadas Y e X e 2 é o valor correspondente ao botão pressionado
 * @return Inteiro que indica se a operação ocorreu be sucedida ou não, 0 caso erro e 1 caso sucesso
*/
int readEvent(int currentPos[], int * newPos);

#endif
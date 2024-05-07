#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "interface.h"

int checkboard[3][3] = {{-1, -1, -1}, 
                                {-1, -1, -1}, 
                                {-1, -1, -1}};

// Variável global que indica se a thread de impressão deve continuar ou não
int shouldPrint = 1;
int vetor[3] = {0,0,-1};


void register_move(int player, int position[]){
  checkboard[position[0]][position[1]] = player;
}

int check_winner()
{
  // verifica colunas
  for (int i = 0; i < 3; i++){
    if ((checkboard[i][0] != -1) && (checkboard[i][0] == checkboard[i][1] && checkboard[i][1] == checkboard[i][2])){
      return checkboard[i][0];
    }
  }

  //verifica linhas
  for (int i = 0; i < 3; i++){
    if ((checkboard[0][i] != -1) && (checkboard[0][i] == checkboard[1][i] && checkboard[1][i] == checkboard[2][i])){
      return checkboard[0][i];
    }
  }

  //verifica diagonais
  if ((checkboard[1][1] != -1) && ((checkboard[0][0] == checkboard[1][1] && checkboard[1][1] == checkboard[2][2]) ||
                                   (checkboard[0][2] == checkboard[1][1] && checkboard[1][1] == checkboard[2][0])))
{
    return checkboard[1][1];
  }

  return -1;
}


int check_empty_space(int position[])
{
  return (checkboard[position[0]][position[1]] == -1) ? 1 : 0;
}



void print_checkboard(int cord_x, int cord_y)
{
  system("clear");
  /* Elementos gráficos */
  char *x[5] = {
      "       \0",
      " * * \0",
      "  *  \0",
      "  *  \0",
      " * * \0"};

  char *o[5] = {
      "       \0",
      "  *  \0",
      " * * \0",
      " * * \0",
      "  *  \0"};

  char *empty[5] = {
      "       \0",
      "       \0",
      "       \0",
      "       \0",
      "       \0"};

  const char horizontal_line[26] = {124, 124, 124, 124, 124,
                                    124, 124, 124, 124, 124,
                                    124, 124, 124, 124, 124,
                                    124, 124, 124, 124, 124,
                                    124, 124, 124, 124, 124, '\0'};

  const char vertical_bar[2] = {'|', '\0'};


  char **spaces[9]; //relacao jogador x elemento grafico
  int index = 0;

  /*Relaciona cada jogada do tabuleiro ao respectivo
  elemento gráfico */
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (checkboard[i][j] == 0 || checkboard[i][j] == 1){
        spaces[index] = x;
      }
      else if (checkboard[i][j] == 2){
        spaces[index] = o;
      }else{
        spaces[index] = empty;
      }

      index++;
    }
  }


  //Imprime o tabuleiro

  switch (cord_x)
  {
  //se for na primeira linha
  case 0:
    if(cord_y == 0) {
      for (int l = 0; l < 5; l++){
        printf("\t\t\t\t\t\t\t\t\t\e[46m%s\e[0m%s%s%s%s\n", spaces[0][l], vertical_bar, spaces[1][l], vertical_bar, spaces[2][l]);
      }
    } else if (cord_y == 1) {
      for (int l = 0; l < 5; l++) {
        printf("\t\t\t\t\t\t\t\t\t%s%s\e[46m%s\e[0m%s%s\n", spaces[0][l], vertical_bar, spaces[1][l], vertical_bar, spaces[2][l]);
      }
    } else {
      for (int l = 0; l < 5; l++) {
        printf("\t\t\t\t\t\t\t\t\t%s%s%s%s\e[46m%s\e[0m\n", spaces[0][l], vertical_bar, spaces[1][l], vertical_bar, spaces[2][l]);
      }
    }
    printf("\t\t\t\t\t\t\t\t\t%s\n", horizontal_line);

    for (int l = 0; l < 5; l++)
    {
      printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[3][l], vertical_bar, spaces[4][l], vertical_bar, spaces[5][l]);
    }

    printf("\t\t\t\t\t\t\t\t\t%s\n", horizontal_line);

    for (int l = 0; l < 5; l++)
    {
      printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[6][l], vertical_bar, spaces[7][l], vertical_bar, spaces[8][l]);
    }
    break;

  //se for na segunda linha
  case 1:
    for (int l = 0; l < 5; l++)
    {
      printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[0][l], vertical_bar, spaces[1][l], vertical_bar, spaces[2][l]);
    }
    printf("\t\t\t\t\t\t\t\t\t%s\n", horizontal_line);

    if(cord_y == 0) {
      for (int l = 0; l < 5; l++)
      {
        printf("\t\t\t\t\t\t\t\t\t\e[46m%s\e[0m%s%s%s%s\n", spaces[3][l], vertical_bar, spaces[4][l], vertical_bar, spaces[5][l]);
      }

    } else if (cord_y == 1) {
      for (int l = 0; l < 5; l++)
      {
        printf("\t\t\t\t\t\t\t\t\t%s%s\e[46m%s\e[0m%s%s\n", spaces[3][l], vertical_bar, spaces[4][l], vertical_bar, spaces[5][l]);
      }

    } else {
      for (int l = 0; l < 5; l++)
      {
        printf("\t\t\t\t\t\t\t\t\t%s%s%s%s\e[46m%s\e[0m\n", spaces[3][l], vertical_bar, spaces[4][l], vertical_bar, spaces[5][l]);
      }
      
    }
    printf("\t\t\t\t\t\t\t\t\t%s\n", horizontal_line);

    for (int l = 0; l < 5; l++)
    {
      printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[6][l], vertical_bar, spaces[7][l], vertical_bar, spaces[8][l]);
    }

    break;

  //se for na terceira linha
  case 2:
    for (int l = 0; l < 5; l++)
    {
      printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[0][l], vertical_bar, spaces[1][l], vertical_bar, spaces[2][l]);
    }
    printf("\t\t\t\t\t\t\t\t\t%s\n", horizontal_line);

    for (int l = 0; l < 5; l++)
    {
      printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[3][l], vertical_bar, spaces[4][l], vertical_bar, spaces[5][l]);
    }

    printf("\t\t\t\t\t\t\t\t\t%s\n", horizontal_line);


    if(cord_y == 0) {
      for (int l = 0; l < 5; l++)
      {
        printf("\t\t\t\t\t\t\t\t\t\e[46m%s\e[0m%s%s%s%s\n", spaces[6][l], vertical_bar, spaces[7][l], vertical_bar, spaces[8][l]);
      }

    } else if (cord_y == 1) {
      for (int l = 0; l < 5; l++)
      {
        printf("\t\t\t\t\t\t\t\t\t%s%s\e[46m%s\e[0m%s%s\n", spaces[6][l], vertical_bar, spaces[7][l], vertical_bar, spaces[8][l]);
      }

    } else {
      for (int l = 0; l < 5; l++)
      {
        printf("\t\t\t\t\t\t\t\t\t%s%s%s%s\e[46m%s\e[0m\n", spaces[6][l], vertical_bar, spaces[7][l], vertical_bar, spaces[8][l]);
      }
      
    }

    break;
  }
};

// Função para imprimir o tabuleiro
void *printBoard(void *arg) {
    while (shouldPrint) {
        print_checkboard(vetor[CORD_X], vetor[CORD_Y]);
        shouldPrint = 0;
    }
    pthread_exit(NULL);
}

// Função para ler o mouse
void *readMouse(void *arg) {

    while (!shouldPrint) {
        if(readEvent(vetor, vetor)){
          shouldPrint = 1;
        }
        
    }
    pthread_exit(NULL);
}

int main() {

  int i =0;
  int vitoria;
  int pos[2] = {0,0};
    pthread_t threadPrint, threadMouse;

  while(1){
    // Criação das threads
    pthread_create(&threadPrint, NULL, printBoard, NULL);
    pthread_create(&threadMouse, NULL, readMouse, NULL);
    if(vetor[CLICK] == 0) {
      pos[CORD_X] = vetor[CORD_X];
      pos[CORD_Y] = vetor[CORD_Y];
      if(check_empty_space(pos)){
        register_move(i,pos);
        if (i == 0) {
          i = 2;
        } else {
          i = 0;
        }
        vitoria =check_winner() ;
        if( vitoria!= -1) {
          system("clear");
          print_checkboard(vetor[CORD_X], vetor[CORD_Y]);
          printf("jogador %d venceu\n", vitoria);
          break;
        }
      }
    } 

    // Espera as threads terminarem
    pthread_join(threadPrint, NULL);
    pthread_join(threadMouse, NULL);
  }

    return 0;
}
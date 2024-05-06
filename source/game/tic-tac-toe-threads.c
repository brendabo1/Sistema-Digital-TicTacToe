/*
Este arquivo implementa a lógica do jogo da velha. A implementação
apresenta três modos de jogo:  i) dual player; ii) single player (easy):
jogadas do computador são geradas aleatoriamente; iii) single player (hard): 
jogadas do computador são geradas com o algoritmo 'minimax'.

Universidade Estadual de Feira de Santana - TEC499 MI Sistemas Digitais
Autores: Brenda Barbosa, Camila Queiroz e Maike de Oliveira
Data da última modificação: 07/05/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "memory-access.c"
#include "../header_files/interface.h"


#define COMPUTER 0 //identificacao do computador
#define PLAYER1 1 //identificacao do jogador 1
#define PLAYER2 2 //identificacao do jogador 2

#define WIDTH 3 // tamanho do tabuleiro

/* Function prototypes */
int tic_tac_toe_dual_player();
int tic_tac_toe_computer_player();
int tic_tac_toe_single_player_hard();
void print_title();
void print_menu();
void print_checkboard();
void reset_board();
int check_empty_space(int[]);
int empty_spaces();
void computer_move(int *);
void register_move(int, int[]);
int check_winner();

/* **************************************************************************** */

/*  VARIAVEIS GLOBAIS  */

/*
* Armazena as jogadas. Cada um dos 9 quadrantes são
* identificados por meio da linha e coluna (xy)
* 00  01  02
* 10  11  12
* 20  21  22

*/
int checkboard[WIDTH][WIDTH] = {{-1, -1, -1}, 
                                {-1, -1, -1}, 
                                {-1, -1, -1}};

int button_pressed = -1; //id do botão pressionado na placa DE1-SoC
int changed = 0; //usado para sincronizar a leitura e utilização dos botões da placa
int position[2] = {5,-1}; //quadrante e confirmação de jogada por meio do mouse
int finished = 0;

pthread_mutex_t button_mutex;
pthread_mutex_t finished_mutex;
pthread_mutex_t mouse_mutex;
pthread_cond_t condIsChanged; //condição que indica que um botão foi pressionado


/*******************************************************************
*  Função: tic_tac_toe_dual_player
*
* Implementa a lógica do jogo no modo dual player.
* Return: a identificação do jogador que ganhou a partida.
*         retorna -1 caso tenha sido um empate
*         retorna -2 caso um player solicite o encerramento
*         da partida
*******************************************************************/
int tic_tac_toe_dual_player()
{
  int playingNow = PLAYER1, //de quem é a vez de jogar
      winner = -1,          //armazena a identificação do vencedor
  
  //Loop do jogo
  while (empty_spaces() && winner == -1)
  {
    // Verificar solicitação de finalização
    if(changed == 1 && button_pressed == 0){
      pthread_mutex_lock(&button_mutex);
      changed = 0;
      pthread_mutex_unlock(&button_mutex);
      return -2;
    }

    system("clear");
    print_title();
    print_checkboard();
    printf("\nPLAYER %d É A SUA VEZ!\n", playingNow);
    printf("\t\t\t\tVOCÊ ESTÁ NO QUADRANTE: %d",position[0]);

    // Jogada do player da vez
    while(position[1] != 0){ //esperando confirmação da jogada
      // Verificando solicitação de finalização
      if(changed == 1 && button_pressed == 0){
        pthread_mutex_lock(&button_mutex);
        changed = 0;
        pthread_mutex_unlock(&button_mutex);
        return -2;
      }
      printf("\e[1D%d",position[0]); //atualiza a visualização do quadrante
    }

    // Registrar jogada
    if (check_empty_space(move))
    {
      register_move(playingNow, move);
      playingNow = (playingNow == PLAYER1) ? PLAYER2 : PLAYER1; //alterna entre players
    }
    else
    {
      continue; //quadrante ocupado
    }

    winner = check_winner(); // Verificar vencedor
  }

  system("clear");
  print_checkboard();
  return winner;
}

/*******************************************************************
*  Função: tic_tac_toe_single_player_easy
*
* Implemeta a lógica do jogo no modo single player (easy).
* Return: a identificação do jogador que ganhou a partida.
*         retorna -1 caso tenha sido um empate
*         retorna -2 caso o player solicite o encerramento
*         da partida
*******************************************************************/
int tic_tac_toe_single_player_easy()
{       
  int playingNow = COMPUTER,//de quem é a vez de jogar
      winner = -1;          //armazena a identificação do vencedor

  //Loop do jogo
  while (empty_spaces() && winner == -1)
  {
    // Verificar solicitação de finalização
    if(changed == 1 && button_pressed == 0){
      pthread_mutex_lock(&button_mutex);
      changed = 0;
      pthread_mutex_unlock(&button_mutex);
      return -2;
    }

    system("clear");
    print_title();
    print_checkboard();

    if (playingNow == COMPUTER) // jogada do computador
    {
      printf("\nCOMPUTADOR ESTÁ JOGANDO...\n");
      computer_move(move);
      sleep(1);
    }
    else //jogada do player
    { 
      printf("\nPLAYER %d É A SUA VEZ!\n", playingNow);
      printf("\t\t\t\tVOCÊ ESTÁ NO QUADRANTE: %d", position[0]);

      while(position[1] != 0){ //esperando confirmação da jogada
        //Verificando solicitação de finalização
        if(changed == 1 && button_pressed == 0){
          pthread_mutex_lock(&button_mutex);
          changed = 0;
          pthread_mutex_unlock(&button_mutex);
          return -2;
        }

      }
    }

    //Registrar jogada
    register_move(playingNow, move);
    playingNow = (playingNow == PLAYER2) ? COMPUTER : PLAYER2; //alterna entre players

    winner = check_winner(); //verificar vencedor
  }

  system("clear");
  print_checkboard();

  return winner;
}

/*******************************************************************
*  Função: tic_tac_toe_single_player_hard
*
* Implemeta a lógica do jogo no modo single player (hard).
* Return: a identificação do jogador que ganhou a partida.
*         retorna -1 caso tenha sido um empate
*         retorna -2 caso o player solicite o encerramento
*         da partida
*******************************************************************/
int tic_tac_toe_single_player_hard() {
  //TODO
}

/*******************************************************************
*  Função: print_title
* Imprime o título do jogo (TIC TAC TOE)
*******************************************************************/
void print_title()
{
  printf("\t\t\t\t########   ########   ########        ########   ########   ########      ########   ########   ########\n");
  printf("\t\t\t\t   ##         ##      ##                 ##      ##    ##   ##               ##      ##    ##   ##\n");
  printf("\t\t\t\t   ##         ##      ##                 ##      ########   ##               ##      ##    ##   ########\n");
  printf("\t\t\t\t   ##         ##      ##                 ##      ##    ##   ##               ##      ##    ##   ##\n");
  printf("\t\t\t\t   ##      ########   ########           ##      ##    ##   ########         ##      ########   ########\n\n\n\n");
}

/*******************************************************************
*  Função: print_menu
* Imprime o menu do jogo com os modos de jogo.
*******************************************************************/

void print_menu()
{
  printf("1. DUAL PLAYER\n2. SINGLE PLAYER (easy)\n3. SINGLE PLAYER (hard)");
  printf("\n\nSELECIONE SUA ESCOLHA PELOS BOTÕES DA PLACA")
}

/*******************************************************************
*  Função: print_checkboard
* Imprime o tabuleiro do jogo no estado atual.
*******************************************************************/

void print_checkboard()
{
  /* Elementos gráficos */
  char *x[5] = {
      "       \0",
      " ** ** \0",
      "  ***  \0",
      "  ***  \0",
      " ** ** \0"};

  char *o[5] = {
      "       \0",
      "  ***  \0",
      " ** ** \0",
      " ** ** \0",
      "  ***  \0"};

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
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < WIDTH; j++){
      if (checkboard[i][j] == PLAYER1 || checkboard[i][j] == COMPUTER){
        spaces[index] = x;
      }
      else if (checkboard[i][j] == PLAYER2){
        spaces[index] = o;
      }else{
        spaces[index] = empty;
      }

      index++;
    }
  }

  //Imprime o tabuleiro
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

  for (int l = 0; l < 5; l++)
  {
    printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n", spaces[6][l], vertical_bar, spaces[7][l], vertical_bar, spaces[8][l]);
  }
};


/*******************************************************************
*  Função: reset_board
* Reinicializa o tabuleiro. Seta todos os quadrantes com o valor -1
*******************************************************************/
void reset_board()
{
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < WIDTH; j++){
      checkboard[i][j] = -1;
    }
  }
}

/*******************************************************************
*  Função: check_empty_space
* Verifica se o quadrante passado está vazio
* position: vetor de inteiros com o quadrante escolhido (linha, coluna)
* Return: 1 se o quadrante estiver vazio ou 
*         0 se estiver ocupado
*******************************************************************/
int check_empty_space(int position[])
{
  return (checkboard[position[0]][position[1]] == -1) ? 1 : 0;
}

/*******************************************************************
*  Função: empty_spaces
* Verifica se existe algum quadrante vazio no tabuleiro
* Return: 1 se o existe algum quadrante vazio ou 
*         0 se todos estiverem ocupados
*******************************************************************/
int empty_spaces()
{

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      if (checkboard[i][j] == -1)
      {
        return 1;
      }
    }
  }

  return 0;
}

/*******************************************************************
*  Função: computer_move
* Seleciona de forma aleatória um quadrante vazio do tabuleiro
* p: ponteiro inteiro que será utilizado para salvar o quadrante
* (linha, coluna) selecionado
*******************************************************************/
void computer_move(int *p){
  srand(time(0)); //defincao da seed do rand
  do
  {
    p[0] = rand() % WIDTH;
    p[1] = rand() % WIDTH;

  } while (!check_empty_space(p));
}

/*******************************************************************
*  Função: register_move
* Registra a jogada passada no tabuleiro
* player: identificação do autor da jogada
* position: vetor de inteiros com o quadrante a
* ser marcado (linha, coluna)
*******************************************************************/
void register_move(int player, int position[]){
  checkboard[position[0]][position[1]] = player;
}

/*******************************************************************
*  Função: check_winner
* Verifica, no tabuleiro atual, se existe algum vencedor da partida
* Return: o identificador do vencedor da partida ou 
*         -1 caso não exista um vencedor
*******************************************************************/
int check_winner()
{
  // verifica colunas
  for (int i = 0; i < WIDTH; i++){
    if ((checkboard[i][0] != -1) && (checkboard[i][0] == checkboard[i][1] && checkboard[i][1] == checkboard[i][2])){
      return checkboard[i][0];
    }
  }

  //verifica linhas
  for (int i = 0; i < WIDTH; i++){
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

/*******************************************************************
*  Função: get_pressed_key_routine
* Identifica o último botão pressionado na placa DE1-SoC por meio da
* leitura do registrador edgecapture. Atualiza as variáveis globais 
* pressed_button e changed.
* Return: ponteiro nulo
*******************************************************************/
void* get_pressed_key_routine(){

  volatile int *KEY_ptr; // endereco virtual para os botoes
  int fd = -1; // usado para abrir /dev/mem
  void *LW_virtual; // endereco fisico para light-weight bridge
  int button;

  /* Cria endereco de acesso virtual para FPGA light-weight bridge */
  if ((fd = open_physical(fd)) == -1)
    return (-1);

  if (!(LW_virtual = map_physical(fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)))
      return (-1);
  
  //Seta o endereço virtual para a porta KEY
  KEY_ptr = LW_virtual + KEY_BASE;

  //Inicializa o registrador edgecapture
  *(KEY_ptr + 3) = 0xF;

  while(!finished){
    button = *(KEY_ptr + 3);
    *(KEY_ptr + 3) = button; //limpa registrador

    pthread_mutex_lock(&button_mutex);
    if(button & 0x1){
      button_pressed = 0;
      changed = 1;
    }else if(button & 0x2){
      button_pressed = 1;
      changed = 1;
    }else if(button & 0x4){
      button_pressed = 2;
      changed = 1;
    }else if(button & 0x8){
      button_pressed = 3;
      changed = 1;
    }
    pthread_mutex_unlock(&button_mutex);
    pthread_cond_signal(&condIsChanged);
  }

  return NULL;
}

/*******************************************************************
*  Função: game_menu_routine
* Implementa o menu do jogo
* Return: ponteiro nulo

*******************************************************************/
void* game_menu_routine(){

  int winner = -100;
  int option = -1;
  
  while(winner != -2){
    system("clear");
    print_title();
    print_menu();


    pthread_mutex_lock(&button_mutex);
    while (!changed)
    {
      pthread_cond_wait(&condIsChanged,&button_mutex);
    }
    option = button_pressed;
    changed = 0;
    pthread_mutex_unlock(&button_mutex);


    switch (option)
    {
    case 0:
      winner = -2;
      break;
    case 1:
      winner = tic_tac_toe_dual_player();
      break;
    case 2:
      winner = tic_tac_toe_single_player_easy();
      break;
    case 3:
      winner = tic_tac_toe_single_player_hard();
      break;
    }

    

    switch (winner) //identifica vencedor
    {
    case 0:
      printf("Computer wins!\n");
      break;
    case 1:
      printf("Player 1 wins!\n");
      break;
    case 2:
      printf("Player 2 wins!\n");
      break;
    case -1:
      printf("It's a draw!\n");
      break;
    case -2:
      system("clear");
      printf("Game finished!\n");
      
      pthread_mutex_lock(&finished_mutex);
      finished = 1;
      pthread_mutex_unlock(&finished_mutex);
      
      return NULL;
    }
  }
}

/*******************************************************************
*  Função: read_mouse_routine
*  Atualiza o vetor position para com as informações do quadrante
*  em que o mouse se encontra.
* Return: ponteiro nulo
*******************************************************************/
void* read_mouse_routine(){
  int mouseEvent[3] = {1,1,-1};

  while(!finished){ //lê mouse enquanto o jogo não foi finalizado
    if(!readEvent(position, position)) //repetir leitura em caso de erro
      continue;

    // Identificando quadrante
    pthread_mutex_lock(&mouse_mutex);
    if(mouse[0] == 0 && mouse[1] == 0){
      position[0] = 1;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 1 && mouse[1] == 0){
      position[0] = 2;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 2 && mouse[1] == 0){
      position[0] = 3;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 0 && mouse[1] == 1){
      position[0] = 4;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 1 && mouse[1] == 1){
      position[0] = 5;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 2 && mouse[1] == 1){
      position[0] = 6;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 0 && mouse[1] == 2){
      position[0] = 7;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 1 && mouse[1] == 2){
      position[0] = 8;
      position[1] = mouseEvent[2];
    }else if(mouse[0] == 2 && mouse[1] == 2){
      position[0] = 9;
      position[1] = mouseEvent[2];
    }
    pthread_mutex_unlock(&mouse_mutex);
  }


}
// Driver do jogo
int main(int argc, char const *argv[])
{

  pthread_t button_handler, game, mouse_handler;
  
  pthread_mutex_init(&button_mutex, NULL);
  pthread_mutex_init(&mouse_mutex, NULL);
  pthread_mutex_init(&finished_mutex, NULL);

  pthread_cond_init(&condIsChanged, NULL);

  if(pthread_create(&button_handler, NULL, &get_pressed_key_routine, NULL) !=0)
    perror("Failed to created thread");

  if(pthread_create(&game, NULL, &game_menu_routine, NULL) !=0)
    perror("Failed to created thread");

  if(pthread_create(&mouse_handler, NULL, &read_mouse_routine, NULL) != 0)
    perror("Failed to create thread");

  if(pthread_join(button_handler, NULL) !=0)
    perror("Failed to join thread");

  if(pthread_join(game, NULL) !=0)
    perror("Failed to join thread");

  if(pthread_join(mouse_handler, NULL) != 0)
    perror("Failed to join thread");


  pthread_mutex_destroy(&button_mutex);
  pthread_mutex_destroy(&mouse_mutex);
  pthread_mutex_destroy(&finished_mutex);
  pthread_cond_destroy(&condIsChanged);

  return 0;
 
}
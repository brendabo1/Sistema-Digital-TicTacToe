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
#include "../header_files/interface.c"
#include "../header_files/mouseHandler.c"
#include "../header_files/mouseHandler.h"
#include "../header_files/posTranslate.h"
#include "../header_files/posTranslate.c"

#define COMPUTER 0 // identificacao do computador
#define PLAYER1 1  // identificacao do jogador 1
#define PLAYER2 2  // identificacao do jogador 2

#define WIDTH 3 // tamanho do tabuleiro

/* Function prototypes */
void check_finish_game();
int translate_position();
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

int button_pressed = -1; // id do botão pressionado na placa DE1-SoC
int changed = 0;         // usado para sincronizar a leitura e utilização dos botões da placa
int finished = 0;             // identificação de partida finalizada externamente
int position[3] = {1, 1, -1}; // quadrante e confirmação de jogada por meio do mouse

pthread_mutex_t button_mutex;
pthread_mutex_t finished_mutex;
pthread_mutex_t mouse_mutex;
pthread_cond_t condIsChanged; // condição que indica que um botão foi pressionado

/*******************************************************************
 *  Função: check_finish_game
 *
 * Verifica se a partida foi finalizada por meio dos botões da placa DE1-SoC
 * Return: 1 se a partida foi finalizada por meio da placa DE1-SoC
 *         0 caso contrário
 *******************************************************************/

void check_finish_game()
{
  // Verificar solicitação de finalização
  if (changed == 1 && button_pressed == 0)
  {
    pthread_mutex_lock(&button_mutex);
    changed = 0; // informação lida
    pthread_mutex_unlock(&button_mutex);
    pthread_mutex_lock(&finished_mutex);
    finished = 1;
    pthread_mutex_unlock(&finished_mutex);
    // partida finalizada
  }
}

/*******************************************************************
 *  Função: translate_position
 *
 * Traduz a posição do cursor para uma visualização user friendly
 * Return: valor de 1 a 9 correspondente ao quadrante em que o cursor
 *         se encontra
 *******************************************************************/
int translate_position()
{
  return 0;
  // todo
}
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
  int playingNow = PLAYER1, // de quem é a vez de jogar
      winner = -1;          // armazena a identificação do vencedor
  int lastClick = -1;
  int move[3] = {1, 1, -1};

  // Loop do jogo
  while (empty_spaces() && winner == -1)
  {
    check_finish_game();

    if (finished) // verificando se a partida foi encerrada externamente
      return -2;

    print_title();
    print_checkboard();
    printf("\nPLAYER %d É A SUA VEZ!\n", playingNow);
    printf("\t\t\t\tVOCÊ ESTÁ NO QUADRANTE: %d", translate_position());

    // Jogada do player da vez
    while (1)
    {
      check_finish_game();
      if (finished)
        return -2;
      move[0] = position[CORD_X];
      move[1] = position[CORD_Y];
      lastClick = move[2];
      move[2] = position[2];
      printf("\033[1D");
      printf("%d", translate_position());
      if (lastClick != 0 && move[2] == 0)
        break;
    }

    if (!check_empty_space(move))
    {
      continue; // quadrante ocupado
    }

    // Registrar jogada
    register_move(playingNow, move);
    playingNow = (playingNow == PLAYER1) ? PLAYER2 : PLAYER1; // alterna entre players
    winner = check_winner();                                  // Verificar vencedor
  }

  print_title();
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
  int playingNow = COMPUTER, // de quem é a vez de jogar
      winner = -1;           // armazena a identificação do vencedor
  int lastClick = -1;
  int move[3] = {1, 1, -1};

  // Loop do jogo
  while (empty_spaces() && winner == -1)
  {
    check_finish_game();
    if (finished)
      return -2;

    print_title();
    print_checkboard();

    if (playingNow == COMPUTER) // jogada do computador
    {
      printf("\nCOMPUTADOR ESTÁ JOGANDO...\n");
      computer_move(move);
      sleep(1);
    }
    else // jogada do player
    {
      printf("\n\nPLAYER %d É A SUA VEZ!\nVOCÊ ESTÁ NO QUADRANTE:%d", playingNow, translate_position()); // atualiza a visualização do quadrante

      while (1)
      {
        check_finish_game();
        if (finished)
          return -2;
        move[0] = position[CORD_X];
        move[1] = position[CORD_Y];
        lastClick = move[2];
        move[2] = position[2];
        printf("\033[1D");
        printf("%d", translate_position());
        if (lastClick != 0 && move[2] == 0)
          break;
      }
    }

    if (!check_empty_space(move))
      continue;

    // Registrar jogada
    register_move(playingNow, move);
    playingNow = (playingNow == PLAYER2) ? COMPUTER : PLAYER2; // alterna entre players

    winner = check_winner(); // verificar vencedor
    move[0] = 1;
    move[1] = 1;
    move[2] = -1;
  }

  print_title();
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
int tic_tac_toe_single_player_hard()
{
  // TODO
}

/*******************************************************************
 *  Função: print_title
 * Imprime o título do jogo (TIC TAC TOE)
 *******************************************************************/
void print_title()
{
  printf("\033c");
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
  printf("[KEY1]. DUAL PLAYER\n[KEY2]. SINGLE PLAYER (easy)\n[KEY0]. SAIR");
  printf("\n\nSELECIONE SUA ESCOLHA PELOS BOTÕES DA PLACA\n\n");
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

  const char horizontal_line[26] = {95, 95, 95, 95, 95,
                                    95, 95, 95, 95, 95,
                                    95, 95, 95, 95, 95,
                                    95, 95, 95, 95, 95,
                                    95, 95, 95, 95, 95, '\0'};

  const char vertical_bar[2] = {'|', '\0'};

  char **spaces[9]; // relacao jogador x elemento grafico
  int index = 0;

  /*Relaciona cada jogada do tabuleiro ao respectivo
  elemento gráfico */
  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      if (checkboard[i][j] == PLAYER1 || checkboard[i][j] == COMPUTER)
      {
        spaces[index] = x;
      }
      else if (checkboard[i][j] == PLAYER2)
      {
        spaces[index] = o;
      }
      else
      {
        spaces[index] = empty;
      }

      index++;
    }
  }

  // Imprime o tabuleiro
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
}

/*******************************************************************
 *  Função: reset_board
 * Reinicializa o tabuleiro. Seta todos os quadrantes com o valor -1
 *******************************************************************/
void reset_board()
{
  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
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
void computer_move(int *p)
{
  srand(time(0)); // defincao da seed do rand
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
void register_move(int player, int position[])
{
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
  for (int i = 0; i < WIDTH; i++)
  {
    if ((checkboard[i][0] != -1) && (checkboard[i][0] == checkboard[i][1] && checkboard[i][1] == checkboard[i][2]))
    {
      return checkboard[i][0];
    }
  }

  // verifica linhas
  for (int i = 0; i < WIDTH; i++)
  {
    if ((checkboard[0][i] != -1) && (checkboard[0][i] == checkboard[1][i] && checkboard[1][i] == checkboard[2][i]))
    {
      return checkboard[0][i];
    }
  }

  // verifica diagonais
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
void *get_pressed_key_routine()
{

  volatile int *KEY_ptr; // endereco virtual para os botoes
  int fd = -1;           // usado para abrir /dev/mem
  void *LW_virtual;      // endereco fisico para light-weight bridge
  int button;

  /* Cria endereco de acesso virtual para FPGA light-weight bridge */
  if ((fd = open_physical(fd)) == -1)
    return (NULL);

  if (!(LW_virtual = map_physical(fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)))
    return (LW_virtual);

  // Seta o endereço virtual para a porta KEY
  KEY_ptr = LW_virtual + KEY_BASE;

  // Inicializa o registrador edgecapture
  *(KEY_ptr + 3) = 0xF;

  while (!finished)
  {

    button = *(KEY_ptr + 3);
    *(KEY_ptr + 3) = button; // limpa registrador

    // Identificação do botão pressionado
    pthread_mutex_lock(&button_mutex);
    if (button & 0x1)
    {
      button_pressed = 0;
      changed = 1;
    }
    else if (button & 0x2)
    {
      button_pressed = 1;
      changed = 1;
    }
    else if (button & 0x4)
    {
      button_pressed = 2;
      changed = 1;
    }
    else if (button & 0x8)
    {
      button_pressed = 3;
      changed = 1;
    }
    pthread_mutex_unlock(&button_mutex);
    pthread_cond_signal(&condIsChanged); // sinalização de novo botão pressionado
  }

  return NULL;
}

/*******************************************************************
*  Função: game_menu_routine
* Implementa o menu do jogo
* Return: ponteiro nulo

*******************************************************************/
void *game_menu_routine()
{
  /* Identificação do vencedor
  -1 -> empate
  -2 -> partida finalizada externamente
  0 -> COMPUTADOR
  1 -> PLAYER 1
  2 -> PLAYER 2
  */
  int winner = -100;
  int option = -1; // seleção do menu

  while (winner != -2)
  {
    print_title();
    print_menu();

    pthread_mutex_lock(&button_mutex);
    while (!changed) // esperando um novo botão ser lido
    {
      pthread_cond_wait(&condIsChanged, &button_mutex);
    }
    option = button_pressed;
    changed = 0; // sinalizando que a informação foi lida
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
    }

    switch (winner) // identifica vencedor
    {
    case 0:
      printf("Computer wins!\n");
      sleep(5);
      break;
    case 1:
      printf("Player 1 wins!\n");
      sleep(5);
      break;
    case 2:
      printf("Player 2 wins!\n");
      sleep(5);
      break;
    case -1:
      printf("It's a draw!\n");
      sleep(5);
      break;
    case -2:
      pthread_mutex_lock(&finished_mutex);
      finished = 1; // sinalizando que a partida foi encerrada externamente
      pthread_mutex_unlock(&finished_mutex);

      printf("\033c");
      printf("\n\t\t\t\tGame finished!\n");
      sleep(3);
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
void *read_mouse_routine()
{
  while (!finished)
  { // lê mouse enquanto o jogo não foi finalizado externamente
    pthread_mutex_lock(&mouse_mutex);
    readEvent(position, position);
    pthread_mutex_unlock(&mouse_mutex);
  }
  return NULL;
}

// Driver do jogo
int main(int argc, char const *argv[])
{
  pthread_t button_handler, game, mouse_handler;

  // INiicalização dos mutexes
  pthread_mutex_init(&button_mutex, NULL);
  pthread_mutex_init(&mouse_mutex, NULL);
  pthread_mutex_init(&finished_mutex, NULL);
  // Inicialização da condição
  pthread_cond_init(&condIsChanged, NULL);

  // Criação das threads
  if (pthread_create(&button_handler, NULL, &get_pressed_key_routine, NULL) != 0)
    perror("Failed to created thread");

  if (pthread_create(&game, NULL, &game_menu_routine, NULL) != 0)
    perror("Failed to created thread");

  if (pthread_create(&mouse_handler, NULL, &read_mouse_routine, NULL) != 0)
    perror("Failed to create thread");

  // Join das threads
  if (pthread_join(button_handler, NULL) != 0)
    perror("Failed to join thread");

  if (pthread_join(game, NULL) != 0)
    perror("Failed to join thread");

  if (pthread_join(mouse_handler, NULL) != 0)
    perror("Failed to join thread");

  // Destruição dos mutexes
  pthread_mutex_destroy(&button_mutex);
  pthread_mutex_destroy(&mouse_mutex);
  pthread_mutex_destroy(&finished_mutex);
  // Destruição da condição
  pthread_cond_destroy(&condIsChanged);

  return 0;
}

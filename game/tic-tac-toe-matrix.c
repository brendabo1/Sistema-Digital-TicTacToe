#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define PLAYER1  0
#define PLAYER2  1

#define WIDTH 3

//Function prototypes
int tic_tac_toe_dual_player();
void print_title();
void print_checkboard();
void reset_board();
int check_empty_space(int []);
int empty_spaces();
void register_move(int, int []);
int check_winner();


// ##########################################################

// Global variables
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

const char horizontal_line[26] = {220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
                                  220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, '\0'};
const char vertical_bar[2] = {219, '\0'};

int checkboard[WIDTH][WIDTH] = {{-1,-1,-1},
                                {-1,-1,-1},
                                {-1,-1,-1}};

//Functions
int tic_tac_toe_dual_player(){
  int move[2];
  int plays = 0, playingNow = PLAYER1, winner = -1;
  

  while(plays<9 && winner == -1){

    //display title and board
      system("clear");
      print_title();
      
      print_checkboard();
      
      scanf("%d",&move[0]);
      scanf("%d",&move[1]);

      //Game control
      if(move[0] == -1){
        break;		
      }else if(move[0] == 40){
        reset_board();
        continue;
      }

      //Register move
      if(check_empty_space(move)){
        register_move(playingNow, move);

        playingNow = (playingNow == PLAYER1) ? PLAYER2 : PLAYER1;

      }else{
        continue;
      }

      //Checking winner
      winner = check_winner();

      //Updating play count
      plays++;

  }
  system("clear");
  print_checkboard();
  return winner;



};
void print_title(){
  printf("\t\t\t\t########   ########   ########        ########   ########   ########      ########   ########   ########\n");
  printf("\t\t\t\t   ##         ##      ##                 ##      ##    ##   ##               ##      ##    ##   ##\n");
  printf("\t\t\t\t   ##         ##      ##                 ##      ########   ##               ##      ##    ##   ########\n");
  printf("\t\t\t\t   ##         ##      ##                 ##      ##    ##   ##               ##      ##    ##   ##\n");
  printf("\t\t\t\t   ##      ########   ########           ##      ##    ##   ########         ##      ########   ########\n\n\n\n");
}


void print_checkboard(){
  char** spaces[9];
  int index = 0;

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      if (checkboard[i][j] == PLAYER1)
      {
        spaces[index] = x;
      }else if (checkboard[i][j] == PLAYER2)
      {
        spaces[index] = o;
      }else{
        spaces[index] = empty;
      }

      index++;
    }
     
  }
  
  
  int l = 0;

  for (l = 0; l < 5; l++)
  {
    printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n",spaces[0][l],vertical_bar,spaces[1][l],vertical_bar,spaces[2][l]);
  }
  printf("\t\t\t\t\t\t\t\t\t%s\n",horizontal_line);

  l = 0;
  for (l = 0; l < 5; l++)
  {
    printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n",spaces[3][l],vertical_bar,spaces[4][l],vertical_bar,spaces[5][l]);
  }

  printf("\t\t\t\t\t\t\t\t\t%s\n",horizontal_line);

  l = 0;
  for (l = 0; l < 5; l++)
  {
    printf("\t\t\t\t\t\t\t\t\t%s%s%s%s%s\n",spaces[6][l],vertical_bar,spaces[7][l],vertical_bar,spaces[8][l]);
  }
  
  



};
void reset_board(){

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      checkboard[i][j] = -1;
    }
    
  }
}


int check_empty_space(int position[]){
  return (checkboard[position[0]][position[1]] == -1) ? 1 : 0;

}

int empty_spaces(){

  for (int i = 0; i < WIDTH; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
       if(checkboard[i][j]==-1){return 1;}
    }
  }
  
  return 0;


}


void register_move(int player, int position[]){
  
  checkboard[position[0]][position[1]] = player;
  
}

// 00 01 02
// 10 11 12
// 20 21 22

int check_winner(){
  //checking rows
  for (int i = 0; i < WIDTH; i++){
    if ((checkboard[i][0] != -1) && (checkboard[i][0] == checkboard[i][1] && checkboard[i][1] == checkboard[i][2])){
      return checkboard[i][0];
    }
    
  }
  
  //checking columns
  for (int i = 0; i < WIDTH; i++){
    if ((checkboard[0][i] != -1) && (checkboard[0][i] == checkboard[1][i] && checkboard[1][i] == checkboard[2][i]))
    {
      return checkboard[0][i];
    }
    
  }

  //checking diagonals
  if ((checkboard[1][1] != -1) && (
    (checkboard[0][0] == checkboard[1][1] && checkboard[1][1] == checkboard[2][2]) ||
    (checkboard[0][2] == checkboard[1][1] && checkboard[1][1] == checkboard[2][0])))
  {
    return checkboard[1][1];
    
  }
   
   return -1;
}


int main(int argc, char const *argv[])
{
  int winner = tic_tac_toe_dual_player();

  switch (winner)
  {
  case 0:
    printf("Player 1 wins!");
    break;
  case 1:
    printf("Player 2 wins!");
    break;
  default:
    printf("It's a draw!");
    break;
  }

    
  
  return 0;
}


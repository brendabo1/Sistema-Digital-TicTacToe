/**
 * Função para uso dos dados dos botões
*/

#include "button.h"

void game_state(int *state_p, int *buttons_p){
    /*
        state = 0 -> Menu inicial
        state = 1 -> Partida iniciada no modo 1 jogador
        state = 2 -> Partida iniciada no modo dois jogadores
        state = 2 -> Partida em pausa
        state = 3 -> Finaliza a partida

        button = 1 -> KEY_0 Encerra a partida
        button = 2 -> KEY_1 Seleciona modo 1 jogador
        button = 4 -> KEY_2 Seleciona modo 2 jogadores
        button = 8 -> KEY_3 Pause/Play na partida
    */
   switch (*state_p)
   {
    case 0:  //Menu Inicial
        if(*buttons_p == 2) *state_p = 1;  //seleciona modo single player
        else if(*buttons_p == 4) *state_p = 2; //seleciona modo dual player
    
        break;
    case 1:
        if(*buttons_p == 1) *state_p = 0;
        else if(*buttons_p == 8) *state_p = 2;
        break;
    case 2:
        if(*buttons_p == 1) *state_p = 0;
        else if(*buttons_p == 8) *state_p = 2;
        break;  
    case 3:
        *state_p = 0;
        // if(*buttons_p == 0) *state_p = 0; //Confirma o encerramento
        // else if(*buttons_p == 8) *state_p = 2;
        break; 

    }
}

void get_button(int *buttons_p, int *b_pressed){
    switch (*buttons_p)
    {
    case 1:
        *b_pressed = 0; 
        break;
    case 2:
        *b_pressed = 1; 
        break;
    case 4:
        *b_pressed = 2; 
        break;
    case 8:
        *b_pressed = 3; 
        break;
    
    }
}

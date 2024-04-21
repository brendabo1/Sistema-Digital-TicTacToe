#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "posTranslate.h"

/**
 * @param currentpos a array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetoright(int currentpos[]) {
    if(currentpos[CORD_X] != 2)
        return true;
    else   
        return false;
}

/**
 * @param currentpos a array when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetoleft(int currentpos[]) {
    if(currentpos[CORD_X] != 0){
        return true;
    } else {
        return false;
    }
}

/**
 * @param currentpos a array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetoup(int currentpos[]) {
    if(currentpos[CORD_Y] != 0) {
        return true;
    } else{
        return false;
    }
}

/**
 * @param currentpos a array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @return true if the position is valid, false otherwise
*/
bool movetodown(int currentpos[]) {
    if(currentpos[CORD_Y] != 2)
        return true;
    else 
        return false;
}

/**
 * @param currentposa array with 2 values, when 0 is y cordinate and 1 is x cordinate
 * @param move the move to be made, is a char
 * @param newPos pointer to array with 2 values for new cordinates, when 0 is cordinate y and 1 is cordinate x
 * @return 0 is have a error, 1 if the move is valid
*/
int getnewpos(int currentpos[], char move, int* newPos) {
    switch (move)
    {
    case UP:
        if (movetoup(currentpos)) {
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y] - 1;
            return 1;
        } else
            return 0;
        break;
    case DOWN:
        if(movetodown(currentpos)) {
            newPos[CORD_X] = currentpos[CORD_X];
            newPos[CORD_Y] = currentpos[CORD_Y] + 1;
            return 1;
        } else {
            return 0;
        }
    break;
    case LEFT:
        if(movetoleft(currentpos)) {
            newPos[CORD_X] = currentpos[CORD_X] - 1;
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        } else {
            return 0;
        }
    break;
    case RIGHT:
        if (movetoright(currentpos))
        {
            newPos[CORD_X] = currentpos[CORD_X] + 1;
            newPos[CORD_Y] = currentpos[CORD_Y];
            return 1;
        } else{
            return 0;
        }
    break;
    }
    return 0;

}
#include <stdio.h>
#include "interface.h"
#include "mouseHandler.h"
#include "posTranslate.h"

int readEvent(int currentPos[], int * newPos){
    char move = ' ';
    int response = 0;
    do {
        response = getMousePos(&move);
    } while (response == -1);
    
    

    if (response) {
            switch (response)
            {
            case MOVE_EVENT:
                    if (getnewpos(currentPos, move, newPos)){
                        newPos[CLICK] = -1;
                        return SUCCESS;
                    } else {
                        return ERROR;
                    }
                    break;
            case CLICK_EVENT:
                    switch (move)
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
    } else {
        return ERROR;
    }

    return ERROR;
//fazer o makefile
}


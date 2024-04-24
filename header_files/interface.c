#include <stdio.h>
#include "interface.h"
#include "mouseDriver.h"
#include "posTranslate.h"

int readEvent(int currentPos[], int * newPos){
    char move = ' ';
    int response = 0;
    response = getMousePos(&move);

    if (response) {
            switch (response)
            {
            case MOVE_EVENT:
                    if (getnewpos(currentPos, move, newPos)){
                        return SUCCESS;
                    } else {
                        return ERROR;
                    }
                    break;
            case CLICK_EVENT:
                    switch (move)
                    {
                    case LEFT_CLICK:
                        newPos[CORD_X] = INVALID_CORD;
                        newPos[CORD_Y] = INVALID_CORD;
                        newPos[CLICK] = 0;
                        return SUCCESS;
                        break;
                    case RIGHT_CLICK:
                        newPos[CORD_X] = INVALID_CORD;
                        newPos[CORD_Y] = INVALID_CORD;
                        newPos[CLICK] = 1;
                        return SUCCESS;
                        break;
                    case MIDDLE_CLICK:
                        newPos[CORD_X] = INVALID_CORD;
                        newPos[CORD_Y] = INVALID_CORD;
                        newPos[CLICK] = 2;
                        return SUCCESS;
                        break;
                    }
                    break;
            
                }
    } else {
        return ERROR;
    }

        
//fazer o makefile
}
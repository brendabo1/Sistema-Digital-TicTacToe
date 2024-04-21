#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mouseDriver.h"

int getMouseEvent(int *data) {

        struct input_event ev;

        FILE *pathFile;

        pathFile = fopen(MOUSE, B_READONLY);
        if (fread(&ev, sizeof(ev), 1, pathFile)) {

                data[TYPE] = ev.type;
                data[CODE] = ev.code;
                data[VALUE] = ev.value;
                return SUCCESS;

        } else{

                return ERROR;

        }

        fclose(pathFile);
}

int getMousePos(char * ev) {

        int data[3];

        if (getMouseEvent(data)) {

                        if(data[TYPE] == 2 && data[CODE] == 1){
                                if (data[VALUE] < -8){
                                        ev = UP;
                                        return MOVE_EVENT;

                                } else if (data[VALUE] > 8) {
                                        ev = DOWN;
                                        return MOVE_EVENT;
                                }

                        } else  if (data[TYPE] == 2 && data[CODE] == 0) {

                                if (data[VALUE] < -8){
                                        ev = LEFT;
                                        return MOVE_EVENT;

                                } else if (data[VALUE] > 8) {
                                        ev = RIGHT;
                                        return MOVE_EVENT;
                                }

                        }
                        else if (data[TYPE] == 4) {

                                data[VALUE] = data[VALUE] - 589553;

                                if (data[VALUE] == 272) {
                                        ev = LEFT_CLICK;
                                        return CLICK_EVENT;

                                } else if (data[VALUE] == 273) {
                                        ev = RIGHT_CLICK;
                                        return CLICK_EVENT;

                                } else if (data[VALUE] == 274) {
                                        ev = MIDDLE_CLICK;
                                        return CLICK_EVENT;
                                }
                        }
                        
                } else {

                        return ERROR;
                }
}

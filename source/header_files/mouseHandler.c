#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mouseHandler.h"

int count_to_x = 0;
int count_to_y = 0;
int count_click = 0;
//alterar o nome

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
                                if (data[VALUE] < -6){
                                        count_to_y +=1;

                                        if (count_to_y == 7){
                                                count_to_y = 0;
                                                *ev = UP;
                                                return MOVE_EVENT;
                                        } else {
                                                return -1;
                                        }
                                        

                                } else if (data[VALUE] > 6) {
                                        count_to_y -=1;
                                        if(count_to_y == -7){
                                                count_to_y = 0;

                                                *ev = DOWN;
                                                return MOVE_EVENT;
                                        } else {
                                                return -1;
                                        }

                                        
                                } else {
                                        return -1;
                                }

                        } else  if (data[TYPE] == 2 && data[CODE] == 0) {

                                if (data[VALUE] < -6){
                                        count_to_x += 1;
                                        if (count_to_x == 7) {
                                                count_to_x = 0;
                                                *ev = LEFT;
                                                return MOVE_EVENT;
                                        } else {
                                                return -1;
                                        }

                                } else if (data[VALUE] > 6) {
                                        count_to_x -= 1;
                                        if(count_to_x == -7){
                                                count_to_x = 0;
                                                *ev = RIGHT;
                                                return MOVE_EVENT;
                                        }
                                        else {
                                                return -1;
                                        }
                                } else {
                                        return -1;
                                }

                        }
                        else if (data[TYPE] == 4) {

                                data[VALUE] = data[VALUE] - 589553;

                                if (data[VALUE] == 272) {
                                        count_click +=1 ;
                                        if (count_click == 2) {
                                                count_click = 0;
                                                *ev = LEFT_CLICK;
                                                return CLICK_EVENT;
                                        }

                                } else if (data[VALUE] == 273) {
                                        count_click +=1 ;
                                        if (count_click == 2) {
                                                count_click = 0;
                                                *ev = RIGHT_CLICK;
                                                return CLICK_EVENT;
                                        }

                                } else if (data[VALUE] == 274) {
                                        count_click +=1 ;
                                        if (count_click == 2) {
                                                count_click = 0;
                                                *ev = MIDDLE_CLICK;
                                                return CLICK_EVENT;
                                        }
                                } else {
                                        return -1;
                                }
                        }
                        
                } else {

                        return ERROR;
                }
}

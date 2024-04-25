#ifndef INTERFACE_MOUSE_JOGO
#define INTERFACE_MOUSE_JOGO
#include "mouseDriver.h"
#include "posTranslate.h"

#define CLICK 2
#define CORD_X 1
#define CORD_Y 0
#define INVALID_CORD -1

int readEvent(int currentPos[], int * newPos);

#endif
#include <stdio.h>
#include "interface.h"

int main() {
    int currentpos[3] = {0,0,0};
    while(1){
        if (readEvent(currentpos, currentpos)){
            printf("deu bom\n");
        } else {
            printf("deu ruim\n");
        }

        printf("cord x = %d\ncord y = %d\n botão = %d\n", currentpos[1], currentpos[0], currentpos[2]);
    }
    return 0;
}
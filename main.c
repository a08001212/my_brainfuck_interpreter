#include <stdio.h>
#include <stdlib.h>
#include "Interpreter.h"
int main(int argv, char **argc) {
    if(argv < 2){
        printf("Please choose a file\n");
        exit(1);
    }
    Interpreter(argc[1]);
    return 0;
}

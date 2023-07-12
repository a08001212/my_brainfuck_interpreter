#include <stdio.h>
#include <stdlib.h>
#include "Interpreter.h"
int main(int argc, char **argv) {
    if(argc < 2){
        printf("Please choose a file\n");
        exit(1);
    }
    for(int i = 1; i<argc; ++i){
        Interpreter(argv[i]);
    }

    return 0;
}

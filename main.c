#include <stdio.h>
#include <stdlib.h>

//leer el path de los archivos de entrada y de salida
int main(int argc, char *argv[]){

    for(int i = 0; i < argc; i++){
        printf("argv[%d]: %s\n",i,argv[i]);
    }
    return EXIT_SUCCESS;
}

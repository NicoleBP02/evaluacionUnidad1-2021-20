#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

//leer el path de los archivos de entrada y de salida
int main(int argc, char *argv[]){
    //El programa se debe ejecutar en la línea de comandos así:
    //./main pathInFileName pathOutFileName
    FILE *inFile = NULL; 
    FILE *outFile = NULL;
    for(int i = 0; i < argc; i++){
        if(i == 1){
            inFile = fopen(argv[i],"r");
            if (inFile == NULL){
            perror("open file fails: ");
            return(EXIT_FAILURE);
            }
        }
        if(i == 2){
            outFile = fopen(argv[i], "r+");
            if (outFile == NULL){
            perror("out file fails: ");
            return(EXIT_FAILURE);
            }
        }
    }

    //Feature1 
    int data = 0;
    int lfcount = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; //el código ASCII para nueva linea es 10
        printf("%d\n", data);
        if(lfcount < 1){ //copia solo la primera linea en outFile
            fputc (data, outFile);
        } 
        else break; 
    }
    
    return EXIT_SUCCESS;
}

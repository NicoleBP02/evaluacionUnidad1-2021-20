#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "student.h"

//leer el path de los archivos de entrada y de salida
int main(int argc, char *argv[]){
    //El programa se debe ejecutar en la línea de comandos así:
    //./main pathInFileName pathOutFileName
    FILE *inFile = NULL; 
    FILE *outFile = NULL;
    for(uint8_t i = 0; i < argc; i++){
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

    feature1(inFile, outFile);
    feature2(inFile, outFile);
    feature3(inFile, outFile);  
    int len = 0; 
    int *arr = NULL;
    char *op = NULL;
    feature4(inFile, &arr, &len, &op);

    return EXIT_SUCCESS;
}
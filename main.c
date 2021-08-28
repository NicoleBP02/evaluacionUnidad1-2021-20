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
    int *parr = NULL;
    char *op = NULL;
    feature4(inFile, &parr, &len, &op);
    //printf("len: %d\n", len);
    for(uint8_t j=0;j<sizeof(op);j++){
        //printf("op[%d]: %s\n",j,op);
    }
    for(uint8_t j=0;j<len;j++){
        //printf("parr[%d]: %d\n",j,parr[j]);
    }
    return EXIT_SUCCESS;
}
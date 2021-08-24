#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

//leer el path de los archivos de entrada y de salida
int main(int argc, char *argv[]){

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

    char buffer[64];
    char *status =  NULL;

    do{
        status = fgets(buffer, sizeof(buffer),inFile);
        if(status != NULL){
            printf("%s",buffer);
        }
    }while (status !=NULL);
    printf("\n");

    fclose(inFile);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void Feature1(FILE *inFile, FILE *outFile);
int Feature2(FILE *inFile, FILE *outFile);
char *create_array(int);
void destroy_array(char *);

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

    Feature1(inFile, outFile);
    Feature2(inFile, outFile);

    return EXIT_SUCCESS;
}
void Feature1(FILE *inFile, FILE *outFile){
    //Feature1 
    uint8_t data = 0;
    uint8_t lfcount = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; //el código ASCII para nueva linea es 10
        if(lfcount < 1){ //copia solo la primera linea en outFile
            fputc (data, outFile);
        } 
        else break; 
    }
}
int Feature2(FILE *inFile, FILE *outFile){
    //Feature2
    char *buffer = create_array(160); //reserva espacio en mem din para un arreglo 
    if(buffer == NULL) return EXIT_FAILURE;

    uint8_t data2 = 0;
    uint8_t lfcount2 = 0;
    uint8_t i = 0;
    while((data2 = fgetc(inFile)) != EOF){
        i++;
        if(data2 == 10) lfcount2++; 
        if(lfcount2 == 1){ //copia la segunda linea en outFile
            buffer[i] = data2;
        } 
        if(lfcount2 > 1) break;
    }
    for(uint8_t i = 0; i < 10; i++){
        printf("buffer[%d]: %d\n",i, buffer[i]);
    }
    destroy_array(buffer);
    return EXIT_SUCCESS;
}
char *create_array(int size){
    return (char * ) malloc(sizeof(int)* size );
}

void destroy_array(char *this){
    free(this);
}

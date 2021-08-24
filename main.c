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
    //Feature1: lee la primer línea del archivo de entrada y 
    //la escribe en la primer línea del archivo de salida.
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
    //Feature2: lee la segunda línea del archivo de entrada, invierte su orden 
    //y la escribe en la segunda línea del archivo de salida.

    //reservo espacio en mem para buffer que contendrá data
    char *buffer = create_array(40); //160 lo que podía pesar una línea llena
    if(buffer == NULL) return EXIT_FAILURE;

    buffer[0] = 10; //enter... para que comienze en la 2da línea
    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t i = 1;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break;
        buffer[i] = data;
        i++;
    }
    //cuento la cantidad de chars para crear otro arreglo 
    uint8_t cont = 0;
    for(uint8_t i = 0;i<sizeof(buffer);i++){
        if(buffer[i] == 0) break;
        cont++;
    }
    //creo un arreglo (que es buffer invertido) y lo escribo en file de salida
    char *invertido = create_array(cont);
    invertido[0]= 10;
    for(uint8_t i = 0;i<cont;i++){
        if(i != 0){
            invertido[i] = buffer[cont-i];
        }
        fputc (invertido[i], outFile);
    }

    destroy_array(buffer);
    destroy_array(invertido);
    return EXIT_SUCCESS;
}
char *create_array(int size){
    return (char * ) malloc(sizeof(int)* size );
}

void destroy_array(char *this){
    free(this);
}

#include <stdlib.h>
#include <stdint.h>
#include "student.h"

void feature1(FILE *inFile, FILE *outFile);
int feature2(FILE *inFile, FILE *outFile);
int feature3(FILE *inFile, FILE *outFile);
char *create_array(int);
void destroy_array(char *);

void feature1(FILE *inFile, FILE *outFile){
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
int feature2(FILE *inFile, FILE *outFile){
    //Feature2: lee la segunda línea del archivo de entrada, invierte su orden 
    //y la escribe en la segunda línea del archivo de salida.

    //reservo espacio en mem para buffer que contendrá data
    char *buffer = create_array(300); //lo que podía ocupar en bytes una línea llena 
    if(buffer == NULL) return EXIT_FAILURE;

    buffer[0] = 10; //enter... para que comienze en la 2da línea
    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t j = 1;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break;
        buffer[j] = data;
        j++;
        //printf("buffer[%d]: %d\n",j,data);
    }

    //creo un arreglo (que es buffer invertido) y lo escribo en file de salida
    char *invertido = create_array(j);
    invertido[0]= 10;
    for(uint8_t i = 0;i<j;i++){
        if(i != 0){
            invertido[i] = buffer[j-i];
        }
        fputc (invertido[i], outFile);
    }

    destroy_array(buffer);
    destroy_array(invertido);
    return EXIT_SUCCESS;
}
int feature3(FILE *inFile, FILE *outFile){
    //Feature3: lee el arreglo de enteros de la tercera línea del archivo de entrada, 
    //calcula la suma y almacena el resultado en la tercera línea del archivo de salida.
    uint8_t size = 160;
    char *nums = create_array(size);
    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t i = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break; 
        nums[i] = data;
        //printf("nums[%d]: %d\n",i,nums[i]);
        i++;
    }
    for(uint8_t j = 0; j < i;j++){
        nums[j]-=48;
        printf("nums[%d]: %d\n", j, nums[j]);
    }
    uint8_t suma = 0;
    for(uint8_t j = 0; j < i;j++){
        if(nums[j] > -4 && nums[j]!=-2 && nums[j]!=-1){
           if(nums[j]==-3){
               nums[j+1]*=-1;
           }
           else suma+=nums[j];
           printf("num[%d]:%d\n",j,nums[j]);
        }
        //printf("suma: %d\n",suma);
    }
    //printf("suma: %d\n",suma);
    destroy_array(nums);
    return EXIT_SUCCESS;
}
char *create_array(int size){
    return (char * ) malloc(sizeof(int)* size );
}

void destroy_array(char *this){
    free(this);
}
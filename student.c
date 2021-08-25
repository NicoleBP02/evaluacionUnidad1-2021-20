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
    fgets(buffer, sizeof(buffer), inFile);
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
        nums[i] = data-48;
        //printf("nums[%d]: %d\n",i,nums[i]);
        i++;
    }
    char *aux = create_array(size);
    uint8_t k = 0;
    for(uint8_t j = 0; j < i;j++){
        if(nums[j]>-16){
            if(nums[j]==-3){
                nums[j+1] = nums[j+1]*(-1);
                if(nums[j+2]!=-16){
                   nums[j+2] = (nums[j+1]*-10) + nums[j+2]; 
                   aux[k] = nums[j+2]*-1;
                   j+=2;
                }
                else aux[k] = nums[j+1];
            }
            else aux[k] = nums[j];
            if(nums[j+1]!=-16) nums[j+1] += nums[j]*10;
        }
        else k++;
    }
    uint8_t suma = 0;
    for(uint8_t j = 0; j < i;j++){
        //printf("aux[%d]: %d\n", j, aux[j]);
        suma+=aux[j];
        aux[j] = 0;
    }
    //hallar digitos de suma y transformarlos en ASCII
    aux[0] = 10;
    aux[1] = (suma/10)+48; //1er digito
    aux[2] = (suma%10)+48; //2do digito

    for(uint8_t j=0;j<3;j++){
         fputc (aux[j], outFile);
    }

    destroy_array(nums);
    destroy_array(aux);
    return EXIT_SUCCESS;
}
char *create_array(int size){
    return (char * ) malloc(sizeof(int)* size );
}

void destroy_array(char *this){
    free(this);
}
#include <stdlib.h>
#include <stdint.h>
#include "student.h"

void feature1(FILE *inFile, FILE *outFile);
int feature2(FILE *inFile, FILE *outFile);
int feature3(FILE *inFile, FILE *outFile);
void feature4(FILE *inFile, int **parr, int *length, char **op);
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
    //SOLO IMPRIMIRÁ AQUELLAS SUMAS CUYOS NUMEROS NO SUPEREN LOS 3 DÍGITOS
    if(suma > 0){ //si la suma es positiva
        if(suma>-1&&suma<10){ //1 dígito
            aux[0] = 10;
            aux[1] = suma+48;
            for(uint8_t j=0;j<3;j++){
                fputc (aux[j], outFile);
            }
        }
        if(suma>9&&suma<100){ //2 dígitos
            //hallar digitos de suma y transformarlos en ASCII
            aux[0] = 10;
            aux[1] = (suma/10)+48; //1er digito
            aux[2] = (suma%10)+48; //2do digito
            for(uint8_t j=0;j<3;j++){
                fputc (aux[j], outFile);
            }
        }
        else{ //3 dígitos
            aux[0] = 10;
            aux[1] = (suma/100)+48;
            aux[2] = ((suma%100)/10)+48;
            aux[3] = ((suma%100)%10)+48;
            for(uint8_t j=0;j<3;j++){
                fputc (aux[j], outFile);
            }
        }
    }
    else{ //si la suma es negativa
        suma*=-1;
        if(suma>-1&&suma<10){ //1 dígito
            aux[0] = 10;
            aux[1]= -3;
            aux[2] = suma+48;
            for(uint8_t j=0;j<3;j++){
                fputc (aux[j], outFile);
            }
        }
        if(suma>9&&suma<100){ //2 dígitos
            //hallar digitos de suma y transformarlos en ASCII
            aux[0] = 10;
            aux[1] =-3;
            aux[2] = (suma/10)+48; //1er digito
            aux[3] = (suma%10)+48; //2do digito
            for(uint8_t j=0;j<3;j++){
                fputc (aux[j], outFile);
            }
        }
        else{ //3 dígitos
            aux[0] = 10;
            aux[1] = -3;
            aux[2] = (suma/100)+48;
            aux[3] = ((suma%100)/10)+48;
            aux[4] = ((suma%100)%10)+48;
            for(uint8_t j=0;j<3;j++){
                fputc (aux[j], outFile);
            }
        }
    }
    
    destroy_array(nums);
    destroy_array(aux);
    return EXIT_SUCCESS;
}
void feature4(FILE *inFile, int **parr, int *length, char **op){
    //feature4: lee el arreglo de enteros de la cuarta línea del archivo de entrada 
    //así como la operación especificada luego del arreglo, separada por un espacio.
    int len = 256;
    char *arr = create_array(len); //arreglo temporal para leer el file

    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t i = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break; 
        arr[i] = data; //lleno el arreglo temporal con los chars de la línea
        i++;
    }
    char *opp = create_array(8);
    char aux;
    uint8_t k=0;
    for(uint8_t j=i;j>0;j--){
        if(arr[j]==32) break;
        if(arr[j] > 31 && arr[j] < 255 && arr[j] != 127 || arr[j] == 0){
            aux = arr[j];
            opp[k] = aux;
            printf("opp[%d]: %d  arr[%d]: %d\n",k,opp[k],j,arr[j]);
            arr[j] = 32;
            k++;
        }
    }
    printf("\n");
    for(uint8_t j=0;j<sizeof(opp);j++){
        printf("opp[%d]: %d\n",j,opp[j]);
    }

    //al final, cuando necesite que los parámetros queden en el heap debo hacer lo sig:
    //  *len = 256;
    //  char *ope = create_array(8);
    //  *op = ope;
    destroy_array(arr);
    destroy_array(opp);
}
char *create_array(int size){
    return (char * ) malloc(sizeof(int)* size );
}

void destroy_array(char *this){
    free(this);
}
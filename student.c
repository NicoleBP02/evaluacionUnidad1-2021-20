#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "student.h"

void feature1(FILE *inFile, FILE *outFile);
int feature2(FILE *inFile, FILE *outFile);
void feature3(FILE *inFile, FILE *outFile);
void feature4(FILE *inFile, int **parr, int *length, char **op);
void feature5(FILE *fout, int *parr, int length, char *op);
char *create_array(int);
int *create_intarray(int size);
void destroy_array(char *);
void destroy_intarray(int *this);

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
void feature3(FILE *inFile, FILE *outFile){
    //Feature3: lee el arreglo de enteros de la tercera línea del archivo de entrada, 
    //calcula la suma y almacena el resultado en la tercera línea del archivo de salida.
    uint8_t size = 160;
    char *buffer = create_array(size);
    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t i = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break; 
        buffer[i] = data;
        //printf("buffer[%d]: %d\n",i,buffer[i]);
        i++;
    }
    //recorrer buffer para quitar chars extraños
    for(uint8_t j=0; j<size;j++){
        if(buffer[j] > 58 || buffer[j] < 32) buffer[j] = 0;
    }
    char *token;
    int suma = 0;
    token = strtok(buffer, " ");
    if(token == NULL) EXIT_FAILURE;
    suma += atoi(token);
    while(token != NULL){
        token = strtok(NULL, " ");
        if(token==NULL) break;
        suma += atoi(token);
    }
    //printf("suma %d\n",suma);
    fprintf(outFile, "\n");
    fprintf(outFile, "%d",suma);
    destroy_array(buffer);
}
void feature4(FILE *inFile, int **parr, int *length, char **op){
    //feature4: lee el arreglo de enteros de la cuarta línea del archivo de entrada 
    //así como la operación especificada luego del arreglo, separada por un espacio.
    int size_buffer = 256;
    char *buffer = create_array(size_buffer); //para guardar el contenido de la 4ta linea
    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t i = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break; 
        buffer[i] = data; //lleno el arreglo temporal con los chars de la línea
        i++;
    }
    // PARA ENCONTRAR OP
    uint8_t size_opp = 8;
    char *opp = create_array(size_opp);
    for(uint8_t j=0;j<size_opp;j++) opp[j] = 0;
    char aux;
    uint8_t k=0;
    for(uint8_t j=i;j>0;j--){
        if(buffer[j]==32) break;
        if(buffer[j] > 31 && buffer[j] < 255 && buffer[j] != 127){
            aux = buffer[j];
            opp[k] = aux;
            //printf("opp[%d]: %d  buffer[%d]: %d\n",k,opp[k],j,buffer[j]);
            buffer[j] = 0;
            k++;
        }
    }
    char *temp = create_array(k); //arreglo temporal que contendrá lo que tendrá op
    for(uint8_t j=0;j<k;j++) temp[j] = 0; //lleno todo de ceros para evitar nums raros al final
    uint8_t inv = k-1;
    for(uint8_t j=0;j<k;j++){
        temp[inv] = opp[j]; //OP 
        //printf("temp[%d]: %d\n",inv,temp[inv]);
        inv--;
    }
    //PARA ENCONTRAR PARR Y LEN
    int *arr = create_intarray(size_buffer);
    char *token;
    token = strtok(buffer, " ");
    if(token == NULL) EXIT_FAILURE;
    arr[0] = atoi(token);
    uint8_t n = 0;
    while(token != NULL){
        if(token!=NULL){
            arr[n] = atoi(token);
            //printf("arr[%d]: %d\n",n,arr[n]);
        }else break;  
        token = strtok(NULL, " "); 
        n++;
    }
    uint8_t cont = 0;
    for(uint8_t j=0;j<size_buffer-1;j++){ //ciclo para conocer len
        if(arr[j] == 0) break;
        cont++; //LEN
    }
    int *temp2 = create_intarray(cont); //PARR
    for(uint8_t j=0;j<cont;j++){
        temp2[j] = (int)arr[j];
        //printf("temp[%d]: %d\n",j,temp2[j]);
    }

    //  IMPORTANTE!!!! 
    
    *length = cont; //this works
    *op = temp; //this doesn't
    *parr = temp2; //this doesn't

    destroy_array(buffer);
}
void feature5(FILE *fout, int *parr, int length, char *op){
    //feature5: recibe la dirección del arreglo y de la operación leída en la feature anterior 
    //realiza la operación y guarda el resultado en la cuarta línea del archivo de salida. 
    //La operación puede ser avg, max, min correspondientes al promedio, máximo o mínimo. 
    //TODOS los resultados deben ser ENTEROS, NO en punto flotante.

    unsigned int sumop = 0;
    for(uint8_t i=0;i<3;i++){
        sumop+=op[i];
        //printf("sumop: %d\n",sumop);
    }
    if(sumop == 318){ //la operación es avg
        int suma=0;
        for(uint8_t i=0;i<length;i++){
            suma+=parr[i];
        }
        int avg = suma/length;
        fprintf(fout,"\n");
        fprintf(fout,"%d",avg);
    }
    if(sumop == 326){ //la op es max
        int max = 0;
        for(uint8_t i=0;i<length;i++){
            if(parr[i]>max) max = parr[i];
        }
        fprintf(fout,"\n");
        fprintf(fout,"%d",max);
    }
    if(sumop == 324){ //la op es min
        int min = 99999;
         for(uint8_t i=0;i<length;i++){
            if(parr[i]<min) min = parr[i];
        }
        fprintf(fout,"\n");
        fprintf(fout,"%d",min);
    }
}
char *create_array(int size){
    return (char * ) malloc(sizeof(int)* size );
}
int *create_intarray(int size){
    return (int * ) malloc(sizeof(int)* size );
}
void destroy_array(char *this){
    free(this);
}
void destroy_intarray(int *this){
    free(this);
}
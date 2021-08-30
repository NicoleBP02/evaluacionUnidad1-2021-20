#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "student.h"

void feature1(FILE *inFile, FILE *outFile);
int feature2(FILE *inFile, FILE *outFile);
void feature3(FILE *inFile, FILE *outFile);
void feature4(FILE *inFile, int **parr, int *length, char **op);
void feature5(FILE *fout, int *parr, int length, char *op);
void feature6(FILE *fin, struct Obj_t *pobj);
void feature7(FILE *fout, struct Obj_t *pobj);
void feature8(FILE *fin, struct _courseInfo_t **pobj,int *length);
void feature9(FILE *fout, struct _courseInfo_t *pobj,int length);
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
    
    *length = cont; 
    *op = temp; 
    *parr = temp2; 

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
void feature6(FILE *inFile, struct Obj_t *pobj){
    //feature6: lee la quinta línea del archivo de entrada y con esta información 
    //debes configurar los valores de la siguiente estructura de datos cuya dirección 
    //se pasará a la función.

    uint8_t size = 160;
    char *buffer = create_array(size);
    uint8_t data = 0;
    uint8_t lfcount = 0;
    uint8_t i = 0;
    while((data = fgetc(inFile)) != EOF){
        if(data == 10) lfcount++; 
        if(lfcount >= 1) break; 
        buffer[i] = data;
        i++;
    }
    char *token;
    token = strtok(buffer, ",");
    if(token == NULL) EXIT_FAILURE;
    char *nombre = token;
    char *token2 = strtok(NULL, "");
    int cedula = atoi(token2);

    pobj->nombre=nombre; 
    pobj->cedula=cedula;
    //printf("nombre: %s\n",pobj->nombre);
    //printf("cedula: %d\n",pobj->cedula);

}
void feature7(FILE *fout, struct Obj_t *pobj){
    //feature7: recibe la dirección en memoria de la estructura anterior y 
    //la guarda en la quinta línea del archivo de salida primero la cédula, 
    //seguido por una coma y finalizando con el nombre. 
    fprintf(fout, "\n");
    fprintf(fout, "%d",pobj->cedula);
    fprintf(fout, ", ");
    fprintf(fout, "%s",pobj->nombre);

}
void feature8(FILE *inFile, struct _courseInfo_t **pobj,int *length){
    //feature8: lee la sexta línea del archivo de entrada que contiene un número entero positivo 
    //que especifica la cantidad de cursos que un estudiante cursó en un semestre. Luego solicita 
    //al usuario ingresar el nombre del curso, los créditos y la nota
    int size_buffer = 16;
    int cursos;
    char *buffer = create_array(size_buffer); //leo linea
    fgets(buffer,size_buffer,inFile);
    for(int j=0;j<size_buffer;j++){ //encuentro LENGTH
        buffer[j]-=48;
        if(buffer[j] > 0 && buffer[j] < 10){
            cursos = buffer[j];
        } else break;
    }
    *length = cursos; 

    char *token;
    struct _courseInfo_t *arrObj = malloc(sizeof(*arrObj)); //creo arreglo de objetos
    struct _courseInfo_t courseObj; //creo objeto
    arrObj[0] = courseObj;
    for(uint8_t i=0;i<cursos;i++){
        //printf("i: %d\n",i);
        char linea[32];  
        printf("Ingrese el curso %d: curso(sin espacios),créditos,nota\n",i+1); //leo linea
        scanf("%s", linea);
        if(linea == NULL) EXIT_FAILURE;
        //printf("linea: %s\n",linea);
        //lleno objeto con datos de linea
        char *tok_curso;
        tok_curso = strtok(linea, ",");
        strcpy(courseObj.name,tok_curso);

        //printf("curso:%s\n",courseObj.name);
        char *tok_creditos = strtok(NULL, ",");
        courseObj.credits = atoi(tok_creditos);
        //printf("creditos:%d\n",courseObj.credits);
        char *tok_nota= strtok(NULL, "");
        courseObj.grade = atof(tok_nota);
        //printf("nota:%f\n",courseObj.grade);
        arrObj[i] = courseObj;
    }
    
    *pobj = arrObj;  
    /*printf("arrObj[0]: %s, %d, %f\n",arrObj[0].name,arrObj[0].credits,arrObj[0].grade); //PRUEBA
    printf("arrObj[1]: %s, %d, %f\n",arrObj[1].name,arrObj[1].credits,arrObj[1].grade);*/
}
void feature9(FILE *fout, struct _courseInfo_t *pobj,int length){
    //feature9: finalmente, calcula el promedio ponderado del semestre. 
    //Pregunta al usuario si desea almacenar la información la información en el archivo de salida 

    //1 calcular prom ponderado
    float pond = 0;
    uint8_t sum_cred = 0;
    for(uint8_t i=0;i<length;i++){
        float nota = pobj[i].grade;
        int creditos = pobj[i].credits;
        pond = pond + (nota*creditos);
        //printf("pond: %f\n",pond);
        sum_cred = sum_cred + creditos;
    }
    float prom = pond/sum_cred;

    /*printf("ponderación: %f\n",pond);
    printf("creditos: %d\n", sum_cred);
    printf("prom: %f\n",prom);*/

    char linea[32];  
    printf("deseas almacenar la informacion (s) o (n)\n"); //leo linea
    scanf("%s", linea);
    if(linea == NULL) EXIT_FAILURE;
    //printf("linea: %s",linea);
    if(linea[0] == 115 || linea[0] == 83){
        for(uint8_t i=0;i<length;i++){
            fprintf(fout, "\n");
            fprintf(fout, "%s",pobj[i].name);
            fprintf(fout, ", ");
            fprintf(fout, "%d",pobj[i].credits);
            fprintf(fout, ", ");
            fprintf(fout, "%f",pobj[i].grade);
        }
        fprintf(fout,"\n");
        fprintf(fout,"El promedio ponderado es: %f", prom);
    }
    else{
        fprintf(fout,"\n");
        fprintf(fout,"%f",prom);
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
#ifndef _STUDENT_H
#define _STUDENT_H

#include <stdio.h>

struct Obj_t{
    char *nombre;
    int cedula;
};

void feature1(FILE *fin, FILE *fout);
int feature2(FILE *fin, FILE *fout);
int feature3(FILE *fin, FILE *fout);
void feature4(FILE *fin, int **parr, int *length, char **op);
void feature5(FILE *fout, int *parr, int length, char *op);
void feature6(FILE *fin, struct Obj_t *pobj);
void feature7(FILE *fout, struct Obj_t *pobj);
void feature8(FILE *fin, struct Obj_t **pobj,int *length);
void feature9(FILE *fout, struct Obj_t *pobj,int length);

#endif
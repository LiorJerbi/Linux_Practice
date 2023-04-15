#ifndef COPY_H
#define COPY_H
#include <stdio.h>

int check_exist(FILE *f);
int copy_f2f(FILE *f1, FILE *f2);
void verbose(int state);

#endif
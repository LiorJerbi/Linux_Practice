#ifndef CMP_H
#define CMP_H
#include <stdio.h>

int cmp_files(FILE *f1,FILE *f2);
void verbose(int state);
int ignored_case_cmp(FILE *f1,FILE *f2);

#endif 
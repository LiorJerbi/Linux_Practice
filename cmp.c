#include "cmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cmp_files(FILE *f1,FILE *f2){
    fseek(f1,0,SEEK_END);
    fseek(f2,0,SEEK_END);
    long sizef1 = ftell(f1);
    long sizef2 = ftell(f2);

    if(sizef1!=sizef2){
        return 1;
    }
    rewind(f1);
    rewind(f2);
    int b1,b2;
    while((b1 = fgetc(f1)) != EOF && (b2 = fgetc(f2)) != EOF){
        if(b1 != b2){
            return 1;
        }
    }
    return 0;
}
void verbose(int state){
    if(state == 0){     //equal
        printf("equal\n");
    }
    else if (state == 1)
    {
        printf("distinct\n");
    }
    else{
        printf("error");
    }
}
int ignored_case_cmp(FILE *f1,FILE *f2){
    fseek(f1,0,SEEK_END);
    fseek(f2,0,SEEK_END);
    long sizef1 = ftell(f1);
    long sizef2 = ftell(f2);

    if(sizef1!=sizef2){
        return 1;
    }
    rewind(f1);
    rewind(f2);
    int b1,b2;
    while((b1 = fgetc(f1)) != EOF && (b2 = fgetc(f2)) != EOF){
        if(tolower(b1) != tolower(b2)){
            return 1;
        }
    }
    return 0;
}


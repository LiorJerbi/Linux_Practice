#include "copy.h"
#include <stdio.h>


int check_exist(FILE *f){
    fseek(f,0,SEEK_END);
    long fsize = ftell(f);
    rewind(f);
    if(fsize == 0){     //file not exsit
        return 0;
    }
    else{               //file exist
        return 1;
    }
}

int copy_f2f(FILE *src, FILE *trgt){
    int c;
    while((c = fgetc(src)) != EOF){
        fputc(c,trgt);
    }
    fseek(src,0,SEEK_END);
    fseek(trgt,0,SEEK_END);
    long ssize = ftell(src);
    long tsize = ftell(trgt);
    rewind(src);
    rewind(trgt);
    if(ssize != tsize){
        return 1;
    }
    else{
        return 0;
    }
}
void verbose(int state){
    if(state == 0){     //equal
        printf("success\n");
    }
    else if (state == 1)
    {
        printf("target file exist\n");
    }
    else{
        printf("error");
    }
}
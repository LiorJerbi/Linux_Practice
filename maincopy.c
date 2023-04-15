#include "copy.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){

    if(argc < 3){
        printf("Usage: ./copy <file1> <file2> Optional[-v,-f]");
        return 1;
    }
    char *command  = argv[0];
    int state,ex;
    if(!strcmp(command,"./copy") || !strcmp(command,"copy")){
        FILE *f1 = fopen(argv[1],"rb");
        if(f1 == NULL){
            printf("error opening file.\n");
            return -2;
        }
        FILE *f2;
        if(access(argv[2],F_OK) == 0){
            f2 = fopen(argv[2],"rb");
            if(f2 == NULL){
                printf("error opening file.\n");
                return -2;
            }
            ex=1;
        }
        else{
            f2 = fopen(argv[2],"wb");
            if(f2 == NULL){
                printf("error opening file.\n");
                fclose(f1);
                return -2;
            }
            ex=0;
        }
        if(argc==3){        //No flags included.
            if(ex==1){
                state=ex;
            }
            else{
                state = copy_f2f(f1,f2);
            }
        }
        else if(argc == 4){     // -v OR -f included.
            if(!strcmp(argv[3],"-v")){
                if(ex == 1){
                    state = ex;
                }
                else{
                    state = copy_f2f(f1,f2);
                }
                verbose(state);
            }
            else if(!strcmp(argv[3],"-f")){
                fclose(f2);
                f2 = fopen(argv[2],"wb");
                if(f2 == NULL){
                    printf("error opening file.\n");
                    fclose(f1);
                    return -2;
                }
                state = copy_f2f(f1,f2);                
            }
            else{           //Not identified Flag
                printf("Usage: ./copy <file1> <file2> Optional[-v,-f]\n");
                fclose(f1);
                fclose(f2);
                return -3;
            }            
        }
        else if(argc == 5){     // -v AND -f included
            if((!strcmp(argv[3],"-f") || !strcmp(argv[3],"-v")) && (!strcmp(argv[4],"-f") || !strcmp(argv[4],"-v"))){
                fclose(f2);
                f2 = fopen(argv[2],"wb");
                if(f2 == NULL){
                    printf("error opening file.\n");
                    fclose(f1);
                    return -2;
                }
                state = copy_f2f(f1,f2);
                verbose(state);
            }
            else{
                printf("Usage: ./copy <file1> <file2> Optional[-v,-f]\n");
                fclose(f1);
                fclose(f2);
                return -3;
            } 
            fclose(f1);
            fclose(f2);      
        }
        else{
            printf("Usage: ./copy <file1> <file2> Optional[-v,-f]\n");
            fclose(f1);
            fclose(f2);
            return -3;
            }
        }
        else{
            printf("Usage: ./copy <file1> <file2> Optional[-v,-f]\n");
            return -3;
        }

        return state;
    }
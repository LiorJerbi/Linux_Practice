#include "cmp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    

    if(argc < 3){
        printf("Usage: ./cmp <file1> <file2> Optional[-v,-i]\n");
        return 1;
    }
    char *command  = argv[0];
    int state;
    if(!strcmp(command,"./cmp") || !strcmp(command,"cmp")){
        FILE *f1 = fopen(argv[1],"rb");
        FILE *f2 = fopen(argv[2],"rb");
        if(f1 == NULL || f2 == NULL){
            printf("error opening file.\n");
            return -2;
        }
        if(argc == 5){      //-v AND -i included
            if((!strcmp(argv[3],"-i") || !strcmp(argv[3],"-v")) && (!strcmp(argv[4],"-i") || !strcmp(argv[4],"-v"))){
                state = ignored_case_cmp(f1,f2);
                verbose(state);
            }
            else{
                printf("Usage: ./cmp <file1> <file2> Optional[-v,-i]\n");
                fclose(f1);
                fclose(f2);
                return -5;
            }
        }
        else if(argc == 4){      //-v OR -i included
            if(!strcmp(argv[3],"-v"))
            {
                state = cmp_files(f1,f2);
                verbose(state);
            }
            else if (!strcmp(argv[3],"-i"))
            {
                state = ignored_case_cmp(f1,f2);
            }
            else{           //Not identified Flag
                printf("Usage: ./cmp <file1> <file2> Optional[-v,-i]\n");
                fclose(f1);
                fclose(f2);
                return -3;
            }
            
        }
        else if(argc == 3){      //No flags included
            state = cmp_files(f1,f2);
        }
        fclose(f1);
        fclose(f2);
    }
    else{
        printf("Usage: ./cmp <file1> <file2> Optional[-v,-i]");
        return -4;
    }
// printf("%d\n",state);
return state;

}
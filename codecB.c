#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include "codecB.h"

void enB(char** ecode){
    int size = strlen(*ecode);
    for(int i=0;i<size;++i){
        if((*ecode)[i] > 64 && (*ecode)[i] <91 ){
            if((*ecode)[i] > 87){
                (*ecode)[i]= (*ecode)[i] - 23;
            }
            else{
                (*ecode)[i]= (*ecode)[i] + 3 ;
            }
        }
        else if ((*ecode)[i] >96 && (*ecode)[i] < 123)
        {
            if((*ecode)[i] > 119){
                (*ecode) [i] = (*ecode)[i] - 23;
            }
            else{
                (*ecode)[i] = (*ecode)[i] + 3;
            }
        }

    }

}
    
void deB(char** dcode){
    int size = strlen(*dcode);

    for(int i=0;i<size;++i){
        if((*dcode)[i] > 64 && (*dcode)[i] <91 ){
            if((*dcode)[i] < 68){
                (*dcode)[i] = (*dcode)[i] + 23;
            }
            else (*dcode)[i]= (*dcode)[i] - 3;
        }
        else if ((*dcode)[i] > 96 && (*dcode)[i] < 123){
            if((*dcode)[i] < 100){
                (*dcode)[i] = (*dcode)[i] + 23;
            }
            else (*dcode)[i]= (*dcode)[i] -3;
        }
    }

}
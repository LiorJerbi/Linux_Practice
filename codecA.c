#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "codecA.h"

void convert_letters(char** astring){
    int size = strlen((*astring));
    char ans[size+1];
    for(int i=0;i<size;++i){
        if((*astring)[i]>='A' && (*astring)[i]<= 'Z')
        {
            (*astring)[i] = (*astring)[i]+32;
        }
        else if ((*astring)[i] >= 'a' && (*astring)[i] <= 'z')
        {
            (*astring)[i] = (*astring)[i]-32;
        }

    }
    
}


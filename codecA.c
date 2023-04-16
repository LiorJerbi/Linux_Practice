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

char* convert_letters(char* astring){
    int size = strlen(astring);
    char ans[size+1];
    for(int i=0;i<size;++i){
        if(astring[i]>='A' && astring[i]<= 'Z')
        {
            ans[i] = astring[i]+32;
        }
        else if (astring[i] >= 'a' && astring[i] <= 'z')
        {
            ans[i] = astring[i]-32;
        }
        else
        {
            ans[i]=astring[i];
        }
    }
    // ans[size+1] = '\0';
    astring = ans;
    // printf("%s\n",ans);
    return astring;
    
}


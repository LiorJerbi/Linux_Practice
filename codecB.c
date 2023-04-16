#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include "codecB.h"

char* enB(char* ecode){
    int size = strlen(ecode);
    char ans[size];
    for(int i=0;i<size;++i){
        if(ecode[i] > 64 && ecode[i] <91 ){
            if(ecode[i] > 87){
                ans[i]= ecode[i] - 23;
            }
            else{
                ans[i]= ecode[i] + 3 ;
            }
        }
        else if (ecode[i] >96 && ecode[i] < 123)
        {
            if(ecode[i] > 119){
                ans [i] = ecode[i] - 23;
            }
            else{
                ans[i] = ecode[i] + 3;
            }
        }
        else{
            ans[i] = ecode[i];
        }
    }
    ans[size] = '\0';
    // printf("%s\n",ans);
    ecode = ans;
    return ecode;
}
    
char* deB(char* dcode){
    int size = strlen(dcode);
    char ans[size];
    for(int i=0;i<size;++i){
        if(dcode[i] > 64 && dcode[i] <91 ){
            if(dcode[i] < 68){
                ans[i]= dcode[i] + 23;
            }
            else ans[i]= dcode[i] - 3;
        }
        else if (dcode[i] > 96 && dcode[i] < 123){
            if(dcode[i] < 100){
                ans[i] = dcode[i] + 23;
            }
            else ans[i]= dcode[i] -3;
        }
        else ans[i]= dcode[i];
    }
    ans[size] = '\0';
    // printf("%s\n",ans);
    dcode= ans;
    return dcode;

}

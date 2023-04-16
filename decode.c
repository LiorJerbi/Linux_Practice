#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>


char* (*decode)( char *);

bool init_library(char* lib)
{
    void *hdl;
    if (!strcmp(lib,"codecA"))
    {
        hdl = dlopen("./libcodecA.so",RTLD_LAZY);
        if (NULL == hdl){
		    return false;
        }
        decode = (char*(*)(char *))dlsym(hdl,"convert_letters");
        if (NULL == decode)
        {
            return false;
        }
        
    }
    else if (!strcmp(lib,"codecB"))
    {
        hdl = dlopen("./libcodecB.so",RTLD_LAZY);
        if (NULL == hdl){
		    return false;
        }
        decode = (char*(*)( char *))dlsym(hdl,"deB");
        if (NULL == decode)
        {
            return false;
        }
    }
    else{
        printf("Usage : decode <codec> <message>");
        exit(-1);
    }
}




int main(int argc, char* argv[]){

    if(argc < 3){
        printf("Usage : encode <codec> <message>");
        return -1;
    }
    char* ans;
    if (init_library(argv[1])){
		ans = decode(argv[2]);
        printf("%s\n",ans);
    }
	else
		printf("Library was not loaded \n");
	return 0;


}
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>


int main() {
	int i;
	char *argv[10];
	char command[1024];
	char *token;

	while (1) {

		// Handles CTRL+C Signal and ignores it.
		signal(SIGINT,SIG_IGN);

	    printf("Welcome to stshell: ");
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

	    /* parse command line */
	    i = 0;
	    token = strtok (command," ");
	    while (token != NULL)
	    {
		argv[i] = token;
		token = strtok (NULL, " ");
		i++;
	    }
	    argv[i] = NULL;
	    /* Is command empty */ 
	    if (argv[0] == NULL)
		continue;

		if(!strcmp(argv[0],"exit")){
			printf("Exits stshell\n");
			exit(0);
		}
	    /* for commands not part of the shell command language */ 
	    if (fork() == 0) {
			//Using default handler to CTRL+C signal.
			signal(SIGINT,SIG_DFL);
			// printf("I am the child pid:%d\n",(int)getpid());
			int j=0;
			while(argv[j] != NULL){
				if(!strcmp(argv[j],">")){
					int fd = open(argv[j+1],O_TRUNC |O_WRONLY | O_CREAT,0666);
					close(1);
					dup2(fd,1);
					argv[j] = NULL;
					argv[j+1] = NULL;
					break;
				}
				else if(!strcmp(argv[j],">>")){
					int fd = open(argv[j+1],O_WRONLY | O_APPEND | O_CREAT,0666);
					close(1);
					dup2(fd,1);					
					argv[j] = NULL;
					argv[j+1] = NULL;					
					break;	
				}
				else if(!strcmp(argv[j],"|")){
					int fds[2];
					if(pipe(fds) == -1){
						exit(1);
					}
	
					if (fork() == 0) {			//Grand Child!
						// printf("I am the Gchild pid:%d\n",(int)getpid());
						dup2(fds[0],0);
						close(fds[1]);
						//Using default handler to CTRL+C signal.
						signal(SIGINT,SIG_DFL);
						int start = j+1;
						j++;
						while(argv[j] != NULL){
							if(!strcmp(argv[j],">")){
								int fd = open(argv[j+1],O_TRUNC |O_WRONLY | O_CREAT,0666);
								close(1);
								dup2(fd,1);
								argv[j] = NULL;
								argv[j+1] = NULL;
								break;
							}
							else if(!strcmp(argv[j],">>")){
								int fd = open(argv[j+1],O_WRONLY | O_APPEND | O_CREAT,0666);
								close(1);
								dup2(fd,1);					
								argv[j] = NULL;
								argv[j+1] = NULL;					
								break;	
							}
							else if(!strcmp(argv[j],"|")){
								int fds[2];
								if(pipe(fds) == -1){
									exit(1);
								}

								if (fork() == 0) {			//Grand Grand Child!
									dup2(fds[0],0);
									close(fds[1]);
									signal(SIGINT,SIG_DFL);
									int start2 = j+1;
									j++;
									while(argv[j] != NULL){
										if(!strcmp(argv[j],">")){
											int fd = open(argv[j+1],O_TRUNC |O_WRONLY | O_CREAT,0666);
											close(1);
											dup2(fd,1);
											argv[j] = NULL;
											argv[j+1] = NULL;
											break;
										}
										else if(!strcmp(argv[j],">>")){
											int fd = open(argv[j+1],O_WRONLY | O_APPEND | O_CREAT,0666);
											close(1);
											dup2(fd,1);					
											argv[j] = NULL;
											argv[j+1] = NULL;					
											break;	
										}
										j++;

									}	
									execvp(argv[start2], (argv+start2));
									exit(EXIT_FAILURE);
									wait(NULL);												
								}
								dup2(fds[1],1);
								close(fds[0]);				
								argv[j] = NULL;
								break;
							}
							j++;
						}
						execvp(argv[start],(argv+start));
						exit(EXIT_FAILURE);
						wait(NULL);														
					}
					dup2(fds[1],1);
					close(fds[0]);
					argv[j] = NULL;			
					break;
				}
				j++;
			}
			execvp(argv[0], argv);
			exit(EXIT_FAILURE);
			wait(NULL);
		}
		int status;
		wait(&status);
		// printf("I am the father pid:%d\n",(int)getpid());
		

	}
}

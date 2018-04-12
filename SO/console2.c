#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
	printf("Iniciando um console do caralho...\n");
	int pid, ret, st;
	char* token;
	char* args[2];
	char comando[100];
	char argumento1[100];


	const char s[2] = " ";

	while(1){
		printf(">");
		gets(comando);

	    token = strtok(comando, s);
	   
    	strcpy(comando, token);
	    
    	token = strtok(NULL, s);

    	strcpy(argumento1, token);

    	args[0] = comando;
    	args[1] = argumento1;

		pid = fork();
		
		if(pid == 0){
			if(strcmp("ls", args[0]) == 0){
				char* testearg[]={"ls",NULL};
				execv("/bin/ls", testearg);
			} else if(strcmp("mkdir", args[0]) == 0){
				mkdir(args[1],0700);
			} else if(strcmp("cd",args[0]) == 0){
				chdir(args[1]);
			} else if (strcmp("rm", args[0]) == 0){
				rmdir(args[1]);
			} else{
				printf("Comando inválido!!!\n");
			}

		} else{
			waitpid(pid,&st,0);
		}

		printf("\n\n");
	}
}
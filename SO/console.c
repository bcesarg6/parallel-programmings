#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	printf("Iniciando um console do caralho...\n");
	int pid, ret, st;
	char* token;
	char* args[3];
	char comando[100];
	char argumento1[100];
	char argumento2[100];

	const char s[2] = " ";

	while(1){
		printf(">");
		gets(comando);

		/* get the first token */
	    token = strtok(comando, s);
	   
    	strcpy(comando, token);
	    
    	token = strtok(NULL, s);

    	strcpy(argumento1, token);

    	token = strtok(NULL, s);

    	strcpy(argumento2,token);

    	args[0] = comando;
    	args[1] = argumento1;
    	args[2] = argumento2;

		pid = fork();
		
		if(pid == 0){
			execv(args[0], args);
		} else{
			waitpid(pid,&st,0);
			printf("Processo filho %d terminou com valor: %d\n", pid, st);
		}

		printf("\n\n");
	}
}
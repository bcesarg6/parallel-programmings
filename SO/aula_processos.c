#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int pid, ret, st;
	pid = fork();

	if(pid){
		printf("Processo pai!\n");
		printf("Processo criado: %d\n", pid);
		ret = waitpid(-1, &st, 0);
		printf("Processo %d encerrou com valor %d!\n", ret, st);
	} else {
		printf("Processo filho!\n");
		return 25;
	}
}
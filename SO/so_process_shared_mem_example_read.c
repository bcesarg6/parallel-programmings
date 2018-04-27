#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	int shx, *x;

	shx = shm_open("/shx",O_RDONLY, S_IRUSR);
	if(shx == -1){
		printf("Não foi possivel abrir a area\n");
		exit(0);
	}

	x = mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, shx, 0);

	printf("O valor compartilhado: %d\n", *x);

	munmap(x, sizeof(int));

	shm_unlink("/shx");

	return 0;
}
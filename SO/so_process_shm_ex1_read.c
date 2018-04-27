#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	int shx;
	char* str;

	shx = shm_open("/shx",O_RDONLY, S_IRUSR);
	if(shx == -1){
		printf("Não foi possivel abrir a area\n");
		exit(0);
	}

	str = mmap(NULL, sizeof(char) * 100, PROT_READ, MAP_SHARED, shx, 0);

	printf("A mensagem escrita foi: %s\n", str);

	munmap(str, sizeof(char) * 100);

	return 0;
}
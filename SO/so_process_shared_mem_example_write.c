#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	int shx, *x;

	shx = shm_open("/shx", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(shx,sizeof(int));

	x = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, shx, 0);

	*x = 10;
	getchar();

	munmap(x, sizeof(int));

	shm_unlink("/shx");

	return 0;
}
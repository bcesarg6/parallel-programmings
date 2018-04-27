#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	int shx;
	char* str;

	shx = shm_open("/shx", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(shx,sizeof(char) * 100);

	str = mmap(NULL, sizeof(char) * 100, PROT_READ|PROT_WRITE, MAP_SHARED, shx, 0);

	do{
		scanf("%s[^\n]", str);
		getchar();
	}while(str[0] != '\0');

	munmap(str, sizeof(char) * 100);

	shm_unlink("/shx");

	return 0;
}
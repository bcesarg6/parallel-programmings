#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int a,b,c;

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	c = a + b;

	printf("SOMA DE %d + %d = %d\n", a,b,c);
	return 0;
}
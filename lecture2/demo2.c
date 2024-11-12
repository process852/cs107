#include <stdio.h>
#include <stdlib.h>

int main(){
	int* p = malloc(sizeof(int));
	*p = 17;

	printf("%d\n", *p);

	free(p);
	return 0;
}


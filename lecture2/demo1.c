#include <stdio.h>

int main(){
	int i = 42, j = 107;
	int* p = &i; // get the address of value i
	int* q = &j;
	printf("%p\n", p);

	// see bytes different type
	printf("%ld\n", sizeof(i));
	printf("%ld\n", sizeof(p));

	// deference address
	printf("%d\n", *p);
	printf("%d\n", *q);

	return 0;

}

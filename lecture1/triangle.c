#include <stdio.h>
#include <stdlib.h>
#include <error.h>

void print_triangle(int nlevels){
	int size = 1 << nlevels;

	for(int row = size - 1; row >= 0; row--){
		for(int col = 0; col < row; col++){
			printf(" ");
		}
		for(int col = 0; col + row < size; col++){
			printf("%c ", (col & row) ? ' ' : '*');
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]){
	int nlevels = 3;
	if(argc > 1)
		nlevels = atoi(argv[1]);
	if(nlevels > 8 || nlevels < 0){
		printf("next time enter an integer i. 0 <= i <=8.\n");
	}

	print_triangle(nlevels);
	return 0;

}

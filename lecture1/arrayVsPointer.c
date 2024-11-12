#include <stdio.h>
#include <limits.h> // define limits of integer types
#include <stdlib.h> // 
		  

int main(int argc, char* argv[]){
	printf("(long)NULL: %lx\n", (long) NULL);
	printf("LONG MAX, LONG_MIN: %lx %lx\n", LONG_MAX, LONG_MIN); // long type 表示的最大值和最小
	
	long ar[11]; // 创建一个数组 ar，数组元素类型为 long
	long* pt;
	
	printf("%lx %lx\n", (long)ar, (long) &ar); 
	printf("%lx %lx\n", (long)pt, (long) &pt);

	pt = malloc(11); // 分配11个字节内存空间
	printf("%lx %lx\n", ar[12], pt[12]); // 越界访问元素，不安全，但是在C中可以编译通过
	return 0;
}

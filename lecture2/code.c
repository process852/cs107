#include <sys/param.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

/*
#define powerof2(x) ((((x) - 1) & (x)) == 0)
*/

int mid_orig(int low, int high){
	return (low + high) / 2;
}

int mid_A(int low, int high){
	return low + ((high - low) / 2);
}

int mid_B(int low, int high){
	return ((unsigned int) low + (unsigned int) high) >> 1;
}

int mid_C(int low, int high){
	return (low & high) + ((low ^ high) >> 1);
}

bool has_zero_byte(unsigned long val){
	unsigned long ones = ~0UL/ UCHAR_MAX;
	unsigned long highs = ones << (CHAR_BIT - 1);
	return ((val - ones) & (~val & highs)) != 0;
}

int main(int argc, char* argv[]){
    for(int i = 0; i < 10; i++){
        printf("powerof(%d) = %d\n", i, powerof2(i));
    }

    for(int i = 0; i > -10; i--){
        printf("powerof(%d) = %d\n", i, powerof2(i));
    }

    int a = 10, b = 10;
    printf("mid(%d, %d) = %d(orig) %d(A) %d(B) %d(C)\n", 
	a, b, mid_orig(a, b), mid_A(a, b), mid_B(a, b), mid_C(a, b));
    unsigned long num = 0x1a2b3c004d5e6f;
    printf("has_zero_byte(%#lx) = %d\n", num, has_zero_byte(num));

    printf("INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
    printf("mid(%d, %d) = %d(orig) %d(A) %d(B) %d(C)\n", 
	INT_MIN, INT_MAX, mid_orig(INT_MIN, INT_MAX), 
    mid_A(INT_MIN, INT_MAX), mid_B(INT_MIN, INT_MAX), mid_C(INT_MIN, INT_MAX));
    printf("%d\n", (INT_MAX - INT_MIN)); // 数据溢出，产生 -1
    printf("%d\n", (INT_MAX - INT_MIN) / 2);

    return 0;
}

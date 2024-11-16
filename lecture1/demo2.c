#include <stdio.h>
#include <limits.h>


int main(){
    unsigned long ones = ~0UL / UCHAR_MAX;
    printf("%lu, %lx\n", ones, ones);
    printf("%u\n", UCHAR_MAX);
    return 0;
}
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

long signed_max(int bitwidth){
    return (1L << (bitwidth - 1)) - 1;
}

long signed_min(int bitwidth){
    return ~0L << (bitwidth - 1);
}


long sat_add(long a, long b, int bitwidth){
    long c = a + b;
    long msb = 1L << (bitwidth - 1);

    if(!(a & msb) && !(b & msb) && (c & msb)){
        return signed_max(bitwidth);
    }
    else if ((a&msb) && (b&msb) && !(c&msb)){
        return signed_min(bitwidth);
    }
}

long convert_arg(const char* str, long low, long high, const char* argname){
    long n = atol(str);
    if(n < low || n > high )
        printf("Illegal value");
    return n;
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Missing argument. Please specify the bitwidth.\n");
        exit(1);
    }
    int bitwidth = convert_arg(argv[1], 4, sizeof(long)*8, "Bitwidth");
    printf("%d\n", bitwidth);
    long min = signed_min(bitwidth);
    long max = signed_max(bitwidth);
    if (argc < 4)  {
        printf("%d-bit signed integer range\n", bitwidth);
        printf("min: %ld   %#018lx\n", min, min);
        printf("max:  %ld   %#018lx\n", max, max);
    } else {
        long a = convert_arg(argv[2], min, max, "Operand");
        long b = convert_arg(argv[3], min, max, "Operand");
        printf("%ld + %ld = %ld\n", a, b, sat_add(a, b, bitwidth));   
    }
    return 0;

}
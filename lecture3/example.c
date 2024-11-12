#include <stdio.h>

typedef unsigned char BYTE;

void printBytes(BYTE* p, int bytes){
    printf("0x");
    for(int i = 0; i < bytes; i++){
        printf("%.2x", *(p + i));
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    int x = 0xffff;
    printf("%d\n", sizeof(x));
    printBytes((BYTE*)&x, sizeof(x));
    short * sp = (short *) &x;
    printf("%d\n", *sp); // 输出为 -1，由于short只占据2个字节，只解释0xffff 
    return 0;
}
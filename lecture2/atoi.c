#include <stdio.h>
#include <ctype.h>

int atoi(const char* s){
    int n = 0, neg = 0;
    while(isspace(*s)) s++;
    switch(*s){
        case '-': neg = 1;
        case '+': s++;
    }
    while(isdigit(*s)){
        n = 10*n - (*s++ - '0');
    }
    return neg ? n : -n;
}

void showBits(const char* s){
    char* p = s;
    for(int i = 0; i < sizeof(char)*8; i++){
        printf("%d ", (*p >> i) & 0x1);
    }
    printf("\n");
}

int main(){
    unsigned int i = 1u;
    printf("%d\n", *(unsigned char *)(&i) == 0x1 ? 1 : 0);
    printf("%d\n", atoi(" $5")); // output 0
    printf("%d\n", atoi("12:34)"));  // output 12
    printf("%d\n", atoi("-2147483649")); // 溢出2147483647
    int num = 50; // 0011 0010
    printf("%d\n", isspace('\0'));
    showBits(&num);
    printf("%p\n", &num);
    printf("%d\n", atoi(&num));
    // printf("%d\n", atoi(num)); // segment fault
    return 0;
}
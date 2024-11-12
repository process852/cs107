# 内存模型

计算机中的内存是一个bit位一个bit位堆叠而成，一般将8个比特位捆绑成一起表示一个字节(byte)。不同的数据类型占据了不同的字节大小，一般`char`占据一个字节，`short`表示2个字节，`float`占据4个字节等。

## 整数类型的内存表示

```C
// int 类型占据 4个字节内存大小，一共32个bit位
// 二进制表示 2^3 + 2^1 = 10 
// 0000 0000 0000 0000 0000 0000 0000 0110
#include <stdio.h>

typedef unsigned char BYTE;

void printBytes(BYTE* p, int bytes){
    printf("0x");
    for(int i = 0; i < bytes; i++){
        printf("%x", *(p + i));
    }
    printf("\n");
}

int main(int argc, char* argv[]){
    int x = 10;
    printBytes((BYTE*)&x, sizeof(x)); // 输出 0xa000
    return 0;
}
```

## 指针解引用

不同类型指针解引用，指定了该指针可以操纵的字节大小。依据不同类型指针，可以将相同的数据解释为不同的数据。

```C
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
```
#include <stdio.h>
#include <stdlib.h>

#define RANGE 3
/*
* 将码点转换为 UTF-8 的字节表示形式
* code_point表示码点
* seq 表示字节数组，用于存放UTF-8表示
* 返回类型是 int 表示写入到字节数组的字节数量
*/
int to_utf8(unsigned short code_point, unsigned char seq[]);
int countBits(unsigned short n);
void showBits(unsigned char n){
    unsigned char ones = 1u;
    for(int i = sizeof(unsigned char) * 8 - 1; i >= 0; i--){
        printf("%d ", n & (ones << i) ? 1 : 0);
    }
    printf("\n");
}


void test(unsigned short n){
    unsigned short codePoint = n;
    unsigned char seq[10];
    int bytes = to_utf8(codePoint, seq);
    printf("%d bytes\n", bytes);
    for(int i = 0; i < bytes; i++){
        showBits(seq[i]);
    }
}

int main(int argc, char* argv[]){
    test(0x20AC);
    test(0x2);
    test(0x611);
    return 0;
}


int countBits(unsigned short n){
    int count = 0;
    while(n){
        count++;
        n >>= 1;
    }
    return count;
}

int to_utf8(unsigned short code_point, unsigned char seq[]){
    unsigned short byteRange[] = {0x7f, 0x07ff, 0xffff};
    // 检查需要几个字节进行表示
    int bytes = 0;
    int numBits = 0;
    for(int i = 0; i < RANGE; i++){
        if(code_point <= byteRange[i]){
            bytes = i + 1; // bits 为 1的个数
            numBits = countBits(byteRange[i]);
            break;
        }
    }
    printf("Num bits = %d\n", numBits);
    if(bytes == 0){
        printf("Out of range\n");
        exit(1);
    }
    // 处理前导字节
    int seqIndex = 0;
    if(bytes == 1){
        seq[0] = (unsigned char)code_point;
    }
    else{
        unsigned char leadByte;
        int prefixLen = bytes + 1;
        leadByte = code_point >> (numBits - (sizeof(unsigned char)*8 - prefixLen));
        unsigned char bitPattern = 1u;
        for(int i = sizeof(unsigned char)*8 - prefixLen; i < 8; i++){
            if(i == sizeof(unsigned char)*8 - prefixLen){
                leadByte = leadByte & (~(bitPattern << i));
            }
            else{
                leadByte = leadByte | (bitPattern << i);
            }
        }
        seq[seqIndex] = leadByte;
        seqIndex++;
        // 处理连续字节
        unsigned short bitFxied = 0x3f;
        unsigned char continueByte;
        int leftByte = bytes - 1;
        for(int i = leftByte - 1; i >= 0; i--){
            continueByte = (code_point >> (i * 6)) & bitFxied;
            continueByte += 128;
            seq[seqIndex] = continueByte;
            seqIndex++;
        }

    }
    return bytes;
}
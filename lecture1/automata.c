/*
一维的自动生成机
每3个cell生成中间位置的下一个状态
bit1-bit2-bit3 表示的十进制数字，作为ruleset的位索引
ruleset 表示映射规则

example:
110 -> 6
ruleset: 10000000 -> 0
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

void draw_generation(unsigned long gen);

unsigned long advance(unsigned long gen, unsigned char ruleSet);

int main(int argc, char* argv[]){
    unsigned long gen_0 = 1UL << 32;
    unsigned char ruleSet = 30;

    // 检查输入的命令行参数必须大于2
    if(argc < 2){
        printf("Missing argument, must provide init gen and ruleset\n");
        exit(1);
    }

    // convert string to int
    ruleSet = atol(argv[1]);
    if(argc > 2)
        gen_0 = atoi(argv[2]);
    // 
    unsigned long gen = gen_0;
    for(int i = 0; i < 32; i++){
        draw_generation(gen); // 绘制某一行的图像
        gen = advance(gen, ruleSet);
    }
    return 0;
}

void draw_generation(unsigned long gen){
    // 从最高位开始遍历
    unsigned long bitPattrn = 1UL << 63;
    while(bitPattrn){
        if(bitPattrn & gen){
            printf("+");
        }
        else{
            printf(" ");
        }
        bitPattrn >>= 1;
    }
    printf("\n");
}

unsigned long advance(unsigned long gen, unsigned char ruleSet){
    unsigned long genNext = 0;
    for(int i = 63; i >= 0; i--){
        unsigned char index;
        if(i >= 1){
            index = (gen >> (i - 1)) & 7u;
        }
        else{
            index = (gen << 1) & 7u;
        }
        unsigned char bitAnd = 1u << index;
        unsigned char nextBit = bitAnd & ruleSet;
        genNext += (nextBit ? 1UL << i : 0u); // 此处一定要使用 UL表示64位
    }

    return genNext;
}
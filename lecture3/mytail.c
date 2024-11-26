/*
mytail:
1. 仅支持一个命令行参数 -N 用于表示输出的行数
2. 仅支持读取一个文件或标准输入
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <error.h>
#include <limits.h>

#define MAX_STACK_LINE 32

char* read_line(FILE* fp){
    int count = 32;
    int numCount = count;
    int addCount = count;
    char* buf = malloc(count * sizeof(char));
    assert(buf);
    char* s = buf;
    char* ret = NULL;
    while((ret = fgets(s, addCount, fp))){
        // 寻找首个出现的换行字符
        char* charFlag = strchr(ret, '\n');
        if(charFlag == NULL){// 不存在换行符
            char lastchar = getc(fp);
            if(lastchar == '\n' || lastchar == EOF)
                return buf;
            if (ungetc(lastchar, fp) == EOF)
                return buf;
            numCount *= 2;
            addCount = numCount / 2;
            s = realloc(buf, numCount * sizeof(char));
            assert(s);
            buf = s;
            s = buf + (addCount - 1); // 地址前进 count - 1
            addCount++;
            // assert(fseek(fp, -1, SEEK_CUR) == 0);
        }
        else{
            *charFlag = '\0';
            return buf;
        }
    }
    if(!ret){
        free(buf);
        return NULL;
    }
    return ret;
}


void print_last_n(FILE *fp, int n){
    // 分配 n 个指向字符串指针的内存空间， 每个元素是 char**
    char** queue = (char **)malloc(n * sizeof(char*));
    char* line;
    int firstIndex = 0;
    int curIndex = 0;
    int countLines = 0;
    while((line = read_line(fp)) != NULL){
        if(curIndex < n){
            char* tmp = (char*)malloc((strlen(line)+1) * sizeof(char));
            assert(tmp != NULL);
            strcpy(tmp, line);
            free(line);
            *(queue + curIndex) = tmp; // 将字符串地址放置到 queue+curIndex 地址上
            curIndex++;
            countLines++;
        }
        else{
            // 如果新增元素多余 n，则从头开始抛弃
            char* tmp = (char*)malloc((strlen(line)+1) * sizeof(char));
            assert(tmp != NULL);
            strcpy(tmp, line);
            free(line);
            // 先释放原先内存空间的元素
            free(*(queue + curIndex % n));
            // 改变起始位置
            firstIndex = (firstIndex + 1) % n;
            *(queue + curIndex % n) = tmp;
            curIndex++;
        }
    }

    for(int i = firstIndex; i < countLines + firstIndex; i++){
        char* line = *(queue + i % n);
        assert(line != NULL);
        printf("%s\n", line);
        free(line);
        line = NULL;
    }
    free(queue); // 释放字符串指针数组的内存空间

}

int convert_arg(const char *str)
{
    char *end;
    long n = strtol(str, &end, 10);
    if (*end != '\0') 
        error(1, 0, "Invalid number '%s'", str);
    if (n < 1 || n > INT_MAX) 
        error(1, 0, "%s is not within the acceptable range [%d, %d]", str, 1, INT_MAX);
    return n;
}

int main(int argc, char *argv[])
{
    int num = 10;

    if (argc > 1 && argv[1][0] == '-') {
        num = convert_arg(argv[1] + 1);
        argv++;
        argc--;
    }

    FILE *fp;
    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, 0, "%s: no such file", argv[1]);
    }
    print_last_n(fp, num);
    fclose(fp);
    return 0;
}
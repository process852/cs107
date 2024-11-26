#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <error.h>
/*
uniq命令：
从输入过滤相邻的匹配行，并且输出

myuniq要求：
1. 每一行输出一个前缀，表示相邻的重复次数
2. 去除相邻的重复行，只保留一行，不相邻的不删除
*/
char* read_line(FILE* fp);


void print_uniq_lines(FILE* fp){
    char* line = NULL;
    char* preLine = NULL;
    int count = 0;
    while((line = read_line(fp)) != NULL){
        if(preLine == NULL){
            count = 1;
            preLine = malloc((strlen(line) + 1) * sizeof(char));
            assert(preLine != NULL);
            strcpy(preLine, line);
        }
        else{
            if(strcmp(line, preLine) == 0){
                count++;
            }
            else{
                // 打印输出上一个不相同的行
                printf("%d ", count);
                printf("%s\n", preLine);
                free(preLine); // 释放之前的副本空间
                preLine = NULL;
                preLine = malloc((strlen(line) + 1) * sizeof(char));
                assert(preLine != NULL);
                strcpy(preLine, line);
                count = 1;
            }
            free(line);

        }
    }
    if(count > 0){
        printf("%d ", count);
        printf("%s\n", preLine);
        if(preLine != NULL){free(preLine); preLine = NULL;}
    }
    
}

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

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, 0, "%s: no such file", argv[1]);
    }
    print_uniq_lines(fp);
    fclose(fp);
    return 0;
}
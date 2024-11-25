#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <error.h>

/*
char* read_line(FILE* fp);
1. 从文件中读取下一行文本，一行的结束以换行符或者EOF表示结束
2. 如果某一行只包含 '\n'则返回空字符串，若某一行有元素，则最后一个字符替换为 '\0'
3. 使用malloc动态分配内存空间，初始分配32个字节，若不足，则翻倍直到读完整行数据
4. 若空间分配失败，应该assert报错
5. 返回的字符串是动态分配的空间，用户应该负责释放内存空间
*/
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
        if (fp == NULL) exit(1);
    }

    char *line;
    for (int i = 1; (line = read_line(fp)) != NULL; i++) {
        printf("%6d  %s\n", i, line);
        free(line);
    }
    fclose(fp);
    return 0;
}

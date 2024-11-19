#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/*
函数实现要求：
1. 不要在函数内部破坏原始字符串
2. buf 是用于存储 token 的固定大小的字符数组， buflen表示数组大小
3. 如果token字符大于 buflen，则应该将 buflen - 1字符写入 buf
4. 下一次扫描应该从溢出的 token的下一个字符开始，如果上一个token放不进buf的话
*/

bool scan_token(const char**p_input, const char* delimiters, char buf[], size_t buflen){
    const char* str1 = *p_input;
    if(str1 == NULL){
        return false;
    }
    str1 += strspn(str1, delimiters); // 丢弃开头的分割字符
    if(!*str1){
        return false;
    }
    size_t count = strcspn(str1, delimiters); // 表示 token 的字符个数
    if(count < buflen){
        memcpy(buf, str1, count);
        buf[count] = '\0';
    }
    else{
        memcpy(buf, str1, buflen - 1);
        buf[buflen - 1] = '\0';
    }
    str1 = count < buflen ? str1 + count : str1 + buflen - 1;
    *p_input = str1;
    return true;
}
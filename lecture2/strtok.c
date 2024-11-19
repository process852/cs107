/*
1. 首先认识一下内置函数
获取前缀子串的长度
size_t strspn(const char*s, const char* accept);
即字符串开始连续几个字符都在字符串accept内

strcspn
返回值表示开始连续几个字符串都不在第二个参数字符串中

*/
#include <stdio.h>
#include <string.h>


char* strtok(char*s, const char* sep){
    // 局部静态变量只在函数第一次进行初始化
    // 需要使用常量进行初始化，默认初始化为0
    static char*p = NULL; // 静态变量保存函数上次的信息
    if(s == NULL && ((s = p) == NULL)){ // 上一次扫描至'\0`时触发
        return NULL;
    }
    // 跳过只有分割符开头的部分
    s += strspn(s, sep); // 字符指针移动,移除开头的分割字符
    if(!*s){
        return NULL;
    }
    p = s + strcspn(s, sep); // 字符指针移动，移动至下一个分割位置
    if(*p)
        // 将分离的token末尾添加 '\0'
        *p++ = '\0';
    else
        p = NULL;
    return s;
}


void testStrspn(){
    char str1[] = "hello";
    char str2[] = "heo";
    printf("%ld\n", strspn(str1, str2));
}
int main(){
    testStrspn();
    return 0;

}
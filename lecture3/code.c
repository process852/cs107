#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>


char* apple_gets(char* buf){
    // 仍然没有考虑缓存字符数组溢出的问题
    int c;
    static int warned;
    static const char w[] = "warning: this program uses gets(), which is unsafe.\n";

    if(!warned){
        fprintf(stderr, "%s", w);
        warned = 1;
    }
    char* s = buf;
    // int getc( FILE* stream );
    // 从给定输入流读取下一个字符，失败时返回EOF
    // EOF 表示宏常量，int型负值整数常量表达式
    while((c = getc(stdin)) != '\n'){
        if(c == EOF){
            if(s == buf)
                return NULL;
            else
                break;
        }
        else{
            *s++ = c;
        }
    }
    *s = '\0';
    return buf;
}

char* musl_gets(char* s){
    // char* fgets( char* restrict str, int count, FILE* restrict stream );
    // fgets 至多读取 count-1 个字符并存储与str所指向的字符数组
    // restrict 是C99引入的关键字，用于修饰指针
    // 告诉编译器，该指针是访问该对象的唯一且初始的方式
    // fgets读取失败时，返回空指针
    char* ret = fgets(s, INT_MAX, stdin);
    if(ret && s[strlen(s) - 1] == '\n') s[strlen(s) -1] = '\0';
    return ret;
}

void *calloc(size_t m, size_t n){
    // SIZE_MAX 表示size_t的最大值
    if(n && m > SIZE_MAX / n){
        return NULL;
    }
    size_t sz = n*m;
    void* p = malloc(sz);
    if(p != NULL){
        size_t *wp;
        size_t nw = (sz + sizeof(*wp) - 1) / sizeof(*wp);
        for(wp = p; nw != 0; nw--, wp++){
            if(*wp) *wp = 0;
            // *wp = 0;
        }
    
    }
    return p;
}

size_t available_size_at_address(void *addr)
{
    // The internal record-keeping of the heap allocator
    // can determine the available space for a given heap address
    // but we are not privy to that information (yet! :-)
    error(1, 0, "Privileged operation for the heap allocator only!");
    return 0;
}

void* realloc(void* oldptr, size_t newsz){
    size_t = oldsz = available_size_at_address(oldptr);

    if(newsz == 0){
        free(oldptr);
        return NULL;
    }
    if(oldsz >= newsz){
        return oldptr;
    }
    void* newptr = malloc(newsz);
    if (newptr != NULL){
        if(oldptr != NULL) memcpy(newptr, oldptr, oldsz);
        free(oldptr);
    }
    return newptr;

}

int main(int argc, char *argv[])
{
    char buf[16];

    printf("This is the assign3 code program.\nWhat is your name? ");
    if (gets(buf))   // this calls myth's version of gets
        printf("Buffer is size %zu, your name is size %zu.\n", sizeof(buf), strlen(buf));
    return 0;
}
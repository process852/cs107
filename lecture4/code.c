#include <dirent.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

int dirCompare(const struct dirent** s1, const struct dirent** s2){
    return -1*strcmp((*s1)->d_name, (*s2)->d_name);
}


int musl_scandir(const char* path, struct dirent***res, 
    int (*sel)(const struct dirent*),
    int(*cmp)(const struct dirent**, const struct dirent**)){
    DIR* d = opendir(path);
    struct dirent *de, **names = NULL, **tmp;
    size_t cnt = 0, len = 0;
    if(!d) return -1; // 文件打开失败

    while((de = readdir(d))){
        if(sel && !sel(de)) continue;
        if(cnt >= len){
            len = 2*len + 1;
            if(len > SIZE_MAX / sizeof(*names)) break;
            tmp = realloc(names, len * sizeof(*names));
            if(!tmp) break;
            names = tmp;
        }
        names[cnt] = malloc(de->d_reclen);
        if(!names[cnt]) break;
        memcpy(names[cnt++], de, de->d_reclen);

    }

    closedir(d);

    if(errno){
        if(names) while(cnt--) free(names[cnt]);
        free(names);
        return -1;
    }

    if(cmp) qsort(names, cnt, sizeof *names, (int(*)(const void *, const void *))cmp);
    // if(cmp) qsort(names, cnt, sizeof *names, cmp);
    *res = names;
    return cnt;
}


int main(int argc, char* argv[]){
    struct dirent** res;
    int count = musl_scandir("/home/jinjuncan/codespace/cs107/lecture4", &res, NULL, dirCompare);
    printf("%d\n", count);
    for(int i = 0; i < count; i++){
        printf("%s\n", res[i]->d_name);
    }

    if(res) while(count--) free(res[count]);

    return 0;
}
/*
mywhich 查找可执行文件所在的目录
1.当没有参数时，则列出所有查询的目录
2.任何命令行参数有前缀+,表示通配符
3.不支持任何命令行标志位
4.默认搜索路径为MYPATH，若MYPATH不存在，则搜索PATH
5.按照路径的顺序进行精确匹配，若找到，则停止，若不存在，则输出空
6. 如何判断文件是可执行文件?
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <dirent.h>
#include "scan_token.h"

bool startsWith(const char* src, const char* prefix){
    int lenSrc = strlen(src);
    int lenPrefix = strlen(prefix);
    if(lenSrc < lenPrefix){
        return false;
    }
    else{
        for(int i = 0; i < lenPrefix; i++){
            if(src[i] != prefix[i]){
                return false;
            }
        }
        return true;
    }
}

const char* searchPath(char** env){
    int i = 0;
    const char* strPath = NULL;
    const char* strMyPath = NULL;
    const char* tmp = NULL;
    while((tmp = env[i++]) != NULL){
        if(startsWith(tmp, "MYPATH")){
            assert(tmp[6] == '=');
            strMyPath =  tmp + 7;
        }
        if(startsWith(tmp, "PATH")){
            assert(tmp[4] == '=');
            strPath = tmp + 5;
        }
    }
    return strMyPath ? strMyPath : strPath;
}
// version1
// int main(int argc, char* argv[], char* envp[]){
//     if(argc > 2){
//         printf("Only support one command line args\n");
//         exit(1);
//     }
//     else if (argc == 2){
//         char* searchBin = argv[1];
//         bool exactSearch = startsWith(searchBin, "+");
//         if (exactSearch) searchBin += 1;
//         bool notFind = true;
//         const char* Paths = searchPath(envp);
//         int maxBuf = strlen(Paths)* sizeof(char);
//         char* buf = malloc(maxBuf);
//         while (scan_token(&Paths, ":", buf, maxBuf)) { 
//             DIR* dp = opendir(buf);
//             if(dp == NULL) continue;
//             struct dirent* entry;
//             while((entry = readdir(dp)) != NULL){
//                 char* subStr = strstr(entry->d_name, searchBin);
//                 if(!exactSearch && subStr == entry->d_name && strlen(subStr) == strlen(searchBin)){
//                     printf("%s/%s\n", buf, entry->d_name);
//                     return 0;
//                 }
//                 if(exactSearch && subStr != NULL){
//                     notFind = false;
//                     printf("%s/%s\n", buf, entry->d_name);
//                 }
//             }
//             closedir(dp);
//         }
//         free(buf);
//         if(notFind) printf("\n");
//     }
//     else{
//         // print search path
//         printf("Directories in search path:\n");
//         const char* Paths = searchPath(envp);
//         // printf("%s\n", Paths);
//         int maxBuf = strlen(Paths)* sizeof(char);
//         char* buf = malloc(maxBuf);
//         while (scan_token(&Paths, ":", buf, maxBuf)) { 
//             printf("%s\n", buf); 
//         }
//         free(buf);

//     }
//     return 0;

// }


// version2
int main(int argc, char* argv[], char* envp[]){
    if(argc > 2){
        printf("Only support one command line args\n");
        exit(1);
    }
    if(argc == 1) printf("Directories in search path:\n");

    // 解析环境变量名 MYPATH 或 PATH 对应的路径字符串
    const char* Paths = searchPath(envp);
    int maxBuf = strlen(Paths)* sizeof(char);
    char* buf = malloc(maxBuf);

    char* searchBin = argc == 1 ? NULL : argv[1];
    bool exactSearch = searchBin == NULL ? false : startsWith(searchBin, "+");
    if (exactSearch) searchBin += 1;
    bool notFind = true;

    // 遍历每个路径
    while (scan_token(&Paths, ":", buf, maxBuf)){
        if(searchBin == NULL) printf("%s\n", buf); 
        else{
            DIR* dp = opendir(buf);
            if(dp == NULL) continue;
            struct dirent* entry;
            while((entry = readdir(dp)) != NULL){
                char* subStr = strstr(entry->d_name, searchBin);
                if(!exactSearch && subStr == entry->d_name && strlen(subStr) == strlen(searchBin)){
                    printf("%s/%s\n", buf, entry->d_name);
                    return 0;
                }
                if(exactSearch && subStr != NULL){
                    notFind = false;
                    printf("%s/%s\n", buf, entry->d_name);
                }
            }
            closedir(dp);
        }
    }
    if(notFind && !searchPath) printf("\n");
    free(buf);
    return 0;

}


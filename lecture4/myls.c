#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <dirent.h>
#include <stdbool.h>
#include <assert.h>

/*
myls
1. 传递0个或多个路径作为参数， 列出每个路径下的内容
2. myls 只支持目录作为路径， 如果是文件或不存在的路径，则打印错误信息，并忽略
3. myls 打印每个目录下的内容在每一行
4. myls 忽略 .开头的entry，除非加 -a
5. -z 表示先打印目录，再打印是非目录的文件
*/
#define N 4
int* parseArgs(int argc, char** ptr, bool* aPtr, bool* zPtr){
    // first args is filename
    int len = N;
    int countPaths = 0;
    int* arrays = malloc(len*sizeof(int));
    assert(arrays != NULL);
    arrays[0] = 0;
    for(int i = 1; i < argc; i++){
        char* tmp = ptr[i];
        if(*tmp == '-'){
            char c = *(tmp + 1);
            switch(c){
                case 'a':
                    *aPtr = true;
                    break;
                case 'z':
                    *zPtr = true;
                    break;
                default:
                    printf("-%c is not supported!!!", c);
            }
        }
        else{
            // 检查其余字符串是否是有效路径放在后续处理
            if(countPaths + 1 >= len - 1){
                len *= 2;
                arrays = realloc(arrays, len*sizeof(int));
                assert(arrays != NULL);
            }
            arrays[countPaths + 1] = i;
            countPaths++;
        }
    }
    arrays[0] = countPaths;
}

void parsePaths(int** indexArg, char** Paths, bool aFlag, bool zFlag){
    int count = (*indexArg)[0]; // the numbers of paths
    struct dirent **namelist;
    char* curDir = ".";
    bool defaultMode = false;
    if(count == 0){
        Paths = &curDir;
        count = 1;
        defaultMode = true;
    }
    const char* string;
    for(int i = 1; i < count + 1; i++){
        if(defaultMode)
            string = Paths[0];
        else{
            int index = (*indexArg)[i];
            string = Paths[index];
        }
        int n = scandir(string, &namelist, NULL, alphasort);
        if(n == -1) {
            printf("%s no exits!!! ignore !!!\n", string);
            continue;
        }
        printf("%s:\n", string);
        int *otherIndex = malloc(n * sizeof(int));
        assert(otherIndex);
        int otherI = 0;
        for(int j = 0; j < n; j++){
            if(!aFlag && namelist[j]->d_name[0] == '.') continue;
            if(namelist[j]->d_type == DT_DIR)
                printf("%s_\n", namelist[j]->d_name);
            else{
                if(zFlag){
                    otherIndex[otherI++] = j;
                    continue;
                }
            printf("%s\n", namelist[j]->d_name);
            }
        }
        for(int j = 0; j < otherI; j++){
            printf("%s\n", namelist[otherIndex[j]]->d_name);
        }
        free(otherIndex);
        otherIndex = NULL;
        for(int j = 0; j < n; j++){
            free(namelist[j]);
        }
        free(namelist);
        printf("\n");
    }
}

int main(int argc, char* argv[]){
    bool aFlag = false, zFlag = false;
    int* index;
    index = parseArgs(argc, argv, &aFlag, &zFlag);
    // printf("%d, %d\n", aFlag, zFlag);
    parsePaths(&index, argv, aFlag, zFlag);
    free(index);
    return 0;
}
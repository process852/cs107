#include <dirent.h>
#include <stdio.h>

void list_filenames(const char* dirpath){
    DIR* dp = opendir(dirpath);
    if(dp == NULL) return;
    struct dirent* entry;
    while((entry = readdir(dp)) != NULL){
        printf("%s\n", entry->d_name);
    }
    closedir(dp);
}

int main(){
    list_filenames("/");
    return 0;
}
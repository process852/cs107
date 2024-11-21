#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[], char* envp[]){
    int i = 0;
    char* strPoint = NULL;
    while((strPoint = envp[i]) != NULL){
        printf("%s\n", strPoint);
        i++;
    }
    return 0;
}
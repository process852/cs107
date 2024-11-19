#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "scan_token.h"


int main(){
    const char *input = "super-duper-awesome-magnificent"; 
    char buf[10]; 
    const char *remaining = input; 

    while (scan_token(&remaining, "-", buf, sizeof(buf))) { 
        printf("Next token: %s\n", buf); 
    }
    return 0;
}
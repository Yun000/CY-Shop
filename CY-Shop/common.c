#include "common.h"

#include <stdio.h>
#include <ctype.h>

void* common_safe_malloc(size_t size)
{
    void* p = malloc(size);
    if (p == NULL)
    {
        printf("Memory allocation error\n");
        exit(0);
    }
    return p;
}

void common_free(void* p){
    free(p);
}

char* common_stringToLowerCase(char* str)
{
    for(int i = 0; str[i] != '\0'; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

char* common_stringToUpperCase(char* str)
{
    for(int i = 0; str[i] != '\0'; i++){
        str[i] = toupper(str[i]);
    }
    return str;
}

int common_digits_only(char *str)
{
    for(int i = 0; str[i] != '\0'; i++){
        if (isdigit(str[i]) == 0)
            return 0;
    }
    return 1;
}
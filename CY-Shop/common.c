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

int common_digits_only(char *str)
{
    for(int i = 0; str[i] != '\0'; i++){
        // Si le caractère n'est pas un nombre, on retourne 0
        if (isdigit(str[i]) == 0)
            return 0;
    }
    // Si tous les caractères sont des nombres, on retourne 1
    return 1;
}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
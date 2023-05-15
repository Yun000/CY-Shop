#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLEAR_SCREEN "\e[1;1H\e[2J"
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

void* common_safe_malloc(size_t size);

void common_free(void* p);

// Verifie si une chaine de caractère contient seulement des nombres
int common_digits_only(char *str);

size_t getline(char **lineptr, size_t *n, FILE *stream)

#endif
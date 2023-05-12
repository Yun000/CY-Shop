#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

void* common_safe_malloc(size_t size);

void common_free(void* p);

// Convert all character in string to lower case
char* common_stringToLowerCase(char* str);

// Convert all character in string to upper case
char* common_stringToUpperCase(char* str);

// Check if a string only contains number
int common_digits_only(char *str);

#endif
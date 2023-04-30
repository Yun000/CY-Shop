#ifndef PRODUCT_H
#define PRODUCT_H
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


enum SIZE { SMALL, MEDIUM, BIG };

typedef struct {
    char* name;
    int referenceNumber;
    int stock;
    int price;
    enum SIZE size;
} Product;







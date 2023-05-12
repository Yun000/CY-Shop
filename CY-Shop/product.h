#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>

enum SIZE { SIZE_NONE = -1, SMALL = 0, MEDIUM, BIG };

typedef struct {
    char* name;
    int referenceNumber;
    int quantity;
    float price;
    enum SIZE size;
} Product;

// Constructor for product
Product* product_new(char* name, int referenceNumber, int quantity, float price, enum SIZE size);

// Return a enum SIZE from a string
enum SIZE product_get_size_from_string(char* str);

// Get a product in the file by its name
Product* product_get_by_name(char* name);

// Get a product in the file by its reference number
Product* product_get_by_reference_number(int referenceNumber);

// Destructor for product
void product_free(Product* product);

#endif
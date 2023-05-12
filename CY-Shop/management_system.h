#ifndef MANAGEMENT_SYSTEM_H
#define MANAGEMENT_SYSTEM_H

#include "product.h"

void management_system_menu();

// Return the stock of a product by reference number
int management_system_get_product_stock(int referenceNumber);

// Increase the product stock of a product
void management_system_increase_product_stock(Product* product, int add);

#endif
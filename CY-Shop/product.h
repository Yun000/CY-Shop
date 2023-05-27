#ifndef PRODUCT_H
#define PRODUCT_H

#include "common.h"

enum SIZE { SIZE_NONE = -1, SMALL = 1, MEDIUM = 2, BIG = 4};

typedef struct {
    char* name;
    int referenceNumber;
    int quantity;
    float price;
    enum SIZE size;
} Product;

// Constructeur pour le produit
Product* product_new(char* name, int referenceNumber, int quantity, float price, enum SIZE size);

// Retourne les produits dans un fichier
Product** product_load_from_file(char* filePath, int productsCount);

// Retourne un produit selon une ligne
Product* product_load_from_line(FILE* file);

// Retourne la taille d'un produit selon le fichier
enum SIZE product_get_size_from_string(char* str);

// Retourne une chaine de caractère de la taille d'un produit
char* product_get_string_from_size(enum SIZE size);

// Affiche le nom, la quantité et le prix du produit
void product_display(Product* product);

// Destructeur pour le produit
void product_free(Product* product);

#endif
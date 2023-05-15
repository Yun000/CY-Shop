#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>

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

// Retourne la taille d'un produit selon le fichier
enum SIZE product_get_size_from_string(char* str);

// Retourne la chaine de caractère de la taille d'un produit
char* product_get_string_from_size(enum SIZE size);

// Affiche le nom, la quantité et le prix du produit
void product_display(Product* product);

// Affiche le nom, la quantité et le prix des produits dans le fichier à partir de la ligne donnée
void product_file_print_from_line(int startLine);

void product_file_print_out_of_stock();

void product_file_write_to_line(Product* product, int lineNumber);

// Retourne un produit dans le fichier par son nom ou son nombre de référence
Product* product_get(char* name);

// Retourne le numéro de la ligne d'un produit dans le fichier par son nom ou son nombre de référence
int product_search(char* name);

// Destructeur pour le produit
void product_free(Product* product);

#endif
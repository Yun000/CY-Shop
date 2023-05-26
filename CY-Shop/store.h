#ifndef STORE_H
#define STORE_H

#include "product.h"
#include "customer.h"
#include "common.h"

#define STORE_CAPACITY_SIZE 1024

typedef struct {
    Product** products;
    Customer** customers;
    int customersCount;
    int productsCount;
    int currentCapacity;
} Store;

// Constructeur pour le magasin
Store* store_new(char* customersFilePath, char* productsFilePath);

// Met a jour la capacité du magasin
void store_update_remaining_capacity(Store* store, Product* product);

// Returne la capacité restante du magasin
int store_get_remaining_capacity(Store* store);

// Recherche un client par son nom et prénom
Customer* store_customer_search(Store* store, char* name, char* firstName);

// Affiche les trois derniers achats du client
void store_customer_show_purchases(Store* store, Customer* customer);

// Recherche un produit dans le magasin par son nom ou son numéro de référence
Product* store_product_search(Store* store, char* name);

// Affiche tous les produits
void store_product_show_all(Store* store);

// Affiche les produits selon une catégorie
void store_product_show_category(Store* store, char* category);

// Affiche tous les produits dont le stock est le plus bas
void store_product_show_out_stock(Store* store);

// Retourne la quantité d'un produit
int store_product_get_stock(Store* store, Product* product);

// Augmente la quantité d'un produit
void store_product_increase_stock(Store* store, Product* product, int add);

// Sauvegarde les produits dans le fichier
void store_save_products(Store* store, char* filePath);

// Destructeur pour le magasin
void store_free(Store* store);

#endif
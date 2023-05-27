#ifndef STORE_H
#define STORE_H

#include "product.h"
#include "customer.h"
#include "common.h"

// Capacité totale du magasin
#define STORE_CAPACITY_SIZE 1024

typedef struct {
    Product** products; // Les produits du magasin
    Customer** customers; // Les clients du magasin
    int customersCount; // Le nombre de client enregistré dans le magasin
    int productsCount; // Le nombre de produit différent enregistré dans le magasin
    int currentCapacity; // Capacité actuelle du magasin
} Store;

// Constructeur pour le magasin
// customersFilePath : Chemin du fichier pour les clients
// productsFilePath : Chemin du fichier pour les produits
Store* store_new(char* customersFilePath, char* productsFilePath);

// Met a jour la capacité actuelle du magasin selon le nouveau stock d´un produit
// product : Produit que l'on met dans le magasin
void store_update_remaining_capacity(Store* store, Product* product);

// Returne la capacité restante du magasin
int store_get_remaining_capacity(Store* store);

// Recherche un client par son nom et prénom
// name : Nom du client
// firstName : Prénom du client
Customer* store_customer_search(Store* store, char* name, char* firstName);

// Affiche les trois derniers achats du client
// customer : Client dont on veut afficher ses 3 derniers achats
void store_customer_show_purchases(Store* store, Customer* customer);

// Recherche un produit dans le magasin par son nom ou son numéro de référence
// name : Nom ou numéro de référence du produit
Product* store_product_search(Store* store, char* name);

// Affiche tous les produits
void store_product_show_all(Store* store);

// Affiche les produits selon une catégorie
void store_product_show_category(Store* store, char* category);

// Affiche tous les produits dont le stock est le plus bas
void store_product_show_out_stock(Store* store);

// Retourne la quantité d'un produit
// produit : Produit dont on veut connaitre le stock
int store_product_get_stock(Store* store, Product* product);

// Augmente la quantité d'un produit
// add : Quantité qu'on veut rajouter
void store_product_increase_stock(Store* store, Product* product, int add);

// Diminuer la quantité d'un produit
// dele : Quantité qu'on veut enlever
void store_product_decrease_stock(Store* store, Product* product, int dele);

// Sauvegarde les produits dans le fichier
// filePath : Chemin du fichier des produits
void store_save_products(Store* store, char* filePath);

// Destructeur pour le magasin
void store_free(Store* store);

#endif

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>

typedef struct {
    char* name;
    char* firstName;
    int purchases[3];
} Customer;

// Constructeur de la structure client
Customer* customer_new(char* name, char* firstName);

// Créer un fichier pour le client
void customer_write_to_file(char* name, char* firstName);

// Lis et retourne les informations qui sont stockées dans un fichier pour le client
Customer* customer_get_from_file(FILE* clientFile);

// Supprime le fichier du client
void customer_delete_file(char* name, char* firstName);

// Retourne un client qui se trouve dans le dossier "customers"
Customer* customer_get_from_directory(char* name, char* firstName);

// Recherche un client par son nom et prénom
Customer* customer_search(char* name, char* firstName);

// Affiche les trois derniers achats du client
void customer_show_purchases(Customer* customer);

// Destucteur de la structure client
void customer_free(Customer* customer);

#endif
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "common.h"

typedef struct {
    char* name;
    char* firstName;
    int purchases[3];
} Customer;

// Constructeur de la structure client
Customer* customer_new(char* name, char* firstName);

// Charger une ancienne structure client
Customer* customer_old(char* name, char* firstName,int prod1,int prod2,int prod3);

// Charge tous les fichier client qui se trouve dans un dossier
Customer** customer_load_all_from_directory(char* customersDirectoryPath, int customersCount);

// Charge le fichier client
Customer* customer_load_from_file_path(char* filePath);

// Créer un fichier pour le client
void customer_write_to_file(char* directoryPath, Customer* customer);

// Lis et retourne les informations qui sont stockées dans un fichier pour le client
Customer* customer_get_from_file(FILE* clientFile);

// Supprime le fichier du client dans un dossier
void customer_delete_file(char* directoryPath, Customer* customer);

#endif
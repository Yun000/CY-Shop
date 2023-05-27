#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "common.h"

typedef struct {
    char* name;
    char* firstName;
    int purchases[3];
} Customer;

// Constructeur de la structure client
// Name : Nom du client
// firstName : Prénom du client
Customer* customer_new(char* name, char* firstName);

// Charger une ancienne structure client
// Name : Nom du client
// firstName : Prénom du client
Customer* customer_old(char* name, char* firstName,int prod1,int prod2,int prod3);

// Charge tous les fichier client qui se trouve dans un dossier
// customersDirectoryPath : Chemin du dossier des clients
// customersCount : Nombre de client qui se trouve dans le dossier, utilisé pour allouer la mémoire
Customer** customer_load_all_from_directory(char* customersDirectoryPath, int customersCount);

// Charge le fichier client
// filePath : Chemin du fichier d'un client
Customer* customer_load_from_file_path(char* filePath);

// Créer un fichier pour le client
// directoryPath : Chemin du dossier des clients
// customer : Client que l'on veut rajouter dans le dossier
void customer_write_to_file(char* directoryPath, Customer* customer);

// Lis et retourne les informations qui sont stockées dans un fichier pour le client
// clientFile : Fichier du client que l'on va lire
Customer* customer_get_from_file(FILE* clientFile);

// Supprime le fichier du client dans un dossier
// directoryPath : Chemin du dossier des clients
// customer : Client que l'on enlever du dossier
void customer_delete_file(char* directoryPath, Customer* customer);

#endif

#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>

#include <stdlib.h>

// Pour les sleep
#include <unistd.h>

// Manipulation de dossier
#include <dirent.h>

// Faire des comparaison chaines de caracteres
#include <string.h>

// Pour afficher les couleurs dans le terminale
#define CLEAR_SCREEN    "\e[1;1H\e[2J"
#define RED             "\x1B[31m"
#define YELLOW          "\x1B[33m"
#define RESET           "\x1B[0m"

// Alloue en mémoire en sécurité une structure 
// size : Taille de la structure
void* common_safe_malloc(size_t size);

// Ouvre en sécurité un fichier
// filePath : Chemin du fichier
// mode : Le mode que l'on veut utilisé pour le fichier
FILE* common_file_safe_open(char* filePath, char* mode);

// Retourne le nombre de ligne dans un fichier
// filePath : Chemin du fichier
// mode : Le mode que l'on veut utilisé pour le fichier
int common_file_get_line_count(char* filePath, char* mode);

// Ouvre en sécurité un dossier
// directoryPath : Chemin du dossier
DIR* common_directory_safe_open(char* directoryPath);

// Returne le nombre de fichier dans un dossier
// directoryPath : Chemin du dossier
int common_directory_get_file_count(char* directoryPath);

#endif

#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>

#include <stdlib.h>

// Pour les sleep
#include <unistd.h>

// Ouvrir un dossier
#include <dirent.h>

// Faire des comparaison
#include <string.h>


#define CLEAR_SCREEN    "\e[1;1H\e[2J"
#define RED             "\x1B[31m"
#define YELLOW          "\x1B[33m"
#define RESET           "\x1B[0m"

// Alloue en mémoire en sécurité une structure 
void* common_safe_malloc(size_t size);

// Ouvre en sécurité un fichier
FILE* common_file_safe_open(char* filePath, char* mode);

// Retourne le nombre de ligne dans un fichier
int common_file_get_line_count(char* filePath, char* mode);

// Ouvre en sécurité un dossier
DIR* common_directory_safe_open(char* directoryPath);

// Returne le nombre de fichier dans un dossier
int common_directory_get_file_count(char* directoryPath);

#endif
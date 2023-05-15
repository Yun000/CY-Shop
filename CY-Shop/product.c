#include "product.h"

#include <stdlib.h>
#include <string.h>
#include "common.h"

Product* product_new(char* name, int referenceNumber, int quantity, float price, enum SIZE size){
	Product* product = common_safe_malloc(sizeof(Product));
	product->name = name;
	product->referenceNumber = referenceNumber;
	product->quantity = quantity;
	product->price = price;
	product->size = size;
	return product;
}

enum SIZE product_get_size_from_string(char* str)
{	
	if (!strcasecmp(str, "SMALL"))
		return SMALL;
	else if (!strcasecmp(str, "MEDIUM"))
		return MEDIUM;
	else if (!strcasecmp(str, "BIG"))
		return BIG;
		
	printf("Taille non reconnue !\n");
	return SIZE_NONE;
}

char* product_get_string_from_size(enum SIZE size)
{
	switch (size)
	{
		case SMALL:
			return "SMALL";
			break;
		
		case MEDIUM:
			return "MEDIUM";
			break;
		
		case BIG:
			return "BIG";
			break;
		
		default:
			break;
	}
	return "NONE";
}

void product_display(Product* product){
	if (product->quantity == 0)
		printf(RED);
	printf("%-30s %12.2f€ x%d", product->name, product->price, product->quantity);
	if (product->quantity == 0)
		printf(RESET);
	printf("\n");
}

void product_file_print_from_line(int startLine)
{
	FILE * productFile;
    char * line = NULL;
    size_t len = 0;
	
    productFile = fopen("products/products.txt", "r");
    if (productFile == NULL) {
		exit(1);
	}
        

	int lineNumber = 0; // Nombre de la ligne actuelle
    while (getline(&line, &len, productFile) != -1) 
	{
		if (startLine <= lineNumber)
		{
			int i = 0;

			char *ptr = strtok(line, ";"); // Séparateur qui permet de lire chaque mot de la ligne
			char* informations[5]; // Liste où on stocke les informations du produit

			while(ptr != NULL)
			{
				if (strcmp(ptr, "\n") != 0) // Ignorer "\n"
					informations[i++] = ptr; // Stocker l'information dans la liste
				ptr = strtok(NULL, ";"); // Passer au mot suivant
			}

			Product* product = product_new(informations[0], atoi(informations[1]), atoi(informations[2]), atof(informations[3]), product_get_size_from_string(informations[4]));
			product_display(product);
			common_free(product);
		}
		lineNumber++;
    }

    fclose(productFile);
    if (line){
		free(line);
	}
}

void product_file_print_out_of_stock()
{
	FILE * productFile;
    char * line = NULL;
    size_t len = 0;
	Product* productLowestStocks[5];

    productFile = fopen("products/products.txt", "r");
    if (productFile == NULL) {
		exit(1);
	}
        

    while (getline(&line, &len, productFile) != -1) 
	{
		int i = 0;

		char *ptr = strtok(line, ";"); // Séparateur qui permet de lire chaque mot de la ligne
		char* informations[5]; // Liste où on stocke les informations du produit

		while(ptr != NULL)
		{
			if (strcmp(ptr, "\n") != 0) // Ignorer "\n"
				informations[i++] = ptr; // Stocker l'information dans la liste
			ptr = strtok(NULL, ";"); // Passer au mot suivant
		}

		Product* product = product_new(informations[0], atoi(informations[1]), atoi(informations[2]), atof(informations[3]), product_get_size_from_string(informations[4]));
		if (product->quantity == 0)
			product_display(product);
		common_free(product);
    }

    fclose(productFile);
    if (line){
		free(line);
	}
}

void product_file_write_to_line(Product* product, int lineNumber)
{
	FILE *productFile, *productFileTemp;
    char * line = NULL;
    size_t len = 0;
	
    productFile = fopen("products/products.txt", "r+");
	productFileTemp = fopen("products/productsTemp.txt", "w");
    if (productFile == NULL || productFileTemp == NULL){
		exit(1);
	}
        
	int currentLineNumber = 1; // Nombre de la ligne actuelle
    while (getline(&line, &len, productFile) != -1) 
	{
		if (currentLineNumber == lineNumber)
		{
			fprintf(productFileTemp, "%s;%03d;%d;%.2f;%s;\n", product->name, product->referenceNumber, product->quantity, product->price, product_get_string_from_size(product->size));
		}
		else{
			fputs(line, productFileTemp);
		}
		currentLineNumber++;
    }

    fclose(productFile);
	fclose(productFileTemp);
    if (line){
		free(line);
	}

	remove("products/products.txt");
    rename("products/productsTemp.txt", "products/products.txt");
}

Product* product_get(char* name)
{
	// Verifie si l'argument correspond à un nombre de référence
	int isReferenceNumber = common_digits_only(name);

	Product* product = NULL;

	FILE * productFile;
    char * line = NULL;
    size_t len = 0;

    productFile = fopen("products/products.txt", "r");
    if (productFile == NULL)
        exit(1);

	// Regarder chaque ligne du ficher jusqu'à la fin
    while (getline(&line, &len, productFile) != -1) 
	{
		int i = 0;

		char *ptr = strtok(line, ";"); // Séparateur qui permet de lire chaque mot de la ligne
		char* informations[5]; // Liste où on stocke les informations du produit

		while(ptr != NULL)
		{
			if (strcmp(ptr, "\n") != 0) // Ignorer "\n"
				informations[i++] = ptr; // Stocker l'information dans la liste
			ptr = strtok(NULL, ";"); // Passer au mot suivant
		}

		// Si le nom correspond à celui que l'on a choisi, on arrete la boucle ( mais on ne retourne pas directement le produit car on veut fermer le fichier et libérer de la mémoire )
		if ((isReferenceNumber && atoi(informations[1]) == atoi(name)) || !strcasecmp(informations[0], name))
		{
			char * productName = strdup(informations[0]); // Allouer une nouvelle mémoire pour le nom du produit ( car free(line) enleve le nom de la mémoire )
			product = product_new(productName, atoi(informations[1]), atoi(informations[2]), atof(informations[3]), product_get_size_from_string(informations[4]));
			break;
		}
    }

    fclose(productFile);
    if (line){
		free(line);
	}

	if(isReferenceNumber && product == NULL)
		printf("Le produit n°%s n'a pas été trouvé !\n", name);
	else if(product == NULL)
		printf("\"%s\" n'a pas été trouvé !\n", name);

	return product;
}

int product_search(char* name)
{
	// Verifie si l'argument correspond à un nombre de référence
	int isReferenceNumber = common_digits_only(name);
	int productFound = 0;

	FILE * productFile;
    char * line = NULL;
    size_t len = 0;

    productFile = fopen("products/products.txt", "r");
    if (productFile == NULL){
		exit(1);
	}
        
	int currentLineNumber = 1; // Nombre de la ligne actuelle
	// Regarder chaque ligne du ficher jusqu'à la fin
    while (getline(&line, &len, productFile) != -1) 
	{
		int i = 0;

		char *ptr = strtok(line, ";"); // Séparateur qui permet de lire chaque mot de la ligne
		char* informations[5]; // Liste où on stocke les informations du produit

		while(ptr != NULL)
		{
			if (strcmp(ptr, "\n") != 0) // Ignorer "\n"
				informations[i++] = ptr; // Stocker l'information dans la liste
			ptr = strtok(NULL, ";"); // Passer au mot suivant
		}

		// Si le nom correspond à celui que l'on a choisi, on arrete la boucle ( mais on ne retourne pas directement la ligne car on veut fermer le fichier et libérer de la mémoire )
		if ((isReferenceNumber && atoi(informations[1]) == atoi(name)) || !strcasecmp(informations[0], name))
		{
			productFound = 1;
			break;
		}
		currentLineNumber++;
    }

    fclose(productFile);
    if (line){
		free(line);
	}

	if(isReferenceNumber && !productFound)
		printf("Le produit n°%s n'a pas été trouvé !\n", name);
	else if(!productFound)
		printf("\"%s\" n'a pas été trouvé !\n", name);

	return currentLineNumber;
}

void product_free(Product* product){
    free(product);
}
#include "product.h"


Product* product_new(char* name, int referenceNumber, int quantity, float price, enum SIZE size)
{
	Product* product = common_safe_malloc(sizeof(Product));
	product->name = name;
	product->referenceNumber = referenceNumber;
	product->quantity = quantity;
	product->price = price;
	product->size = size;
	return product;
}

Product** product_load_from_file(char* filePath, int productsCount)
{
	Product** products = common_safe_malloc(sizeof(Product*) * productsCount);

	FILE* productsFile = common_file_safe_open(filePath, "r");

	for (int i = 0; i < productsCount; i++)
    {
        products[i] = product_load_from_line(productsFile);
    }
    
    fclose(productsFile);

	return products;
}

Product* product_load_from_line(FILE* file)
{
    char * line = NULL;
    size_t len = 0;

    getline(&line, &len, file);
	int i = 0;

	char *ptr = strtok(line, ";"); // Séparateur qui permet de lire chaque mot de la ligne
	char* informations[5]; // Liste où on stocke les informations du produit

	while(ptr != NULL)
	{
		if (strcmp(ptr, "\n") != 0) // Ignorer "\n"
			informations[i++] = ptr; // Stocker l'information dans la liste
		ptr = strtok(NULL, ";"); // Passer au mot suivant
	}

	char * productName = strdup(informations[0]); // Allouer une nouvelle mémoire pour le nom du produit ( car free(line) enleve le nom de la mémoire )
	Product* product = product_new(productName, atoi(informations[1]), atoi(informations[2]), atof(informations[3]), product_get_size_from_string(informations[4]));

	if (line){
		free(line);
	}

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

void product_display(Product* product)
{
	if (product->quantity == 0)
		printf(RED);
	else if (product->quantity > 0 && product->quantity < 3)
		printf(YELLOW);
	printf("%-30s %12.2f€ x%d", product->name, product->price, product->quantity);
	printf(RESET);
	printf("\n");
}

void product_free(Product* product)
{
    free(product);
}
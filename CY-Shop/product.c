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
	enum SIZE size = SIZE_NONE;
	if (!strcmp(str, "SMALL"))
		size = SMALL;
	else if (!strcmp(str, "MEDIUM"))
		size = MEDIUM;
	else if (!strcmp(str, "BIG"))
		size = BIG;
	return size;
}

void product_display(){
	
}

Product* product_get_by_name(char* name)
{
	Product* product = NULL;

	FILE * productFile;
    char * line = NULL;
	int i = 0;
    size_t len = 0;

    productFile = fopen("products/products.txt", "r");
    if (productFile == NULL)
        exit(1);

    while (getline(&line, &len, productFile) != -1) 
	{
		char *ptr = strtok(line, ";");
		char* informations[5];

		while(ptr != NULL)
		{
			informations[i++] = ptr;
			ptr = strtok(NULL, ";");
		}

		if (!strcmp(informations[0], name))
		{
			product = product_new(informations[0], atoi(informations[1]), atoi(informations[2]), atof(informations[3]), product_get_size_from_string(informations[4]));
			break;
		}
    }

    fclose(productFile);
    if (line){
		free(line);
	}
        
	return product;
}

Product* product_get_by_reference_number(int referenceNumber)
{
	Product* product = NULL;

	FILE * productFile;
    char * line = NULL;
	int i = 0;
    size_t len = 0;

    productFile = fopen("products/products.txt", "r");
    if (productFile == NULL)
        exit(1);

    while (getline(&line, &len, productFile) != -1) 
	{
		char *ptr = strtok(line, ";");
		char* informations[5];

		while(ptr != NULL)
		{
			informations[i++] = ptr;
			ptr = strtok(NULL, ";");
		}

		if (atoi(informations[1]) == referenceNumber)
		{
			product = product_new(informations[0], atoi(informations[1]), atoi(informations[2]), atof(informations[3]), product_get_size_from_string(informations[4]));
			break;
		}
    }

    fclose(productFile);
    if (line){
		free(line);
	}
        
	return product;
}

void product_free(Product* product){
    free(product);
}
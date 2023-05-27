#include "store.h"


Store* store_new(char* customersDirectoryPath, char* productsFilePath)
{
    Store* store = common_safe_malloc(sizeof(Store));

    // Charger les clients
    store->customersCount = common_directory_get_file_count(customersDirectoryPath);

    store->customers = customer_load_all_from_directory(customersDirectoryPath, store->customersCount);
    
    // Charger les produits
    store->productsCount = common_file_get_line_count(productsFilePath, "r");

    store->products = product_load_from_file(productsFilePath, store->productsCount);
    
    // Avoir la quantité actuelle du magasin
    for (int i = 0; i < store->productsCount; i++)
    {
        store_update_remaining_capacity(store, store->products[i]);
    }
    
    return store;
}

void store_update_remaining_capacity(Store* store, Product* product)
{
    // Mettre à jour la quantité actuelle du magasin
    store->currentCapacity += product->quantity * product->size;
}

int store_get_remaining_capacity(Store* store)
{
    return STORE_CAPACITY_SIZE - store->currentCapacity;
}

Customer* store_customer_search(Store* store, char* name, char* firstName)
{
    for (int i = 0; i < store->customersCount; i++){
        Customer* customer = store->customers[i];
        if (!strcasecmp(customer->name, name) && !strcasecmp(customer->firstName, firstName)){
            return customer;
        }
    }
    return NULL;
}

void store_customer_show_purchases(Store* store, Customer* customer)
{
    for (int i = 0; i < 3; i++)
    {
        if (customer->purchases[i] != -1){
            printf("%s ",store->products[customer->purchases[i]-1]->name);
            }
    }
    printf("\n");    
}

Product* store_product_search(Store* store, char* name)
{
    for (int i = 0; i < store->productsCount; i++)
    {
        Product* product = store->products[i];
        if ((product->referenceNumber == atoi(name)) || !strcasecmp(product->name, name)){
            return product;
        }
    }
    return NULL;
}

void store_product_show_all(Store* store)
{
    for (int i = 0; i < store->productsCount; i++){
        product_display(store->products[i]);
    }
}

void store_product_show_out_stock(Store* store)
{
    // Liste temporaire
    Product* productLowestStocks[5] = {NULL, NULL, NULL, NULL, NULL};

    // On regarde chaque produit qui se trouve le fichier
    for (int i = 0; i < store->productsCount; i++)
    {
        // Passer si le produit à une stock égale à 0
        if (store->products[i]->quantity == 0){
            product_display(store->products[i]);
        }
        else{
            int max = -1; // Produit avec le plus grand stock dans la liste temporaire
            int maxIndex = -1; // Utilisé pour trouver la place du produit dans la liste qui à la plus grande quantité

            // Voir dans la liste temporaire qui à un stock plus grand
            for (int j = 0; j < 5; j++)
            {
                // Mettre le produit dans la liste temporaire s'il contient NULL
                if (productLowestStocks[j] == NULL){
                    productLowestStocks[j] = store->products[i];
                    break;
                }
                
                // Si on trouve un stock plus grand que celui stocké dans maxIndex, on replace la valeur
                if (max < productLowestStocks[j]->quantity){
                    max = productLowestStocks[j]->quantity; // On récupère le stock du produit
                    maxIndex = j; // On récupère l'index du produit avec le plus gros stock
                }
            }

            if(maxIndex == -1){
                continue;
            }
            
            // On compare le stock du produit avec celle de la liste temporaire
            if (productLowestStocks[maxIndex]->quantity > store->products[i]->quantity){                    
                productLowestStocks[maxIndex] = store->products[i];
            }
        }
    }

    // Afficher les produits avec le plus bas stock
    for (int i = 0; i < 5; i++){
        product_display(productLowestStocks[i]);
    }
}
       

int store_product_get_stock(Store* store, Product* product)
{
    return product->quantity;
}

void store_product_increase_stock(Store* store, Product* product, int add)
{
    if (product->size * add + store->currentCapacity > STORE_CAPACITY_SIZE){
        printf("Impossible d'augmenter le stock car celui-ci dépasse la capacité maximale du magasin !\n");
        sleep(2);
        return;
    }
    product->quantity += add;
    store->currentCapacity += product->size * add;
}

void store_product_decrease_stock(Store* store, Product* product, int dele)
{
    if (product->quantity < dele){
        printf("Impossible de diminuer le stock car celui-ci est trop bas!\n");
        sleep(2);
        return;
    }
    product->quantity -= dele;
    store->currentCapacity -= product->size * dele;
}

void store_save_products(Store* store, char* filePath)
{	
    FILE * productFile = common_file_safe_open(filePath, "w");

    for (int i = 0; i < store->productsCount; i++){
        fprintf(productFile, "%s;%03d;%d;%.2f;%s;\n", store->products[i]->name, store->products[i]->referenceNumber, store->products[i]->quantity, store->products[i]->price, product_get_string_from_size(store->products[i]->size));
    }

    fclose(productFile);
}

void store_free(Store* store)
{
    for (int i = 0; i < store->customersCount; i++){
        free(store->customers[i]);
    }

    for (int i = 0; i < store->productsCount; i++){
        free(store->products[i]);
    }

    free(store);
}

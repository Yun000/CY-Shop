#include "purchase_system.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "purchase_system.h"
#include "customer.h"
#include "product.h"
#include "common.h"

#include <string.h>

#include "unistd.h"

void purchase_system_menu()
{
    char name[256];
    char firstName[256];

    printf("Entrez votre nom :\n");
    scanf("%s", name);
    printf("Entrez votre prenom :\n");
    scanf("%s", firstName);

    Customer* customer = customer_get_from_directory(name, firstName);

    // A faire : Inscrisption du nouveau client si "customer == NULL"
    if (customer == NULL){
        printf("Compte non inscrit, création du compte\n");

        customer_write_to_file(name, firstName);

        customer = customer_new(name, firstName);
    }
    else
        printf("Identification réussie !\n");

    sleep(2);

    printf(CLEAR_SCREEN);

    // A faire : les trois derniers points du mode achat dans le pdf
    customer_show_purchases(customer);

    int option = -1;
    //int page = 0;
    
    char productName[256];
    float totalPrice = 0;
    int customerPurchase = -1;

    do{
        printf(CLEAR_SCREEN);

        printf("Votre prix total est de %.2f€\n", totalPrice);
        printf("Souhaitez-vous achetez un produit ?\n");
        printf("0 : Oui\n");
        printf("1 : Non\n");

        scanf("%d", &option);

        if (option < 0 || option > 1)
            printf("Option non valide\n");
        else if (option == 1)
            break;

        printf(CLEAR_SCREEN);

        Product* product = NULL;

        product_file_print_from_line(0);

        printf("Entrez le nom ou le nombre de référence du produit que vous voulez achetez :\n");
        scanf("%s", productName);

        // On récupère le produit que le client veut acheter dans le fichier 
        product = product_get(productName);
        
        if (product == NULL){
            printf(CLEAR_SCREEN);
            printf("%s n'a pas été trouver dans le fichier !\n", productName);
            sleep(2);
        }
        else if (product->quantity == 0)
        {
            printf(CLEAR_SCREEN);
            printf("%s n'est plus en stock !\n", productName);
            sleep(2);
        }
        else{
            // Mettre a jour l(historique des produits acheté par le client
            customerPurchase++;
            if (customerPurchase > 3)
                customerPurchase = 0;
            customer->purchases[customerPurchase] = product->referenceNumber;

            totalPrice += product->price;
            product->quantity--;
        }
        
        strcpy(productName, "");

    } while (option <= 0 || option > 1);
}
#include "purchase_system.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "purchase_system.h"
#include "customer.h"
#include "product.h"
#include "common.h"

#include <string.h>

void purchase_system_menu()
{
    // A faire : Demander au client s'il y a un compte ou pas au lieu de demander directement le nom et le prénom
    char name[256];
    char firstName[256];

    printf("Entrez votre nom :\n");
    scanf("%s", name);
    printf("Entrez votre prenom :\n");
    scanf("%s", firstName);

    Customer* customer = customer_get_from_directory(name, firstName);

    // A faire : Inscrisption du nouveau client si "customer == NULL"
    if (customer == NULL){
        customer_write_to_file(name, firstName);

        customer = customer_new(name, firstName);
    }

    // A faire : les trois derniers points du mode achat dans le pdf
    customer_show_purchases(customer);

    //product_get_by_name("NomDuProduit1");

    int option = -1;
    int page = 0;

    do{
        printf("Souhaitez-vous achetez un produit ?\n");
        printf("0 : Oui\n");
        printf("1 : Non\n");

        scanf("%d", &option);

        if (option < 0 || option > 1)
            printf("Option non valide\n");
        else if (option == 1)
            break;

        /*
        Afficher la liste des produits avec le prix et stock
        L'utilisateur achetera un produit en entrant le nom du produit ou le nombre de référence
        */

    } while (option <= 0 || option > 1);
}
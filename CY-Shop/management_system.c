#include "management_system.h"

#include <unistd.h>
#include "common.h"

void management_system_menu()
{
    int option = -1;
    int page = 0;
    
    char productName[256];

    do{
        printf(CLEAR_SCREEN);

        product_file_print_out_of_stock();
        printf("Que souhaitez vous faire ?\n");
        printf("0 : Savoir le stock d'un produit\n");
        printf("1 : Augmenter le stock d'un produit\n");
        printf("2 : Quitter le mode gestion\n");

        scanf("%d", &option);

        if (option < 0 || option > 1)
            printf("Option non valide\n");
        if (option == 2)
            break;

        printf(CLEAR_SCREEN);

        Product* product = NULL;

        product_file_print_from_line(0);

        printf("Entrez le nom ou le nombre de référence du produit que vous voulez achetez :\n");
        scanf("%s", productName);

        product = product_get(productName);

        if (product == NULL)
        {
            printf(CLEAR_SCREEN);
            printf("%s n'a pas été trouver dans le fichier !\n", productName);
            sleep(2);
        }
        else
        {
            switch (option)
            {
                case 0:
                    printf(CLEAR_SCREEN);
                    printf("Il y a %d %s en stock\n", management_system_get_product_stock(product), product->name);
                    sleep(2);
                    break;

                case 1:
                    int add = 0;

                    printf(CLEAR_SCREEN);
                    printf("Combien voulez vous ajouter ? :\n");
                    scanf("%d", &add);

                    management_system_increase_product_stock(product, add);
                    break;
                
                default:
                    break;
            }
        }

    } while (option <= 0 || option >= 1);
}

int management_system_get_product_stock(Product* product)
{
    return product->quantity;
}

void management_system_increase_product_stock(Product* product, int add)
{
    product->quantity += add; // On augmente la quantitée du produit
    int productLine = product_search(product->name); // On récupère le nombre de la ligne du produit dans le fichier
    product_file_write_to_line(product, productLine); // On met a jour le produit dans le fichier
}
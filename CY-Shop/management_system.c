#include "management_system.h"


void management_system_menu(Store* store)
{
    int option;
    int add;
    int del;
    char productName[256];

    do{
        printf(CLEAR_SCREEN);

        store_product_show_out_stock(store);
        sleep(2);
        printf("Capacité de stockage restante : %d \n", store_get_remaining_capacity(store));
        sleep(2);
        printf("Que souhaitez vous faire ?\n0 : Savoir le stock d'un produit\n1 : Augmenter le stock d'un produit\n2 : Diminuer le stock d'un produit\n3 : Quitter\n");

        do {
        scanf("%d", &option);
        } while(option < 0 || option > 3);

        if (option == 3)
            break;

        sleep(2);
        printf(CLEAR_SCREEN);

        Product* product = NULL;

        store_product_show_all(store);
        if(option == 1){
            printf("Entrez le nom ou le numero de référence du produit dont vous souhaitez augmenter le stock :\n");
            scanf("%s", productName);
            }
        else if(option == 2){
            printf("Entrez le nom ou le numero de référence du produit dont vous souhaitez diminuer le stock :\n");
            scanf("%s", productName);
        }
        else{
        printf("Entrez le nom ou le numero de référence du produit dont vous souhaitez connaitre le stock :\n");
        scanf("%s", productName);
        }

        product = store_product_search(store, productName);
        sleep(2);
        // Si le produit n'a pas été trouver dans le fichier
        if (product == NULL)
        {
            printf(CLEAR_SCREEN);
            printf("%s n'a pas été trouver dans le magasin !\n", productName);
            sleep(2);
        }
        else
        {
            switch (option)
            {
                // Si l'utilisateur veut savoir le stock d'un produit
                case 0:
                    printf(CLEAR_SCREEN);
                    sleep(1);
                    if(store_product_get_stock(store, product)<=1){
                    printf("Il reste %d exemplaire du produit %s en stock.\n",store_product_get_stock(store, product),productName);}
                    else{
                        printf("Il reste %d exemplaires du produit %s en stock.\n",store_product_get_stock(store, product),productName);
                    }
                    sleep(2);
                    sleep(1);
                    break;

                // Si l'utilisateur veut ajouter en stock un produit
                case 1:
                    printf(CLEAR_SCREEN);
                    printf("Le produit est de taille %s\nCombien voulez vous en ajouter ? : ", product_get_string_from_size(product->size));
                        do {
                        scanf("%d", &add);
                        } while(add <= 0);

                    store_product_increase_stock(store, product, add);
                    store_save_products(store, "products/products.txt");
                    sleep(1);
                    break;
                // Si l'utilisateur veut diminuer en stock un produit
                case 2 :
                    printf(CLEAR_SCREEN);
                    printf("Le produit est de taille %s\nCombien voulez vous en enlever ? : ", product_get_string_from_size(product->size));
                        do {
                        scanf("%d", &del);
                        } while(del > product->quantity);
                    store_product_decrease_stock(store, product, del);
                    store_save_products(store, "products/products.txt");
                    sleep(1);
                    break;
                default:
                    break;
            }
        }

    } while (option <= 0 || option >= 2);

}
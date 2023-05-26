#include "management_system.h"


void management_system_menu(Store* store)
{
    int option;
    int add;
    int dele;
    char productName[256];
    int choice = 1;
    while(choice){
        printf(CLEAR_SCREEN);
        store_product_show_out_stock(store);
        sleep(2);
        printf("\nCapacité de stockage restante : %d \n", store_get_remaining_capacity(store));
        sleep(1);
        printf("========================================\n");
        printf("Que souhaitez vous faire ?\n0 : Savoir le stock d'un produit\n1 : Augmenter le stock d'un produit\n2 : Diminuer le stock d'un produit\n3 : Ajouter un prduit\n4 : Quitter\n");

        do{
        scanf("%d", &option);
        } while(option < 0 || option > 4);

        sleep(2);
        printf(CLEAR_SCREEN);

        Product* product = NULL;

        switch (option) 
        {

            // Si l'utilisateur veut savoir le stock d'un produit

            case 0:
                    
                store_product_show_all(store);
                printf("Entrez le nom ou le numero de référence du produit dont vous souhaitez connaitre le stock :\n");
                scanf("%s", productName);
                product = store_product_search(store, productName);
                sleep(2);

                    // Si le produit n'a pas été trouver dans le fichier
                    if (product == NULL)
                    {
                        printf(CLEAR_SCREEN);
                        printf("%s n'a pas été trouver dans le magasin !\n", productName);
                        sleep(2);
                    }
                printf(CLEAR_SCREEN);
                sleep(1);
                if(store_product_get_stock(store, product)<=1)
                {
                    printf("Il reste %d exemplaire du produit %s en stock.\n",store_product_get_stock(store, product),productName);
                }
                    else
                    {
                        printf("Il reste %d exemplaires du produit %s en stock.\n",store_product_get_stock(store, product),productName);
                    }
                sleep(2);
                sleep(1);
                break;


            // Si l'utilisateur veut ajouter en stock un produit

            case 1:

                store_product_show_all(store);
                printf("Entrez le nom ou le numero de référence du produit dont vous souhaitez augmenter le stock :\n");
                scanf("%s", productName);
                product = store_product_search(store, productName);
                sleep(2);

                    // Si le produit n'a pas été trouver dans le fichier
                    if (product == NULL)
                    {
                        printf(CLEAR_SCREEN);
                        printf("%s n'a pas été trouver dans le magasin !\n", productName);
                        sleep(2);
                    }
                printf(CLEAR_SCREEN);
                printf("Le produit est de taille %s\nCombien voulez vous en ajouter ? : ", product_get_string_from_size(product->size));
                    do{
                    scanf("%d", &add);
                    } while(add <= 0);

                store_product_increase_stock(store, product, add);
                store_save_products(store, "products/products.txt");
                sleep(1);
                break;


            // Si l'utilisateur veut diminuer en stock un produit

            case 2 :

                store_product_show_all(store);
                printf("Entrez le nom ou le numero de référence du produit dont vous souhaitez diminuer le stock :\n");
                scanf("%s", productName);
                product = store_product_search(store, productName);
                sleep(2);

                    // Si le produit n'a pas été trouver dans le fichier
                    if (product == NULL)
                    {
                        printf(CLEAR_SCREEN);
                        printf("%s n'a pas été trouver dans le magasin !\n", productName);
                        sleep(2);
                    }
                printf(CLEAR_SCREEN);
                printf("Le produit est de taille %s\nCombien voulez vous en enlever ? : ", product_get_string_from_size(product->size));
                    do{
                    scanf("%d", &dele);
                    } while(dele > product->quantity);

                store_product_decrease_stock(store, product, dele);
                store_save_products(store, "products/products.txt");
                sleep(1);
                break;
                

            // Si L'utilisateur veut ajouter un produit

            /*case 3 :
                
                printf("Vous allez ajouter un nouveau produit\nQuel est le nom de ce produit?\n");
                scanf("%s",&productname);
                if(store_product_search(Store, productName)!=NULL){
                    printf("Le produit est deja disponble.\n");
                }
                else{
                    product->name = productName;
                    product->referenceNumber = common_file_get_line_count("./products/product.txt","r")+1;
                    product->quantity = 0;
                    printf("Combien coute le produit %s à l'unite : ",productName);
                    do{
                    scanf("%f",&product->price);
                    } while(product->price < 0);
                    printf("Quel est la taille du produit %s (1 pour SMALL, 2 pour MEDIUM, 4 pour BIG) : ");
                    do{
                    scanf("%d",&product->size);
                    } (while(product->size = 1 || product->size = 2 || product->size = 4));
                }
                break;*/

            // Quitter
            default :
                    choice = 0;
                    printf("\n\nMerci\n\n");
                    break;
        }
    }
}
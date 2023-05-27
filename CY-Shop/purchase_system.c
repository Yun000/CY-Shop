#include "purchase_system.h"


Customer* purchase_system_login(Store* store)
{
    char name[256];
    char firstName[256];

    printf("========================================\nEntrez votre nom :\n");
    scanf("%s", name);
    printf("Entrez votre prenom :\n");
    scanf("%s", firstName);

    Customer* customer = store_customer_search(store, name, firstName);

    if (customer == NULL){
        printf("Compte non inscrit, création du compte\n========================================\n");
        sleep(2);
        customer = customer_new(name, firstName);
        customer_write_to_file("customers/", customer);
    }
    else{
        printf("Identification réussie !\n========================================\n");
        sleep(2);
    }

    sleep(1);
    purchase_system_purchase(store,customer);    
    sleep(1);

    return customer;
}

void purchase_system_purchase(Store* store, Customer* customer)
{
    int option;
    char productName[256];
    float totalPrice = 0;
    int customerPurchase = 0;
    int choice = 1;

    while(choice){
        printf(CLEAR_SCREEN);
        store_customer_show_purchases(store,customer);
        printf("Votre prix total est de %.2f€\n0 : Souhaitez-vous achetez un produit ?\n1 : Se désinscrire\n2 : Quitter\n", totalPrice);
        
        do{
        scanf("%d", &option);
        } while(option < 0 || option > 2);

        switch (option)
        {

            //Le client veut acheter un produit

            case 0 :  

                printf(CLEAR_SCREEN);
                Product* product = NULL;
                store_product_show_all(store);
                printf("Entrez le nom ou le numero de référence du produit que vous voulez achetez :\n");
                scanf("%s", productName);

                    // On récupère le produit que le client veut acheter dans le fichier
                    product = store_product_search(store, productName);

                    // Si le produit n'a pas été trouver dans le fichier
                    if (product == NULL)
                    {
                    printf(CLEAR_SCREEN);
                    printf("%s n'a pas été trouver dans le magasin !\n", productName);
                    sleep(2);
                    }

                    // Si le produit n'est plus en stock
                    else if (product->quantity == 0)
                    {
                        printf(CLEAR_SCREEN);
                        int confirmation;
                        int joke;
                        printf("%s n'est plus en stock !\n", productName);
                        sleep(2);

                        // Le client peut se désinscrire
                        printf("Souhaitez-vous vous desincrire du magasin ?\n0 : Oui\n1 : Non\n");
                            do{
                            scanf("%d", &joke);
                            } while (joke < 0 || joke > 1);
                        if (joke == 1){
                            break;
                        }

                        else 
                        {
                            sleep(3);
                            printf(CLEAR_SCREEN);
                            printf("Erreur d'affichage, veuillez verifier votre connexion internet et reessayer\n");
                            sleep(3);
                            printf("C'etait une blague,\nEtes-vous sûr de vouloir vous desincrire du magasin ?\n0 : Oui\n1 : Non\n");
                            do{
                                scanf("%d", &confirmation);
                            } while (confirmation < 0 || confirmation > 1);

                            if (confirmation == 0)
                            {
                                customer_delete_file("customers/", customer);
                            }
                            break;
                        }
                    }

                
                    // Mettre a jour l'historique des produits acheté par le client
                    else{ 
                        customerPurchase++;
                        customer->purchases[0] = customer->purchases[1];
                        customer->purchases[1] = customer->purchases[2];
                        customer->purchases[2] = product->referenceNumber;
                        totalPrice += product->price;
                        product->quantity--;
                        store_save_products(store, "products/products.txt");
                        customer_write_to_file("customers/", customer);
                        strcpy(productName, "");
                    }
            
            // Le client souhaite se désinscrire

            case 1 :
                int confirmation;
                int joke;
                printf("Souhaitez-vous vous desincrire du magasin ?\n0 : Oui\n1 : Non\n");
                            do{
                            scanf("%d", &joke);
                            } while (joke < 0 || joke > 1);
                        if (joke == 1){
                            break;
                        }
                printf("Etes-vous sûr de vouloir vous desincrire du magasin ?\n0 : Oui\n1 : Non\n");
                            do{
                                scanf("%d", &confirmation);
                            } while (confirmation < 0 || confirmation > 1);

                            if (confirmation == 0)
                            {
                                customer_delete_file("customers/", customer);
                                choice = 0;
                                break;
                            }
                            

            // Quitter mode achat

            default :

                choice = 0;
                printf("\n\nMerci pour vos achats, à bientôt.\n\n");
                sleep(2);
                break;

        }
    }
}
#include "customer.h"


Customer* customer_new(char* name, char* firstName)
{
	Customer* customer = common_safe_malloc(sizeof(Customer));
	customer->name = name;
    customer->firstName = firstName;
    for(int i = 0; i < 3; i++){
        customer->purchases[i] = -1;
    }
	return customer;
}

Customer* customer_old(char* name, char* firstName,int prod1,int prod2,int prod3)
{
	Customer* customer = common_safe_malloc(sizeof(Customer));
	customer->name = name;
    customer->firstName = firstName;
    customer->purchases[0] = prod1;
    customer->purchases[1] = prod2;
    customer->purchases[2] = prod3;
	return customer;
}

Customer** customer_load_all_from_directory(char* customersDirectoryPath, int customersCount)
{
	Customer** customers = common_safe_malloc(sizeof(Customer*) * customersCount);

    // Ouvrir tous les fichiers client dans le répertoire "customers"
    DIR* directory = common_directory_safe_open(customersDirectoryPath);;
    struct dirent *ent;
    char filename[512];

    int index = 0;
    while ((ent = readdir(directory)) != NULL) 
    {
        if (!strcmp (ent->d_name, ".") || !strcmp (ent->d_name, ".."))
            continue;

        // Ajouter le nom du répertoire (customers) à la fiche client
        strcpy(filename, "customers/");
        strcat(filename, ent->d_name);

        customers[index] = customer_load_from_file_path(filename);

        index++;
    }

    closedir(directory);

    return customers;
}

Customer* customer_load_from_file_path(char* filePath)
{
	Customer* customer = NULL;

    // Ouvrir le fichier client
    FILE* file = common_file_safe_open(filePath, "r");

    customer = customer_get_from_file(file);

    fclose(file);

    return customer;
}

Customer* customer_get_from_file(FILE* customerFile)
{
    char* name = NULL;
    char* firstName = NULL;
    size_t nameLen = 0;
    size_t firstNameLen = 0;
    
    // Obtenir le nom du clien dans le fichier en lisant sa ligne (premère ligne)
    getline(&name, &nameLen, customerFile);
    name[strlen(name)-1] = '\0'; // Remplacer la fin de la ligne par \0

    // Obtenir le prénom du clien dans le fichier en lisant sa ligne (deuxième ligne)
    getline(&firstName, &firstNameLen, customerFile);
    firstName[strlen(firstName)-1] = '\0'; // Remplacer la fin de la ligne par \0
    int prod1, prod2, prod3;
    fscanf(customerFile,"%d;%d;%d",&prod1,&prod2,&prod3);
        
    Customer* customer = customer_old(name, firstName, prod1, prod2, prod3);

    return customer;
}

void customer_write_to_file(char* directoryPath, Customer* customer)
{
    DIR *dir;
    FILE* customerFile;
    char filename[512];

    // Ouvrir le répertoire "customers"
    dir = common_directory_safe_open(directoryPath);
    
    // Ajouter le nom du réperoire (customers) au nom du fichier client
    strcpy(filename, directoryPath);
    strcat(filename, customer->name);
    strcat(filename, customer->firstName);
    strcat(filename, ".txt");

    customerFile = fopen(filename, "w");

    fputs(customer->name, customerFile);
    putc('\n', customerFile);
    fputs(customer->firstName, customerFile);
    putc('\n', customerFile);
    fprintf(customerFile, "%d;%d;%d;", customer->purchases[0], customer->purchases[1], customer->purchases[2]);
    putc('\n', customerFile);

    fclose(customerFile);

    closedir(dir);
}

void customer_delete_file(char* directoryPath, Customer* customer)
{
    DIR *dir;
    char filename[512];

    // Ouvrir le répertoire "customers"
    dir = common_directory_safe_open(directoryPath);
    
    // Ajouter le nom du réperoire (customers) au nom du fichier client
    strcpy(filename, directoryPath);
    strcat(filename, customer->name);
    strcat(filename, customer->firstName);
    strcat(filename, ".txt");

    int result = remove(filename);
    if (result == -1){
        printf("Failed to delete %s\n", filename);
        exit(1);
    }

    closedir(dir);
}
#include "customer.h"

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "common.h"

Customer* customer_new(char* name, char* firstName){
	Customer* customer = common_safe_malloc(sizeof(Customer));
	customer->name = name;
    customer->firstName = firstName;
    for(int i = 0; i < 3; i++){
        customer->purchases[i] = -1;
    }
	return customer;
}

void customer_write_to_file(char* name, char* firstName)
{
    DIR *dir;
    FILE* customerFile;
    char filename[512];

    // Open the "customers" directory
    dir = opendir("customers");
    
    if (dir == NULL) {
        printf("Failed to open %s directory\n", "customers");
        exit(1);
    }

    // Add the directory name (customers) to the customer file name
    strcpy(filename, "customers/");
    strcat(filename, name);
    strcat(filename, firstName);
    strcat(filename, ".txt");

    printf("%s\n", filename);

    customerFile = fopen(filename, "w");

    fputs(name, customerFile);
    putc('\n', customerFile);
    fputs(firstName, customerFile);
    putc('\n', customerFile);
    fputs("-1;-1;-1", customerFile);
    putc('\n', customerFile);

    fclose(customerFile);

    closedir(dir);
}

Customer* customer_get_from_file(FILE* customerFile)
{
    char* name = NULL;
    char* firstName = NULL;
    size_t nameLen = 0;
    size_t firstNameLen = 0;
    
    // Get the name of the client in the file by reading its line (first line)
    getline(&name, &nameLen, customerFile);
    name[strlen(name)-1] = '\0'; // Replace the newline terminator with a null terminator

    // Get the first name of the client in the file by reading its line (second line)
    getline(&firstName, &firstNameLen, customerFile);
    firstName[strlen(firstName)-1] = '\0'; // Replace the newline terminator with a null terminator
        
    Customer* customer = customer_new(name, firstName);

    return customer;
}

Customer* customer_get_from_directory(char* name, char* firstName)
{
    Customer* customer = NULL;

   // Open all customer file in "customers" directory
    DIR *dir;
    struct dirent *ent;
    FILE* customerFile;
    char filename[512];

    // Open the "customers" directory
    dir = opendir("customers");
    
    if (dir == NULL) {
        printf("Failed to open directory\n");
        exit(1);
    }

    while ((ent = readdir(dir)) != NULL) {

        if (!strcmp (ent->d_name, ".") || !strcmp (ent->d_name, ".."))
            continue;

        // Add the directory name (customers) to the customer file name
        strcpy(filename, "customers/");
        strcat(filename, ent->d_name);

        //printf("%s\n", ent->d_name);

        // Open the customer file
        customerFile = fopen(filename, "r");
        if (customerFile == NULL)
        {
            printf("Error : Failed to open entry file - %s\n", filename);
            fclose(customerFile);

            exit(1);
        }

        customer = customer_get_from_file(customerFile);
        // Check if the customer from the file is the same as the one as entered
        if (!strcasecmp(customer->name, name) && !strcasecmp(customer->firstName, firstName)){
            // Stop checking the files from the "customers" directory if the current customer file is the same one as the one entenred
            fclose(customerFile);
            break;
        }

        // Free space if the customer from the file isn't the same as the one entered
        common_free(customer);
        customer = NULL;

        fclose(customerFile);
    }

    closedir(dir);

    return customer;
}

void customer_show_purchases(Customer* customer){
    for(int i = 0; i < 3; i++){
        if (customer->purchases[i] != -1){
            printf("%d\n", customer->purchases[i]);
        }
    }
}

void customer_delete_file(char* name, char* firstName)
{
    DIR *dir;
    char filename[512];

    // Open the "customers" directory
    dir = opendir("customers");
    
    if (dir == NULL) {
        printf("Failed to open %s directory\n", "customers");
        exit(1);
    }

    // Add the directory name (customers) to the customer file name
    strcpy(filename, "customers/");
    strcat(filename, name);
    strcat(filename, firstName);
    strcat(filename, ".txt");

    int result = remove(filename);
    if (result == -1){
        printf("Failed to delete %s\n", filename);
        exit(1);
    }

    closedir(dir);
}

void customer_free(Customer* customer){
    free(customer);
}
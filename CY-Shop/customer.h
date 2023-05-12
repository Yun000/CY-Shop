#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>

typedef struct {
    char* name;
    char* firstName;
    int purchases[3];
} Customer;

// Constructor for customer
Customer* customer_new(char* name, char* firstName);

// Create a file for a customer
void customer_write_to_file(char* name, char* firstName);

// Return a customer from a file
Customer* customer_get_from_file(FILE* clientFile);

// Delete the file for a customer
void customer_delete_file(char* name, char* firstName);

// Return a customer from the "customers" directory
Customer* customer_get_from_directory(char* name, char* firstName);

// Search customer in the files from its name and first name
Customer* customer_search(char* name, char* firstName);

// Show the last three purchases of the customer
void customer_show_purchases(Customer* customer);


void customer_free(Customer* customer);

#endif
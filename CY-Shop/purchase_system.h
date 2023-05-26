#ifndef PURCHASE_SYSTEM_H
#define PURCHASE_SYSTEM_H

#include "store.h"
#include "customer.h"
#include "product.h"
#include "common.h"

// Authentification du client
Customer* purchase_system_login(Store* store);

// Affichage pour les optiosn d'achat
void purchase_system_purchase(Store* store, Customer* customer);

#endif
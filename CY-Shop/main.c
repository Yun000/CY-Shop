#include <stdio.h>

#include "management_system.h"
#include "purchase_system.h"

int main()
{
    int mode;

    printf("Entrez :\n");
    printf("0 : Pour le mode gestion\n");
    printf("1 : Pour le mode achat\n");

    do {
        scanf("%d", &mode);
    } while (mode < 0 || mode > 1);
    
    switch (mode)
    {
        case 0:
            management_system_menu();
            break;
        case 1:
            purchase_system_menu();
            break;
        
        default:
            break;
    }

    return 0;
}

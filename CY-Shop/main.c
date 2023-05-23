#include "common.h"
#include "management_system.h"
#include "purchase_system.h"

int main()
{
    int mode;
    printf(CLEAR_SCREEN);
    printf("\n\n\n     ______ _                                            _                 \n     | ___ (_)                                          | |                \n     | |_/ /_  ___ _ ____   _____ _ __  _   _  ___    __| | __ _ _ __  ___ \n     | ___ \040 |/ _ \040 '_ \040 \040 / / _ \040 '_ \040| | | |/ _ \040  / _` |/ _` | '_ \040/ __|\n     | |_/ / |  __/ | | \040 V /  __/ | | | |_| |  __/ | (_| | (_| | | | \040__ \040\n     \040____/|_|\040___|_| |_|\040_/ \040___|_| |_|\040__,_|\040___|  \040__,_|\040__,_|_| |_|___/\n     \n                 _______   __     _____ _                                  \n                /  __ \040 \040 / /    /  ___| |                                 \n                | /  \040/\040 V /_____\040 `--.| |__   ___  _ __                   \n                | |     \040 /______|`--. \040 '_ \040 / _ \040| '_ \040                  \n                | \040__/\040 | |      /\040__/ / | | | (_) | |_) |                 \n                 \040____/ \040_/      \040____/|_| |_|\040___/| .__/                  \n                                                   | |                     \n                                                   |_|                     \n");
    sleep(3);
    printf("Entrez :\n");
    printf("0 : Pour le mode gestion\n");
    printf("1 : Pour le mode achat\n");

    do {
        scanf("%d", &mode);
    } while (mode < 0 || mode > 1);

    printf(CLEAR_SCREEN);

    Store* store = store_new("customers/", "products/products.txt");

    switch (mode)
    {
        case 0:
            management_system_menu(store);
            break;
        case 1:
            purchase_system_login(store);
            break;
    }

    store_free(store);

    return 0;
}
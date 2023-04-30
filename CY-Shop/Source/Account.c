#include "product.h"


// Array which stock Account.txt data

char name [1000][30];
char pwd [1000][30];


// Encrypt the password
// Source of this function : https://gist.github.com/touatily/3af14ed032c407fd3e2bb2dbe3bdc154
// Take the normal password and the encryption key
// Return the crypted password in the third parameter

void vigenereEnc(const char * text, const char * key, char * ciphertext){

    unsigned int i, size = strlen(key);

    for(i = 0; text[i] != '\0'; i++){

        if( (text[i] >= 'a') && (text[i] <= 'z') ){
            int rang = (text[i] + key[i % size] - 2 * 'a') % 26;

            ciphertext[i] = 'a' + rang;
        }
        else if( (text[i] >= 'A') && (text[i] <= 'Z') ){
            int rang = (text[i] + key[i % size] - 'a' - 'A') % 26;

            ciphertext[i] = 'A' + rang;
        }
        else
            ciphertext[i] = text[i];
    }

    ciphertext[i] = '\0';
}


// Take data from Account.txt and stock them in idAccount
// Return the number of line in Account.txt (the Account number)

int stockAccount(){

    FILE *acc = fopen("./Data/Account.txt","r");
    if(acc == NULL){acc = fopen("./Data/Account-save.txt","r");}

    int nbrl =nbrL(acc);

    for(int i=0;i<nbrl;i++){

        fscanf(acc,"%s %s",name[i],pwd[i]);
    }

    fclose(acc);
    return nbrl;
}


// Create a new account
// Take the account number and return the new account number

int createAccount(int nbrl){

    char username[30];
    char pw[30];
    char pwC[30];
    int answer=1;


    // Check if the name is already used

    while(answer){

        answer = 2;
        printf("Ecrivez votre pseudo (pas d'espace et 30 caractere max):\n");

        scanf("%30s",username);

        for (int i=0;i<nbrl;i++){

            if (strDif(username,name[i])){
                printf("Pseudo deja utilise, voulez vous reessayer ?(oui/non)\n");

                answer =YorN();
            }
        }

        if(answer==2){
            break;
        }
    }
    if (answer!=0){

        printf("Ecrivez votre mot de passe (pas d'espace et 30 caractere max):\n");
        scanf("%30s",pw);


        // Save account in  Account.txt

        FILE *acc = fopen("./Data/Account.txt","r+");
        if(acc == NULL){acc = fopen("./Data/Account-save.txt","r+");}

        fseek(acc,0,SEEK_END);
        fputc('\n',acc);

        vigenereEnc(pw, "CYTECHLIBRARY", pwC);
        fprintf(acc,"%s %s",username,pwC);

        printf("Compte cree !\n");

        rewind(acc);
        fclose(acc);
        return stockAccount();
    }
}


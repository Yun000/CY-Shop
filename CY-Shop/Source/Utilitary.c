#include "product.h"

// Scanf which need a "oui" or a "non"
// Return 1 for "oui" and 0 for "non"

int YorN(){

    char answer[4];

    while(1){

        scanf("%4s",answer);

        if(answer[0]=='o' && answer[1]=='u' && answer[2]=='i'&& answer[3]=='\0'){
            return 1;
        }
        else if(answer[0]=='n' && answer[1]=='o' && answer[2]=='n' && answer[3]=='\0'){
            return 0;
        }

        printf("\nVeuillez repondre oui ou non :\n\n");
    }
}


// Scanf safe
// Take the minimum the maximum of the ask number
// Return the scanf number as int

int scan(int min,int max){

    float answer;

    while(1){

        if (scanf("%f",&answer)==0){
            printf("\nEcrivez un chiffre :\n\n");

            scanf("%*[^\n]%*1[\n]");
        }
        else if(answer<min || answer>max){
            printf("\nEcrivez un chiffre entre %d et %d:\n\n",min,max);
        }
        else{
            int intPart = (int)answer;

            printf("\n");

            return intPart;
        }

    }
}


// Take 2 string, return 1 if they are the same and 0 if not

int strDif(char *str1,char*str2){

    int i=0;

    while(1){

        if(*(str1+i)=='\0' && *(str2+i)=='\0'){
            return 1;
        }
        else if(*(str2+i)!=*(str1+i)){
            return 0;
        }

        i++;
    }
}



// Take a file and return its number of lines

int nbrL(FILE *file){

    int i =0;
    char c;

    while ((c=getc(file))!=EOF){

		if (c=='\n'){
            i++;
        }
	}

    rewind(file);
    return i+1;
}
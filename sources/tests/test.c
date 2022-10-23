#include<stdio.h>
#include<string.h>
#include<string.h>

#include "test.h"

int main(void) {
    test_extensionType();
    return 0;
}


void test_extensionType() {

    printf("[TEST] extensionType() :\n\n");

    int res = extensionType("o.itbob");
    printf("REs : %d\n", res);

    /*
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "o.itbob", 1, extensionType("o.itbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "m.rtbob", 1, extensionType("m.rtbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "m.mtbob", 1, extensionType("m.mtbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "", 1, extensionType(""));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "sujet.pdf", 1, extensionType("sujet.pdf"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n   ", "jeidjioc", 1, extensionType("jeidjioc")); 
    */


}

int extensionType(char* filename) { 
    if(strlen(filename) <= 6) { // .*tbob == 6 caractères
        return EXTENSION_INVALIDE;
    }

    char* prefixe = malloc(sizeof(char) * 255);
    prefixe = strtok(filename, ".");

    char* extension = malloc(sizeof(char) * 255);
    extension = strtok(NULL, ".");

    if(strcmp(extension, "itbob")) { 
        return EXTENSION_FICHIER_OBJET;
    } else if(strcmp(extension, "mtbob")) { 
        return EXTENSION_FICHIER_MONSTRES;
    } else if(strcmp(extension, "rtbob")) { 
        return EXTENSION_FICHIER_SALLES;
    } 

    return EXTENSION_INVALIDE;
}
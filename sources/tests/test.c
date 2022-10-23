#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "test.h"
#include "../include/mystring.h"

int main(void) {
    test_extensionType();
    return 0;
}


void test_extensionType() {

    printf("[TEST] extensionType() :\n\n");
   
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "o.itbob", EXTENSION_FICHIER_OBJET, extensionType("o.itbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "m.rtbob", EXTENSION_FICHIER_MONSTRES, extensionType("m.mtbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "m.rtbob", EXTENSION_FICHIER_SALLES, extensionType("m.rtbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "", EXTENSION_INVALIDE, extensionType(""));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "sujet.pdf", EXTENSION_INVALIDE, extensionType("sujet.pdf"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "jeidjioc", EXTENSION_INVALIDE, extensionType("jeidjioc"));

}

int extensionType(char* filename) { 
    char* nomFichier = duplicateString(filename);
    if(strlen(nomFichier) == 0) {
        return EXTENSION_INVALIDE;
    }
    
    char* prefix = strtok(nomFichier, ".");
    if(strcmp(prefix, nomFichier) == 0) { // pas de "."
        return EXTENSION_INVALIDE;
    }

    char* extension = strtok(NULL, ".");
    if(strcmp(extension, "mtbob") == 0) {
        return EXTENSION_FICHIER_MONSTRES;
    } else if(strcmp(extension, "itbob") == 0) {
        return EXTENSION_FICHIER_OBJET;
    } else if(strcmp(extension, "rtbob") == 0) {
        return EXTENSION_FICHIER_SALLES;
    } 

    return EXTENSION_INVALIDE;
}
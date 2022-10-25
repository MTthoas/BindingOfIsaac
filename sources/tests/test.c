#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "test.h"
#include "../include/mystring.h"

int main(void) {
    //test_extensionType();
    //test_displayObjet();
    test_displayListeObjets();
    //test_addObjet();
    //test_duplicateObject();
    
    return 0;
}


void test_duplicateObject() {
    printf("[TEST] duplicateObject() :\n\n");

    Objet o1;
    o1.id = 1;
    o1.name = "Un objet";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;

    Objet* o1copy = duplicateObject(&o1);
    printf("Objet 1 : \n");
    displayObjet(&o1);
    printf("\nCopie Objet 1 : \n");
    displayObjet(o1copy);

    Objet* o2copy = duplicateObject(NULL);
    printf("Objet 2 (NULL) : \n");
    displayObjet(NULL);
    printf("\nCopie Objet 2 : \n");
    displayObjet(o2copy);
    
}

Objet* duplicateObject(Objet* objet) {
    if(objet == NULL) {
        return NULL;
    }

    Objet* newObjet = malloc(sizeof(Objet)* 1);
    newObjet->id = objet->id;
    newObjet->name = duplicateString(objet->name);
    newObjet->hpMax = objet->hpMax;
    newObjet->shield = objet->shield;
    newObjet->damage = objet->damage;
    newObjet->piercingShot = objet->piercingShot;
    newObjet->spectralShot = objet->spectralShot;
    newObjet->flight = objet->flight;
    
    return newObjet;
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

void test_displayObjet() {
    printf("[TEST] displayObjet() :\n\n");
    Objet o;
    o.id = 1;
    o.name = "Mon objet";
    o.hpMax = 100;
    o.shield = 100;
    o.damage = 0;
    o.piercingShot = 1;
    o.spectralShot = 0;
    o.flight = 0;

    Objet o2;
    o2.id=2;

    Objet o3;

    displayObjet(&o); 
    displayObjet(&o2);
    displayObjet(&o3);
}

void* displayObjet(Objet* objet) {
    if(objet == NULL) {
        printf("Pas d'objet\n");
        return NULL;
    }

    printf("[WARN] Utilisation de displayObjet(). \nSi les champs ne sont pas remplis, erreur de segmentation possible.\n");
    char* nomObjet = duplicateString(objet->name);
    
    printf("\n");
    printf("id : %d\n", objet->id);
    printf("name : %s\n", nomObjet);
    printf("hpMax : %d\n", objet->hpMax);
    printf("shield : %d\n", objet->shield);
    printf("damage : %d\n", objet->damage);
    printf("piercingShot : %d\n", objet->piercingShot);
    printf("spectralShot : %d\n", objet->spectralShot);
    printf("flight : %d\n", objet->flight);
    printf("\n");

    return NULL;
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
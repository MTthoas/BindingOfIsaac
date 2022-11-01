/**
 * @file testLectureFichiers.c
 * @author TheGreat-Chain
 * @brief Tests des fonctions de lectureFichiers.h
 * @version 0.1
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/mystring.h"
#include "../include/objets.h"
#include "../include/lectureFichiers.h"

void test_extensionType(); //ok
void test_getNbLignesFichier(); //ok
void test_fichierToListeObjets(); //ok

int main(void) {
    test_fichierToListeObjets();

    //test_extensionType();
    //test_getNbLignesFichier();
    return 0;
}

void test_getNbLignesFichier() {
    char* chemin = "./test.itbob";
    printf("Attendu : 10\nResultat : %d\n\n", getNbLignesFichier(chemin));
    chemin = "rkovnej";
    printf("\nAttendu : 0 (Impossible d'ouvrir le fichier)\nRésultat : %d\n", getNbLignesFichier(chemin));

}

int getNbLignesFichier(char* chemin_fichier) {
    FILE* fichier = fopen(chemin_fichier, "r");
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier %s\nFonction getNbLignesFichier().\n", chemin_fichier);
        return 0;
    } // ouverture fichier

    int nbLignes = 0;
    char buffer[255];
    while(fgets(buffer, 255, fichier)) {
        nbLignes += 1;
    }

    rewind(fichier);
    fclose(fichier);
    return nbLignes;
}

void test_fichierToListeObjets() {
    printf("[TEST] fichierObjetsToListeObjets() :\n\n");

    FILE* fichier = fopen("../../resources/items.itbob", "r");

    printf("Fichier de base : \n");
    afficherFichier(fichier);
    fclose(fichier);

    printf("\nAffichage de la liste : \n");
    ListeObjets* l = fichierObjetsToListeObjets();
    displayListeObjets(l);
    freeListeObjets(l);
}

ListeObjets* fichierObjetsToListeObjets() {
    FILE* fichier = fopen(CHEMIN_FICHIER_OBJETS, "r"); // ouverture fichier
    if(fichier == NULL) { 
        fichier = fopen("../../resources/items.itbob", "r");
        if(fichier == NULL) {
            printf("Problème d'ouverture du fichier\n");
            return NULL;
        }
    }
    rewind(fichier);
    
   
    ListeObjets* liste = createListeObjets(); // variables
    Objet* o;
    char* name = "";
    float hpMax = 0;
    float shield = 0;
    float damage = 0;
    int piercingShot = 0;
    int spectralShot = 0;
    int flight = 0;
    int activated = 0;

    char buffer[255];
    char* stat = malloc(sizeof(char) * 255); 
    char* value = malloc(sizeof(char) * 255);
    int creatingObjet = 0;

    while(fgets(buffer, 255, fichier)) { // lecture fichier ligne par ligne
        if(creatingObjet == 0 && strcmp(buffer, "---\n") == 0) { // creation de l'objet
            creatingObjet = 1;
            continue;
        }

        if(creatingObjet == 1 && strcmp(buffer, "---\n") != 0) { // preparation de l'objet
            stat = strtok(buffer, "="); //ex : hpMax (depuis "hpMax=1")
            value = strtok(NULL, "="); //ex : 1 (depuis "hpMax=1")
            uppercase(stat);
            uppercase(value);

            if(strcmp(stat, "NAME") == 0) {
                name = duplicateString(value);
            } else if((strcmp(stat, "HPMAX") == 0)) {
                hpMax = atof(value);
            } else if((strcmp(stat, "SHIELD") == 0)) {
                shield = atof(value);
            } else if((strcmp(stat, "DMG") == 0)) {
                damage = atof(value);
            } else if((strcmp(stat, "PS") == 0)) {
                activated = (strcmp(value, "TRUE\n") == 0);
                piercingShot = activated;
            } else if((strcmp(stat, "SS") == 0)) {
                activated = (strcmp(value, "TRUE\n") == 0);
                spectralShot = activated;
            } else if((strcmp(stat, "FLIGHT") == 0)) {
                activated = (strcmp(value, "TRUE\n") == 0);
                flight = activated;
            }            
        }

        if(creatingObjet == 1 && strcmp(buffer, "---\n") == 0) { // ajouter l'objet
            //printf("%s%f, %f, %f, %d, %d, %d\n\n", name, hpMax, shield, damage, piercingShot, spectralShot, flight);
            o = createObjet(name, hpMax, shield, damage, piercingShot, spectralShot, flight);
            addObjet(liste, o);
            name = "";
            hpMax = 0;
            shield = 0;
            damage = 0;
            piercingShot = 0;
            spectralShot = 0;
            flight = 0;
        } else if(feof(fichier)) { // fin de fichier -> ajouter l'objet
            o = createObjet(name, hpMax, shield, damage, piercingShot, spectralShot, flight);
            addObjet(liste, o);
        }
    }

    fclose(fichier);
    return liste;
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

/*
int extensionType(char* filename) { 
    if(strlen(duplicateString(filename)) == 0) {
        return EXTENSION_INVALIDE;
    }
    
    char* prefix = strtok(duplicateString(filename), ".");
    if(strcmp(prefix, filename) == 0) { // pas de "."
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
*/
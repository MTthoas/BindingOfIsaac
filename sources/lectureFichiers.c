/**
 * @file lectureFichiers.c
 * @author TheGreat-Chain
 * @brief Fontions relatives à la lecture des fichiers des monstres, objets et pièces.
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "include/lectureFichiers.h"
#include "include/cheminsFichiers.h"
#include "include/array.h"
#include "include/mystring.h"

#include <string.h>

ListeObjets* fichierToListeObjets() {
    ListeObjets* listeObjets = malloc(sizeof(ListeObjets) * 1);

    FILE* fichier = NULL;
    fichier = fopen(CHEMIN_FICHIER_OBJETS, "r");

    if(fichier == NULL) { //gestion erreur
        printf("Impossible d'ouvrir le fichier : %s.\nFin.\n", CHEMIN_FICHIER_OBJETS);
        exit(EXIT_FAILURE);
    }

    // vérifier validité du fichier ?

    int nbObjets = getNombreObjets(fichier);
    if(nbObjets == 0) {
        printf("Attention, 0 objets bonus créés.\n");
    }
    listeObjets->nombreObjets = nbObjets;

    Objet* tabObjets = getTabObjets(fichier, nbObjets);
    listeObjets->tabObjets = tabObjets;

    //afficherFichier(fichier);
    fclose(fichier);
    return listeObjets;
}

int getNombreObjets(FILE* fichierObjets){
    char token[256];
    int index = 0;
    char c = fgetc(fichierObjets);
    while(c != EOF) { // parcours du fichier
        if(c == '{') { //récupération du nb d'objets
            while(c != '}') {
                c = fgetc(fichierObjets);
                token[index] = c;
                index += 1;
            }
        token[index+1] = '\n'; // transformation en string
        return atoi(token);    
        c = fgetc(fichierObjets); 
        }    
    }
    return 0; 
}

Objet* getTabObjets(FILE* fichierObjets, int nbObjets) {
    rewind(fichierObjets); 

    Objet* tabObjets = malloc(sizeof(Objet) * nbObjets);
    
    Objet* objet = NULL;
    char buffer[255]; 
    char* stat = malloc(sizeof(char) * 255);
    char* value = malloc(sizeof(char) * 255);
    unsigned int id = 0;

    while(fgets(buffer, 255, fichierObjets)) { // lecture ligne par ligne
        printf("A finir");
    }   

    free(tabObjets);
    return NULL;
}

void afficherFichier(FILE* fichier) {
    rewind(fichier); 
    char c = fgetc(fichier);
    while(c != EOF) {
        printf("%c", c);
        c = fgetc(fichier);
    }
    printf("\n");
    return;
}

int fichierValide(FILE* fichier, char* filename) {
    printf(" à coder :)\n");

    /**
     * prendre l'extension. 
     * si ok, vérifer que premiere ligne {x}
     * ensuite
     * si salle :
     * - vérifier dimensions, lettre inconnues
     * 
     * si mobs / items à chaque ligne :
     * - vérifier si lettre ou -
     * - si -, vérifier que buffer == ---
     * - si lettre, vérifier que mot avant = est une stat existante 
     * 
     * 2 heures pour coder ça, donc vérifier le besoin avant
     */

    return 0;
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
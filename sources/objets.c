/**
 * @file objets.c
 * @author TheGreat-Chain
 * @brief Structures et fonctions relatives aux objets de personnage
 * @version 0.1
 * @date 2022-10-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "include/objets.h"
#include "include/mystring.h"

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

void* displayListeObjets(ListeObjets* listeObjets) {
    if(listeObjets == NULL) {
        printf("Pas de liste d'objet\n");
        return NULL;
    }

    int nbObjets = listeObjets->nombreObjets;
    printf("\n");
    for (int i = 0 ; i < nbObjets ; i+=1) {
        displayObjet(&listeObjets->tabObjets[i]);
    }

    return NULL;
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
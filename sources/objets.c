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
#include <stdlib.h>
#include <string.h>

#include "include/objets.h"
#include "include/mystring.h"

void* displayObjet(Objet* objet) {
    if(objet == NULL) {
        printf("Pas d'objet\n");
        return NULL;
    }

    //printf("[WARN] Utilisation de displayObjet(). \nSi les champs ne sont pas remplis, erreur de segmentation possible.\n");
    
    printf("\n");
    printf("id : %d\n", objet->id);
    printf("name : %s\n", duplicateString(objet->name));
    printf("hpMax : %f\n", objet->hpMax);
    printf("shield : %f\n", objet->shield);
    printf("damage : %f\n", objet->damage);
    printf("piercingShot : %d\n", objet->piercingShot);
    printf("spectralShot : %d\n", objet->spectralShot);
    printf("flight : %d\n", objet->flight);
    printf("\n");

    return NULL;
}

void* displayListeObjets(ListeObjets* listeObjets) {
    if(listeObjets == NULL) {
        printf("Pas de liste.\n");
        return NULL;
    }

    Objet* courant = listeObjets->premier;
    while(courant != NULL) { // tant qu'on n'est pas à la fin de la liste 
        displayObjet(courant);
        courant = courant->suivant;
    }
    return NULL;
}

Objet* duplicateObjet(Objet* objet) {
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
    newObjet->suivant = objet->suivant;
    
    return newObjet;
}

int addObjet(ListeObjets* listeObjets, Objet* newObjet) {
    Objet* courant = listeObjets->premier;
    int index = 1; //formera l'id du nouvel objet

    if(courant == NULL) { // liste vide
        newObjet->id = index;
        listeObjets->premier = duplicateObjet(newObjet);
        return index;
    }

    while(courant != NULL) { // ajout a la fin de liste
        index += 1;
        if(courant->suivant == NULL) {
            newObjet->id = index;
            courant->suivant = duplicateObjet(newObjet);
            return index;
        }
        courant = courant->suivant;
    }

    return 0;
}

Objet* createObjet(char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight) {
    Objet* o = malloc(sizeof(Objet) * 1);
    
    // verification des entrees
    if(strcmp("", name) == 0) { //nom par défaut
        name = duplicateString("objet");
    }
    piercingShot = (piercingShot == 0) ? 0 : 1;
    spectralShot = (spectralShot == 0) ? 0 : 1;
    flight = (flight == 0) ? 0 : 1;

    // allocation 
    o->id = 1;
    o->name = duplicateString(name);
    o->hpMax = hpMax;
    o->shield = shield;
    o->damage = damage;
    o->piercingShot = piercingShot;
    o->spectralShot = spectralShot;
    o->flight = flight;
    o->suivant = NULL;

    return o;
}

void modifyObjet(ListeObjets* liste, int id, Objet* newObjet) {
    Objet* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // modifier premier element
        toDelete = liste->premier;
        newObjet->suivant = liste->premier->suivant;
        liste->premier = newObjet;
        freeObjet(toDelete);
        rangerListeObjets(liste);
        return;
    }

    Objet* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // modifier
            toDelete = courant->suivant;
            newObjet->suivant = courant->suivant->suivant;
            courant->suivant = newObjet;
            freeObjet(toDelete);
            rangerListeObjets(liste);
            return;
        }
        
        courant = courant->suivant;
    }
}

void rangerListeObjets(ListeObjets* liste) {
    int count = 1;
    Objet* courant = liste->premier;
    while(courant != NULL) {
        courant->id = count;
        count += 1;
        courant = courant->suivant;
    }
}

void removeObjet(ListeObjets* liste, int id) {
    Objet* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // supprimer premier element
        toDelete = liste->premier;
        liste->premier = liste->premier->suivant;
        freeObjet(toDelete);
        rangerListeObjets(liste);
        return;
    }

    Objet* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // suppression
            toDelete = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            freeObjet(toDelete);
            rangerListeObjets(liste);
            return;
        }
        
        courant = courant->suivant;
    }

}

Objet* getObjetById(ListeObjets* liste, int id) {
    Objet* result = liste->premier;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->suivant;
    }

    return NULL;
}

void freeListeObjets(ListeObjets* liste) {
    Objet* courant = liste->premier;
    Objet* suivant;

    while(courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

ListeObjets* createListeObjets() {
    ListeObjets* liste = malloc(sizeof(ListeObjets) * 1);
    return liste;   
}

void freeObjet(Objet* objet) {
    free(objet);
}

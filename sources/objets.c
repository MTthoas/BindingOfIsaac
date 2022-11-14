/**
 * @file zs.c
 * @author TheGreat-Chain - Nairod36
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
#include <stdlib.h>
#include <string.h>

#include "include/objets.h"
#include "include/mystring.h"



int getTailleListeobjets(Listeobjets* l) {
    objet* courant = l->premier;
    if(courant == NULL) {
        return 0;
    }

    int count = 0;
    while(courant != NULL) {
        count += 1;
        courant = courant->suivant;
    }

    return count;
}

void* displayobjet(objet* objet) {
    if(objet == NULL) {
        printf("Pas d'objet\n");
        return NULL;
    }

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

void* displayListeobjets(Listeobjets* listeobjets) {
    if(listeobjets == NULL) {
        printf("Pas de liste.\n");
        return NULL;
    }

    objet* courant = listeobjets->premier;
    while(courant != NULL) { // tant qu'on n'est pas à la fin de la liste 
        displayobjet(courant);
        courant = courant->suivant;
    }
    return NULL;
}

objet* duplicateobjet(objet* objet) {
    if(objet == NULL) {
        return NULL;
    }

    objet* newobjet = malloc(sizeof(objet)* 1);
    newobjet->id = objet->id;
    newobjet->name = duplicateString(objet->name);
    newobjet->hpMax = objet->hpMax;
    newobjet->shield = objet->shield;
    newobjet->damage = objet->damage;
    newobjet->piercingShot = objet->piercingShot;
    newobjet->spectralShot = objet->spectralShot;
    newobjet->flight = objet->flight;
    newobjet->suivant = objet->suivant;
    
    return newobjet;
}

int addobjet(Listeobjets* listeobjets, objet* newobjet) {
    objet* courant = listeobjets->premier;
    int index = 1; //formera l'id du nouvel objet

    if(courant == NULL) { // liste vide
        newobjet->id = index;
        listeobjets->premier = duplicateobjet(newobjet);
        return index;
    }

    while(courant != NULL) { // ajout a la fin de liste
        index += 1;
        if(courant->suivant == NULL) {
            newobjet->id = index;
            courant->suivant = duplicateobjet(newobjet);
            return index;
        }
        courant = courant->suivant;
    }

    return 0;
}

objet* createobjet(char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight) {
    objet* o = malloc(sizeof(objet) * 1);
    
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

void modifyobjet(Listeobjets* liste, int id, objet* newobjet) {
    objet* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // modifier premier element
        toDelete = liste->premier;
        newobjet->suivant = liste->premier->suivant;
        liste->premier = newobjet;
        freeobjet(toDelete);
        rangerListeobjets(liste);
        return;
    }

    objet* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // modifier
            toDelete = courant->suivant;
            newobjet->suivant = courant->suivant->suivant;
            courant->suivant = newobjet;
            freeobjet(toDelete);
            rangerListeobjets(liste);
            return;
        }
        
        courant = courant->suivant;
    }
}

void rangerListeobjets(Listeobjets* liste) {
    int count = 1;
    objet* courant = liste->premier;
    while(courant != NULL) {
        courant->id = count;
        count += 1;
        courant = courant->suivant;
    }
}

void removeobjet(Listeobjets* liste, int id) {
    objet* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // supprimer premier element
        toDelete = liste->premier;
        liste->premier = liste->premier->suivant;
        freeobjet(toDelete);
        rangerListeobjets(liste);
        return;
    }

    objet* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // suppression
            toDelete = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            freeobjet(toDelete);
            rangerListeobjets(liste);
            return;
        }
        
        courant = courant->suivant;
    }

}

objet* getobjetById(Listeobjets* liste, int id) {
    objet* result = liste->premier;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->suivant;
    }

    return NULL;
}

void freeListeobjets(Listeobjets* liste) {
    objet* courant = liste->premier;
    objet* suivant;

    while(courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

Listeobjets* createListeobjets() {
    Listeobjets* liste = malloc(sizeof(Listeobjets) * 1);
    return liste;   
}

void freeobjet(objet* objet) {
    free(objet);
}


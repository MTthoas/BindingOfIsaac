/**
 * @file monstres.c
 * @author Nairod36
 * @brief Structures et fonctions relatives aux monstres
 * @version 0.1
 * @date 2022-10-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/monstre.h"
#include "include/mystring.h"

void* displayMonstre(Monstre* monstre) {
    if(monstre == NULL) {
        printf("Pas d'monstre\n");
        return NULL;
    }

    //printf("[WARN] Utilisation de displayMonstre(). \nSi les champs ne sont pas remplis, erreur de segmentation possible.\n");
    
    printf("\n");
    printf("id : %d\n", monstre->id);
    printf("name : %s\n", duplicateString(monstre->name));
    printf("hpMax : %f\n", monstre->hpMax);
    printf("shoot : %d\n", monstre->shoot);
    printf("flight : %d\n", monstre->flight);
    printf("ss : %d\n", monstre->ss);
    printf("\n");

    return NULL;
}

void* displayListeMonstres(ListeMonstres* listeMonstres) {
    if(listeMonstres == NULL) {
        printf("Pas de liste.\n");
        return NULL;
    }

    Monstre* courant = listeMonstres->premier;
    while(courant != NULL) { // tant qu'on n'est pas à la fin de la liste 
        displayMonstre(courant);
        courant = courant->suivant;
    }
    return NULL;
}

Monstre* duplicateMonstre(Monstre* monstre) {
    if(monstre == NULL) {
        return NULL;
    }

    Monstre* newMonstre = malloc(sizeof(Monstre)* 1);
    newMonstre->id = monstre->id;
    newMonstre->name = duplicateString(monstre->name);
    newMonstre->hpMax = monstre->hpMax;
    newMonstre->shoot = monstre->shoot;
    newMonstre->flight = monstre->flight;
    newMonstre->ss = monstre->ss;
    newMonstre->suivant = monstre->suivant;
    
    return newMonstre;
}

int addMonstre(ListeMonstres* listeMonstres, Monstre* newMonstre) {
    Monstre* courant = listeMonstres->premier;
    int index = 1; //formera l'id du nouveau monstre

    if(courant == NULL) { // liste vide
        newMonstre->id = index;
        listeMonstres->premier = duplicateMonstre(newMonstre);
        return index;
    }

    while(courant != NULL) { // ajout a la fin de liste
        index += 1;
        if(courant->suivant == NULL) {
            newMonstre->id = index;
            courant->suivant = duplicateMonstre(newMonstre);
            return index;
        }
        courant = courant->suivant;
    }

    return 0;
}

Monstre* createMonstre(char* name, float hpMax, float shoot, float flight, int ss) {
    Monstre* o = malloc(sizeof(Monstre) * 1);
    
    // verification des entrees
    if(strcmp("", name) == 0) { //nom par défaut
        name = duplicateString("monstre");
    }
    flight = (flight == 0) ? 0 : 1;

    // allocation 
    o->id = 1;
    o->name = duplicateString(name);
    o->hpMax = hpMax;
    o->shoot = shoot;
    o->flight = flight;
    o->ss = ss;
    o->suivant = NULL;

    return o;
}

void modifyMonstre(ListeMonstres* liste, int id, Monstre* newMonstre) {
    Monstre* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // modifier premier element
        toDelete = liste->premier;
        newMonstre->suivant = liste->premier->suivant;
        liste->premier = newMonstre;
        freeMonstre(toDelete);
        rangerListeMonstres(liste);
        return;
    }

    Monstre* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // modifier
            toDelete = courant->suivant;
            newMonstre->suivant = courant->suivant->suivant;
            courant->suivant = newMonstre;
            freeMonstre(toDelete);
            rangerListeMonstres(liste);
            return;
        }
        
        courant = courant->suivant;
    }
}

void rangerListeMonstres(ListeMonstres* liste) {
    int count = 1;
    Monstre* courant = liste->premier;
    while(courant != NULL) {
        courant->id = count;
        count += 1;
        courant = courant->suivant;
    }
}

void removeMonstre(ListeMonstres* liste, int id) {
    Monstre* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // supprimer premier element
        toDelete = liste->premier;
        liste->premier = liste->premier->suivant;
        freeMonstre(toDelete);
        rangerListeMonstres(liste);
        return;
    }

    Monstre* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // suppression
            toDelete = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            freeMonstre(toDelete);
            rangerListeMonstres(liste);
            return;
        }
        
        courant = courant->suivant;
    }

}

Monstre* getMonstreById(ListeMonstres* liste, int id) {
    Monstre* result = liste->premier;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->suivant;
    }

    return NULL;
}

void freeListeMonstres(ListeMonstres* liste) {
    Monstre* courant = liste->premier;
    Monstre* suivant;

    while(courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

ListeMonstres* createListeMonstres() {
    ListeMonstres* liste = malloc(sizeof(ListeMonstres) * 1);
    return liste;   
}

void freeMonstre(Monstre* monstre) {
    free(monstre);
}
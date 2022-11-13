/**
 * @file objects.c
 * @author TheGreat-Chain - Nairod36
 * @brief Structures et fonctions relatives aux objects de personnage
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

#include "include/objects.h"
#include "include/mystring.h"



int getTailleListeObjects(ListeObjects* l) {
    Object* courant = l->premier;
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

void* displayObject(Object* object) {
    if(object == NULL) {
        printf("Pas d'object\n");
        return NULL;
    }

    printf("\n");
    printf("id : %d\n", object->id);
    printf("name : %s\n", duplicateString(object->name));
    printf("hpMax : %f\n", object->hpMax);
    printf("shield : %f\n", object->shield);
    printf("damage : %f\n", object->damage);
    printf("piercingShot : %d\n", object->piercingShot);
    printf("spectralShot : %d\n", object->spectralShot);
    printf("flight : %d\n", object->flight);
    printf("\n");

    return NULL;
}

void* displayListeObjects(ListeObjects* listeObjects) {
    if(listeObjects == NULL) {
        printf("Pas de liste.\n");
        return NULL;
    }

    Object* courant = listeObjects->premier;
    while(courant != NULL) { // tant qu'on n'est pas à la fin de la liste 
        displayObject(courant);
        courant = courant->suivant;
    }
    return NULL;
}

Object* duplicateObject(Object* object) {
    if(object == NULL) {
        return NULL;
    }

    Object* newObject = malloc(sizeof(Object)* 1);
    newObject->id = object->id;
    newObject->name = duplicateString(object->name);
    newObject->hpMax = object->hpMax;
    newObject->shield = object->shield;
    newObject->damage = object->damage;
    newObject->piercingShot = object->piercingShot;
    newObject->spectralShot = object->spectralShot;
    newObject->flight = object->flight;
    newObject->suivant = object->suivant;
    
    return newObject;
}

int addObject(ListeObjects* listeObjects, Object* newObject) {
    Object* courant = listeObjects->premier;
    int index = 1; //formera l'id du nouvel object

    if(courant == NULL) { // liste vide
        newObject->id = index;
        listeObjects->premier = duplicateObject(newObject);
        return index;
    }

    while(courant != NULL) { // ajout a la fin de liste
        index += 1;
        if(courant->suivant == NULL) {
            newObject->id = index;
            courant->suivant = duplicateObject(newObject);
            return index;
        }
        courant = courant->suivant;
    }

    return 0;
}

Object* createObject(char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight) {
    Object* o = malloc(sizeof(Object) * 1);
    
    // verification des entrees
    if(strcmp("", name) == 0) { //nom par défaut
        name = duplicateString("object");
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

void modifyObject(ListeObjects* liste, int id, Object* newObject) {
    Object* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // modifier premier element
        toDelete = liste->premier;
        newObject->suivant = liste->premier->suivant;
        liste->premier = newObject;
        freeObject(toDelete);
        rangerListeObjects(liste);
        return;
    }

    Object* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // modifier
            toDelete = courant->suivant;
            newObject->suivant = courant->suivant->suivant;
            courant->suivant = newObject;
            freeObject(toDelete);
            rangerListeObjects(liste);
            return;
        }
        
        courant = courant->suivant;
    }
}

void rangerListeObjects(ListeObjects* liste) {
    int count = 1;
    Object* courant = liste->premier;
    while(courant != NULL) {
        courant->id = count;
        count += 1;
        courant = courant->suivant;
    }
}

void removeObject(ListeObjects* liste, int id) {
    Object* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // supprimer premier element
        toDelete = liste->premier;
        liste->premier = liste->premier->suivant;
        freeObject(toDelete);
        rangerListeObjects(liste);
        return;
    }

    Object* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->suivant != NULL && courant->suivant->id == id) { // suppression
            toDelete = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            freeObject(toDelete);
            rangerListeObjects(liste);
            return;
        }
        
        courant = courant->suivant;
    }

}

Object* getObjectById(ListeObjects* liste, int id) {
    Object* result = liste->premier;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->suivant;
    }

    return NULL;
}

void freeListeObjects(ListeObjects* liste) {
    Object* courant = liste->premier;
    Object* suivant;

    while(courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

ListeObjects* createListeObjects() {
    ListeObjects* liste = malloc(sizeof(ListeObjects) * 1);
    return liste;   
}

void freeObject(Object* object) {
    free(object);
}


/**
 * @file objects.c
 * @author TheGreat-Chain
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

#include "include/objects.h"
#include "include/mystring.h"

int getNumberObjects(Object* head) {
    if(head == NULL) { 
        return 0;
    }

    if(head->id != 1) { // pas le premier objet
        return -1;
    }

    int count = 0;
    while(head != NULL) {
        count += 1;
<<<<<<< HEAD
        courant = courant->next;
=======
        head = head->next;
>>>>>>> menu-crud-items
    }

    return count;
}

void displayObject(Object* object) {
    if(object == NULL) {
        printf("Pas d'object\n");
        return;
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
}

void displayAllObjects(Object* head) {
    while(head != NULL) {  
        displayObject(head);
        head = head->next;
    }
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
    newObject->next = object->next;

    free(object);
    return newObject;
}

int addObject(Object* head, Object* newObject) {
    Object* current = head;
    //int count = 1;

    if(head == NULL || head->id != 1) { // fail if null or not first
        return 0; 
    }

    while(current->next != NULL) { // aller a la fin de liste
        current = current->next;
    }

    current->next = duplicateObject(newObject);
    arrangeObjectsIds(head);
    return 1; // success
}

Object* createObject(int id, char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight) {
    Object* o = malloc(sizeof(Object) * 1);
    
    // verification des entrees
    if(strcmp("", name) == 0) { //nom par défaut
        name = duplicateString("object");
    }
    piercingShot = (piercingShot == 0) ? 0 : 1;
    spectralShot = (spectralShot == 0) ? 0 : 1;
    flight = (flight == 0) ? 0 : 1;

    // allocation 
    o->id = id;
    o->name = duplicateString(name);
    o->hpMax = hpMax;
    o->shield = shield;
    o->damage = damage;
    o->piercingShot = piercingShot;
    o->spectralShot = spectralShot;
    o->flight = flight;
    o->next = NULL;

    return o;
}

int arrangeObjectsIds(Object* head) {
    if(head == NULL || head->id != 1) {
        return 0;
    }

    int count = 1;
    while(head != NULL) {
        head->id = count;
        count += 1;
        head = head->next;
    }

    return 1;
}


void removeObject(Object** ptr_head, int id) {
    Object* tmp = *ptr_head;
    Object* previous;

    if(tmp != NULL && tmp->id == id) { // supprimer premier element
        tmp->next->id = 1; // the second object becomes the first
        *ptr_head = tmp->next;
        free(tmp);
        arrangeObjectsIds(*ptr_head);
        return;
    }

    while(tmp != NULL && tmp->id != id) { // aller jusqu'à l'objet à delete
        previous = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL) { // id non présent
        return;
    }

    previous->next = tmp->next;
    arrangeObjectsIds(*ptr_head);
}

Object* getObjectById(Object* head, int id) {
    Object* result = head;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->next;
    }

    return NULL;
}

int freeAllObjects(Object* head) {
    if(head == NULL || head->id != 1) { // pas le premier objet
        return 0;
    }

    Object* next;
    while(head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }

    return 1;
}
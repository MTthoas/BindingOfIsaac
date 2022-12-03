#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/mystring.h"
#include "../include/objects.h"

void test_createObject(); // OK
void test_displayObject(); // OK
void test_duplicateObject(); // OK
void test_addObject(); // OK
void test_displayAllObjects();//OK
void test_getNumberObjects(); //OK
void test_arrangeObjectsIds(); // not tested but OK
void test_removeObject(); //OK
void test_getObjectById(); //ok
void test_freeAllObjects(); //ok
void test_getRandomObject(); //ok 

int main(void) {
    //test_displayAllObjects();
    //test_createObject();
    //test_displayObject();
    ///test_duplicateObject();
    //test_addObject();
    //test_getNumberObjects();
    //test_freeAllObjects();
    //test_removeObject();
    //test_getObjectById();

    //test_getRandomObject();

    return 0;
}

void test_getRandomObject() {
    printf("[TEST] getObjectById()\n\n");
    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));
    addObject(head, createObject(678, "item4", 0, 0, 0, 0, 0, 1));
    addObject(head, createObject(678, "item5", 0, 0, 0, 0, 0, 1));
    addObject(head, createObject(678, "item6", 0, 0, 0, 0, 0, 1));

    displayObject(getRandomObject(head));
}

void test_getObjectById() {
    printf("[TEST] getObjectById()\n\n");
    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));

    printf("Attendu : item2\nResultat : %s\n", getObjectById(head, 2)->name);
    printf("Attendu : item3\nResultat : %s\n", getObjectById(head, 3)->name);

}

void test_freeAllObjects() {
    printf("[TEST] freeAllObjects()\n\n");
    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));

    freeAllObjects(head);
    printf("Should give random numbers (or crash) :) \n");
    printf("%d %d %d\n", head->id, head->next->id, head->next->next->id);
}

void test_removeObject() {
    printf("[TEST] removeObject()\n\n");
    printf("Inital list : \n");
    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));
    displayAllObjects(head);

    printf("\nTEST 1 - Remove first object\n");
    removeObject(&head, 1);
    displayAllObjects(head);

    freeAllObjects(head);
    head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));

    printf("\nTEST 2 - Remove object in the middle\n");
    removeObject(&head, 2);
    displayAllObjects(head);

    freeAllObjects(head);
    head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));

    printf("\nTEST 3 - Remove last object \n");
    removeObject(&head, 3);
    displayAllObjects(head);

    freeAllObjects(head);
}

void test_getNumberObjects() {
    printf("[TEST] displayAllObjects()\n\n");
    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    addObject(head, createObject(678, "item2", -2, 0, 0, 1, 0, 0));
    addObject(head, createObject(678, "item3", 0, 0, 0, 0, 0, 1));

    printf("TEST 1 - Liste avec 3 objets : \n");
    displayAllObjects(head);

    printf("Nombre d'objets.\nAttendu : 3\nRésultat : %d\n", getNumberObjects(head));

    printf("\nTEST 2 - Liste vide : \n");
    printf("Nombre d'objets.\nAttendu : 0\nRésultat : %d\n", getNumberObjects(NULL));

    printf("\nTEST 3 - Donner un objet de la liste mais pas le premier: \n");
    printf("Nombre d'objets.\nAttendu : -1\nRésultat : %d\n", getNumberObjects(head->next));

}

void test_displayAllObjects() {
    printf("[TEST] displayAllObjects()\n\n");

    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    Object* o2  = createObject(2, "item2", -2, 0, 0, 1, 0, 0);
    Object* o3  = createObject(3, "item3", 2, 1, 0, 0, 1, 0);

    head->next = o2;
    o2->next = o3;
    printf("TEST 1 - Affichage d'une chaîne d'objet à  partir du 1e objet\n");
    displayAllObjects(head);
    printf("TEST 2 - Affichage d'une chaîne d'objet à  partir du 2e objet\n");
    free(head);
    displayAllObjects(o2);
    printf("TEST 3 - Affichage d'une chaîne d'objet à partir de NULL\n");
    free(NULL);
    
    free(o2);
    free(o3);
}

void test_addObject() {
    printf("[TEST] addObject()\n\n");

    Object* head = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    Object* o = createObject(7, "item2", 2, -1.02, 0, 1, 1, 0);
    addObject(head, o);

    printf("TEST 1 - Ajout d'un objet en donnant head\n");
    displayAllObjects(head);

    printf("TEST 2 - Ajout d'un objet en donnant un objet de la liste\n");
    Object* o2  = createObject(-1, "item3", 2, 1, 0, 0, 1, 0);
    printf("\nAttendu : 0\nResultat : %d\n\n", addObject(o, o2));
    
    printf("TEST 3 - Ajout d'un troisième objet en donnant head\n");
    printf("\nAttendu : 1\nResultat : %d\n", addObject(head, o2));
    arrangeObjectsIds(head);
    printf("\nAttendu : 1, 2, 3\nResultat : %d, %d, %d\n", head->id, head->next->id, head->next->next->id);
}

void test_duplicateObject() {
    printf("[TEST] duplicateObject()\n");
    Object* item = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    Object* copied = duplicateObject(item);

    printf("Objet original : \n");
    displayObject(item);
    printf("Objet copié : \n");
    displayObject(copied);

}
void test_createObject() {
    printf("[TEST] createObject()\n");

    Object* item = createObject(1, "item", 0, 0, 0, 1, 0, 0);
    printf("Attendu : 1\nResultat : %d\n\n", item->id);
    printf("Attendu : item\nResultat : %s\n\n", item->name);
    printf("Attendu : 0.0000\nResultat : %f\n\n", item->hpMax);
    printf("Attendu : 0.0000\nResultat : %f\n\n", item->shield);
    printf("Attendu : 0.0000\nResultat : %f\n\n", item->damage);
    printf("Attendu : 1\nResultat : %d\n\n", item->piercingShot);
    printf("Attendu : 0\nResultat : %d\n\n", item->spectralShot);
    printf("Attendu : 0\nResultat : %d\n\n", item->flight);

}

void test_displayObject() {
    printf("[TEST] displayObject()\n");

    Object* item = createObject(1, "item", 0, -2, 0, 1, 0, 0);
    printf("Affichage : \n");
    displayObject(item);
}


/*
 COMMENTEES POUR EVITER LES APPARITIONS MULTIPLES :

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

 void freeObject(Object* object) {
    free(object);
}

 ListeObjects* createListeObjects() {
    ListeObjects* liste = malloc(sizeof(ListeObjects) * 1);
    return liste;   
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

void* displayObject(Object* object) {
    if(object == NULL) {
        printf("Pas d'object\n");
        return NULL;
    }

    //printf("[WARN] Utilisation de displayObject(). \nSi les champs ne sont pas remplis, erreur de segmentation possible.\n");
    
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

void rangerListeObjects(ListeObjects* liste) {
    int count = 1;
    Object* courant = liste->premier;
    while(courant != NULL) {
        courant->id = count;
        count += 1;
        courant = courant->suivant;
    }
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
*/
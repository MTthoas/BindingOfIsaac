#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/mystring.h"
#include "../include/objects.h"

void test_displayObject(); // ok
void test_duplicateObject(); //ok
void test_displayListeObjects(); // ok
void test_addObject(); //ok
void test_createObject(); // ok
void test_freeObject(); // ok
void test_createListeObjects(); //ok
void test_freeListeObject(); //ok
void test_getObjectById(); //ok
void test_rangerListeObjects(); //ok
void test_removeObject(); // ok
void test_modifyObject(); //ok

void test_getTailleListe();


int main(void) {
    //test_displayObject();
    //test_displayListeObjects();
    //test_duplicateObject();
    //test_addObject();
    //test_createObject();
    //test_freeObject();
    //test_createListeObjects(); 
    //test_freeListeObject();
    //test_getObjectById();
    //test_rangerListeObjects();
    // test_removeObject();
    //test_modifyObject();
    test_getTailleListe();

    return 0;
}

void test_getTailleListe() {
    printf("[TEST] getTailleListe() \n\n");

    //initialisation
    ListeObjects* l = createListeObjects();
    Object* o = createObject("Epee", 0, 0, 0, 0, 1, 0);
    Object* o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    Object* o3 = createObject("Epee3", 0, 0, 0, 0, 1, 0);
    addObject(l, o);
    addObject(l, o2);
    addObject(l, o3);

    // tests
    int res = getTailleListeObjects(l);
    printf("Attendu : 3\nRésultat : %d\n\n", res);

    removeObject(l, 2);
    res = getTailleListeObjects(l);
    printf("Attendu : 2\nRésultat : %d\n\n", res);

    removeObject(l, 1);
    removeObject(l, 1);
    res = getTailleListeObjects(l);
    printf("Attendu : 0\nRésultat : %d\n\n", res);

    free(l);
}


void test_modifyObject() {
    printf("[TEST] modifyObject() :\n\n");

    //initialisation
    ListeObjects* l = createListeObjects();
    Object* o = createObject("Epee", 0, 0, 0, 0, 1, 0);
    Object* o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    Object* o3 = createObject("Epee3", 0, 0, 0, 0, 1, 0);
    addObject(l, o);
    addObject(l, o2);
    addObject(l, o3);

    //tests
    printf("Liste avant modification :\n");
    displayListeObjects(l);

    printf("TEST 1 - Modification du 1e object de la liste :\n\n");
    Object* newObject = createObject("LanceFlamme", 0, 0, 0, 0, 1, 0);
    modifyObject(l, 1, newObject);
    printf("Attendu : Epee devient LanceFlamme\n");
    printf("Résultat : ");
    displayListeObjects(l);

    printf("TEST 2 - Modification d'un object en plein dans la liste :\n\n");
    newObject = createObject("Bombe", 0, 0, 7, 0, 1, 0);
    modifyObject(l, 2, newObject);
    printf("Attendu : Epee2 devient Bombe, damage = 7\n");
    printf("Résultat : ");
    displayListeObjects(l);

    printf("TEST 3 - Modification d'un object pas dans la liste :\n\n");
    newObject = createObject("Bombe", 0, 0, 7, 0, 1, 0);
    modifyObject(l, 78, newObject);
    printf("Attendu : Aucun changement\n");
    printf("Résultat : ");
    displayListeObjects(l);
}


void test_rangerListeObjects() {
    printf("[TEST] rangerListeObjects() :\n\n");

    // initialisation
    Object o1, o2;
    ListeObjects liste;
    liste.premier = &o1;

    // remplissage
    o1.id = 99;
    o1.name = "Un object";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;
    o1.next = &o2;

    o2.id = 99;
    o2.name = "PC";
    o2.hpMax = 100;
    o2.shield = 20;
    o2.damage = 30;
    o2.piercingShot = 1;
    o2.spectralShot = 0;
    o2.flight = 0;
    o2.next = NULL;

    // tests
    printf("Affichage de la liste avant arrangement : \n");
    displayListeObjects(&liste);
    printf("Arrangement :\n\n");
    rangerListeObjects(&liste);
    printf("Attendu : id de 1 à 2\n");
    printf("Résultat :");
    displayListeObjects(&liste);
    

}

void test_removeObject() {
    printf("[TEST] removeObject() :\n\n");
    
    ListeObjects* l = createListeObjects();
    Object* o = createObject("Epee", 0, 0, 0, 0, 1, 0);
    Object* o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    Object* o3 = createObject("Epee3", 0, 0, 0, 0, 1, 0);
    addObject(l, o);
    addObject(l, o2);
    addObject(l, o3);

    printf("Liste avant suppression : \n");
    displayListeObjects(l);

    printf("TEST 1 - Suppression d'un élément en plein dans la liste.\n");
    removeObject(l, 2);
    printf("Attendu : liste sans 'epee2' ET identifiants de 1 à 2.\n");
    printf("Resultat : ");
    displayListeObjects(l);

    printf("TEST 2 - Suppression du premier élément de la liste.\n");
    o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    addObject(l,o2);
    removeObject(l, 1);
    printf("Attendu : liste sans 'epee' ET identifiants de 1 à 2.\n");
    printf("Resultat : ");
    displayListeObjects(l);

    printf("TEST 3 - Suppression du dernier élément de la liste.\n");
    o3 = createObject("Epee3", 0, 0, 0, 0, 1, 0);
    addObject(l,o3);
    removeObject(l, 3);
    printf("Attendu : liste sans 'epee3' ET identifiants de 1 à 2.\n");
    printf("Resultat : ");
    displayListeObjects(l);

    printf("TEST 4 - Suppression d'un élément dont l'id n'est pas dans la liste.\n");
    o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    addObject(l,o2);
    removeObject(l, 1000);
    printf("Attendu : liste avec 3 objects, id de 1 à 3\n");
    printf("Resultat : ");
    displayListeObjects(l);
}



void test_getObjectById() {
    printf("[TEST] getObjectById() :\n\n");

    ListeObjects* l = createListeObjects();
    Object* o = createObject("Epee", 0, 0, 0, 0, 1, 0);
    Object* o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    addObject(l, o);
    addObject(l, o2);

    printf("Attendu : Object id : 1 \n"),
    printf("Resultat : ");
    displayObject(getObjectById(l, 1));

    printf("Attendu : Object id:2 \n"),
    printf("Resultat : ");
    displayObject(getObjectById(l, 2));

    printf("Attendu : Pas d'object \n"),
    printf("Resultat : ");
    displayObject(getObjectById(l, 0));

    printf("Attendu : Pas d'object \n"),
    printf("Resultat : ");
    displayObject(getObjectById(l, 3));

}

void test_freeListeObject() {
    printf("[TEST] freeListeObject() :\n\n");

    ListeObjects* l = createListeObjects();
    Object* o = createObject("Epee", 0, 0, 0, 0, 1, 0);
    Object* o2 = createObject("Epee2", 0, 0, 0, 0, 1, 0);
    addObject(l, o);
    addObject(l, o2);

    printf("Affichage de la liste : \n");
    printf("Attendu : Affichage de 2 objects\n");
    printf("Résultat : ");
    displayListeObjects(l);

    printf("Désallocation : \n");
    freeListeObjects(l);

    printf("Affichage de la liste : \n");
    printf("Attendu : Erreur de segmentation\n");
    printf("Résultat : ");
    displayListeObjects(l);
}



void test_createListeObjects() {
    printf("[TEST] createListeObject() :\n\n");
    
    ListeObjects* l = createListeObjects();
    printf("Affichage de la liste \n");
    printf("Attendu : (rien car liste vide)\n");
    printf("Résultat : ");
    displayListeObjects(l);

    printf("Ajout d'un object dans la liste\n");
    Object* o = createObject("Epee", 0, 0, 0, 0, 1, 0);
    addObject(l, o);
    printf("Attendu : Affichage d'un object\n");
    printf("Résultat : ");
    displayListeObjects(l);

    printf("Ajout d'un deuxième object dans la liste\n");
    addObject(l, o);
    printf("Attendu : Affichage de 2 objects \n");
    printf("Résultat : ");
    displayListeObjects(l);
}

void test_freeObject() {
    printf("[TEST] freeObject() :\n\n");

    Object* o = createObject("mon object", 10, 0, 0, 0, 0, 0);
    printf("Affichage de l'object : \n");
    displayObject(o);

    printf("Désaloccation : \n");
    freeObject(o);

    printf("Affichage après désallocation (erreur de segmentation attendue) : \n");
    displayObject(o);
}

void test_createObject() {
    printf("[TEST] createObject() :\n\n");

    Object* o1 = createObject("<3", 1, 0, 0, 0, 0, 0);
    printf("Attendu : 'nom' : '<3', 'hpMax' : '1'. Le reste à 0.\n");
    printf("Résultat :\n");
    displayObject(o1);

    Object* o2 = createObject("yo", 0, 2.1, 0, -2, 0, -1);
    printf("Attendu : 'name' : 'yo', 'shield' : '2.1', 'piercingShot : '1', 'flight' : '1'. Le reste à 0.\n");
    printf("Résultat :\n");
    displayObject(o2);

    Object* o3 = createObject("", 0, 0, 0, 0, 0, 0);
    printf("Attendu : 'nom' : 'object'.\n");
    printf("Résultat :\n");
    displayObject(o3);

}

void test_addObject() {
    printf("[TEST] addObject() :\n\n");

    // initialisation
    Object o1, o2;
    ListeObjects liste;
    liste.premier = NULL;

    // remplissage
    o1.id = 99;
    o1.name = "Un object";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;
    o1.next = NULL;

    o2.id = 99;
    o2.name = "PC";
    o2.hpMax = 100;
    o2.shield = 20;
    o2.damage = 30;
    o2.piercingShot = 1;
    o2.spectralShot = 0;
    o2.flight = 0;
    o2.next = NULL;

    // appel fonction
    int res;
    printf("Liste vide : []\n");
    displayListeObjects(&liste);

    printf("Après 1 ajout : \n");
    res = addObject(&liste, &o1);
    displayListeObjects(&liste);
    printf("Attendu : 1\nRésultat : %d\n\n", res);

    printf("Après 2 ajouts : \n");
    res = addObject(&liste, &o2);
    displayListeObjects(&liste);
    printf("Attendu : 2\nRésultat : %d\n\n", res); 

    printf("Après 3 ajouts : \n");
    res = addObject(&liste, duplicateObject(&o1));
    displayListeObjects(&liste);
    printf("Attendu : 3\nRésultat : %d\n\n", res);

}



void test_displayListeObjects() {
    printf("[TEST] displayListeObjects() :\n\n");

    // initialisation
    Object o1, o2, o3;
    ListeObjects liste;
    liste.premier = &o1;

    // maillage
    o1.next = &o2;
    o2.next = &o3;
    o3.next = NULL;

    // remplissage
    o1.id = 1;
    o1.name = "Un object";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;

    o2.id = 2;
    o2.name = "PC";
    o2.hpMax = 100;
    o2.shield = 20;
    o2.damage = 30;
    o2.piercingShot = 1;
    o2.spectralShot = 0;
    o2.flight = 0;

    o3.id = 3;
    o3.name = "Livre";
    o3.hpMax = 100;
    o3.shield = 20;
    o3.damage = 30;
    o3.piercingShot = 1;
    o3.spectralShot = 0;
    o3.flight = 0;

    // appel de la fonction
    displayListeObjects(&liste);
}

void test_duplicateObject() {
    printf("[TEST] duplicateObject() :\n\n");

    Object o1;
    o1.id = 1;
    o1.name = "Un object";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;

    Object* o1copy = duplicateObject(&o1);
    printf("Object 1 : \n");
    displayObject(&o1);
    printf("\nCopie Object 1 : \n");
    displayObject(o1copy);

    Object* o2copy = duplicateObject(NULL);
    printf("Object 2 (NULL) : \n");
    displayObject(NULL);
    printf("\nCopie Object 2 : \n");
    displayObject(o2copy);
    
}

void test_displayObject() {
    printf("[TEST] displayObject() :\n\n");
    Object o;
    o.id = 1;
    o.name = "Mon object";
    o.hpMax = 100;
    o.shield = 100;
    o.damage = 0;
    o.piercingShot = 1;
    o.spectralShot = 0;
    o.flight = 0;

    Object o2;
    o2.id=2;
    o2.name = "";

    Object o3;

    displayObject(&o); 
    displayObject(&o2);
    displayObject(&o3);
}

/*
 COMMENTEES POUR EVITER LES APPARITIONS MULTIPLES :

 void modifyObject(ListeObjects* liste, int id, Object* newObject) {
    Object* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // modifier premier element
        toDelete = liste->premier;
        newObject->next = liste->premier->next;
        liste->premier = newObject;
        freeObject(toDelete);
        rangerListeObjects(liste);
        return;
    }

    Object* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->next != NULL && courant->next->id == id) { // modifier
            toDelete = courant->next;
            newObject->next = courant->next->next;
            courant->next = newObject;
            freeObject(toDelete);
            rangerListeObjects(liste);
            return;
        }
        
        courant = courant->next;
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
    o->next = NULL;

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
        if(courant->next == NULL) {
            newObject->id = index;
            courant->next = duplicateObject(newObject);
            return index;
        }
        courant = courant->next;
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
        courant = courant->next;
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
    newObject->next = object->next;
    
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
        courant = courant->next;
    }

    return count;
}

void rangerListeObjects(ListeObjects* liste) {
    int count = 1;
    Object* courant = liste->premier;
    while(courant != NULL) {
        courant->id = count;
        count += 1;
        courant = courant->next;
    }
}

void freeListeObjects(ListeObjects* liste) {
    Object* courant = liste->premier;
    Object* next;

    while(courant != NULL) {
        next = courant->next;
        free(courant);
        courant = next;
    }
}

void removeObject(ListeObjects* liste, int id) {
    Object* toDelete;
    if(liste->premier != NULL && liste->premier->id == id) { // supprimer premier element
        toDelete = liste->premier;
        liste->premier = liste->premier->next;
        freeObject(toDelete);
        rangerListeObjects(liste);
        return;
    }

    Object* courant = liste->premier;
    while(courant != NULL ) {

        if(courant->next != NULL && courant->next->id == id) { // suppression
            toDelete = courant->next;
            courant->next = courant->next->next;
            freeObject(toDelete);
            rangerListeObjects(liste);
            return;
        }
        
        courant = courant->next;
    }

}

Object* getObjectById(ListeObjects* liste, int id) {
    Object* result = liste->premier;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->next;
    }

    return NULL;
}
*/
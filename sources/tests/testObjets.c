#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/mystring.h"
#include "../include/objets.h"

void test_displayObjet(); // ok
void test_duplicateObjet(); //ok
void test_displayListeObjets(); // ok
void test_addObjet(); //ok
void test_createObjet(); // ok

void test_freeObjet();

int main(void) {
    //test_displayObjet();
    //test_displayListeObjets();
    //test_duplicateObjet();
    //test_addObjet();
    //test_createObjet();

    //test_freeObjet();
    
    //test_createListeObjet();
    //test_freeListeObjet();
    //test_removeObjet();
    //test_getObjetById();
    //test_modifyObjet();
    
    return 0;
}

void test_createObjet() {
    printf("[TEST] createObjet() :\n\n");

    Objet* o1 = createObjet(0, "<3", 1, 0, 0, 0, 0, 0);
    printf("Attendu : 'nom' : '<3', 'hpMax' : '1'. Le reste à 0.\n");
    printf("Résultat :\n");
    displayObjet(o1);

    Objet* o2 = createObjet(0, "yo", 0, 2.1, 0, -2, 0, -1);
    printf("Attendu : 'name' : 'yo', 'shield' : '2.1', 'piercingShot : '1', 'flight' : '1'. Le reste à 0.\n");
    printf("Résultat :\n");
    displayObjet(o2);

    Objet* o3 = createObjet(0, "", 0, 0, 0, 0, 0, 0);
    printf("Attendu : 'nom' : 'objet'.\n");
    printf("Résultat :\n");
    displayObjet(o3);

}

Objet* createObjet(int id, char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight) {
    Objet* o = malloc(sizeof(Objet) * 1);
    
    // verification des entrees
    if(strcmp("", name) == 0) { //nom par défaut
        name = duplicateString("objet");
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
    o->suivant = NULL;

    return o;
}

void test_addObjet() {
    printf("[TEST] addObjet() :\n\n");

    // initialisation
    Objet o1, o2;
    ListeObjets liste;
    liste.premier = NULL;

    // remplissage
    o1.id = 99;
    o1.name = "Un objet";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;
    o1.suivant = NULL;

    o2.id = 99;
    o2.name = "PC";
    o2.hpMax = 100;
    o2.shield = 20;
    o2.damage = 30;
    o2.piercingShot = 1;
    o2.spectralShot = 0;
    o2.flight = 0;
    o2.suivant = NULL;

    // appel fonction
    int res;
    printf("Liste vide : []\n");
    displayListeObjets(&liste);

    printf("Après 1 ajout : \n");
    res = addObjet(&liste, &o1);
    displayListeObjets(&liste);
    printf("Attendu : 1\nRésultat : %d\n\n", res);

    printf("Après 2 ajouts : \n");
    res = addObjet(&liste, &o2);
    displayListeObjets(&liste);
    printf("Attendu : 2\nRésultat : %d\n\n", res); 

    printf("Après 3 ajouts : \n");
    res = addObjet(&liste, duplicateObjet(&o1));
    displayListeObjets(&liste);
    printf("Attendu : 3\nRésultat : %d\n\n", res);

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

void test_displayListeObjets() {
    printf("[TEST] displayListeObjets() :\n\n");

    // initialisation
    Objet o1, o2, o3;
    ListeObjets liste;
    liste.premier = &o1;

    // maillage
    o1.suivant = &o2;
    o2.suivant = &o3;
    o3.suivant = NULL;

    // remplissage
    o1.id = 1;
    o1.name = "Un objet";
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
    displayListeObjets(&liste);
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


void test_duplicateObjet() {
    printf("[TEST] duplicateObjet() :\n\n");

    Objet o1;
    o1.id = 1;
    o1.name = "Un objet";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;

    Objet* o1copy = duplicateObjet(&o1);
    printf("Objet 1 : \n");
    displayObjet(&o1);
    printf("\nCopie Objet 1 : \n");
    displayObjet(o1copy);

    Objet* o2copy = duplicateObjet(NULL);
    printf("Objet 2 (NULL) : \n");
    displayObjet(NULL);
    printf("\nCopie Objet 2 : \n");
    displayObjet(o2copy);
    
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

void test_displayObjet() {
    printf("[TEST] displayObjet() :\n\n");
    Objet o;
    o.id = 1;
    o.name = "Mon objet";
    o.hpMax = 100;
    o.shield = 100;
    o.damage = 0;
    o.piercingShot = 1;
    o.spectralShot = 0;
    o.flight = 0;

    Objet o2;
    o2.id=2;
    o2.name = "";

    Objet o3;

    displayObjet(&o); 
    displayObjet(&o2);
    displayObjet(&o3);
}

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
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
void test_freeObjet(); // ok
void test_createListeObjets(); //ok
void test_freeListeObjet(); //ok
void test_getObjetById(); //ok
void test_rangerListeObjets(); //ok
void test_removeObjet(); // ok
void test_modifyObjet(); //ok


int main(void) {
    //test_displayObjet();
    //test_displayListeObjets();
    //test_duplicateObjet();
    //test_addObjet();
    //test_createObjet();
    //test_freeObjet();
    //test_createListeObjets(); 
    //test_freeListeObjet();
    //test_getObjetById();
    //test_rangerListeObjets();
    // test_removeObjet();
    //test_modifyObjet();
    
    return 0;
}

void test_modifyObjet() {
    printf("[TEST] modifyObjet() :\n\n");

    //initialisation
    ListeObjets* l = createListeObjets();
    Objet* o = createObjet(1, "Epee", 0, 0, 0, 0, 1, 0);
    Objet* o2 = createObjet(9, "Epee2", 0, 0, 0, 0, 1, 0);
    Objet* o3 = createObjet(9, "Epee3", 0, 0, 0, 0, 1, 0);
    addObjet(l, o);
    addObjet(l, o2);
    addObjet(l, o3);

    //tests
    printf("Liste avant modification :\n");
    displayListeObjets(l);

    printf("TEST 1 - Modification du 1e objet de la liste :\n\n");
    Objet* newObjet = createObjet(89, "LanceFlamme", 0, 0, 0, 0, 1, 0);
    modifyObjet(l, 1, newObjet);
    printf("Attendu : Epee devient LanceFlamme\n");
    printf("Résultat : ");
    displayListeObjets(l);

    printf("TEST 2 - Modification d'un objet en plein dans la liste :\n\n");
    newObjet = createObjet(89, "Bombe", 0, 0, 7, 0, 1, 0);
    modifyObjet(l, 2, newObjet);
    printf("Attendu : Epee2 devient Bombe, damage = 7\n");
    printf("Résultat : ");
    displayListeObjets(l);

    printf("TEST 3 - Modification d'un objet pas dans la liste :\n\n");
    newObjet = createObjet(89, "Bombe", 0, 0, 7, 0, 1, 0);
    modifyObjet(l, 78, newObjet);
    printf("Attendu : Aucun changement\n");
    printf("Résultat : ");
    displayListeObjets(l);
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


void test_rangerListeObjets() {
    printf("[TEST] rangerListeObjets() :\n\n");

    // initialisation
    Objet o1, o2;
    ListeObjets liste;
    liste.premier = &o1;

    // remplissage
    o1.id = 99;
    o1.name = "Un objet";
    o1.hpMax = 100;
    o1.shield = 20;
    o1.damage = 30;
    o1.piercingShot = 1;
    o1.spectralShot = 0;
    o1.flight = 0;
    o1.suivant = &o2;

    o2.id = 99;
    o2.name = "PC";
    o2.hpMax = 100;
    o2.shield = 20;
    o2.damage = 30;
    o2.piercingShot = 1;
    o2.spectralShot = 0;
    o2.flight = 0;
    o2.suivant = NULL;

    // tests
    printf("Affichage de la liste avant arrangement : \n");
    displayListeObjets(&liste);
    printf("Arrangement :\n\n");
    rangerListeObjets(&liste);
    printf("Attendu : id de 1 à 2\n");
    printf("Résultat :");
    displayListeObjets(&liste);
    

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

void test_removeObjet() {
    printf("[TEST] removeObjet() :\n\n");
    
    ListeObjets* l = createListeObjets();
    Objet* o = createObjet(1, "Epee", 0, 0, 0, 0, 1, 0);
    Objet* o2 = createObjet(9, "Epee2", 0, 0, 0, 0, 1, 0);
    Objet* o3 = createObjet(9, "Epee3", 0, 0, 0, 0, 1, 0);
    addObjet(l, o);
    addObjet(l, o2);
    addObjet(l, o3);

    printf("Liste avant suppression : \n");
    displayListeObjets(l);

    printf("TEST 1 - Suppression d'un élément en plein dans la liste.\n");
    removeObjet(l, 2);
    printf("Attendu : liste sans 'epee2' ET identifiants de 1 à 2.\n");
    printf("Resultat : ");
    displayListeObjets(l);

    printf("TEST 2 - Suppression du premier élément de la liste.\n");
    o2 = createObjet(9, "Epee2", 0, 0, 0, 0, 1, 0);
    addObjet(l,o2);
    removeObjet(l, 1);
    printf("Attendu : liste sans 'epee' ET identifiants de 1 à 2.\n");
    printf("Resultat : ");
    displayListeObjets(l);

    printf("TEST 3 - Suppression du dernier élément de la liste.\n");
    o3 = createObjet(9, "Epee3", 0, 0, 0, 0, 1, 0);
    addObjet(l,o3);
    removeObjet(l, 3);
    printf("Attendu : liste sans 'epee3' ET identifiants de 1 à 2.\n");
    printf("Resultat : ");
    displayListeObjets(l);

    printf("TEST 4 - Suppression d'un élément dont l'id n'est pas dans la liste.\n");
    o2 = createObjet(9, "Epee2", 0, 0, 0, 0, 1, 0);
    addObjet(l,o2);
    removeObjet(l, 1000);
    printf("Attendu : liste avec 3 objets, id de 1 à 3\n");
    printf("Resultat : ");
    displayListeObjets(l);
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

void test_getObjetById() {
    printf("[TEST] getObjetById() :\n\n");

    ListeObjets* l = createListeObjets();
    Objet* o = createObjet(1, "Epee", 0, 0, 0, 0, 1, 0);
    Objet* o2 = createObjet(9, "Epee2", 0, 0, 0, 0, 1, 0);
    addObjet(l, o);
    addObjet(l, o2);

    printf("Attendu : Objet id : 1 \n"),
    printf("Resultat : ");
    displayObjet(getObjetById(l, 1));

    printf("Attendu : Objet id:2 \n"),
    printf("Resultat : ");
    displayObjet(getObjetById(l, 2));

    printf("Attendu : Pas d'objet \n"),
    printf("Resultat : ");
    displayObjet(getObjetById(l, 0));

    printf("Attendu : Pas d'objet \n"),
    printf("Resultat : ");
    displayObjet(getObjetById(l, 3));

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

void test_freeListeObjet() {
    printf("[TEST] freeListeObjet() :\n\n");

    ListeObjets* l = createListeObjets();
    Objet* o = createObjet(1, "Epee", 0, 0, 0, 0, 1, 0);
    Objet* o2 = createObjet(9, "Epee2", 0, 0, 0, 0, 1, 0);
    addObjet(l, o);
    addObjet(l, o2);

    printf("Affichage de la liste : \n");
    printf("Attendu : Affichage de 2 objets\n");
    printf("Résultat : ");
    displayListeObjets(l);

    printf("Désallocation : \n");
    freeListeObjets(l);

    printf("Affichage de la liste : \n");
    printf("Attendu : Erreur de segmentation\n");
    printf("Résultat : ");
    displayListeObjets(l);
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

void test_createListeObjets() {
    printf("[TEST] createListeObjet() :\n\n");
    
    ListeObjets* l = createListeObjets();
    printf("Affichage de la liste \n");
    printf("Attendu : (rien car liste vide)\n");
    printf("Résultat : ");
    displayListeObjets(l);

    printf("Ajout d'un objet dans la liste\n");
    Objet* o = createObjet(1, "Epee", 0, 0, 0, 0, 1, 0);
    addObjet(l, o);
    printf("Attendu : Affichage d'un objet\n");
    printf("Résultat : ");
    displayListeObjets(l);

    printf("Ajout d'un deuxième objet dans la liste\n");
    addObjet(l, o);
    printf("Attendu : Affichage de 2 objets \n");
    printf("Résultat : ");
    displayListeObjets(l);
}

ListeObjets* createListeObjets() {
    ListeObjets* liste = malloc(sizeof(ListeObjets) * 1);
    return liste;   
}

void test_freeObjet() {
    printf("[TEST] freeObjet() :\n\n");

    Objet* o = createObjet(1, "mon objet", 10, 0, 0, 0, 0, 0);
    printf("Affichage de l'objet : \n");
    displayObjet(o);

    printf("Désaloccation : \n");
    freeObjet(o);

    printf("Affichage après désallocation (erreur de segmentation attendue) : \n");
    displayObjet(o);
}

void freeObjet(Objet* objet) {
    free(objet);
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
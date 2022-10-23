#include "headers/objets.h"
#include <stdio.h>

void displayObjet(Objet* objet) {
    printf("\n");
    printf("id : %d\n", objet->id);
    printf("name : %s\n", objet->name);
    printf("hpMax : %d\n", objet->hpMax);
    printf("shield : %d\n", objet->shield);
    printf("damage : %d\n", objet->damage);
    printf("piercingShot : %d\n", objet->piercingShot);
    printf("spectralShot : %d\n", objet->spectralShot);
    printf("flight : %d\n", objet->flight);
    printf("\n");
}
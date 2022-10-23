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
#include "include/objets.h"

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
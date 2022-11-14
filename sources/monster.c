/**
 * @file monster.c
 * @author  Nairod36
 * @brief Fonctions des mobs
 * @version 0.2
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/monster.h"
#include "include/mystring.h"
#include "Room.h"
#include "Player.h"



Monster *  spawnMonster(Donjon* d, char* name, float hpMax, int idMonster, int shoot, int flight, int ss){
    srand(time(NULL));
    int randomPositionX,randomPositionY;
    //  TODO : IL FAUT FREE LE MONSTER 
    Monster * monster1 = malloc(sizeof(Monster));
    int heightRoom = d->stages[0].rooms[0].height - 1;
    int widthRoom = d->stages[0].rooms[0].width -2;
    while (1){
        randomPositionY = 1 + rand() % (heightRoom - 1);
        randomPositionX = 2 + rand() % (widthRoom - 2);
        if (randomPositionX % 2 == 0 && d->stages[0].rooms[0].room[randomPositionY][randomPositionX] == ' ' && d->stages[0].rooms[0].room[randomPositionY][randomPositionX - 2] != 'P' && d->stages[0].rooms[0].room[randomPositionY][randomPositionX + 2] != 'P' && d->stages[0].rooms[0].room[randomPositionY - 1][randomPositionX] != 'P' && d->stages[0].rooms[0].room[randomPositionY + 1][randomPositionX] != 'P' ){
            monster1->positionX = randomPositionX;
            monster1->positionY = randomPositionY;
            monster1->idMonster = idMonster;
            monster1->name = name;
            monster1->hpMax = hpMax;
            monster1->shoot = shoot;
            monster1->flight = flight;
            monster1->ss = ss;

            break;
        }   
    } 
    d->stages[0].rooms[0].room[monster1->positionY][monster1->positionX] = 'M'; 
    return monster1;
       
}


//TODO
void monsterAttack(Monster* monster, Player* player) {
    if(monster == NULL || player == NULL) {
        return;
    }
}

int getTailleListeMonster(ListeMonster* l) {
    Monster* courant = l->premier;
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

ListeMonster* createListeMonster() {
    ListeMonster* liste = malloc(sizeof(ListeMonster) * 1);
    return liste;   
}

void freeMonster(Monster* monster) {
    free(monster);
}

void freeListeMonster(ListeMonster* liste) {
    Monster* courant = liste->premier;
    while(courant != NULL) {
        Monster* tmp = courant;
        courant = courant->suivant;
        freeMonster(tmp);
    }
    free(liste);
}

// int addMonster(ListeMonster* listeMonster, Monster* newMonster) {
//     Monster* courant = listeMonster->premier;
//     int index = 1; //formera l'id du nouveau monster

//     if(courant == NULL) { // liste vide
//         newMonster->idMonster = index;
//         listeMonster->premier = duplicateMonster(newMonster);
//         return index;
//     }

//     while(courant != NULL) { // ajout a la fin de liste
//         index += 1;
//         if(courant->suivant == NULL) {
//             newMonster->idMonster = index;
//             courant->suivant = duplicateMonster(newMonster);
//             return index;
//         }
//         courant = courant->suivant;
//     }

//     return 0;
// }

Monster* getMonsterById(ListeMonster* liste, int id) {
    Monster* result = liste->premier;

    while(result != NULL) {
        if(result->idMonster == id) {
            return result;
        }
        result = result->suivant;
    }

    return NULL;
}
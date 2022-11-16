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
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>     


#include "include/monster.h"
#include "include/mystring.h"
#include "Room.h"
#include "Player.h"


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

void spawnMonster(Donjon* d, Monster * monster){
    srand(time(NULL));
    int randomPositionX,randomPositionY;
    int heightRoom = d->stages[0].rooms[0].height - 1;
    int widthRoom = d->stages[0].rooms[0].width -2;
    while (1){
        randomPositionY = 1 + rand() % (heightRoom - 1);
        randomPositionX = 2 + rand() % (widthRoom - 2);
        if (randomPositionX % 2 == 0 && d->stages[0].rooms[0].room[randomPositionY][randomPositionX] == ' ' && d->stages[0].rooms[0].room[randomPositionY][randomPositionX - 2] != 'P' && d->stages[0].rooms[0].room[randomPositionY][randomPositionX + 2] != 'P' && d->stages[0].rooms[0].room[randomPositionY - 1][randomPositionX] != 'P' && d->stages[0].rooms[0].room[randomPositionY + 1][randomPositionX] != 'P' ){
            monster->positionX = randomPositionX;
            monster->positionY = randomPositionY;
            break;
        }   
    } // la lettre doit correspondre au monstre 
    char letterForMonster = monster->name[0];
    letterForMonster = toupper(letterForMonster);
    d->stages[0].rooms[0].room[monster->positionY][monster->positionX] = letterForMonster;        
}


//TODO
void monsterAttack(Monster* monster, Player* player) {
    if(monster == NULL || player == NULL) {
        return;
    }
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

Monster* createMonster(int idMonster, char* name, float hpMax, int shoot, int flight, int ss) {
    Monster* o = malloc(sizeof(Monster) * 1);
    
    // verification des entrees
    if(strcmp("", name) == 0) { //nom par défaut
        name = duplicateString("monster");
    }
    // allocation 
    o->idMonster = idMonster;
    o->name = duplicateString(name);
    o->hpMax = hpMax;
    o->shoot = shoot;
    o->flight = flight;
    o->ss = ss;
    o->suivant = NULL;

    return o;
}

void addMonster(struct ListeMonster *listeMonster,Monster* newMonster){
    Monster* courant = listeMonster->premier;

    if(courant == NULL) { // liste vide
       listeMonster->premier = duplicateMonster(newMonster);
    }
// ??? TODO pourquoi retour vide
        // ajout a la fin de liste
        if(courant->suivant == NULL) {
            courant->suivant = duplicateMonster(newMonster);
        }   
}

Monster* duplicateMonster(Monster* monster) {
    if(monster == NULL) {
        return NULL;
    }

    Monster* newMonster = malloc(sizeof(Monster)* 1);
    newMonster->idMonster = monster->idMonster;
    newMonster->name = duplicateString(monster->name);
    newMonster->hpMax = monster->hpMax;
    newMonster->shoot = monster->shoot;
    newMonster->flight = monster->flight;
    newMonster->ss = monster->ss;
    newMonster->suivant = monster->suivant;
    
    return newMonster;
}
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


void spawnMonster(Donjon * d, Monster * monster, int stage, int id){
    srand(time(NULL));
    int randomPositionX,randomPositionY;
    int heightRoom = d->stages[stage].rooms[id].height - 1;
    int widthRoom = d->stages[stage].rooms[id].width -2;
    while (1){
        randomPositionY = 1 + rand() % (heightRoom - 1);
        randomPositionX = 2 + rand() % (widthRoom - 2);
        if (randomPositionX % 2 == 0 && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX] == ' ' && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX - 2] != 'P' && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX + 2] != 'P' && d->stages[stage].rooms[id].room[randomPositionY - 1][randomPositionX] != 'P' && d->stages[stage].rooms[id].room[randomPositionY + 1][randomPositionX] != 'P' ){
            monster->positionX = randomPositionX;
            monster->positionY = randomPositionY;
            break;
        }   
    } // la lettre doit correspondre au monstre 
    char letterForMonster = monster->name[0];
    letterForMonster = toupper(letterForMonster);
    monster->firstLetter = letterForMonster;
    d->stages[stage].rooms[id].room[monster->positionY][monster->positionX] = letterForMonster;        
}


void monsterShoot(Monster * monster, Player * player) {

    if(monster == NULL || player == NULL) {
        return;
    }
}

void monsterFollowPlayerAndAttack(Monster * monster, Player * player) {
    while( player->positionX - 2 != monster->positionX ||player->positionX + 2 != monster->positionX || player->positionY - 1!= monster->positionY || player->positionY + 1!= monster->positionY) {
        if(player->positionX > monster->positionX) {
            monster->positionX += 2;
        } else if(player->positionX < monster->positionX) {
            monster->positionX -= 2;
        } else if(player->positionY > monster->positionY) {
            monster->positionY += 1;
        } else if(player->positionY < monster->positionY) {
            monster->positionY -= 1;
        }     
    }
    if(player->shield <= 0){
        player->hpMax -= 1;
    } else {
        player->shield -= 1;
    }
}

void monsterRandomMove(Monster * monster, Player * player) {
    if(monster == NULL || player == NULL) {
        return;
    }
}


Monster createMonster(int idMonster, char* name, float hpMax, int shoot, int flight, int ss) {

    Monster monster;
    monster.idMonster = idMonster;
    monster.name = duplicateString(name);
    monster.hpMax = hpMax;
    monster.shoot = shoot;
    monster.flight = flight;
    monster.ss = ss;

    return monster;
}

Monster * getMonsterById(Monster * arrayMonster,int id) {

    struct Monster * monster = malloc(sizeof(struct Monster)*1);
    for(int i = 0; i < 9; i++) {
        if(arrayMonster[i].idMonster == (id)) {
            *monster = arrayMonster[i];
            return monster;
        }
    }

    return NULL;
}

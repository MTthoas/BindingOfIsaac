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



void spawnMonster(Donjon* d, char idMonster){
    srand(time(NULL));
    int randomPositionX,randomPositionY;
    Monster * monster1 = malloc(sizeof(Monster));
    int heightRoom = d->stages[0].rooms[0].height - 1;
    int widthRoom = d->stages[0].rooms[0].width -2;
    while (1){
        randomPositionY = 1 + rand() % (heightRoom - 1);
        randomPositionX = 2 + rand() % (widthRoom - 2);
        if (randomPositionX % 2 == 0 && d->stages[0].rooms[0].room[randomPositionY][randomPositionX] == ' ' && d->stages[0].rooms[0].room[randomPositionY][randomPositionX - 2] != 'P' && d->stages[0].rooms[0].room[randomPositionY][randomPositionX + 2] != 'P' && d->stages[0].rooms[0].room[randomPositionY - 1][randomPositionX] != 'P' && d->stages[0].rooms[0].room[randomPositionY + 1][randomPositionX] != 'P' ){
            monster1->positionX = randomPositionX;
            monster1->positionY = randomPositionY;
            monster1->idLetter = idMonster;
            break;
        }   
    } 
    printf("positionX : %d\n", monster1->positionX);
    printf("positionY : %d\n", monster1->positionY);
    d->stages[0].rooms[0].room[monster1->positionY][monster1->positionX] = 'M'; 
    free(monster1);   
}



//TODO
void monsterAttack(Monster* monster, Player* player) {
    if(monster == NULL || player == NULL) {
        return;
    }

    float damage = monster->shoot;
    if(monster->flight == 1) {
        damage *= 1.5;
    }

    player->hpMax -= damage;
}
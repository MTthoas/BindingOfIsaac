/**
 * @file monster.h
 * @author  Nairod36
 * @brief Declaration fonctions des mobs et structures
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef MONSTER_H
#define MONSTER_H

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"


struct Monster {
    char idLetter;
    char* name;
    float hpMax;
    int idMonster;
    int shoot;
    int flight;
    int ss;
    int positionX;
    int positionY;
    };    
typedef struct Monster Monster;

void monsterAttack(Monster* monster, Player* player);
void spawnMonster(Donjon* d, char);
#endif //MONSTER_H
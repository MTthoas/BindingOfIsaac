#ifndef MONSTER_H
#define MONSTER_H

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"


struct Monster {
    int id;
    char* name;
    float hpMax;
    int shoot;
    int flight;
    int ss;
    int positionX;
    int positionY;
    };   
typedef struct Monster Monster;

void monsterAttack(Monster* monster, Player* player);
#endif //MONSTER_H
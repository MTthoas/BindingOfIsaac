#ifndef MONSTRE_H
#define MONSTRE_H

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"


struct Monstre {
    int id;
    char* name;
    float hpMax;
    int shoot;
    int flight;
    int ss;
    int positionX;
    int positionY;
    };   
typedef struct Monstre Monstre;

void monsterAttack(Monstre* monster, Player* player);
#endif //MONSTRE_H
/**
 * @file shoot.h
 * @author  Nairod36
 * @brief Declarations fonctions et structures du shoot joueur
 * @version 0.3
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef H_SHOOT
#define H_SHOOT

#include "Room.h"
#include "monster.h"
// #include "Player.h"

typedef struct Shoot {
    int positionX;
    int positionY;
    char directionView;
} Shoot;

typedef struct ShootParams {
    Donjon *d;
    Player *player;
    Monster *monster;
    Boss *boss;
    int idMonster;
    int reloadBoss;
    int reload, reloadMonster;
    int stage;
    int condition;
    int id;
    char directionView;
} ShootParams;


void* shootUp(void *shootParams);
void* shootDown(void *shootParams);
void* shootLeft(void *shootParams);
void* shootRight(void *shootParams);


#endif
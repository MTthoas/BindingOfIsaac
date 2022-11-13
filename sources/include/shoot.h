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
#include "Player.h"

struct Shoot {
    int positionX;
    int positionY;
    char directionView;
};
typedef struct Shoot Shoot;

struct ShootParams {
    Donjon *d;
    Player *player;
    int reload ;
};
typedef struct ShootParams ShootParams;


void* bangishard(void *ShootParams);

#endif
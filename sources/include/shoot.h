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
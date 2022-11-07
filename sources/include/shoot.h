#ifndef H_SHOOT
#define H_SHOOT

#include "Room.h"
#include "Player.h"

struct Shoot {
    int positionX;
    int positionY;
    char directionView;
};
typedef struct Shoot  Shoot;

void bangishard(Donjon *d,Player* player);

#endif
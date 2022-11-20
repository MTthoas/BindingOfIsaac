#ifndef H_PLAYER
#define H_PLAYER

#include "Room.h"

struct Player{
    char * name;
    int positionX;
    int positionY;
    char directionView;
    float hpMax;
    float dmg;
    int shield;
    int flight;
};
typedef struct Player  Player;

int kbhit(void);

#endif
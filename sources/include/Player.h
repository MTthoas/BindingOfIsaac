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
    float shield;
    int flight;
};
typedef struct Player  Player;

void gestionPositionPlayer(Donjon *d, Player *player, int c);
int kbhit(void);

#endif
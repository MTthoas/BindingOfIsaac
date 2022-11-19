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

void gestionPositionPlayer(struct Donjon *d,struct Player *player, int stage, int c);
int kbhit(void);

#endif
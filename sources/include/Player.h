#ifndef H_PLAYER
#define H_PLAYER

#include "Room.h"

struct Player{
    int positionX;
    int positionY;
    char directionView;
    float hpMax;
};

typedef struct Player  Player;

void gestionPositionPlayer(Donjon *d, Player *player, int c);
int kbhit(void);

#endif
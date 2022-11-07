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
// typedef struct Room Room;

int kbhit(void);
// void gestionPosition(Player * player, Room * room, int KeyboardEntry);

#endif
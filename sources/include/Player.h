#ifndef H_PLAYER
#define H_PLAYER

#include "charactersId.h"

struct Player {
    char * name;
    int positionX;
    int positionY;
    char directionView;
    
    float hpMax;
    float dmg;
    float shield;
    int ps;
    int ss;
    int flight;

    int canTakeBonusItem; // put to 0 if user loses hp
};
typedef struct Player Player;

/**
 * @brief Used to save the Player Stats outside the stage generation.
 * Given to the player at each regeneration of stage. * 
 */
struct PlayerStats {
    float hpMax;
    float dmg;
    float shield;
    int ps;
    int ss;
    int flight;
};
typedef struct PlayerStats PlayerStats;

int kbhit(void);

/**
 * @brief Initialise a playerStats structure with the beginning values;
 * @return PlayerStats* 
 */
PlayerStats* initialisePlayerStats(int idCharacter);

#endif
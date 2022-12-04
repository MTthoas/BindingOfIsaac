#ifndef H_PLAYER
#define H_PLAYER

typedef struct Player {
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
    int stageAxeX;
    int stageAxeY;

    int canTakeBonusItem; // put to 0 if user loses hp
} Player;

/**
 * @brief Puts the correct stats to the user depending on the chosen character
 * 
 * @param player 
 * @param character 
 */
void initialisePlayerStats(Player* player, int character);

int kbhit(void);

#endif
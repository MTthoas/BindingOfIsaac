#ifndef H_PLAYER
#define H_PLAYER



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
    int stageAxeX;
    int stageAxeY;
};
typedef struct Player Player;

int kbhit(void);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/monster.h"
#include "include/mystring.h"
#include "Room.h"
#include "Player.h"


//TODO
void monsterAttack(Monster* monster, Player* player) {
    if(monster == NULL || player == NULL) {
        return;
    }

    float damage = monster->shoot;
    if(monster->flight == 1) {
        damage *= 1.5;
    }

    player->hpMax -= damage;
}
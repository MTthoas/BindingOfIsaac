/**
 * @file monster.h
 * @author  Nairod36
 * @brief Declaration fonctions des mobs et structures
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef MONSTER_H
#define MONSTER_H

#include "Player.h"

 typedef struct Monster {
    int idMonster;
    char firstLetter;
    char* name;
    float hpMax;
    int shoot;
    int flight;
    int ss;
    int positionX;
    int positionY;
    int dead;

} Monster;

typedef struct Boss {
    int idMonster;
    char firstLetter;
    char* name;
    int shoot;
    float hpMax;
    int positionX;
    int positionY;
    int dead;

} Boss;


    /**
     * @brief Constructeur de monsters e
     * 
     * @param idMonster
     * @param name 
     * @param hpMax 
     * @param shield 
     * @param shoot 
     * @param flight 
     * @param spectralShot ss
     * 
     * @return void 
     */

    void * Jagger(void *params);

    void* Lenina(void* params);

    Monster createMonster(int idMonster, char* name, float hpMax, int shoot, int flight, int ss);

    Monster * getMonsterById(Monster * arrayMonster, int id);

    void monsterRandomMove(Monster * monster, Player * player);

    void monsterFollowPlayerAndAttack(Monster * monster, Player * player);

    void * bossAthina(void *shootParams);

   void * bossLenina(void *params); 

    void * BossShoot(void * params);

    void * MonsterShoot(void * params);

    void * monsterAttackPlayer(void *params);

    void monsterActivity(void *params);
    
    void* LeninaShoot(void* params);

    void * Jagger(void *params);

    /**
     * @brief Returns a pointer to a monster identical to the given monster
     * 
     * @param monster 
     * @return Monster* 
     */
    Monster* duplicateMonster(Monster* monster);


    //void* Lenina(void *params);

#endif //MONSTER_H
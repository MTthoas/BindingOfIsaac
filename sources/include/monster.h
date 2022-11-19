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

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

 struct Monster {
    int idMonster;
    char firstLetter;
    char* name;
    float hpMax;
    int shoot;
    int flight;
    int ss;
    int positionX;
    int positionY;

};

typedef struct Monster Monster;

    /**
     * @brief Fonction creer monsters
     */

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
    Monster createMonster(int idMonster, char* name, float hpMax, int shoot, int flight, int ss);

    Monster * getMonsterById(Monster * arrayMonster, int id);

    void monsterAttack(Monster * monster, Player * player);

    void spawnMonster(Donjon * d, Monster * monster );    // void freeListeMonster(ListeMonster* liste);
    // void freeMonster(Monster* monster);

#endif //MONSTER_H
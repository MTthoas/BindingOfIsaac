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

typedef struct Monster Monster;
struct Monster {
    int idMonster;
    char* name;
    float hpMax;
    int shoot;
    int flight;
    int ss;
    int positionX;
    int positionY;

    Monster* suivant;
    };    


/**
 * @brief Liste de tous les monsters du jeu. 
 * Pointe vers le premier monster de la liste chainée.
 */
typedef struct ListeMonster {
    Monster* premier;
} ListeMonster;

/**
 * @brief Alloue un espace mémoire pour une liste de monster et renvoie son adresse. 
 * Pour ajouter des Monster dans la liste, utiliser addMonster().
 * 
 * @return ListeMonster* 
 */
ListeMonster* createListeMonster();


void monsterAttack(Monster* monster, Player* player);

Monster * spawnMonster(Donjon* d, char* name, float hpMax, int idMonster, int shoot, int flight, int ss);

/**
     * @brief Ajouter un monster dans la liste des monsters.
     * Retourne l'id du nouveau monster, 0 si le monster n'a pas pu être ajouté.
     * 
     * CREATE du CRUD
     * 
     * @param listeMonster 
     * @param newMonster 
     */
    int addMonster(ListeMonster* listeMonster, Monster* newMonster);



    void freeListeMonster(ListeMonster* liste);
    void freeMonster(Monster* monster);
    int addMonster(ListeMonster* listeMonster, Monster* newMonster);


#endif //MONSTER_H
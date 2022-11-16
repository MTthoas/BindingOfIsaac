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

void spawnMonster(Donjon* d,Monster* monster );

    /**
     * @brief Constructeur d'monsters
     * 
     * @param name 
     * @param hpMax 
     * @param shield 
     * @param shoot 
     * @param flight 
     * @param spectralShot ss
     * 
     * @return Monster* adresse de l'monster suivant (NULL par défaut)
     */
    Monster* createMonster(int idMonster, char* name, float hpMax, int shoot, int flight, int ss);

    /**
     * @brief Ajouter un monster dans la liste des monsters.
     * 
     * @param listeMonster 
     * @param newMonster 
     */
    void addMonster(ListeMonster* listeMonster, Monster* newMonster);

    void freeListeMonster(ListeMonster* liste);
    void freeMonster(Monster* monster);
    Monster* getMonsterById(ListeMonster* liste, int id);

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un monster dont la valeur des champs est identique
     * à ceux de l'monster en paramètre.
     * 
     * @param monster monster à copier
     * @return Monster* 
     */
    Monster* duplicateMonster(Monster* monster);

#endif //MONSTER_H
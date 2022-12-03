/**
 * @file game.h
 * @author MTthoas
 * @brief Declaration fonctions du jeu
 * @version 0.1_
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef H_GAME
#define H_GAME

#include "Room.h"
#include "monster.h"
#include "Player.h"
#include "shoot.h"

typedef struct Monster Monster;

void gestionGame(Donjon * d, ShootParams *shootParams, Monster * Boss, int stage, int * change, Player* player, int numberOfRoomsInt, int id, int axeX, int axeY, Monster* arrayMonster);


/**
 * @brief Set items in the room of the given id and stage
 */
void setItemInsideRoom(Donjon* d, int stage, int id);

/**
 * @brief Applies the item's changes to the player 
 * @param item 
 * @param player 
 */
void setItemEffects(Object* item, Player* player);

#endif
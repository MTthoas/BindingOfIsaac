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

int gestionRoom(Donjon * d, int numberOfRooms, int stage, int axeX, int axeY);
void gestionGame(Donjon * d, int stage, int * change, PlayerStats* playerStats);

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

/**
 * @brief Loads the player stats in the PlayerStats object. 
 * Usage : after a change in the statistics of the player
 * 
 * @param player 
 * @param playerStats 
 */
void savePlayerStats(Player* player, PlayerStats* playerStats);

#endif
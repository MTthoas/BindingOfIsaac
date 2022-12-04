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

int gestionRoom(Donjon * d, int numberOfRooms, int stage, int axeX, int axeY);
void gestionGame(Donjon * d, ShootParams *shootParams, Monster * Boss, int stage, int * change, Player* player, int numberOfRoomsInt, int id, int axeX, int axeY);


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

void InitialiseBossLeninaRoom(Donjon * d, int stage, int id, char letter);
void InitialiseBossRoom(Donjon * d, int stage, int id, char letter);

/**
 * @brief use when the player must lose life
 * 
 * @param player 
 * @param damageTaken 
 */
void playerLoseLife(Player* player, float damageTaken);

void playerMoveUp(Donjon* donjon, int stage, int roomID, Player* player);
void playerMoveDown(Donjon* donjon, int stage, int roomID, Player* player);
void playerMoveLeft(Donjon* donjon, int stage, int roomID, Player* player);
void playerMoveRight(Donjon* donjon, int stage, int roomID, Player* player);

#endif
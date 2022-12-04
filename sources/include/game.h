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

void gestionGame(Donjon * d, ShootParams *shootParams, Boss * Boss, int stage, int * change, Player* player, int numberOfRoomsInt, int id, int axeX, int axeY, Monster* arrayMonster);


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
//void InitialiseDoorsAfterDeath(Donjon* d);

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
void playerLoseLife(Player* player, float damageTaken);
void playerMoveLeft(Donjon* donjon, int stage, int roomID, Player* player);
void playerMoveRight(Donjon* donjon, int stage, int roomID, Player* player);
void playerMoveDown(Donjon* donjon, int stage, int roomID, Player* player);
void playerMoveUp(Donjon* donjon, int stage, int roomID, Player* player);
void PurgeRoomOfBoss(Donjon *d, int stage, int id);
void GestionDoorsForMobRoom(Donjon *d, int stage, int id, int done);
void InitialiseBossLeninaRoom(Donjon * d, int stage, int id, char letter);
void InitialiseBossRoom(Donjon * d, int stage, int id, char letter);
int gestionRoom(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY);
void gestionPassing(Donjon *d, Player * player, int stage, int id, int NumberOfRoomsInt);
void checkName(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY, int t);
void OptimiseDoors(Donjon * d, int stage, int axeX, int axeY, int id, int numberOfRooms);


#endif
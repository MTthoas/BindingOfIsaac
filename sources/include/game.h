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



/**
 * @brief To save an obstacle, it's position, and if it got erased
 * 
 */
typedef struct Obstacle {
    char type; // SPIKE, ROCK, GAP
    int positionX; // position on an X axis
    int positionY; // position on a Y axis
    int isErased; // 
} Obstacle;


void gestionGame(Donjon * d, ShootParams *shootParams, Boss * Boss, int stage, int * change, Player* player, int numberOfRoomsInt, int id, int axeX, int axeY);


/**
 * @brief Set items in the room of the given id and stage
 */
void setItemInsideRoom(Donjon* d, int stage, int id);

/**
 * @brief Applies the item's changes to the player 
 * @param item 
 * @param player 
 */
void setItemEffects(Object* item, Player* player, int isBonusItem);

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

/**
 * @brief use when the player must gain life
 * 
 * @param player 
 * @param damageTaken 
 */
void playerGainLife(Player* player);


// int changeIdRoomForMonsters(int idRoomForMonster, int numberOfRoom);

// /**
//  * @brief to target 1 order array by room
//  */
// void changeRoomMonsterArray(Donjon* d, int stage, int roomID);

void playerMoveUp(Donjon* donjon, int stage, int roomID, Player* player, Obstacle* obstacle);
void playerMoveDown(Donjon* donjon, int stage, int roomID, Player* player, Obstacle* obstacle);
void playerMoveLeft(Donjon* donjon, int stage, int roomID, Player* player, Obstacle* obstacle);
void playerMoveRight(Donjon* donjon, int stage, int roomID, Player* player, Obstacle* obstacle);

void PurgeRoomOfBoss(Donjon *d, int stage, int id);
void GestionDoorsForMobRoom(Donjon *d, int stage, int id, int done);
void InitialiseBossLeninaRoom(Donjon * d, int stage, int id, char letter);
void InitialiseBossRoom(Donjon * d, int stage, int id, char letter);
int gestionRoom(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY);

/**
 * @brief Redraws the player at his new position
 * 
 * @param d 
 * @param player 
 * @param stage 
 * @param id 
 * @param NumberOfRoomsInt 
 */
void redrawPlayer(Donjon *d, Player * player, int stage, int id, int NumberOfRoomsInt);
void checkName(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY, int t);
void OptimiseDoors(Donjon * d, int stage, int axeX, int axeY, int id, int numberOfRooms);

/**
 * @brief Displays the map
 * 
 * @param d 
 * @param stage 
 * @param numberOfRooms 
 */
void printMap(Donjon* d, int stage, int numberOfRooms);

/**
 * @brief Prints the minimap
 * 
 * @param d 
 * @param stage 
 * @param numberOfRooms 
 */
void printMinimap(Donjon* d, int stage, int numberOfRooms);

void printRoomsInfo(Donjon* d, int stage, int roomID, int axeX, int axeY);

void printPlayerInfos(Player* player, int frame, ShootParams* shootParams, Obstacle* obstacle);

void displayGame(Donjon* d, Player* player, int stage, int numberOfRooms, int iteration, int roomID, int axeX, int axeY, ShootParams* shootParams, int BossInfinite, Obstacle* obstacle);

void resetObstacle(Obstacle* obstacle);

/**
 * @brief Set the Bonus Item Inside Room object
 * 
 * @param d 
 * @param stage 
 * @param roomId 
 */
void setBonusItemInsideRoom(Donjon* d, int stage, int roomId);

void openItemRoomBonusDoor(Donjon* d, int stage, int roomId);
#endif
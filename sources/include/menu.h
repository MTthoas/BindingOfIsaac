/**
 * @file menu.h
 * @author  Nairod36
 * @brief Declaration fonctions du menu
 * @version 0.1
 * @date 2022-11-5
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef H_MENU
#define H_MENU

#include "Room.h"

typedef struct ShootParams ShootParams;

void menu_init(void);

void menuCrudItem(void);
int menuSeeItems(void);
int menuCreateItem(void);
int menuModifyItem(void);
int menuDeleteItem(void);

void menuCrudRoom(void);
int menuSeeRooms(void);
int menuCreateRoom(void);
int menuModifyRoom(void);
int menuDeleteRoom(void);

void optionError(void);
void menuControl(void);
void printGameBanner(void);

void menuGame();
void GameRecur(Donjon *d, Boss * boss, ShootParams * shootParams, Player * player, int characterID, int stage, int * change, int NumberOfRoomsInt, int id, int axeX, int axeY);
#endif
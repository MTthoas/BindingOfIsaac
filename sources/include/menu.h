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

typedef struct Donjon Donjon;
typedef struct Monster Monster;
typedef struct Boss Boss;
typedef struct Player Player;
typedef struct ShootParams ShootParams;

void menu_init(void);

void menuCrudItem(void);
void menuSeeItems(void);
void menuCreateItem(void);
void menuModifyItem(void);
void menuDeleteItem(void);

void menuCrudRoom(void);
void menuSeeRooms(void);
void menuCreateRoom(void);
void menuModifyRoom(void);
void menuDeleteRoom(void);

void optionError(void);
void menuControl(void);
void printGameBanner(void);

void menuGame();
void GameRecur(Donjon *d, Monster * Boss, ShootParams * shootParams, Player * player, int characterID, int stage, int * change, int NumberOfRoomsInt, int id, int axeX, int axeY, Monster * arrayMonster);
#endif
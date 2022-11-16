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

void menu_init(void);

void menuCrudItem(void);
void menuSeeItems(void);
void menuCreateItem(void);
void menuModifyItem(void);
void menuDeleteItem(void);

void menuCrudRoom(void);
void menuSeeRoms(void);
void menuCreateRoom(void);
void menuModifyRoom(void);
void menuDeleteRoom(void);

void optionError(void);

void menuControl(void);

void printGameBanner(void);

#endif
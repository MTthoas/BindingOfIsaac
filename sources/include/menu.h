#ifndef H_MENU
#define H_MENU


int menu_init(void);
int menuCrudMonster(void);
void menuCreateMonster(void);
void menuModifyMonster(void);
void menuDeleteMonster(void);

int menuCrudItem(void);
void menuCreateItem(void);
void menuModifyItem(void);
void menuDeleteItem(void);

int menuCrudRoom(void);
void menuCreateRoom(void);
void menuModifyRoom(void);
void menuDeleteRoom(void);

void optionError(void);
 #endif
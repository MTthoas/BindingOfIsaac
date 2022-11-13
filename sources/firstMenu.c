/**
 * @file firstMenu.c
 * @author MTthoas & Nairod36
 * @brief Gestion du programme
 * @version 1.5
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <fcntl.h>


#include "Player.h"
#include "menu.h"
#include "firstMenu.h"
#include "game.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"


void firstMenu(struct Donjon *d) {
	//Menu
	bool condition = true, condition2 = true, etape = true;
	int c,c2;

	while (condition) {
		c = 'p';

		if (etape == true && kbhit()) {
			c = getchar();
		}
		if (c == 'x') {
			condition = false;
		}

		switch (c) {

			case 'g':							
				gestionGame(d);
				menu_init();

			break;
			
			case 'i':
			while (condition2)
			{
			etape = false;
				c2 = 'p';
				menuCrudItem();
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
					case 'a':
						menuCreateItem();
						condition2 = false;
						break;
					case 'd':
						menuDeleteItem();
						condition2 = false;

						break;
					case 'm':
						menuModifyItem();
						condition2 = false;

						break;

				}
			}
			break;
				

			case 'r':
			 while (condition2)
			 {
				etape = false;
				c2 = 'p';
				menuCrudRoom();
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
					case 'a':
						menuCreateRoom();
						condition2 = false;
						break;
					case 'd':
						menuDeleteRoom();
						condition2 = false;
						break;
					case 'm':
						menuModifyRoom();
						condition2 = false;
						break;
				}
			 }
				break;

			case 'c':
				menuControl();
		}
	}
}
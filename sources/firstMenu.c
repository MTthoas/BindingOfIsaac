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
	bool condition = true, condition2, etape = true;
	int c,c2,c3,c4;

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
                system("clear");
                menuCrudItem();
                condition2 = true;
			    while (condition2)
			    {
			    etape = false;
			    	c2 = 'p';
			    	if (kbhit()) {
			    		c2 = getchar();
			    	}
			    	switch (c2) {
						case 's':
			    			menuSeeItems();
			    			condition2 = false;
			    			break;

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
                        case 'b':
                            menu_init();
                            condition2 = false;
                            break;
    
			    	}
                    etape = true;
			    }
			break;
				

			case 'r':
                system("clear");
                menuCrudRoom();
                condition2 = true;
			    while (condition2)
			    {
			    	etape = false;
			    	c3 = 'p';
			    	if (kbhit()) {
			    		c3 = getchar();
			    	}
			    	switch (c3){
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
                        case 'b':
                            menu_init();
                            condition2 = false;
                            break;
			    	}
			        etape = true;
                }
                
		    break;

			case 'c':
				menuControl();
                condition2 = true;
                while (condition2){
			        if (kbhit()) {
                        c4 = 'p';
			    		c4 = getchar();
                        if(c4 == 'b'){
                            menu_init();
			    		    condition2 = false;
			            }
			    	}
                }
            break;    
		}
	}
}
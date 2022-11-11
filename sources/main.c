#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <fcntl.h>

#include "include/Room.h"
#include "include/Player.h"
#include "menu.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"


int main(int argc, char * argv[]) {
	//Menu
	bool condition = true, condition2 = true, etape = true;
	int c,c2;
	menu_init();


	while (condition) {

		SDL_Delay(25);

		c = 'p';

		if (etape == true && kbhit()) {
			c = getchar();
		}

		if (c == 'x') {
			condition = false;
		}

		switch (c) {
			case 'g':
				(void) argc;
				(void) argv;

				Donjon * d = malloc(sizeof(Donjon));

				InitialisationGame(d);

				// Room * room = newRoom(1);

				// printf("\n");

				Player * player = malloc(sizeof(Player));
				player->positionX = 1;
				player->positionY = 1;
				player->directionView = 'D';

				for (int i = 0; i < d -> stages[0].rooms[0].height; i++) {
					for (int y = 0; y < d -> stages[0].rooms[0].width; y++) {
						if(i == d -> stages[0].rooms[0].height/2 && y == d -> stages[0].rooms[0].width/2){
							if(y % 2 == 0){
								d -> stages[0].rooms[0].room[i][y] = 'P';
							}else{
								d -> stages[0].rooms[0].room[i][y+1] = 'P';
							}
						}

					}
				}


				for (int i = 0; i < d -> stages[0].rooms[0].height; i++) {
					for (int y = 0; y < d -> stages[0].rooms[0].width; y++) {
						if (y % 2 == 0) {
							if(d-> stages[0].rooms[0].room[i][y] == 'P'){
								printf("%s", KRED);
								printf("%c ", d-> stages[0].rooms[0].room[i][y]);
    			        		printf("%s", KNRM);
							}else{
								printf("%c ", d-> stages[0].rooms[0].room[i][y]);
							}
							if (d-> stages[0].rooms[0].room[i][y] == 'P') {
								player->positionX = y;
								player->positionY = i;
							}
						}
					}
					printf("\n");
				}

					gestionPositionPlayer(d, player);
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
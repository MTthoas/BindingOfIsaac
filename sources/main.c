#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <fcntl.h>

#include "Room.h"
#include "Player.h"
#include "menu.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"


int main(int argc, char * argv[]) {
	//Menu
	bool condition = true;
	int c;

	while (condition) {

		SDL_Delay(25);

		c = 'p';

		if (kbhit()) {
			c = getchar();
		}

		if (c == 'x') {
			condition = false;
		}

		if (c != 'e') {
			menu_init();
			switch (c) {
				case 1:
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
					break;
				case 2:
					menuCrudMonster();
					if (kbhit()) {
						c = getchar();
					}
					switch (c){
						case 1:
							menuCreateMonster();
							break;
						case 2:
							menuDeleteMonster();
							break;
						case 3:
							menuModifyMonster();
							break;
						// case (!= 1 || != 2 || != 3):
							//optionError();
						// break;						
					}
					break;

				case 3:
					menuCrudItem();
					if (kbhit()) {
						c = getchar();
					}
					switch (c){
						case 1:
							menuCreateItem();
							break;
						case 2:
							menuDeleteItem();
							break;
						case 3:
							menuModifyItem();
							break;
					}
					break;

				case 4:
					menuCrudRoom();
					if (kbhit()) {
						c = getchar();
					}
					switch (c){
						case 1:
							menuCreateRoom();
							break;
						case 2:
							menuDeleteRoom();
							break;
						case 3:
							menuModifyRoom();
							break;
					}
					break;

				case 5:
					menuCommand();
			}
		}	
	}
}
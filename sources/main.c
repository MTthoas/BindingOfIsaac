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

	int choix;

	choix = menu_init();

	if (choix == 1){
        
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

	
	 }


	 if (choix == 2) {
		choix = menuCrudMonster();
        if (choix == 1) {
			menuCreateMonster();
        } else if (choix == 2) {
			menuDeleteMonster();
        } else if (choix == 3) {
			menuModifyMonster();
        } else {
			optionError();
        }        
	}

	if(choix == 3){
		choix = menuCrudItem();
		if (choix == 1) {
			menuCreateItem();
		} else if (choix == 2) {
			menuDeleteItem();
		} else if (choix == 3) {
			menuModifyItem();
		} else {
			optionError();
		}		
	}

	if(choix == 4){
		choix = menuCrudRoom();
		if (choix == 1) {
			menuCreateRoom();
		} else if (choix == 2) {
			menuDeleteRoom();
		} else if (choix == 3) {
			menuModifyRoom();
		} else {
			optionError();
		}
	}
}
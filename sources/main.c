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

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"


int main(int argc, char * argv[]) {

	(void) argc;
	(void) argv;

	Player* player = malloc(sizeof(Player));
	player->dmg = 1;
	player->hpMax = 5;
	player->shield = 5;
	player->ss = 0;
	player->ps = 0;
	player->flight = 0;
	player->positionX = 1;
	player->positionY = 1;
	player->directionView = 'D';
	
	menuGame(player);

	return 0;
}
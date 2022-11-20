/**
 * @file Player.c
 * @author MTthoas 
 * @brief Gestion du deplacement joueurs
 * @version 0.1
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
#include <pthread.h>

#include "Player.h"
#include "shoot.h"
#include "menu.h"


#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"

int kbhit(void) {
	
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, & oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, & newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, & oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

PlayerStats* initialisePlayerStats(int character) {
	PlayerStats* playerStats = 	malloc(sizeof(PlayerStats));

	if(character == BRIATTE) {
		playerStats->hpMax = 3;
		playerStats->dmg = 3.5;
		playerStats->shield = 0;
		playerStats->flight = 0;
	} else if(character == HENNOU) {
		playerStats->hpMax = 6;
		playerStats->dmg = 2.5;
		playerStats->shield = 0;
		playerStats->flight = 0;
	} else if(character == CHEVAILLIER) {
		playerStats->hpMax = 1;
		playerStats->dmg = 2;
		playerStats->shield = 8;
		playerStats->flight = 1;
	}
	
	playerStats->ps = 0;
	playerStats->ss = 0;

	return playerStats;
}


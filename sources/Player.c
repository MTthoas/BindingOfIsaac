/**
 * @file Player.c
 * @author MTthoas 
 * @brief Gestion du deplacement joueurs
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

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
#include "characters.h"


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

void initialisePlayerStats(Player* player, int character) {
	if(character == BRIATTE) {
		player->hpMax = 3;
		player->dmg = 3.5;
		player->shield = 0;
		player->flight = 0;
	} else if(character == HENNOU) {
		player->hpMax = 6;
		player->dmg = 2.5;
		player->shield = 0;
		player->flight = 0;
	} else if(character == CHEVAILLIER) {
		player->hpMax = 1;
		player->dmg = 2;
		player->shield = 8;
		player->flight = 1;
	}
	
	player->ps = 0;
	player->ss = 0;
}


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

void gestionPositionPlayer(struct Donjon *d,struct Player *player, int c){

			switch (c) {
				case 'z':
					if (d->stages[0].rooms[0].room[player->positionY - 1][player->positionX] != 'W' && d->stages[0].rooms[0].room[player->positionY - 1][player->positionX] != 'D') {
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
						player->positionY--;
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
						player->directionView = 'z';
					}
					break;
				case 's':
					if (d->stages[0].rooms[0].room[player->positionY + 1][player->positionX] != 'W' && d->stages[0].rooms[0].room[player->positionY + 1][player->positionX] != 'D') {
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
						player->positionY++;
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
						player->directionView = 's';
					}
					break;
				case 'q':
					if (d->stages[0].rooms[0].room[player->positionY][player->positionX - 2] != 'W' && d->stages[0].rooms[0].room[player->positionY][player->positionX - 2] != 'D') {
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
						player->positionX -= 2;
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
						player->directionView = 'q';
					}
					break;
				case 'd':
					if (d->stages[0].rooms[0].room[player->positionY][player->positionX + 2] != 'W' && d->stages[0].rooms[0].room[player->positionY][player->positionX + 2] != 'D') {
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
						player->positionX += 2;
						d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
						player->directionView = 'd';
					}
			}

	
}
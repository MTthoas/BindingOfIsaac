#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "Room.h"
#include "Player.h"

#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"


int main(int argc, char * argv[]) {

	(void) argc;
	(void) argv;


	Donjon * d = malloc(sizeof(Donjon));
	InitialisationGame(d);
	free(d);

	// system("clear");

	// d = malloc(sizeof(Donjon));
	// InitialisationGame(d);


	// Room * room = newRoom(1);

	// printf("\n");

	// Player * player = malloc(sizeof(Player));
	// player->positionX = 1;
	// player->positionY = 1;
	// player->directionView = 'D';

	// for (int i = 0; i < d -> stages[0].rooms[0].height; i++) {
	// 	for (int y = 0; y < d -> stages[0].rooms[0].width; y++) {
	// 		if(i == d -> stages[0].rooms[0].height/2 && y == d -> stages[0].rooms[0].width/2){
	// 			if(y % 2 == 0){
	// 				d -> stages[0].rooms[0].room[i][y] = 'P';
	// 			}else{
	// 				d -> stages[0].rooms[0].room[i][y+1] = 'P';
	// 			}
	// 		}
			
	// 	}
	// }


	// for (int i = 0; i < d -> stages[0].rooms[0].height; i++) {
	// 	for (int y = 0; y < d -> stages[0].rooms[0].width; y++) {
	// 		if (y % 2 == 0) {
	// 			if(d-> stages[0].rooms[0].room[i][y] == 'P'){
	// 				printf("%s", KRED);
	// 				printf("%c ", d-> stages[0].rooms[0].room[i][y]);
    //         		printf("%s", KNRM);
	// 			}else{
	// 				printf("%c ", d-> stages[0].rooms[0].room[i][y]);
	// 			}
	// 			if (d-> stages[0].rooms[0].room[i][y] == 'P') {
	// 				player->positionX = y;
	// 				player->positionY = i;
	// 			}
	// 		}
	// 	}
	// 	printf("\n");
	// }


	// int c;
	// bool condition = true;
	// int iteration = 0;
	// int frame = 0;

	

	// while (condition ) {

	// 	SDL_Delay(25);
		
	// 	c = 'p';
	// 	iteration++;

	// 	if (kbhit()) {
	// 		c = getchar();
	// 	}


	// 	if (c == ' ') {
			
	// 		if (player->directionView == 'd') {

				
	// 		}

	// 		if (player->directionView == 'q') {
				
	// 		}

	// 	}


	// 	// Touche pour cancel le jeu

	// 	if (c == 'x') {
	// 		condition = false;
	// 	}

	// 	if (c != 'e') {
	// 		system("clear");

	// 		switch (c) {
	// 			case 'z':
	// 				if (d->stages[0].rooms[0].room[player->positionY - 1][player->positionX] != 'W' && d->stages[0].rooms[0].room[player->positionY - 1][player->positionX] != 'D') {
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
	// 					player->positionY--;
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
	// 					player->directionView = 'z';
	// 				}
	// 				break;
	// 			case 's':
	// 				if (d->stages[0].rooms[0].room[player->positionY + 1][player->positionX] != 'W' && d->stages[0].rooms[0].room[player->positionY + 1][player->positionX] != 'D') {
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
	// 					player->positionY++;
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
	// 					player->directionView = 's';
	// 				}
	// 				break;
	// 			case 'q':
	// 				if (d->stages[0].rooms[0].room[player->positionY][player->positionX - 2] != 'W' && d->stages[0].rooms[0].room[player->positionY][player->positionX - 2] != 'D') {
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
	// 					player->positionX -= 2;
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
	// 					player->directionView = 'q';
	// 				}
	// 				break;
	// 			case 'd':
	// 				if (d->stages[0].rooms[0].room[player->positionY][player->positionX + 2] != 'W' && d->stages[0].rooms[0].room[player->positionY][player->positionX + 2] != 'D') {
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = ' ';
	// 					player->positionX += 2;
	// 					d->stages[0].rooms[0].room[player->positionY][player->positionX] = 'P';
	// 					player->directionView = 'd';
	// 				}
	// 		}

	// 		printf("\n");
	// 		for (int i = 0; i < d->stages[0].rooms[0].height; i++) {
	// 			for (int y = 0; y < d->stages[0].rooms[0].width - 1; y++) {
	// 				if (y % 2 == 0) {
	// 					if(d-> stages[0].rooms[0].room[i][y] == 'P'){
	// 						printf("%s", KRED);
	// 						printf("%c ", d-> stages[0].rooms[0].room[i][y]);
	// 						printf("%s", KNRM);
	// 					}else{
	// 						printf("%c ", d-> stages[0].rooms[0].room[i][y]);
	// 					}
	// 				}
	// 			}
	// 			printf("\n");
				
	// 		}

	// 		printf("Player position : %d, %d / Player direction : %c / Iteration : %d", player->positionX, player->positionY, player->directionView, iteration);
	// 		continue;


	// 	}
		
	// frame++;
	// }

	// free(d);
}
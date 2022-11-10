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
#include "shoot.h"


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

void gestionPositionPlayer(struct Donjon *d,struct Player *player){
	bool condition = true;	
	int frame = 0;
	int c, iteration = 0;

	while (condition) {
		

		SDL_Delay(25);
		// float i=0.1;
		// 	while(i<5000){
		// 		if(i == 5000){
		// 			printf("test");
		// 		}
		// 		i= i + 0.1;
		// 		printf("%.2f \n",i);
		// 	}
						
		c = 'p';
		iteration++;

		if (kbhit()) {
			c = getchar();
		}


		if (c == ' ') {
			
			if (player->directionView == 'd') {

				
			}

			if (player->directionView == 'q') {
				
			}

		}


		// Touche pour cancel le jeu

		if (c == 'x') {
			condition = false;
		}

		if (c != 'e') {
			system("clear");

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

			printf("\n");
			for (int i = 0; i < d->stages[0].rooms[0].height; i++) {
				for (int y = 0; y < d->stages[0].rooms[0].width - 1; y++) {
					if (y % 2 == 0) {
						if(d-> stages[0].rooms[0].room[i][y] == 'P'){
							printf("%s", KRED);
							printf("%c ", d-> stages[0].rooms[0].room[i][y]);
							printf("%s", KNRM);
						}else{
							printf("%c ", d-> stages[0].rooms[0].room[i][y]);
						}
					}
				}
				printf("\n");
				
			}
			
			bangishard(d, player);

			printf("Player position : %d, %d / Player direction : %c / Iteration : %d", player->positionX, player->positionY, player->directionView, iteration);
			continue;


		}
		
	 frame++;
	 free(d);
	 free(player);
	}

}
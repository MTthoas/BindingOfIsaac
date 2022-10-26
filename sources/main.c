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


int main(int argc, char * argv[]) {

	(void) argc;
	(void) argv;
	bool condition = true;

	Room * room = newRoom(1);
	// printRoom(*room);

	printf("WIDTH : %d", room ->width / 2);
	printf("\n");
	printf("HEIGHT : %d", room ->height / 2);
	printf("\n");
	printf("\n");

	Player * player = malloc(sizeof(Player));
	player->positionX = 1;
	player->positionY = 1;
	player->directionView = 'D';


	for (int i = 0; i < room -> height; i++) {
		for (int y = 0; y < room ->width - 1; y++) {
			if (y % 2 == 0) {
				printf("%c", room ->room[i][y]);

				if (room ->room[i][y] == 'P') {
					player->positionX = y;
					player->positionY = i;
				}
			}
		}
		printf("\n");
	}

	// Initialise player informations


	printf("Player position : %d, %d", player->positionX, player->positionY);

	printf("\n");
	printf("\n");

	int c;
	static struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, & oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, & newt);

	int iteration = 0;
	int frame = 0;

	

	while (condition ) {

		SDL_Delay(50);
		
		c = 'p';
		iteration++;

		if (kbhit()) {
			c = getchar();
		}


		if (c == ' ') {
			if (player->directionView == 'd') {

				int separator = 0;

					for(int v = 0; v<room->width; v++){
						if(room->room[player->positionY][v] != 'W' && room->room[player->positionY][v] != 'D'  ){
							separator++;
						}
					}

					for(int x = 0; x<separator;)
				
					if (room ->room[player->positionY][player->positionX + 1] != 'W' && room ->room[player->positionY][player->positionX + 1] != 'D') {
						room ->room[player->positionY][player->positionX + 1] = 'o';
					}
			}
				if (player->directionView == 'q') {
					if (room ->room[player->positionY][player->positionX - 1] != 'W' && room ->room[player->positionY][player->positionX - 1] != 'D') {
						room ->room[player->positionY][player->positionX - 1] = 'o';
					}
				}
		}

		if (c == 'x') {
			condition = false;
		}

		if (c != 'e') {

			printf("\n Char = %c\n", c);
			system("clear");

			switch (c) {
				case 'z':
					if (room ->room[player->positionY - 1][player->positionX] != 'W' && room ->room[player->positionY - 1][player->positionX] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionY--;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 'z';
					}
					break;
				case 's':
					if (room ->room[player->positionY + 1][player->positionX] != 'W' && room ->room[player->positionY + 1][player->positionX] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionY++;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 's';
					}
					break;
				case 'q':
					if (room ->room[player->positionY][player->positionX - 2] != 'W' && room ->room[player->positionY][player->positionX - 2] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionX -= 2;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 'q';
					}
					break;
				case 'd':
					if (room ->room[player->positionY][player->positionX + 2] != 'W' && room ->room[player->positionY][player->positionX + 2] != 'D') {
						room ->room[player->positionY][player->positionX] = ' ';
						player->positionX += 2;
						room ->room[player->positionY][player->positionX] = 'P';
						player->directionView = 'd';
					}
			}


			for (int i = 0; i < room ->height; i++) {
				for (int y = 0; y < room ->width - 1; y++) {
					if (y % 2 == 0) {
						printf("%c", room ->room[i][y]);
					}
				}
				printf("\n");
				
			}

			printf("Player position : %d, %d / Player direction : %c / Iteration : %d", player->positionX, player->positionY, player->directionView, iteration);
			continue;


		}




		/*restore the old settings*/
		tcsetattr(STDIN_FILENO, TCSANOW, & oldt);

		
	frame++;
	}

}
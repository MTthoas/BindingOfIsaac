/**
 * @file game.c
 * @author MTthoas & Nairod36
 * @brief Gestion du jeu
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>          
#include <unistd.h>     
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"
#define KCYN  "\x1B[36m"

#include <time.h>
#include "Room.h"
#include "Player.h"
#include "menu.h"
#include "game.h"
#include "shoot.h"

void gestionGame(Donjon * d);

void gestionGame(Donjon * d) {
    (void) d;
    

    int iteration = 0;
    int iterationTest = 0;

    bool condition = true;
    int c;

    Player * player = malloc(sizeof(Player));
	player->positionX = 1;
	player->positionY = 1;
	player->directionView = 'D';

    ShootParams *shootParams = malloc(sizeof(struct ShootParams));
    shootParams->reload = 1;
    shootParams->player = player;
    shootParams->d = d;
	
    // Initialise P at the start, start one time

    for (int i = 0; i < d -> stages[0].rooms[0].height; i++) {
        for (int y = 0; y < d -> stages[0].rooms[0].width; y++) {
            if (i == d -> stages[0].rooms[0].height / 2 && y == d -> stages[0].rooms[0].width / 2) {
                if (y % 2 == 0) {
                    d -> stages[0].rooms[0].room[i][y] = 'P';
                } else {
                    d -> stages[0].rooms[0].room[i][y + 1] = 'P';
                }
            }

        }
    }

    for (int i = 0; i < d -> stages[0].rooms[0].height; i++) {
        for (int y = 0; y < d -> stages[0].rooms[0].width; y++) {
            if (y % 2 == 0) {
                if (d -> stages[0].rooms[0].room[i][y] == 'P') {
                    player -> positionX = y;
                    player -> positionY = i;
                }
            }
        }
    }

    printf("\n");

    for (int i = 0; i < d->stages[0].rooms[0].height; i++) {
                for (int y = 0; y < d->stages[0].rooms[0].width - 1; y++) {
                    if (y % 2 == 0) {

                        if(d -> stages[0].rooms[0].room[i][y] == 'M'){
                            printf("%s", KRED);
                            printf("%c ", d -> stages[0].rooms[0].room[i][y]);
                            printf("%s", KNRM);
                        }else if(d-> stages[0].rooms[0].room[i][y] == 'P'){
                            printf("%s", KCYN);
                            printf("%c ", d-> stages[0].rooms[0].room[i][y]);
                            printf("%s", KNRM);
                        }else{
                            printf("%c ", d-> stages[0].rooms[0].room[i][y]);
                        }

                    }
                }
                printf("\n");

            }

    iterationTest++;   
	while (condition) {

        #ifdef _WIN32 
		Sleep(25); 
		#else 
		usleep(25000); 
		#endif 

        c = 'p';
		iteration++;

		if (kbhit()) {
			c = getchar();
		}


        
		if (c == 'x') {
			condition = false;
		}

		if (c != 'e') {

			system("clear");

            gestionPositionPlayer(d, player, c);

            printf("\n");
			for (int i = 0; i < d->stages[0].rooms[0].height; i++) {
				for (int y = 0; y < d->stages[0].rooms[0].width - 1; y++) {
					if (y % 2 == 0) {
						if(d-> stages[0].rooms[0].room[i][y] == 'P'){
							printf("%s", KCYN);
							printf("%c ", d-> stages[0].rooms[0].room[i][y]);
							printf("%s", KNRM);
						}else{
							printf("%c ", d-> stages[0].rooms[0].room[i][y]);
						}
					}
				}
				printf("\n");
				
			}

            printf("Player position : %d, %d / Player direction : %c / Iteration : %d / IterationTest : %d\n", player->positionX, player->positionY, player->directionView, iteration, iterationTest);
                
            printf("reload : %d\n",shootParams->reload);
            if (shootParams->reload == 1){
            	pthread_t t1;
            	pthread_create(&t1, NULL, bangishard, shootParams);
            }
            continue;

            free(d);
            free(player);
        }

    }


}
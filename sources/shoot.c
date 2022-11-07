
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "shoot.h"
#include "Room.h"
#include "Player.h"

void bangishard(struct Donjon *d,struct Player *player){

    Shoot * shoot = malloc(sizeof(Shoot));

	int c;
    int iteration = 1;

    c = 'p';
		iteration++;

		if (kbhit()) {
			c = getchar();
		}


if (kbhit()) {
			c = getchar();
		}


switch (c) {
				case '8': //shoot
					if(d->stages[0].rooms[0].room[player->positionY-1][player->positionX] == ' '){
                        shoot->positionX = player->positionX;
                        shoot->positionY = player->positionY;
						if(d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] == ' '){
							d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = '*';
							shoot->positionY = shoot->positionY - 1;
						// sleep(0.3);	
							// d->stages[0].rooms[0].room[player->positionY - 1][player->positionX] = ' ';

							while(d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] == ' '){
							
							d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = '*';
							shoot->positionY = shoot->positionY - 1;
					//	sleep(0.5);
							// d->stages[0].rooms[0].room[player->positionY - 1][player->positionX] = ' ';
 							iteration++;
							}
							
							
                           
						}
						
			}


}

}
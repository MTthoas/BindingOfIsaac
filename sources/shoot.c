#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<stdio.h>
#include <termios.h>          
   
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>

#include <fcntl.h>

#include "shoot.h"
#include "mystring.h"
#include "Room.h"
#include "Player.h"

#ifdef _WIN32 
#include <Windows.h>  
#else
#include <unistd.h>
#endif 

void* bangishard(void *shootParams){
    Shoot * shoot = malloc(sizeof(Shoot));

	//((ShootParams*)shootParams)->player->positionX;
	int c;

    c = 'p';

	if (kbhit()) {
		c = getchar();
	}

	switch (c) {
			case '8': //shootUp
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0; 
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] == ' '){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = '*';

						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif 
						
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY - 1][((ShootParams*)shootParams)->player->positionX] = ' ';
						shoot->positionY = shoot->positionY - 1;
						while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] == ' '){
						
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = '*';

							#ifdef _WIN32 
							Sleep(90; 
							#else 
							usleep(90000); 
							#endif

							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = ' ';
							shoot->positionY = shoot->positionY - 1;
						}
					}
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}((ShootParams*)shootParams)->reload = 1; 
				break;
			case '5': //shootBottom
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0; 
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] == ' '){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] = '*';

						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif 
						
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY + 1][((ShootParams*)shootParams)->player->positionX] = ' ';
						shoot->positionY = shoot->positionY + 1;
						while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] == ' '){
						
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] = '*';

							#ifdef _WIN32 
							Sleep(90); 
							#else 
							usleep(90000); 
							#endif

							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] = ' ';
							shoot->positionY = shoot->positionY + 1;
						}
					}
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				} ((ShootParams*)shootParams)->reload = 1;
				break;

				case '4': //shootLeft
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0; 
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX-2] == ' '){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX-2] = '*';

						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif 
						
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] = ' ';
						shoot->positionX = shoot->positionX - 2;
						while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX-2] == ' '){
						
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX-2] = '*';

							#ifdef _WIN32 
							Sleep(90; 
							#else 
							usleep(90000); 
							#endif

							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY ][shoot->positionX-2] = ' ';
							shoot->positionX = shoot->positionX - 2;
						}
					}
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				} ((ShootParams*)shootParams)->reload = 1;
				break;

				case '6': //shootRight
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0; 
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX+2] == ' '){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX+2] = '*';

						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif 
						
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] = ' ';
						shoot->positionX = shoot->positionX + 2;
						while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX+2] == ' '){
						
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX+2] = '*';

							#ifdef _WIN32 
							Sleep(90); 
							#else 
							usleep(90000); 
							#endif

							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY ][shoot->positionX+2] = ' ';
							shoot->positionX = shoot->positionX + 2;
						}
					}
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				} ((ShootParams*)shootParams)->reload = 1;
				break;
	}
	free(shoot);
	return 0;
}
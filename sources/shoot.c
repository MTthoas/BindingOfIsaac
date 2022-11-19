/**
 * @file shoot.c
 * @author  Nairod36
 * @brief Fonctions shoot joueur
 * @version 0.3
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 */

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

	// #ifdef _WIN32 
	// Sleep(25); 
	// #else 
	// usleep(25000); 
	// #endif 

    Shoot * shoot = malloc(sizeof(Shoot));

	int c;

    c = 'p';

	
	if (kbhit()) {
		c = getchar();
	}
	
		

	switch (c) {
			case '8': //shootUp

				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] != ' '){
					break;
				}

				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0; 


					while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] == ' '){
							
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = '*';
						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = ' ';
						shoot->positionY = shoot->positionY - 1;
							
					}

					// if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] == ((ShootParams*)shootParams)->monster->firstLetter){
					// 	((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
						
					// 	if(((ShootParams*)shootParams)->monster->hpMax <= 0){
					// 		((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY - 1][shoot->positionX] = ' ';
					// 	}
					// }


					((ShootParams*)shootParams)->reload = 1;
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}((ShootParams*)shootParams)->reload = 1; 

				
				// if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] == ((ShootParams*)shootParams)->monster->firstLetter){
					
				// 	// Le monstre prends des dégats équivalent aux dmg du Player
				// 	((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
				// 	if(((ShootParams*)shootParams)->monster->hpMax <= 0){
				// 		((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->monster->positionY][((ShootParams*)shootParams)->monster->positionX] = ' ';
				// 	}
				// }
				break;
			case '5': //shootBottom
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0;
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
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] == ((ShootParams*)shootParams)->monster->firstLetter){
						((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->monster->hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY + 1][shoot->positionX] = ' ';
						}
					}
					((ShootParams*)shootParams)->reload = 1;
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}((ShootParams*)shootParams)->reload = 1;
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] == ((ShootParams*)shootParams)->monster->firstLetter){
					
					// Le monstre prends des dégats équivalent aux dmg du Player
					((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
					if(((ShootParams*)shootParams)->monster->hpMax <= 0){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->monster->positionY][((ShootParams*)shootParams)->monster->positionX] = ' ';
					}
				}
				break;
			case '4': //shootLeft

				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] != ' '){
					break;
				}
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0;
					while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX - 2] == ' '){
						
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX - 2] = '*';
						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX - 2] = ' ';
						shoot->positionX = shoot->positionX - 2;
							
					}
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX - 2] == ((ShootParams*)shootParams)->monster->firstLetter){
						((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->monster->hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX - 2] = ' ';
						}
					}
					((ShootParams*)shootParams)->reload = 1;
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}((ShootParams*)shootParams)->reload = 1;
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] == ((ShootParams*)shootParams)->monster->firstLetter){
					
					// Le monstre prends des dégats équivalent aux dmg du Player
					((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
					if(((ShootParams*)shootParams)->monster->hpMax <= 0){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->monster->positionY][((ShootParams*)shootParams)->monster->positionX] = ' ';
					}
				}
				break;
			case '6': //shootRight
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0;
					while(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX + 2] == ' '){
						
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX + 2] = '*';
						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX + 2] = ' ';
						shoot->positionX = shoot->positionX + 2;
							
					}
					if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX + 2] == ((ShootParams*)shootParams)->monster->firstLetter){
						((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->monster->hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[0].rooms[0].room[shoot->positionY][shoot->positionX + 2] = ' ';
						}
					}
					((ShootParams*)shootParams)->reload = 1;
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}((ShootParams*)shootParams)->reload = 1;
				if(((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] == ((ShootParams*)shootParams)->monster->firstLetter){
					
					// Le monstre prends des dégats équivalent aux dmg du Player
					((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
					if(((ShootParams*)shootParams)->monster->hpMax <= 0){
						((ShootParams*)shootParams)->d->stages[0].rooms[0].room[((ShootParams*)shootParams)->monster->positionY][((ShootParams*)shootParams)->monster->positionX] = ' ';
					}
				}
				break;
	}
	free(shoot);
	return 0;
}
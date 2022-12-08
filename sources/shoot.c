/**
 * @file shoot.c
 * @author  Nairod36
 * @brief Fonctions shoot joueur
 * @version 0.3
 * @date 2022-11-13
 * 
 * @copyright Copyright (c) 2022
 */


#include<stdio.h>
#include <termios.h>          
   
#include <stdlib.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <ctype.h>

#include <fcntl.h>

#include "shoot.h"
#include "Room.h"
#include "Player.h"

#ifdef _WIN32 
#include <Windows.h>  
#else
#include <unistd.h>
#endif 

	
void * shootUp(void *shootParams) {
	    
	    Shoot * shoot = malloc(sizeof(Shoot));
		int id = ((ShootParams*)shootParams)->id;
		int stage = ((ShootParams*)shootParams)->stage;

	if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] == ' '){
        shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
        shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
		((ShootParams*)shootParams)->reload = 0; 

		while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == ' '){ 
			((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = '*';
			#ifdef _WIN32 
			Sleep(90); 
			#else 
			usleep(90000); 
			#endif
			((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
			shoot->positionY = shoot->positionY - 1;
		}
		for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
			char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
			if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == letter){
				((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
				if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
					((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
					//TODO: Spawn item 5% chance
				}
			}
		}

		if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == ((ShootParams*)shootParams)->boss->firstLetter){
			((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
			if(((ShootParams*)shootParams)->boss->hpMax <= 0){
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
			}
		}

		((ShootParams*)shootParams)->reload = 1; 
		shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
        shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
	}
	for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
		char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
		if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] == letter){
			((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
			if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] = ' ';
			}
		}
	}
	
	if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY-1][((ShootParams*)shootParams)->player->positionX] == ((ShootParams*)shootParams)->boss->firstLetter){
		// Le boss prends des dégats équivalent aux dmg du Player
		((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
		if(((ShootParams*)shootParams)->boss->hpMax <= 0){
			((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->boss->positionY][((ShootParams*)shootParams)->boss->positionX] = ' ';
		}
	}
	free(shoot);
	return 0;
}
				
				
void* shootDown(void *shootParams) {
	    Shoot * shoot = malloc(sizeof(Shoot));
		int id = ((ShootParams*)shootParams)->id;
		int stage = ((ShootParams*)shootParams)->stage;
				if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0;
					while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] == ' '){
						
						((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = '*';
						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif
						((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = ' ';
						shoot->positionY = shoot->positionY + 1;
							
					}
					for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
						char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
						if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] == letter){
							((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
							if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
								((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = ' ';
							}
						}
					}
					if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] == ((ShootParams*)shootParams)->boss->firstLetter){
						((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->boss->hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = ' ';
						}
					}
					((ShootParams*)shootParams)->reload = 1;
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}
				for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
					char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
					if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] == letter){
						((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] = ' ';
						}
					}
				}
				if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY+1][((ShootParams*)shootParams)->player->positionX] == ((ShootParams*)shootParams)->boss->firstLetter){
					
					// Le boss prends des dégats équivalent aux dmg du Player
					((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
					if(((ShootParams*)shootParams)->boss->hpMax <= 0){
						((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->boss->positionY][((ShootParams*)shootParams)->boss->positionX] = ' ';
					}
				}
				free(shoot);
				return 0;
}
		
void* shootLeft(void *shootParams){
	    Shoot * shoot = malloc(sizeof(Shoot));
		int id = ((ShootParams*)shootParams)->id;
		int stage = ((ShootParams*)shootParams)->stage;
	if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] == ' '){
	    shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	    shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
		((ShootParams*)shootParams)->reload = 0;
		while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] == ' '){
			
			((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] = '*';
			#ifdef _WIN32 
			Sleep(90); 
			#else 
			usleep(90000); 
			#endif
			((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] = ' ';
			shoot->positionX = shoot->positionX - 2;
				
		}
		for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
			char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
			if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] == letter){
				((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
				if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
					((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] = ' ';
				}
			}
		}
		if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] == ((ShootParams*)shootParams)->boss->firstLetter){
			((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
			if(((ShootParams*)shootParams)->boss->hpMax <= 0){
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] = ' ';
			}
		}
		((ShootParams*)shootParams)->reload = 1;
		shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	    shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
	}
	for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
		char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
		if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] == letter){
			((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
			if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] = ' ';
			}
		}
	}
	if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX-2] == ((ShootParams*)shootParams)->boss->firstLetter){
		
		// Le boss prends des dégats équivalent aux dmg du Player
		((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
		if(((ShootParams*)shootParams)->boss->hpMax <= 0){
			((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->boss->positionY][((ShootParams*)shootParams)->boss->positionX] = ' ';
		}
	}
	free(shoot);
	return 0;
}

void* shootRight(void *shootParams){
	    Shoot * shoot = malloc(sizeof(Shoot));
		int id = ((ShootParams*)shootParams)->id;
		int stage = ((ShootParams*)shootParams)->stage;
				if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] == ' '){
	                shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
					((ShootParams*)shootParams)->reload = 0;
					while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] == ' '){
						
						((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = '*';
						#ifdef _WIN32 
						Sleep(90); 
						#else 
						usleep(90000); 
						#endif
						((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = ' ';
						shoot->positionX = shoot->positionX + 2;
							
					}
					for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
						char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
						if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] == letter){
							((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
							if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
								((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = ' ';
							}
						}
					}
					if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] == ((ShootParams*)shootParams)->boss->firstLetter){
						((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->boss->hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = ' ';
						}
					}
					((ShootParams*)shootParams)->reload = 1;
					shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
	                shoot->positionY = ((ShootParams*)shootParams)->player->positionY;
				}
				for (int j = 0; j < ((ShootParams*)shootParams)->d->stages[stage].rooms[id].numberOfMonsters; j++){
					char letter = tolower(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].firstLetter);
					if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] == letter){
						((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax = ((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax - ((ShootParams*)shootParams)->player->dmg;
						if(((ShootParams*)shootParams)->d -> stages[stage].rooms[id].monsters[j].hpMax <= 0){
							((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] = ' ';
						}
					}
				}
				if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->player->positionY][((ShootParams*)shootParams)->player->positionX+2] == ((ShootParams*)shootParams)->boss->firstLetter){
					
					// Le monstre prends des dégats équivalent aux dmg du Player
					((ShootParams*)shootParams)->boss->hpMax = ((ShootParams*)shootParams)->boss->hpMax - ((ShootParams*)shootParams)->player->dmg;
					if(((ShootParams*)shootParams)->boss->hpMax <= 0){
						((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[((ShootParams*)shootParams)->boss->positionY][((ShootParams*)shootParams)->boss->positionX] = ' ';
					}
				}
				free(shoot);
				return 0;
}
	

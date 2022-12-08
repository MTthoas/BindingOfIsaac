/**
 * @file monster.c
 * @author  Nairod36
 * @brief Fonctions des mobs
 * @version 0.2
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
#ifdef _WIN32 
#include <Windows.h>  
#else
#include <unistd.h>
#endif    
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

#include "game.h"
#include "include/mystring.h"


void spawnMonster(Donjon * d, Monster * monster, int stage, int id) {

    srand(time(NULL));
    int randomPositionX,randomPositionY; 
    int heightRoom = d->stages[stage].rooms[id].height - 1;
    int widthRoom = d->stages[stage].rooms[id].width - 2;
 
    // printf("\nOne\n");
    // sleep(1);
    while (1) {
        randomPositionY = 1 + rand() % (heightRoom - 1);
        randomPositionX = 2 + rand() % (widthRoom - 2);
        if (randomPositionX % 2 == 0 && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX] == ' ' && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX - 2] != 'P' && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX + 2] != 'P' && d->stages[stage].rooms[id].room[randomPositionY - 1][randomPositionX] != 'P' && d->stages[stage].rooms[id].room[randomPositionY + 1][randomPositionX] != 'P' ){
            monster->positionX = randomPositionX;
            monster->positionY = randomPositionY;
            break;
        }   
    } // la lettre doit correspondre au monstre 
    // // printf("\nSecond\n");
    // // sleep(30000);
    char letterForMonster = monster->name[0];
    letterForMonster = toupper(letterForMonster);
    monster->firstLetter = letterForMonster;
    d->stages[stage].rooms[id].room[monster->positionY][monster->positionX] = letterForMonster;        

}

Monster * getMonsterById(Monster * arrayMonster,int id) {

    struct Monster * monster = malloc(sizeof(struct Monster)*1);
    printf("Heoh\n");
    
    for(int i = 0; i < 9; i++) {
        if(arrayMonster[i].idMonster == (id)) {
            *monster = arrayMonster[i];
            return monster;
        }
    }

    return NULL;
}



void * bossAthina(void *shootParams) {
    int BossPosX, BossPosY;
    Shoot * shoot = malloc(sizeof(Shoot));
    int reload = 1;    

    for (int i = 0; i < ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].height; i++) {
        for (int y = 0; y < ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].width; y++) {
            if (i == ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].height / 2 && y == ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].width / 2) {
                if (y % 2 == 0) {
                    ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[i][y] = 'A';
                     shoot->positionX = y;
                     BossPosX = shoot->positionX;
                     shoot->positionY = i;
                     BossPosY = shoot->positionY;
                } else {
                    ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[i][y - 1] = 'A';
                    shoot->positionX = y-1;
                    BossPosX = shoot->positionX;
                    shoot->positionY = i;
                    BossPosY =shoot->positionY;
                }
            }

        }
    }   
    if (reload == 1) {
        reload = 0;
        while(((ShootParams*)shootParams)->boss->hpMax > 0 && ((ShootParams*)shootParams)->player->hpMax > 0){
                #ifdef _WIN32 
    	        Sleep(400); 
    	        #else 
    	        usleep(400000); 
    	        #endif

            //ShootUp
            while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == ' '){ 
               

    	        ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = '*';
    	        #ifdef _WIN32 
    	        Sleep(40); 
    	        #else 
    	        usleep(40000); 
    	        #endif
    	        ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
    	        shoot->positionY = shoot->positionY - 1;
    
            }
            if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == 'P'){
				((ShootParams*)shootParams)->player->hpMax = ((ShootParams*)shootParams)->player->hpMax - 1;
				if(((ShootParams*)shootParams)->player->hpMax <= 0){
                    //Le joueur est mort, fin partie 
					((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
				}
			}
            	        shoot->positionY = BossPosY;
            //ShootDown
            while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] == ' '){
						
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = '*';
				#ifdef _WIN32 
				Sleep(40); 
				#else 
				usleep(40000); 
				#endif
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = ' ';
				shoot->positionY = shoot->positionY + 1;			
		    }
            if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] == 'P'){
				((ShootParams*)shootParams)->player->hpMax = ((ShootParams*)shootParams)->player->hpMax - 1;
				if(((ShootParams*)shootParams)->player->hpMax <= 0){
                    //Le joueur est mort, fin partie 
					((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY + 1][shoot->positionX] = ' ';
				}
			}
            	        shoot->positionY = BossPosY;
            //ShootLeft
            while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] == ' '){
						
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] = '*';
				#ifdef _WIN32 
				Sleep(40); 
				#else 
				usleep(40000); 
				#endif
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX - 2] = ' ';
				shoot->positionX = shoot->positionX - 2;
							
			}
            if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX -2] == 'P'){
				((ShootParams*)shootParams)->player->hpMax = ((ShootParams*)shootParams)->player->hpMax - 1;
				if(((ShootParams*)shootParams)->player->hpMax <= 0){
                    //Le joueur est mort, fin partie 
					((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX -2] = ' ';
				}
			}
                        shoot->positionX = BossPosX;
            //ShootRight
            while(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] == ' '){
						
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = '*';
				#ifdef _WIN32 
				Sleep(40); 
				#else 
				usleep(40000); 
				#endif
				((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = ' ';
				shoot->positionX = shoot->positionX + 2;
							
			}
            if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] == 'P'){
				((ShootParams*)shootParams)->player->hpMax = ((ShootParams*)shootParams)->player->hpMax - 1;
				if(((ShootParams*)shootParams)->player->hpMax <= 0){
                    //Le joueur est mort, fin partie 
					((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY][shoot->positionX + 2] = ' ';
				}
			}

            shoot->positionX = BossPosX;
	        shoot->positionY = BossPosY;
            reload = 1;

            
        }
        
    }

    free(shoot);
    return 0;
}

Monster createMonster(int idMonster, char* name, float hpMax, int shoot, int flight, int ss) {

    Monster monster;
    monster.idMonster = idMonster;
    monster.name = duplicateString(name);
    monster.hpMax = hpMax;
    monster.shoot = shoot;
    monster.flight = flight;
    monster.ss = ss;

    return monster;
}

void monsterActivity(void *params){
    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;
    pthread_t tZero;
    pthread_t tUn;
    pthread_t tDeux;
    pthread_t tTrois;
    pthread_t tQuatre;
    pthread_t tCinq;

    if (((ShootParams*)params)->d -> stages[stage].rooms[id].numberOfMonsters != 0){       
        for (int i = 0; i < ((ShootParams*)params)->d -> stages[stage].rooms[id].numberOfMonsters ; i++){

            if (i == 0){
                ((ShootParams*)params)->idMonster = i;
                pthread_create(&tZero, NULL, monsterAttackPlayer, params);
                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
            }
            if (i == 1){
                ((ShootParams*)params)->idMonster = i;
                pthread_create(&tUn, NULL, monsterAttackPlayer, params);
                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
            }
            if (i == 2){
                ((ShootParams*)params)->idMonster = i;
                pthread_create(&tDeux, NULL, monsterAttackPlayer, params);
                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
            }
            if (i == 3){
                ((ShootParams*)params)->idMonster = i;
                pthread_create(&tTrois, NULL, monsterAttackPlayer, params);
                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
            }
            if (i == 4){
                ((ShootParams*)params)->idMonster = i;
                pthread_create(&tQuatre, NULL, monsterAttackPlayer, params);
                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
            }
            if (i == 5){
                ((ShootParams*)params)->idMonster = i;
                pthread_create(&tCinq, NULL, monsterAttackPlayer, params);
                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
            }
        }
    }
    
}

void * monsterAttackPlayer(void *params) {

    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;
    int idMonster = ((ShootParams*)params)->idMonster;

        if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].shoot != 1){
            while(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].hpMax > 0){
            
                //Le monstre se déplace vers la position du joueur pour lui infliger des dégâts de corps à corps ( hpMax - 1) dès qu’ils arrivent au niveau d’une case adjacente au player

                #ifdef _WIN32 
	            Sleep(25); 
	            #else 
	            usleep(25000); 
	            #endif
                #ifdef _WIN32 
	            Sleep(888); 
	            #else 
	            usleep(888000); 
	            #endif       
                char letter = tolower(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].firstLetter);

                for (int i = 0; i < ((ShootParams*)params)->d -> stages[stage].rooms[id].height; i++) {
                
                    for(int y = 0; y < ((ShootParams*)params)->d -> stages[stage].rooms[id].width; y++){
                    
                        if(((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] == letter && ((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] != 'G' && ((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] != 'R' && ((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] != 'S'){
                        
                                (((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] = ' ');
                        }
                    }
                }             

                int positionPlayerX = ((ShootParams*)params)->player->positionX;
                int positionPlayerY = ((ShootParams*)params)->player->positionY;

                int DiffPositionX = ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX - positionPlayerX;
                int DiffPositionY = ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY - positionPlayerY;

                int randMonster = rand() % 2;

                ((ShootParams*)params)->reload = 1;



                if(randMonster == 0){
                
                    if(DiffPositionX > 0){


                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == ' '){
                        
                            ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX--;
                            ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX--;

                            ((ShootParams*)params) -> directionView = 'L';

                        }
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                        }
                        if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
                            if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'G'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'R'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'S'
                            ){
                                ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX--;
                                ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX--;

                                ((ShootParams*)params) -> directionView = 'L';
                            } 
                        }



                    }else{
                    
                        if(DiffPositionX < 0){
                        
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == ' '){
                        
                           ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX++;
                           ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX++;

                            ((ShootParams*)params) -> directionView = 'R';

                        }
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                        }
                        if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
                            if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'G'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'R'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'S'
                            ){
                                ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX++;
                                ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX++;

                                ((ShootParams*)params) -> directionView = 'R';
                            } 
                        }

                        }

                    }

                }else{
                
                    if(DiffPositionY > 0){
                    
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == ' '){
                        
                            ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY--;
                            ((ShootParams*)params) -> directionView = 'T';

                        }
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                        }
                        if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
                            if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'G'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'R'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'S'
                            ){
                                ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY--;
                                ((ShootParams*)params) -> directionView = 'T';
                            } 
                        }


                    }else if(DiffPositionY < 0){
                    
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == ' '){
                        
                            ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY++;
                            ((ShootParams*)params) -> directionView = 'B';

                        }
                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                        }
                        if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
                            if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'G'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'R'
                            || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'S'
                            ){
                                ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY++;
                                ((ShootParams*)params) -> directionView = 'B';
                            } 
                        }

                    }

                }               

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == ' '){
                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] = letter;
                }

        }

        }

        // if (((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].shoot == 1){
        //     pthread_t threadM;
        //     while(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].hpMax > 0){
        //         //Le monstre se depalce se déplacent aléatoirement dans la salle tout en visant le joueur. 
        //         //Le projectile part dans la direction jusqu’à entrer en contact avec un élément (mur, joueur ou rocher) sauf cas exceptionnel (tir spectral). 
        //         //Le monstre ne peut tirer qu’un seul projectile à la fois
        //         #ifdef _WIN32 
	    //         Sleep(25); 
	    //         #else 
	    //         usleep(25000); 
	    //         #endif
        //         #ifdef _WIN32 
	    //         Sleep(1000); 
	    //         #else 
	    //         usleep(1000000); 
	    //         #endif 

        //         char letter = tolower(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].firstLetter);

        //          for (int i = 0; i < ((ShootParams*)params)->d -> stages[stage].rooms[id].height; i++) {

        //             for(int y = 0; y < ((ShootParams*)params)->d -> stages[stage].rooms[id].width; y++){

        //                 if(((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] == letter){

        //                         (((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] = ' ');
        //                 }
        //             }
        //         }

        //         ((ShootParams*)params)->reload = 1;
        //         int direction = rand() % 4;

        //         if(direction == 0){
        //             if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == ' '){
        //                 ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY--;
        //                 ((ShootParams*)params) -> directionView = 'T';
        //             }
        //             if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
        //                 if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'G'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'R'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY-1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'S'
        //                 ){
        //                     ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY--;
        //                     ((ShootParams*)params) -> directionView = 'T';
        //                 } 
        //             }

        //         }else if(direction == 1){
        //             if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == ' '){
        //                 ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY++;
        //                 ((ShootParams*)params) -> directionView = 'B';
        //             }
        //             if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
        //                 if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'G'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'R'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY+1][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX] == 'S'
        //                 ){
        //                     ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY++;
        //                     ((ShootParams*)params) -> directionView = 'B';
        //                 } 
        //             }

        //         }else if(direction == 2){
        //             if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == ' '){
        //                 ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX --;
        //                 ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX --;
        //                 ((ShootParams*)params) -> directionView = 'L';
        //             }
        //             if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
        //                 if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'G'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'R'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX-2] == 'S'
        //                 ){
        //                     ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX --;
        //                     ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX --;
        //                     ((ShootParams*)params) -> directionView = 'L';
        //                 } 
        //             }

        //         }else if(direction == 3){
        //             if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == ' '){
        //                 ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX ++;
        //                 ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX ++;
        //                 ((ShootParams*)params) -> directionView = 'R';
        //             }
        //             if(((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].flight == 1){
        //                 if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'G'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'R'
        //                 || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionY][((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX+2] == 'S'
        //                 ){
        //                     ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX ++;
        //                     ((ShootParams*)params)->d -> stages[stage].rooms[id].monsters[idMonster].positionX ++;
        //                     ((ShootParams*)params) -> directionView = 'R';
        //                 } 
        //             }

        //         }

        //         int shoot = rand() % 2;
        //         if(shoot == 0){
        //             pthread_create(&threadM, NULL, MonsterShoot, params);
        //         }

        //     }
        // }
    return NULL;

}

void * BossShoot(void * params){

    Shoot * shoot = malloc(sizeof(Shoot));
    Boss * boss = malloc(sizeof(Boss));

    
    char letter = ((ShootParams*)params)->boss->firstLetter;

    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;

     for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i++) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y++){
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter){
                boss -> positionX = y;
                boss -> positionY = i;
            }
        }
    }

        shoot -> positionX = boss -> positionX;
        shoot -> positionY = boss -> positionY;

        if(((ShootParams*)params) -> reload == 1){

            if(((ShootParams*)params) -> directionView == 'R'){

                      ((ShootParams*)params)->reloadBoss = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX + 2] == ' ' && ((ShootParams*)params)->reloadBoss  == 0 ){

                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 4] == 'P'){
                            
                                if(((ShootParams*)params)->player->shield <= 0){
                                    ((ShootParams*)params)->player->hpMax -= 1;
                                } else {
                                    ((ShootParams*)params)->player->shield -= 1;
                                }
                                break;
        
                    }

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif



                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = ' ';
                    
                    shoot -> positionX =  shoot -> positionX + 2;

                }
        
                ((ShootParams*)params)->reloadBoss = 1;
        
            }

            if(((ShootParams*)params) -> directionView == 'L'){

                        ((ShootParams*)params)->reloadBoss = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX - 2] == ' ' && ((ShootParams*)params)->reloadBoss  == 0){

                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 4] == 'P'){
                            
                        if(((ShootParams*)params)->player->shield <= 0){
                            ((ShootParams*)params)->player->hpMax -= 1;
                        } else {
                            ((ShootParams*)params)->player->shield -= 1;
                        }
                        break;
        
                    }

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = ' ';
                    
                    
                    shoot -> positionX = shoot -> positionX - 2;

                }

                
                ((ShootParams*)params)->reloadBoss = 1;
        
            }

            if(((ShootParams*)params) -> directionView == 'T'){

                        ((ShootParams*)params)->reloadBoss = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY - 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reloadBoss  == 0){

                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY - 2][shoot->positionX] == 'P'){
                            
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                            break;
        
                    }


                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY-1][shoot->positionX] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY-1][shoot->positionX] = ' ';

                    shoot -> positionY--;

                }

                ((ShootParams*)params)->reloadBoss = 1;

            }

            if(((ShootParams*)params) -> directionView == 'B'){

                        ((ShootParams*)params)->reloadBoss = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY + 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reloadBoss  == 0){ 

                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 2][shoot->positionX] == 'P'){
                            
                                if(((ShootParams*)params)->player->shield <= 0){
                                    ((ShootParams*)params)->player->hpMax -= 1;
                                } else {
                                    ((ShootParams*)params)->player->shield -= 1;
                                }
                                break;
        
                    }

            
                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 1][shoot->positionX] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 1][shoot->positionX] = ' ';

                    shoot -> positionY++;

                }

                ((ShootParams*)params)->reloadBoss = 1;
            }

        }



    (void)params;

    free(shoot);
    return NULL;

}

void * MonsterShoot(void * params){

    Shoot * shoot = malloc(sizeof(Shoot));
    Monster * monster = malloc(sizeof(Monster));

    char letter = ((ShootParams*)params)->monster->firstLetter;

    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;

     for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i++) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y++){
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter){
                monster -> positionX = y;
                monster -> positionY = i;
            }
        }
    }

        shoot -> positionX = monster -> positionX;
        shoot -> positionY = monster -> positionY;

        if(((ShootParams*)params) -> reload == 1){

            if(((ShootParams*)params) -> directionView == 'R'){

                ((ShootParams*)params)->reloadMonster = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX + 2] == ' ' && ((ShootParams*)params)->reloadMonster  == 0 ){

                        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 4] == 'P'){
                            
                                if(((ShootParams*)params)->player->shield <= 0){
                                    ((ShootParams*)params)->player->hpMax -= 1;
                                } else {
                                    ((ShootParams*)params)->player->shield -= 1;
                                }
                                break;
        
                    }

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif



                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = ' ';
                    
                    shoot -> positionX =  shoot -> positionX + 2;

                }
        
                ((ShootParams*)params)->reloadMonster = 1;
        
            }

            if(((ShootParams*)params) -> directionView == 'L'){

                        ((ShootParams*)params)->reloadMonster = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX - 2] == ' ' && ((ShootParams*)params)->reloadMonster  == 0){

                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 4] == 'P'){
                            
                        if(((ShootParams*)params)->player->shield <= 0){
                            ((ShootParams*)params)->player->hpMax -= 1;
                        } else {
                            ((ShootParams*)params)->player->shield -= 1;
                        }
                        break;
        
                    }

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = ' ';
                    
                    
                    shoot -> positionX = shoot -> positionX - 2;

                }

                
                ((ShootParams*)params)->reloadMonster = 1;
        
            }

            if(((ShootParams*)params) -> directionView == 'T'){

                        ((ShootParams*)params)->reloadMonster = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY - 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reloadMonster  == 0){

                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY - 2][shoot->positionX] == 'P'){
                            
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                            break;
        
                    }


                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY-1][shoot->positionX] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY-1][shoot->positionX] = ' ';

                    shoot -> positionY--;

                }

                ((ShootParams*)params)->reloadMonster = 1;

            }

            if(((ShootParams*)params) -> directionView == 'B'){

                        ((ShootParams*)params)->reloadMonster = 0;

                while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY + 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reloadMonster  == 0){ 

                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 2][shoot->positionX] == 'P'){
                            
                                if(((ShootParams*)params)->player->shield <= 0){
                                    ((ShootParams*)params)->player->hpMax -= 1;
                                } else {
                                    ((ShootParams*)params)->player->shield -= 1;
                                }
                                break;
        
                    }

            
                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 1][shoot->positionX] = '*';

                    #ifdef _WIN32 
                        Sleep(290); 
                    #else 
                        usleep(29000); 
                    #endif

                    ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 1][shoot->positionX] = ' ';

                    shoot -> positionY++;

                }

                ((ShootParams*)params)->reloadMonster = 1;
            }

        }



    (void)params;

    free(shoot);
    return NULL;

}


void * Jagger(void *params){

    // Shoot * shoot = malloc(sizeof(Shoot));

    // int condition = 1;

    char letter = ((ShootParams*)params)->boss->firstLetter;

    for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i++) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y++){
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter){
                ((ShootParams*)params)->boss -> positionX = y;
                ((ShootParams*)params)->boss -> positionY = i;
            }
        }
    }

                
        int id = ((ShootParams*)params)->id;
        int stage = ((ShootParams*)params)->stage;
                    pthread_t thread;

    while(((ShootParams*)params)->condition){

        #ifdef _WIN32 
		Sleep(9090); 
		#else 
		usleep(500000); 
		#endif

        int shoot = 0;
        

        for (int i = 0; i < ((ShootParams*)params)->d -> stages[stage].rooms[id].height; i++) {

            for(int y = 0; y < ((ShootParams*)params)->d -> stages[stage].rooms[id].width; y++){

                if(((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] == letter){

                        (((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] = ' ');
                }
            }
        }

        int positionPlayerX = ((ShootParams*)params)->player -> positionX;
        int positionPlayerY = ((ShootParams*)params)->player -> positionY;

        int DiffPositionX = ((ShootParams*)params)->boss -> positionX - positionPlayerX;
        int DiffPositionY = ((ShootParams*)params)->boss -> positionY - positionPlayerY;

        int randMonster = rand() % 2;

        ((ShootParams*)params)->reload = 1;

        if(randMonster == 0){

            if(DiffPositionX > 0){
                
                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX-2] == ' '){
                    
                    ((ShootParams*)params)->boss -> positionX--;
                    ((ShootParams*)params)->boss -> positionX--;

                    ((ShootParams*)params) -> directionView = 'L';

                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX-2] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                            ((ShootParams*)params)->reload = 0;
                    }
                }

            }else{
            
                if(DiffPositionX < 0){

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX+2] == ' '){

                   ((ShootParams*)params)->boss -> positionX++;
                   ((ShootParams*)params)->boss -> positionX++;

                        ((ShootParams*)params) -> directionView = 'R';

                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX+2] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                            ((ShootParams*)params)->reload = 0;
                    }

                }

            }

            }
        
                    
        }else{

            if(DiffPositionY > 0){

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY-1][((ShootParams*)params)->boss ->positionX] == ' '){

                    ((ShootParams*)params) -> boss -> positionY--;
                    ((ShootParams*)params) -> directionView = 'T';
                    
                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY-1][((ShootParams*)params)->boss ->positionX] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                              shoot = 1;
                    }
                }

            }else if(DiffPositionY < 0){

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY+1][((ShootParams*)params)->boss ->positionX] == ' '){

                    ((ShootParams*)params)->boss -> positionY++;
                    ((ShootParams*)params) -> directionView = 'B';

                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY+1][((ShootParams*)params)->boss ->positionX] == 'P'){
                            if(((ShootParams*)params)->player->shield <= 0){
                                ((ShootParams*)params)->player->hpMax -= 1;
                            } else {
                                ((ShootParams*)params)->player->shield -= 1;
                            }
                            ((ShootParams*)params)->reload = 0;
                    }
                }


            }
                    
        }

        if(shoot == 0){
            pthread_create(&thread, NULL, BossShoot, params);
        }
        
        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX] == ' '){
            ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX] = letter;
        }


    }

    free(((ShootParams*)params)->boss);

    return 0;
}


void * Lenina(void *params) {

    char letter = ((ShootParams*)params)->boss->firstLetter;
    int height = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height;
    int width = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width;

    
    for (int i = 0; i < height; i+=1) { // set boss position
        for(int y = 0; y < width; y+=1) {
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter){
                ((ShootParams*)params)->boss -> positionX = y;
                ((ShootParams*)params)->boss -> positionY = i;
            }
        }
    }
    

                
        int id = ((ShootParams*)params)->id;
        int stage = ((ShootParams*)params)->stage;
                    pthread_t thread;

    while(((ShootParams*)params)->condition) {

        int random = rand() % 3;

            if(random == 2) {
                pthread_create(&thread, NULL, LeninaShoot, params);
            }

        #ifdef _WIN32 
		Sleep(9090); 
		#else 
		usleep(500000); 
		#endif
        

        for (int i = 0; i < height; i+=1) {

            for(int y = 0; y < width; y+=1) {

                if(((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] == letter){

                        (((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] = ' ');
                }
            }
        }

        //int positionPlayerX = ((ShootParams*)params)->player -> positionX;
        //int positionPlayerY = ((ShootParams*)params)->player -> positionY;

        //int randBoss = rand() % 2;

        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX] == ' '){
            ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->boss ->positionY][((ShootParams*)params)->boss ->positionX] = letter;
        }

    }

    free(((ShootParams*)params)->boss);

    return 0;
}

void * LeninaShoot(void * params) {

    Shoot * shoot = malloc(sizeof(Shoot));
    Boss * boss = malloc(sizeof(Boss));

    
    char letter = 'L';
    int height = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height;
    int width = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width;


    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;

    for (int i = 0; i < height; i+=1) { // set boss position
        for(int y = 0; y < width; y+=1) {
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter) {
                boss -> positionX = y;
                boss -> positionY = i;
            }
        }
    }

    shoot -> positionX = boss -> positionX;
    shoot -> positionY = boss -> positionY;

    // shoot right
    if(((ShootParams*)params)->player->positionX > boss->positionX) { 

        ((ShootParams*)params)->reloadBoss = 0;

        while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX + 2] == ' ' && ((ShootParams*)params)->reloadBoss  == 0 ){

            ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = '*';

            #ifdef _WIN32 
                Sleep(290); 
            #else 
                usleep(30000); 
            #endif

            ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = ' ';
            
            shoot -> positionX =  shoot -> positionX + 2;

        }

        ((ShootParams*)params)->reloadBoss = 1;
    
    }
    if(((ShootParams*)params)->d->stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[shoot->positionY][shoot->positionX + 2] == 'P'){
        playerLoseLife(((ShootParams*)params)->player, 1);
    }

    // shoot left
    if(((ShootParams*)params)->player->positionX < boss->positionX) {

        ((ShootParams*)params)->reloadBoss = 0;

        while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX - 2] == ' ' && ((ShootParams*)params)->reloadBoss  == 0){

            ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = '*';

            #ifdef _WIN32 
                Sleep(290); 
            #else 
                usleep(30000); 
            #endif

            ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = ' ';
            
            
            shoot -> positionX = shoot -> positionX - 2;

        }

        
        ((ShootParams*)params)->reloadBoss = 1;
    
    }
    if(((ShootParams*)params)->d->stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[shoot->positionY][shoot->positionX - 2] == 'P'){
        ((ShootParams*)params)->player->hpMax = ((ShootParams*)params)->player->hpMax - 1;
        if(((ShootParams*)params)->player->hpMax <= 0) { // dead player
            //Le joueur est mort, fin partie 
        }
    }

    // shoot BOTTOM
    if(((ShootParams*)params)->player->positionX == boss->positionX) { 

        ((ShootParams*)params)->reloadBoss = 0;
        

        while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY + 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reloadBoss  == 0 ) { 
            int placeIsNotBoss = ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX] != letter; // to avoid replacing the boss
            if(placeIsNotBoss) {
                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX] = '*';
            }

            #ifdef _WIN32 
                Sleep(290); 
            #else 
                usleep(33000); 
            #endif

            
            if(placeIsNotBoss) {
                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX] = ' ';
            }

            shoot -> positionY += 1;

        }

        ((ShootParams*)params)->reloadBoss = 1;
    }
    if(((ShootParams*)params)->d->stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[shoot->positionY+1][shoot->positionX] == 'P'){
        ((ShootParams*)params)->player->hpMax = ((ShootParams*)params)->player->hpMax - 1;
        if(((ShootParams*)params)->player->hpMax <= 0) { // dead player
            //Le joueur est mort, fin partie 
        }
    }



    (void)params;

    free(shoot);
    return NULL;

}

Monster* duplicateMonster(Monster* monster) {
    if(monster == NULL) {
        return NULL;
    }

    Monster* newMonster = malloc(sizeof(Monster)* 1);
    newMonster->idMonster = monster->idMonster;
    newMonster->name = duplicateString(monster->name);
    newMonster->firstLetter = newMonster->name[0];
    newMonster->hpMax = monster->hpMax;
    newMonster->shoot = monster->shoot;
    newMonster->ss = monster->ss;
    newMonster->flight = monster->flight;
    newMonster->dead = monster->dead;
    newMonster->positionX = monster->positionX;
    newMonster->positionX = monster->positionY;

    return newMonster;
}

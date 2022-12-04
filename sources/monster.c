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


void spawnMonster(Donjon * d, Monster * monster, int stage, int id){
    srand(time(NULL));
    int randomPositionX,randomPositionY;
    int heightRoom = d->stages[stage].rooms[id].height - 1;
    int widthRoom = d->stages[stage].rooms[id].width -2;
    while (1){
        randomPositionY = 1 + rand() % (heightRoom - 1);
        randomPositionX = 2 + rand() % (widthRoom - 2);
        if (randomPositionX % 2 == 0 && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX] == ' ' && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX - 2] != 'P' && d->stages[stage].rooms[id].room[randomPositionY][randomPositionX + 2] != 'P' && d->stages[stage].rooms[id].room[randomPositionY - 1][randomPositionX] != 'P' && d->stages[stage].rooms[id].room[randomPositionY + 1][randomPositionX] != 'P' ){
            monster->positionX = randomPositionX;
            monster->positionY = randomPositionY;
            break;
        }   
    } // la lettre doit correspondre au monstre 
    char letterForMonster = monster->name[0];
    letterForMonster = toupper(letterForMonster);
    monster->firstLetter = letterForMonster;
    d->stages[stage].rooms[id].room[monster->positionY][monster->positionX] = letterForMonster;        
}

void monsterShoot(Monster * monster, Player * player) {

    if(monster == NULL || player == NULL) {
        return;
    }
}

void * bossAthina(void *shootParams) {
    int BossPosX, BossPosY;
    Shoot * shoot = malloc(sizeof(Shoot));
    int reload = 1;
    Monster * Athina = malloc(sizeof(Monster));
    Athina->firstLetter = 'A';
    Athina->name = "Athina";
    Athina->hpMax = 450;
    Athina->shoot = 1;
    

    for (int i = 0; i < ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].height; i+=1) {
        for (int y = 0; y < ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].width; y+=1) {
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
    if (reload == 1){
        reload = 0;
        while(Athina->hpMax > 0 && ((ShootParams*)shootParams)->player->hpMax > 0){
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
        
    // if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == ((ShootParams*)shootParams)->monster->firstLetter){
    // 	((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
    // 	if(((ShootParams*)shootParams)->monster->hpMax <= 0){
    // 		((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
    }

    free(Athina);
    free(shoot);
    return 0;
}

void monsterFollowPlayerAndAttack(Monster * monster, Player * player) {
    while( player->positionX - 2 != monster->positionX ||player->positionX + 2 != monster->positionX || player->positionY - 1!= monster->positionY || player->positionY + 1!= monster->positionY) {
        if(player->positionX > monster->positionX) {
            monster->positionX += 2;
        } else if(player->positionX < monster->positionX) {
            monster->positionX -= 2;
        } else if(player->positionY > monster->positionY) {
            monster->positionY += 1;
        } else if(player->positionY < monster->positionY) {
            monster->positionY -= 1;
        }     
    }
    if(player->shield <= 0){
        player->hpMax -= 1;
    } else {
        player->shield -= 1;
    }
}

void monsterRandomMove(Monster * monster, Player * player) {
    if(monster == NULL || player == NULL) {
        return;
    }
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

Monster * getMonsterById(Monster * arrayMonster,int id) {

    struct Monster * monster = malloc(sizeof(struct Monster)*1);
    for(int i = 0; i < 9; i+=1) {
        if(arrayMonster[i].idMonster == (id)) {
            *monster = arrayMonster[i];
            return monster;
        }
    }

    return NULL;
}

void * BossShoot(void * params){

    Shoot * shoot = malloc(sizeof(Shoot));
    Monster * monster = malloc(sizeof(Monster));

    
    char letter = ((ShootParams*)params)->monster->firstLetter;

    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;

     for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i+=1) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y+=1){
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


            while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX + 2] == ' ' && ((ShootParams*)params)->reloadBoss  == 0 ){

                     if(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 4] == 'P'){
                        
                             ((ShootParams*)params)->player->hpMax -= 1;
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
                        
                    ((ShootParams*)params)->player->hpMax -= 1;
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
                        
                        ((ShootParams*)params)->player->hpMax -= 1;
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
                        
                             ((ShootParams*)params)->player->hpMax -= 1;
                             break;
    
                }

        
                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 1][shoot->positionX] = '*';

                #ifdef _WIN32 
                    Sleep(290); 
                #else 
                    usleep(29000); 
                #endif

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY + 1][shoot->positionX] = ' ';

                shoot -> positionY+=1;

            }

              ((ShootParams*)params)->reloadBoss = 1;
        }


        }



    (void)params;

    free(shoot);
    return NULL;

}

void * Jagger(void *params){

    // Shoot * shoot = malloc(sizeof(Shoot));

    // int condition = 1;

    char letter = ((ShootParams*)params)->monster->firstLetter;

    for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i+=1) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y+=1){
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter){
                ((ShootParams*)params)->monster -> positionX = y;
                ((ShootParams*)params)->monster -> positionY = i;
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
        

        for (int i = 0; i < ((ShootParams*)params)->d -> stages[stage].rooms[id].height; i+=1) {

            for(int y = 0; y < ((ShootParams*)params)->d -> stages[stage].rooms[id].width; y+=1){

                if(((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] == letter){

                        (((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] = ' ');
                }
            }
        }

        int positionPlayerX = ((ShootParams*)params)->player -> positionX;
        int positionPlayerY = ((ShootParams*)params)->player -> positionY;

        int DiffPositionX = ((ShootParams*)params)->monster -> positionX - positionPlayerX;
        int DiffPositionY = ((ShootParams*)params)->monster -> positionY - positionPlayerY;

        int randMonster = rand() % 2;

    //    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX-2] == 'P'
    //    || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionY-1] == 'P'
    //    || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionY+1] == 'P'
    //    || ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionY+2] == 'P'){
    //         ((ShootParams*)params)->player->hpMax -= 1;
    //         continue;
    //     }

        ((ShootParams*)params)->reload = 1;

        if(randMonster == 0){

            if(DiffPositionX > 0){
                
                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX-2] == ' '){
                    
                    ((ShootParams*)params)->monster -> positionX--;
                    ((ShootParams*)params)->monster -> positionX--;

                    ((ShootParams*)params) -> directionView = 'L';

                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX-2] == 'P'){
                            ((ShootParams*)params)->player->hpMax -= 1;
                            ((ShootParams*)params)->reload = 0;
                    }
                }

            }else if(DiffPositionX < 0){

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX-2] == ' '){

                   ((ShootParams*)params)->monster -> positionX+=1;
                   ((ShootParams*)params)->monster -> positionX+=1;

                    ((ShootParams*)params) -> directionView = 'R';

                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX-2] == 'P'){
                            ((ShootParams*)params)->player->hpMax -= 1;
                            ((ShootParams*)params)->reload = 0;
                    }
                }

            }
        
                    
        }else{

            if(DiffPositionY > 0){

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY-1][((ShootParams*)params)->monster ->positionX] == ' '){

                    ((ShootParams*)params) -> monster -> positionY--;
                    ((ShootParams*)params) -> directionView = 'T';
                    
                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY-1][((ShootParams*)params)->monster ->positionX] == 'P'){
                            ((ShootParams*)params)->player->hpMax -= 1;
                              shoot = 1;
                    }
                }

            }else if(DiffPositionY < 0){

                if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY+1][((ShootParams*)params)->monster ->positionX] == ' '){

                    ((ShootParams*)params)->monster -> positionY+=1;
                    ((ShootParams*)params) -> directionView = 'B';

                }else{
                    if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY+1][((ShootParams*)params)->monster ->positionX] == 'P'){
                            ((ShootParams*)params)->player->hpMax -= 1;
                            ((ShootParams*)params)->reload = 0;
                    }
                }


            }
                    
        }

        if(shoot == 0){
            pthread_create(&thread, NULL, BossShoot, params);
        }
        
        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX] == ' '){
            ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX] = letter;
        }


    }

    free(((ShootParams*)params)->monster);

    return 0;
}

void * Lenina(void *params) {

    char letter = ((ShootParams*)params)->monster->firstLetter;
    int height = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height;
    int width = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width;

    
    for (int i = 0; i < height; i+=1) { // set boss position
        for(int y = 0; y < width; y+=1) {
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter){
                ((ShootParams*)params)->monster -> positionX = y;
                ((ShootParams*)params)->monster -> positionY = i;
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

        //int randMonster = rand() % 2;

        if(((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX] == ' '){
            ((ShootParams*)params)->d->stages[stage].rooms[id].room[((ShootParams*)params)->monster ->positionY][((ShootParams*)params)->monster ->positionX] = letter;
        }

    }

    free(((ShootParams*)params)->monster);

    return 0;
}

void * LeninaShoot(void * params) {

    Shoot * shoot = malloc(sizeof(Shoot));
    Monster * monster = malloc(sizeof(Monster));

    
    char letter = 'L';
    int height = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height;
    int width = ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width;


    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;

    for (int i = 0; i < height; i+=1) { // set monster position
        for(int y = 0; y < width; y+=1) {
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == letter) {
                monster -> positionX = y;
                monster -> positionY = i;
            }
        }
    }

    shoot -> positionX = monster -> positionX;
    shoot -> positionY = monster -> positionY;

    // shoot right
    if(((ShootParams*)params)->player->positionX > monster->positionX) { 

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
    if(((ShootParams*)params)->player->positionX < monster->positionX) {

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
    if(((ShootParams*)params)->player->positionX == monster->positionX) { 

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

/**
 * @file monster.c
 * @author  Nairod36
 * @brief Fonctions des mobs
 * @version 0.2
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>     

#ifdef _WIN32 
#include <Windows.h>  
#else
#include <unistd.h>
#endif 

#include "include/monster.h"
#include "include/mystring.h"
#include "Room.h"
#include "Player.h"
#include "shoot.h"


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

void * bossAthina(void *shootParams){
    Shoot * shoot = malloc(sizeof(Shoot));

    Monster * Athina = malloc(sizeof(Monster));
    Athina->name = "Athina";
    Athina->hpMax = 450;
    Athina->shoot = 1;
    
    shoot->positionX = ((ShootParams*)shootParams)->player->positionX;
    shoot->positionY = ((ShootParams*)shootParams)->player->positionY;

        for (int i = 0; i < ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].height; i++) {
            for (int y = 0; y < ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].width; y++) {
                if (i == ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].height / 2 && y == ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].width / 2) {
                    if (y % 2 == 0) {
                        ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[i][y] = 'A';
                         shoot->positionX = y;
                         shoot->positionY = i;
                    } else {
                        ((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[i][y - 1] = 'A';
                        shoot->positionX = y-1;
                        shoot->positionY = i;
                    }
                }

            }
        }
        while(Athina->hpMax >= 0 || ((ShootParams*)shootParams)->player->hpMax >= 0){
            
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
		    if(((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] == ((ShootParams*)shootParams)->monster->firstLetter){
		    	((ShootParams*)shootParams)->monster->hpMax = ((ShootParams*)shootParams)->monster->hpMax - ((ShootParams*)shootParams)->player->dmg;
		    	if(((ShootParams*)shootParams)->monster->hpMax <= 0){
		    		((ShootParams*)shootParams)->d->stages[((ShootParams*)shootParams)->stage].rooms[((ShootParams*)shootParams)->id].room[shoot->positionY - 1][shoot->positionX] = ' ';
		    	}
		    }

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
    for(int i = 0; i < 9; i++) {
        if(arrayMonster[i].idMonster == (id)) {
            *monster = arrayMonster[i];
            return monster;
        }
    }

    return NULL;
}

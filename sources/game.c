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

#include <time.h>
#include "Room.h"
#include "Player.h"
#include "menu.h"
#include "game.h"
#include "shoot.h"

void OptimiseDoors(Donjon * d, int stage, int axeX, int axeY, int id, int numberOfRooms){

    int t = id;
    int DoorLeft = 0;
    int DoorRight = 0;
    int DoorTop = 0;
    int DoorBottom = 0;
    int width = 0;
    int Ir = 0, Vr = 0, Br = 0;
    int Il = 0, Vl = 0, Bl = 0;
    int It = 0, Vt = 0, Bt = 0;
    int Ib = 0, Vb = 0, Bb = 0;



    for(int i = 0; i < numberOfRooms; i++){
        for(int y = 0; y < numberOfRooms; y++){
            if(d->stages[stage].stage[i][y] == 'P'){

                for(int w = 0; w < numberOfRooms; w++) {

                    if(d->stages[stage].stage[i][w] == 'P'){
                        
                        if(d->stages[stage].stage[i + axeY][w + axeX + 1] != ' '){
                            DoorRight = 1;
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == 'V'){
                                Vr = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == 'I'){
                                Ir = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == 'B'){
                                Br = 1;
                            }
                            // printf("DoorRight");
                        }

                        if(d->stages[stage].stage[i + axeY][w + axeX - 1] !=' '){
                            DoorLeft = 1;
                            if(d->stages[stage].stage[i + axeY][w + axeX - 1] == 'V'){
                                Vl = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX - 1] == 'I'){
                                Il = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX - 1] == 'B'){
                                Bl = 1;
                            }

                            // printf("DoorLeft");
                        }

                        if(d->stages[stage].stage[i + axeY - 1 ][w + axeX]!=' '){
                            DoorTop = 1;
                            if(d->stages[stage].stage[i + axeY - 1][w + axeX] == 'V'){
                                Vt = 1;
                            }
                            if(d->stages[stage].stage[i + axeY - 1][w + axeX] == 'I'){
                                It = 1;
                            }
                            if(d->stages[stage].stage[i + axeY - 1][w + axeX] == 'B'){
                                Bt = 1;
                            }
                            // printf("DoorTop");
                        }

                        if(d->stages[stage].stage[i + axeY + 1][w + axeX]!=' '){
                            DoorBottom = 1;
                            if(d->stages[stage].stage[i + axeY + 1][w + axeX] == 'V'){
                                Vb = 1;
                            }
                            if(d->stages[stage].stage[i + axeY + 1][w + axeX] == 'I'){
                                Ib = 1;
                            }
                            if(d->stages[stage].stage[i + axeY + 1][w + axeX] == 'B'){
                                Bb = 1;
                            }

                            // printf("DoorBottom");
                        }
                         
                    }
                }
            }
        }
    }

    for(int i = 0; i < d->stages[stage].rooms[t].height; i++){
        for(int y = 0; y < d->stages[stage].rooms[t].width; y++){
            if(d->stages[stage].rooms[t].room[i][y] == 'D'){
                d->stages[stage].rooms[t].room[i][y] = 'W';
            }
        }
    }


    for(int i = 0; i < d->stages[stage].rooms[t].height-1; i++){
        for(int y = 0; y < d->stages[stage].rooms[t].width; y++){

            // DoorLeft
            if( y < d->stages[stage].rooms[t].width/2 && d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] == 'W' && DoorLeft == 1){
                

                if(Vl == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'V';
                }else  if(Il == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'I';
                }else if(Bl == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'B';
                }else{
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'D';
                }

                
            }

            // DoorRight
            if(y > d->stages[stage].rooms[t].width/2 && d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] == 'W' && DoorRight == 1){
     
                if(Vr == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'V';
                }else if(Ir == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'I';
                }else if(Br == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'B';
                }else{
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'D';
                }

            }

            // DoorTop

            if(d->stages[stage].rooms[t].width/2 % 2 == 0){
                width = d->stages[stage].rooms[t].width/2;
            }else{
                width = d->stages[stage].rooms[t].width/2-1;
            }

            if(d->stages[stage].rooms[t].room[0][width] == 'W' && DoorTop == 1){

                if(Vt == 1){
                    d->stages[stage].rooms[t].room[0][width] = 'V';
                }else if(It == 1){
                    d->stages[stage].rooms[t].room[0][width] = 'I';
                }else if(Bt == 1){
                    d->stages[stage].rooms[t].room[0][width] = 'B';
                }else{
                    d->stages[stage].rooms[t].room[0][width] = 'D';
                }
                                                                                       
            }

            // DoorBottom
             if(d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] == 'W' && DoorBottom == 1){

                if(Vb == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = 'V';
                }else if(Ib == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = 'I';
                }else if(Bb == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = 'B';
                }else{
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = 'D';
                }
                
                                                                                                     
            }


           
        }
    }

}

void checkName(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY, int t){

    for(int i = 0; i < numberOfRooms+2; i++){
        for(int y = 0; y < numberOfRooms+2; y++){
            if(d->stages[stage].stage[i][y] == 'P'){
                
                if( d->stages[stage].stage[i + axeY][y + axeX] == 'R'){
                    d->stages[stage].rooms[t].name = 'R';
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == 'I'){
                    d->stages[stage].rooms[t].name = 'I';
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == 'B'){
                    d->stages[stage].rooms[t].name = 'B';
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == 'V'){
                    d->stages[stage].rooms[t].name = 'V';
                }

            }
        }
    }
}

int gestionRoom(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY){

    int t = 0;

    if(axeX != 0 && axeY != 0){
        t++;
    }
    
    for(int i = 0; i < numberOfRooms+2; i++){
        for(int y = 0; y < numberOfRooms+2; y++){
            if(d->stages[stage].stage[i][y] == 'P'){

                for(int t = 0; t < numberOfRooms; t++) {

                    if(d->stages[stage].rooms[t].roomUsed == 1){

                        if(d->stages[stage].rooms[t].AxeX == axeX && d->stages[stage].rooms[t].AxeY == axeY){

                            return t;
                        }

                    }             

                }            
            }
        }
    }

    (void)axeX;
    (void)axeY;

    return 0;
}

void SetColorAndPositionForPlayer(Donjon *d, Player *player, int stage, int id ){

    for (int i = 0; i < d -> stages[stage].rooms[id].height; i++) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y++) {
            if (i == d -> stages[stage].rooms[id].height / 2 && y == d -> stages[stage].rooms[0].width / 2) {
                if (y % 2 == 0) {
                    d -> stages[stage].rooms[id].room[i][y] = 'P';
                } else {
                    d -> stages[stage].rooms[id].room[i][y + 1] = 'P';
                }
            }

        }
    }

    for (int i = 0; i < d -> stages[stage].rooms[id].height; i++) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y++) {
            if (y % 2 == 0) {
                if (d -> stages[stage].rooms[id].room[i][y] == 'P') {
                    player -> positionX = y;
                    player -> positionY = i;
                }
            }
        }
    }

    for (int i = 0; i < d->stages[stage].rooms[id].height; i++) {
				for (int y = 0; y < d->stages[stage].rooms[id].width; y++) {
					if (y % 2 == 0) {
						if(d-> stages[stage].rooms[id].room[i][y] == 'P'){
							printf("%s", KRED);
							printf("%c ", d-> stages[stage].rooms[id].room[i][y]);
							printf("%s", KNRM);
						}else{
							printf("%c ", d-> stages[stage].rooms[id].room[i][y]);
						}
					}
				}
				printf("\n");
				
			}

}

void InitialiseBossRoom(Donjon * d, int stage, int id){

    for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
        for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
            if (y % 2 == 0) {
                if(i == d->stages[stage].rooms[id].height / 2 && y == d->stages[stage].rooms[id].width / 2){
                    d->stages[stage].rooms[id].room[i][y] = 'B';
                }
            }

        }
            
    }


   

}

void gestionGame(Donjon * d, int stage, int * change) {
    
    int NumberOfRoomsInt;
    int axeX = 0;
    int axeY = 0;
    int id = 0;
    int *pId = &id;
    int hp = 100;
    int *pHp = &hp;
    int changeOfRoom = 1;
    int chargeBoss = 0;

    int iteration = 0;
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

    NumberOfRoomsInt = numberOfRooms();
    InitialiseOtherRoomsFromArms(d,stage, NumberOfRoomsInt);
    SetColorAndPositionForPlayer(d, player, stage, id);

    for (int i = 0; i < NumberOfRoomsInt; i++) {
        printf("ID : %d\n", d-> stages[stage].rooms[i].id);
        
        for(int y = 0; y < d-> stages[stage].rooms[i].height; y++) {
            for(int v = 0; v < d-> stages[stage].rooms[i].width; v++) {
                printf("%c", d-> stages[stage].rooms[i].room[y][v]);
            }
        }
    }




	while (condition) {

        SDL_Delay(35);

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

            switch (c) {
				case 'z':

                    if(d->stages[stage].rooms[id].room[player->positionY - 1][player->positionX] != 'W' ){

                        d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
                        player->positionY--;

                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }
                        
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){
                            axeY--;

                             for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
                                        for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
                                            if(d->stages[stage].rooms[id].room[i][y] == 'P'){
                                                d->stages[stage].rooms[id].room[i][y] = ' ';
                                            }
                                        }
                                    }

                            player->positionY = d->stages[stage].rooms[id].height - 2;
                            changeOfRoom = 1;

                          
                           
                         
                        }else{

                             d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						    player->directionView = 'd';

                        }

                    }

					break;

				case 's':

					if (d->stages[stage].rooms[id].room[player->positionY + 1][player->positionX] != 'W') {

						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionY++;
                        
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }

                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){
                                axeY++;

                                 for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
                                        for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
                                            if(d->stages[stage].rooms[id].room[i][y] == 'P'){
                                                d->stages[stage].rooms[id].room[i][y] = ' ';
                                            }
                                        }
                                    }

                                 player->positionY = 1;
                                 changeOfRoom = 1;

                              
                           
                               
                       }else{

                             d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						    player->directionView = 's';

                        }

					}
					break;

				case 'q':

					if (d->stages[stage].rooms[id].room[player->positionY][player->positionX - 2] != 'W') {

						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionX -= 2;

                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }
					
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX ] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){                                                                
                                axeX--;

                                 for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
                                        for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
                                            if(d->stages[stage].rooms[id].room[i][y] == 'P'){
                                                d->stages[stage].rooms[id].room[i][y] = ' ';
                                            }
                                        }
                                    }
                           
                                if((d->stages[stage].rooms[id].width - 3) % 2 == 0){
                                    player->positionX = d->stages[stage].rooms[id].width - 5;
                                }else{
                                    player->positionX = d->stages[stage].rooms[id].width - 4;
                                }

                                changeOfRoom = 1;
                           

                        }else{

                             d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						    player->directionView = 'q';

                        }

					}
				
                break;
                    
				case 'd':

					if (d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2] != 'W') {
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionX += 2;
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }
				
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){
                                axeX++;

                                 for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
                                        for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
                                            if(d->stages[stage].rooms[id].room[i][y] == 'P'){
                                                d->stages[stage].rooms[id].room[i][y] = ' ';
                                            }
                                        }
                                    }
                                
                           
                                player->positionX = 2;
                                changeOfRoom = 1;

                             

                        }else{

                             d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						    player->directionView = 'd';

                        }


                        
					}
                
                break;
			}

            for (int v = 0; v < NumberOfRoomsInt + 2; v++) {
                for (int y = 0; y < NumberOfRoomsInt + 2; y++) {

                    printf("%c ", d->stages[stage].stage[v][y]);

                }
                printf("\n");
            }
           
            if(changeOfRoom == 1){
                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);                  
                OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                checkName(d, NumberOfRoomsInt, stage, axeX, axeY, id);
                (void)*pHp;
                
                changeOfRoom = 0;
            }
            
            if(d->stages[stage].rooms[id].name == 'B'){
                if(chargeBoss == 0){
                    InitialiseBossRoom(d, stage, id);      
                    chargeBoss = 1;
                }
                    
            }
    

            printf("Axe Position X : %d / and Position Y : %d\n", axeX, axeY);
            printf("ETAGE : %d\n", stage);
            printf("Name : %c\n",d->stages[stage].rooms[id].name);
            printf("ID : %d\n", id);
            printf("\n");
            printf("HP : %d\n", hp);

			for (int i = 0; i < d->stages[stage].rooms[id].height; i++) {
				for (int y = 0; y < d->stages[stage].rooms[id].width - 1; y++) {
					if (y % 2 == 0) {
						if(d-> stages[stage].rooms[id].room[i][y] == 'P'){
					
							printf("%c ", d-> stages[stage].rooms[id].room[i][y]);
		
						}else{
							printf("%c ", d-> stages[stage].rooms[id].room[i][y]);
						}
					}
				}
				printf("\n");
				
			}


            printf("Player position : %d, %d / Player direction : %c / Iteration : %d \n", player->positionX, player->positionY, player->directionView, iteration);
                
            if( * change == 1){
                condition = false;
            }

            printf("reload : %d\n",shootParams->reload);
            if (shootParams->reload == 1){
            	pthread_t t1;
            	pthread_create(&t1, NULL, bangishard, shootParams);
            }

            continue;
        }

    }


    // (void)condition;
    // (void)c;
    // (void)iteration;
    // (void)chargeBoss;
    // (void)changeOfRoom;
    // (void)pHp;
    // (void)pId;
    // (void)axeX;
    // (void)axeY;
    // (void)change;

    free(player);
    free(shootParams);

}
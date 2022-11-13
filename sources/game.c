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

void gestionGame(Donjon * d, int stage);


void OptimiseDoors(Donjon * d, int stage, int axeX, int axeY, int id, int numberOfRooms){

    int t = id;
    int DoorLeft = 0;
    int DoorRight = 0;
    int DoorTop = 0;
    int DoorBottom = 0;

    for(int i = 0; i < numberOfRooms; i++){
        for(int y = 0; y < numberOfRooms; y++){
            if(d->stages[stage].stage[i][y] == 'P'){

                for(int w = 0; w < numberOfRooms; w++) {

                    if(d->stages[stage].stage[i][w] == 'P'){
                        
                        if(d->stages[stage].stage[i][w+1+axeX] != ' '){
                            DoorRight = 1;
                            // printf("DoorRight");
                        }

                        if(d->stages[stage].stage[i][w-1+axeX] !=' '){
                            DoorLeft = 1;
                            // printf("DoorLeft");
                        }

                        if(d->stages[stage].stage[i-1+axeY][w]!=' '){
                            DoorTop = 1;
                            // printf("DoorTop");
                        }

                        if(d->stages[stage].stage[i+1+axeY][w]!=' '){
                            DoorBottom = 1;
                            // printf("DoorBottom");
                        }
                         
                    }
                }
            }
        }
    }

    for(int i = 0; i < d->stages[stage].rooms[t].height; i++){
        for(int y = 0; y < d->stages[stage].rooms[t].width+1; y++){
            if(d->stages[stage].rooms[t].room[i][y] == 'D'){
                d->stages[stage].rooms[t].room[i][y] = 'W';
            }
        }
    }

    int width = 0;

    for(int i = 0; i < d->stages[stage].rooms[t].height-1; i++){
        for(int y = 0; y < d->stages[stage].rooms[t].width; y++){

            // DoorLeft
            if( y < d->stages[stage].rooms[t].width/2 && d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] == 'W' && DoorLeft == 1){
                d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'D';
                
            }

            // DoorRight
            if(y > d->stages[stage].rooms[t].width/2 && d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] == 'W' && DoorRight == 1){
                d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = 'D';
            }

            // DoorTop

            if(d->stages[stage].rooms[t].width/2 % 2 == 0){
                width = d->stages[stage].rooms[t].width/2;
            }else{
                width = d->stages[stage].rooms[t].width/2-1;
            }

            if(d->stages[stage].rooms[t].room[0][width] == 'W' && DoorTop == 1){
                d->stages[stage].rooms[t].room[0][width] = 'D';                                                                                          
            }

            // DoorBottom
             if(d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] == 'W' && DoorBottom == 1){
                d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = 'D';                                                                                         
            }


           
        }
    }

}

int gestionRoom(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY){
    
    for(int i = 0; i < numberOfRooms; i++){
        for(int y = 0; y < numberOfRooms; y++){
            if(d->stages[stage].stage[i][y] == 'P'){

                for(int t = 0; t < numberOfRooms; t++) {

                    if(d->stages[stage].rooms[t].roomUsed == 1){
                        // printf("ITERATION OF T : %d /AXE X : %d, Y : %d\n", t, d->stages[stage].rooms[t].AxeX, d->stages[stage].rooms[t].AxeY);


                        if(d->stages[stage].rooms[t].AxeX == axeX && d->stages[stage].rooms[t].AxeY == axeY){
                            printf("ROOM FOUND\n");

                            for (int i = 0; i < d->stages[stage].rooms[t].height-1; i++) {
                                for (int y = 0; y < d->stages[stage].rooms[t].width - 1; y++) {
                                    if (y % 2 == 0) {
                                        printf("%c ", d-> stages[stage].rooms[t].room[i][y]);
                                    }
                                }
                                printf("\n");
                                
                            }

                            return t;
                        }

                    }

                    // print d-> stages[stage].rooms[iteration].room                 

                }

                // printf("\n");
                //  printf("\n");


                // for(int t = 0; t < numberOfRooms; t++) {

                //     printf("ROOM UTILISES [%d] USED : %d / and AXEX %d and AXEY %d\n",t,d->stages[stage].rooms[t].roomUsed,d->stages[stage].rooms[t].AxeX,d->stages[stage].rooms[t].AxeY );            

                // }




                
            }
        }
    }

    (void)axeX;
    (void)axeY;

    return 0;
}

void gestionGame(Donjon * d, int stage) {
    (void) d;
    
    int iterationTest = 0;
    int NumberOfRoomsInt;
    int axeX = 0;
    int axeY = 0;

    int id = 0;
    int *pId = &id;
    

        int iteration = 0;
        bool condition = true;
        int c;

        NumberOfRoomsInt = numberOfRooms();
        printf("Number of rooms : %d\n", NumberOfRoomsInt);

    InitialiseOtherRoomsFromArms(d,stage, NumberOfRoomsInt);

    Player * player = malloc(sizeof(Player));
	player->positionX = 1;
	player->positionY = 1;
	player->directionView = 'D';

    ShootParams *shootParams = malloc(sizeof(struct ShootParams));
    shootParams->reload = 1;
    shootParams->player = player;
    shootParams->d = d;
    
    OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );

    // void OptimiseDoors(Donjon * d, int stage, int axeX, int axeY, int id, int numberOfRooms)
	
    // Initialise P at the start, start one time

    for (int i = 0; i < d -> stages[stage].rooms[id].height; i++) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y++) {
            if (i == d -> stages[stage].rooms[id].height / 2 && y == d -> stages[0].rooms[0].width / 2) {
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
				for (int y = 0; y < d->stages[stage].rooms[id].width - 1; y++) {
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

    iterationTest++;   

    printf("ID RESULT : %d\n", gestionRoom(d, NumberOfRoomsInt, stage, 1, 0));
     printf("ID RESULT : %d\n", gestionRoom(d, NumberOfRoomsInt, stage, 0, 1));
     printf("ID RESULT : %d\n", gestionRoom(d, NumberOfRoomsInt, stage, -2, 0));



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
					if (d->stages[stage].rooms[id].room[player->positionY - 1][player->positionX] != 'W') {
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionY--;
                        d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						player->directionView = 'z';

                        if(d->stages[stage].rooms[id].room[player->positionY - 1][player->positionX] == 'D'){
                                axeY--;
                                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);
                                OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                                
                                player->positionY = d->stages[stage].rooms[id].height - 3;
                        }
					}
					break;
				case 's':
					if (d->stages[stage].rooms[id].room[player->positionY + 1][player->positionX] != 'W') {
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionY++;
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						player->directionView = 's';

                        if(d->stages[stage].rooms[id].room[player->positionY + 1][player->positionX] == 'D'){
                                axeY++;
                                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);
                                OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                                
                                player->positionY = 2;
                                

                        }
					}
					break;
				case 'q':
					if (d->stages[stage].rooms[id].room[player->positionY][player->positionX - 2] != 'W') {
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionX -= 2;
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';
						player->directionView = 'q';

                           if(d->stages[stage].rooms[id].room[player->positionY][player->positionX + 1] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2] == 'D' ){                                                                
                                axeX--;
                                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);
                                 OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                           
                                if((d->stages[stage].rooms[id].width - 3) % 2 == 0){
                                    player->positionX = d->stages[stage].rooms[id].width - 5;
                                }else{
                                    player->positionX = d->stages[stage].rooms[id].width - 4;
                                }

                    


                            }
					}
					break;
				case 'd':
					if (d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2] != 'W') {
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionX += 2;
						d->stages[0].rooms[id].room[player->positionY][player->positionX] = 'P';
						player->directionView = 'd';

                           if(d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX + 1] == 'D'){
                                axeX++;
                                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);
                                OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                              
                                player->positionX = 2;

                            }

                        
					}
			}

            for (int v = 0; v < NumberOfRoomsInt + 2; v++) {
                for (int y = 0; y < NumberOfRoomsInt + 2; y++) {

                    printf("%c ", d->stages[stage].stage[v][y]);

                }
                printf("\n");
            }

            printf("Axe Position X : %d / and Position Y : %d\n", axeX, axeY);
            printf("ID : %d\n", id);

            printf("\n");
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


            printf("Player position : %d, %d / Player direction : %c / Iteration : %d / IterationTest : %d\n", player->positionX, player->positionY, player->directionView, iteration, iterationTest);
                
            //     printf("reload : %d\n",shootParams->reload);
            //     if (shootParams->reload == 1){
            //     	//do{
            //     		SDL_Delay(35);
                        
            //     		shootParams->reload = 0;
            //     		pthread_t t1;
            //     		pthread_create(&t1, NULL, bangishard, shootParams);
            //     	//}while(shootParams->reload == 1);
            //     }
                continue;

            free(d);
            free(player);
            // free(shootParams);
        }

    }

}
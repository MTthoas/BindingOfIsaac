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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

#include "include/mystring.h"
#include <time.h>
#include "Room.h"
#include "Player.h"
#include "menu.h"
#include "game.h"
#include "shoot.h"
#include "lectureFichiers.h"


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
            if(d->stages[stage].rooms[t].room[i][y] == 'D' || d->stages[stage].rooms[t].room[i][y] == 'V' || d->stages[stage].rooms[t].room[i][y] == 'I' || d->stages[stage].rooms[t].room[i][y] == 'B'){
                d->stages[stage].rooms[t].room[i][y] = 'W';
            }
        }
    }

    if(axeX == 0 && axeY == 0 ){
        for(int i = 0; i < d->stages[stage].rooms[t].height; i++){
            for(int y = 0; y < d->stages[stage].rooms[t].width; y++){
                if(i != 0 && i < d->stages[stage].rooms[t].height - 1 && y != 0 && y < d->stages[stage].rooms[t].width - 2){
                    if(d->stages[stage].rooms[t].room[i][y] == 'D' || d->stages[stage].rooms[t].room[i][y] == 'V' || d->stages[stage].rooms[t].room[i][y] == 'I' || d->stages[stage].rooms[t].room[i][y] == 'H' || d->stages[stage].rooms[t].room[i][y] == 'I'){
                        d->stages[stage].rooms[t].room[i][y] = ' ';
                    }
                }
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

void gestionPassing(Donjon *d, Player * player, int stage, int id, int NumberOfRoomsInt){

           for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
                for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
                    if(d->stages[stage].rooms[id].room[i][y] == 'P'){
                        d->stages[stage].rooms[id].room[i][y] = ' ';
                    }
                }
            }

            d->stages[stage].rooms[id].room[player->positionY][player->positionX] = 'P';

            for (int v = 0; v < NumberOfRoomsInt + 2; v++) {
                for (int y = 0; y < NumberOfRoomsInt + 2; y++) {

                    printf("%c ", d->stages[stage].stage[v][y]);

                }
                printf("\n");
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
            if (i == d -> stages[stage].rooms[id].height / 2 && y == d -> stages[stage].rooms[id].width / 2) {
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

void * BossShoot(void * params){

    Shoot * shoot = malloc(sizeof(Shoot));
    Monster * monster = malloc(sizeof(Monster));

    int id = ((ShootParams*)params)->id;
    int stage = ((ShootParams*)params)->stage;

     for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i++) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y++){
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == 'H'){
                monster -> positionX = y;
                monster -> positionY = i;
            }
        }
    }

        shoot -> positionX = monster -> positionX;
        shoot -> positionY = monster -> positionY;

        if(((ShootParams*)params) -> directionView == 'R'){

            ((ShootParams*)params)->reload = 0;

            while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX + 2] == ' ' && ((ShootParams*)params)->reload  == 0 ){

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = '*';

                #ifdef _WIN32 
                    Sleep(290); 
                #else 
                    usleep(29000); 
                #endif

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX + 2] = ' ';
                
                shoot -> positionX =  shoot -> positionX + 2;

            }
    
            ((ShootParams*)params)->reload = 1;
       
        }

        if(((ShootParams*)params) -> directionView == 'L'){

            ((ShootParams*)params)->reload = 0;

            while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY][shoot->positionX - 2] == ' ' && ((ShootParams*)params)->reload  == 0){

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = '*';

                #ifdef _WIN32 
                    Sleep(290); 
                #else 
                    usleep(29000); 
                #endif

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX - 2] = ' ';
                
                
                shoot -> positionX = shoot -> positionX - 2;

            }

            
            ((ShootParams*)params)->reload = 1;
       
        }

        if(((ShootParams*)params) -> directionView == 'T'){

            while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY - 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reload  == 0){

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX] = '*';

                #ifdef _WIN32 
                    Sleep(290); 
                #else 
                    usleep(290000); 
                #endif

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX] = ' ';

                shoot -> positionY--;

            }

            ((ShootParams*)params)->reload = 1;

        }

        if(((ShootParams*)params) -> directionView == 'B'){

            while(((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot->positionY + 1][shoot->positionX] == ' ' && ((ShootParams*)params)->reload  == 0){ 

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX] = '*';

                #ifdef _WIN32 
                    Sleep(290); 
                #else 
                    usleep(290000); 
                #endif

                ((ShootParams*)params)->d->stages[stage].rooms[id].room[shoot -> positionY][shoot->positionX] = ' ';

                shoot -> positionY++;

            }

              ((ShootParams*)params)->reload = 1;
        }


    (void)params;

    free(shoot);



    return NULL;

}


void * Jagger(void *params){

    // Shoot * shoot = malloc(sizeof(Shoot));

    Monster * monster = malloc(sizeof(Monster));
    int condition = 1;

    for (int i = 0; i < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].height; i++) {
        for(int y = 0; y < ((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].width; y++){
            if(((ShootParams*)params)->d -> stages[((ShootParams*)params)->stage].rooms[((ShootParams*)params)->id].room[i][y] == 'H'){
                monster -> positionX = y;
                monster -> positionY = i;
            }
        }
    }

    while(condition){

        #ifdef _WIN32 
		Sleep(9013); 
		#else 
		usleep(901300); 
		#endif
        
        
        int positionPlayerX = ((ShootParams*)params)->player -> positionX;
        int positionPlayerY = ((ShootParams*)params)->player -> positionY;
        int id = ((ShootParams*)params)->id;
        int stage = ((ShootParams*)params)->stage;

          ((ShootParams*)params)->reload = 0;
        

        for (int i = 0; i < ((ShootParams*)params)->d -> stages[stage].rooms[id].height; i++) {

            for(int y = 0; y < ((ShootParams*)params)->d -> stages[stage].rooms[id].width; y++){

                if(((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] == 'H'){

                        (((ShootParams*)params)->d -> stages[stage].rooms[id].room[i][y] = ' ');
                }
            }
        }



        int DiffPositionX =  monster -> positionX - positionPlayerX;
        int DiffPositionY =  monster -> positionY - positionPlayerY;

        if(DiffPositionX > 1){
            
            monster -> positionX--;
            monster -> positionX--;

            ((ShootParams*)params) -> directionView = 'L';

        }else if(DiffPositionX < 1){

            monster -> positionX++;
            monster -> positionX++;

           ((ShootParams*)params) -> directionView = 'R';

        }

        if(DiffPositionY > 1){

            monster -> positionY--;

            ((ShootParams*)params) -> directionView = 'T';

        }else if(DiffPositionY < 1){

            monster -> positionY++;

            ((ShootParams*)params) -> directionView = 'B';
            

        }
     
        ((ShootParams*)params)->d->stages[stage].rooms[id].room[monster->positionY][monster->positionX] = 'H';

        int random = rand() % 4;

        if(random == 0 && ((ShootParams*)params)->reload == 0){

            pthread_t thread;
            pthread_create(&thread, NULL, BossShoot, params);

        }

    }

    free(monster);

    return 0;
}

void InitialiseBossRoom(Donjon * d, int stage, int id){

     for (int i = 0; i < d -> stages[stage].rooms[id].height; i++) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y++) {
            if (i == d -> stages[stage].rooms[id].height / 2 && y == d -> stages[stage].rooms[id].width / 2) {
                if (y % 2 == 0) {
                    d -> stages[stage].rooms[id].room[i][y] = 'H';
                } else {
                    d -> stages[stage].rooms[id].room[i][y - 1] = 'H';
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
    int bossActive = 0;

    int iteration = 0;
    bool condition = true;
    int c;

    Player * player = malloc(sizeof(Player));
    player->dmg = 1;
    player->hpMax = 5;
    player->shield = 5;
	player->positionX = 1;
	player->positionY = 1;
	player->directionView = 'D';

    ShootParams *shootParams = malloc(sizeof(struct ShootParams));
    shootParams->reload = 1;
    shootParams->player = player;
    shootParams->d = d;
    shootParams->stage = stage;
    shootParams->id = id;

    NumberOfRoomsInt = numberOfRooms();
    InitialiseOtherRoomsFromArms(d,stage, NumberOfRoomsInt);
    SetColorAndPositionForPlayer(d, player, stage, id);

    for (int i = 0; i < NumberOfRoomsInt; i++) {
        printf("ID : %d\n", d-> stages[stage].rooms[i].id);
        printf("AxeX : %d\n", d-> stages[stage].rooms[i].AxeX);
        printf("AxeY : %d\n", d-> stages[stage].rooms[i].AxeY);
        
        for(int y = 0; y < d-> stages[stage].rooms[i].height; y++) {
            for(int v = 0; v < d-> stages[stage].rooms[i].width; v++) {
                printf("%c", d-> stages[stage].rooms[i].room[y][v]);
            }
        }
    }

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

        if (c == 'm') {

            Monster * arrayMonster = fichierMonsterToListeMonster();
            
            Monster * monster = getMonsterById(arrayMonster, 0);
            
            spawnMonster(d, monster, stage, id);
            shootParams->monster = monster;

        }

		if (c != 'e') {
 
			system("clear");

            switch (c) {

				case 'z':

                    if( d->stages[stage].rooms[id].name == 'B' ){
                        bossActive = 1;
                    }

                    player->directionView = 'z';

                    if(d->stages[stage].rooms[id].room[player->positionY - 1][player->positionX] != 'W' && d->stages[stage].rooms[id].room[player->positionY - 1][player->positionX] != 'H'){

                        d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
                        player->positionY--;

                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }
                        
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){
                            axeY--;

                            //   int temp2 = gestionRoom(d, stage, id, axeX, axeY);

                            player->positionY = d->stages[stage].rooms[id].height - 2;
                            changeOfRoom = 1;   
                        }
                    }
				break;

				case 's':

                   if( d->stages[stage].rooms[id].name == 'B' ){
                        bossActive = 1;
                    }

                    player->directionView = 's';

					if (d->stages[stage].rooms[id].room[player->positionY + 1][player->positionX] != 'W' && d->stages[stage].rooms[id].room[player->positionY + 1][player->positionX] != 'H') {


						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionY++;
                        
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }

                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){
                                axeY++;

                                

                                 player->positionY = 1;
                                 changeOfRoom = 1;   
                               
                       }

					}
				break;

				case 'q':
                
                   if( d->stages[stage].rooms[id].name == 'B' ){
                        bossActive = 1;
                    }

                    player->directionView = 'q';
                    

					if (d->stages[stage].rooms[id].room[player->positionY][player->positionX - 2] != 'W' && d->stages[stage].rooms[id].room[player->positionY][player->positionX - 2] != 'H') {

						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionX -= 2;

                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }
					
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX ] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){                                                                
                                axeX--;

                               if((d->stages[stage].rooms[id].width - 2) % 2 == 0){
                                    player->positionX = d->stages[stage].rooms[id].width - 4;
                                }else{
                                    player->positionX = d->stages[stage].rooms[id].width - 3;
                                }
                                
                                changeOfRoom = 1;
                           

                        }

					}
                break;
                    
				case 'd':

                   if( d->stages[stage].rooms[id].name == 'B' ){
                        bossActive = 1;
                    }

                    player->directionView = 'd';

					if (d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2] != 'W' && d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2] != 'H') {
						d->stages[stage].rooms[id].room[player->positionY][player->positionX] = ' ';
						player->positionX += 2;
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'N'){
                            * change = 1;
                            break;
                        }
				
                        if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'D' || d->stages[stage].rooms[id].room[player->positionY][player->positionX] == 'B'){
                                axeX++;
                                                    
                                player->positionX = 2;
                                changeOfRoom = 1;             

                        }
                        
					}

                break;

                case '8': ;
                    // Shoot Up
                    Monster * monsterVide = malloc(sizeof(Monster));
                    if (shootParams->reload == 1){
                        if( shootParams->monster == NULL){
                            shootParams->monster = monsterVide;
                        }
                    pthread_t t2;
                    pthread_create(&t2, NULL, shootUp, shootParams);                    
                    }
                    free(monsterVide);
                break;
                
                case '5': ;
                    // Shoot Down
                    Monster * monsterVide2 = malloc(sizeof(Monster));
                    if (shootParams->reload == 1){
                        if( shootParams->monster == NULL){
                            shootParams->monster = monsterVide2;
                        }
                    pthread_t t3;
                    pthread_create(&t3, NULL, shootDown, shootParams);
                    }
                    free(monsterVide2);

                break;
                
                case '4': ;
                    // Shoot Left
                    Monster * monsterVide3 = malloc(sizeof(Monster));
                    if (shootParams->reload == 1){
                        if( shootParams->monster == NULL){
                            shootParams->monster = monsterVide3;
                        }
                    pthread_t t4;
                    pthread_create(&t4, NULL, shootLeft, shootParams);
                    }
                    free(monsterVide3);
                break;

                case '6': ;
                    // Shoot Right
                    pthread_t t5;
                    Monster * monsterVide4 = malloc(sizeof(Monster));
                    if (shootParams->reload == 1){
                        if( shootParams->monster == NULL){
                            shootParams->monster = monsterVide4;
                        }
                    pthread_create(&t5, NULL, shootRight, shootParams);
                    }
                    free(monsterVide4);
                break;
                

			}

            if(bossActive == 1){
                
                    pthread_t thread;
                    Monster * Boss = malloc(sizeof(Monster));

                    if(stage == 0){
                        Boss->name = "Jagger";
                        Boss->hpMax = 100;
                        Boss->shoot = 1;
                        if( shootParams->monster == NULL){
                            shootParams->monster = Boss;
                        }

                        pthread_create(&thread, NULL, Jagger, shootParams);
                    }

                    bossActive = 0;         

            }

            gestionPassing(d, player, stage, id, NumberOfRoomsInt);

           
            if(changeOfRoom == 1){
                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);                  
                OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                checkName(d, NumberOfRoomsInt, stage, axeX, axeY, id);
                shootParams->id = id;
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
            printf("Width : %d\n", d->stages[stage].rooms[id].width);
            printf("Height : %d\n", d->stages[stage].rooms[id].height);
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
    //free(shootParams);

}
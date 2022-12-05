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
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <pthread.h>

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

#include "include/mystring.h"
#include "game.h"
#include "shoot.h"

void gestionGame(Donjon * d, ShootParams *shootParams, Boss * Boss, int stage, int * change, Player* player, int NumberOfRoomsInt, int id, int axeX, int axeY) {

    int *pId = &id;
    int changeOfRoom = 1;
    int bossActive = 0;
    int BossInfinite = 0;
    int itemIsSet = 0;
    char FuturPosition = EMPTY;
    char actualPosition = EMPTY;


    int iteration = 0;
    bool condition = true;  
    int spawnMonsterVar = 0;


    Monster * monsterVide = malloc(sizeof(Monster));
    monsterVide->hpMax = 999;
    struct Boss * bossVide = malloc(sizeof(Boss));
    bossVide->hpMax = 999;
    
    pthread_t thread;
    int c;

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

        if(player->hpMax <= 0){
            *pId = 0;
            condition = false;
            player->stageAxeX = 0;
            player->stageAxeY = 0;
            PurgeRoomOfBoss(d, stage, id);
            GestionDoorsForMobRoom(d, stage, id, 1);
            d->stages[stage].rooms[id].name = PLAYER;
            pthread_cancel(thread);
            break;
        }

        c = 'p';
		iteration++;

		if (kbhit()) {
			c = getchar();
		}
        
		if (c == 'x') { // glitch to de-lock doors without beating the monsters
            GestionDoorsForMobRoom(d, stage, id, 1);
		}

        // if (c == 'm') {

        //     Monster * monster = getMonsterById(arrayMonster, 1);
            
        //     spawnMonster(d, monster, stage, id);
        //     shootParams->monster = monster;

        // }

		if (c != 'e') {
 
			system("clear");

            switch (c) {

				case 'z':

                    if( d->stages[stage].rooms[id].name == BOSS_ROOM_NAME ){
                        bossActive = 1;
                    }

                    // Initialisation
                    player->directionView = 'z';
                    FuturPosition = d->stages[stage].rooms[id].room[player->positionY - 1][player->positionX]; 
                    
                    if(FuturPosition == EMPTY 
                    || FuturPosition == DOOR 
                    || FuturPosition == BOSS_ROOM_DOOR 
                    || FuturPosition == ITEM_ROOM_DOOR 
                    || FuturPosition == BONUS_ITEM_DOOR
                    || FuturPosition == SPIKE
                    || FuturPosition == NEXT_STAGE
                    || FuturPosition == HEALTH
                    || (FuturPosition == GAP && player->flight)) {

                         playerMoveUp(d, stage, id, player);
                         actualPosition = d->stages[stage].rooms[id].room[player->positionY][player->positionX];
                    

                        if(actualPosition == NEXT_STAGE) {
                            * change = 1;
                            break;
                        }

                        // if run trough spike then lose life
                        if(actualPosition == SPIKE) {
                            playerLoseLife(player, 1);
                            break;
                        }

                        // if run trough Health then gain life
                        if(actualPosition == HEALTH) {
                            playerGainLife(player);
                            break;
                        }
                        
                        // if you change room : 
                        if(actualPosition == DOOR || actualPosition == BOSS_ROOM_DOOR || actualPosition == BONUS_ITEM_DOOR || actualPosition == ITEM_ROOM_DOOR ) {
                            axeY--;
                            player->positionY = d->stages[stage].rooms[id].height - 2;
                            changeOfRoom = 1;   
                        }

                    }

                    if(actualPosition == ITEM && itemIsSet == 1) {
                        setItemEffects(d->stages[stage].rooms[id].object, player);            
                    }

				break;

				case 's': // move down

                   if( d->stages[stage].rooms[id].name == BOSS_ROOM_NAME ) {
                        bossActive = 1;
                    }

                    player->directionView = 's';
                    FuturPosition = d->stages[stage].rooms[id].room[player->positionY + 1][player->positionX];  

                    if(FuturPosition == EMPTY 
                    || FuturPosition == DOOR 
                    || FuturPosition == BOSS_ROOM_DOOR 
                    || FuturPosition == ITEM_ROOM_DOOR 
                    || FuturPosition == BONUS_ITEM_DOOR
                    || FuturPosition == SPIKE
                    || FuturPosition == NEXT_STAGE
                    || FuturPosition == HEALTH
                    || (FuturPosition == GAP && player->flight)) {
                        
                        // move down :
                        playerMoveDown(d, stage, id, player);
                        actualPosition = d->stages[stage].rooms[id].room[player->positionY][player->positionX];
                    
                        if(actualPosition == NEXT_STAGE) {
                            * change = 1;
                            break;
                        }

                        // if run trough spike then lose life
                        if(actualPosition == SPIKE) {
                            playerLoseLife(player, 1);
                            break;
                        }

                        // if run trough Health then gain life
                        if(actualPosition == HEALTH) {
                            playerGainLife(player);
                            break;
                        }
                        
                        // if you change room : 
                        if(actualPosition == DOOR || actualPosition == BOSS_ROOM_DOOR || actualPosition == BONUS_ITEM_DOOR || actualPosition == ITEM_ROOM_DOOR ) {
                            axeY++;
                            player->positionY = 1;
                            changeOfRoom = 1;  
                        }
                    }

                    if(actualPosition == ITEM && itemIsSet == 1) {
                        setItemEffects(d->stages[stage].rooms[id].object, player);            
                    }

				break;

				case 'q': // move left
                
                   if( d->stages[stage].rooms[id].name == BOSS_ROOM_NAME){
                        bossActive = 1;
                    }

                    player->directionView = 'q';
                    FuturPosition = d->stages[stage].rooms[id].room[player->positionY][player->positionX - 2];
                    
                    if(FuturPosition == EMPTY 
                    || FuturPosition == DOOR 
                    || FuturPosition == BOSS_ROOM_DOOR 
                    || FuturPosition == ITEM_ROOM_DOOR 
                    || FuturPosition == BONUS_ITEM_DOOR
                    || FuturPosition == SPIKE
                    || FuturPosition == NEXT_STAGE
                    || FuturPosition == HEALTH
                    || (FuturPosition == GAP && player->flight)) {
                        
                            
                            // move left :
                            playerMoveLeft(d, stage, id, player);
                            actualPosition = d->stages[stage].rooms[id].room[player->positionY][player->positionX];
                    
                        if(actualPosition == NEXT_STAGE) {
                            * change = 1;
                            break;
                        }

                        // if run trough spike then lose life
                        if(actualPosition == SPIKE) {
                            playerLoseLife(player, 1);
                            break;
                        }

                        // if run trough Health then gain life
                        if(actualPosition == HEALTH) {
                            playerGainLife(player);
                            break;
                        }
                        
                        // if you change room : 
                        if(actualPosition == DOOR || actualPosition == BOSS_ROOM_DOOR || actualPosition == BONUS_ITEM_DOOR || actualPosition == ITEM_ROOM_DOOR ) {
                                axeX--;

                               if((d->stages[stage].rooms[id].width - 2) % 2 == 0) {
                                    player->positionX = d->stages[stage].rooms[id].width - 4;
                                } else {
                                    player->positionX = d->stages[stage].rooms[id].width - 3;
                                }
                                
                                changeOfRoom = 1;  
                            }
                    }

                    if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == ITEM && itemIsSet == 1) {
                        setItemEffects(d->stages[stage].rooms[id].object, player);            
                    }

                break;
                    
				case 'd': // move right

                   if( d->stages[stage].rooms[id].name == BOSS_ROOM_NAME ) {
                        bossActive = 1;
                    }

                    player->directionView = 'd';
                    FuturPosition = d->stages[stage].rooms[id].room[player->positionY][player->positionX + 2];

                    if(FuturPosition == EMPTY 
                    || FuturPosition == DOOR 
                    || FuturPosition == BOSS_ROOM_DOOR 
                    || FuturPosition == ITEM_ROOM_DOOR 
                    || FuturPosition == BONUS_ITEM_DOOR
                    || FuturPosition == SPIKE
                    || FuturPosition == NEXT_STAGE
                    || FuturPosition == HEALTH
                    || (FuturPosition == GAP && player->flight)) {
                        
                            // move right :
                            playerMoveRight(d, stage, id, player);
                            actualPosition = d->stages[stage].rooms[id].room[player->positionY][player->positionX];
                    
                        if(actualPosition == NEXT_STAGE) {
                            * change = 1;
                            break;
                        }

                        // if run trough spike then lose life
                        if(actualPosition == SPIKE) {
                            playerLoseLife(player, 1);
                            break;
                        }

                        // if run trough Health then gain life
                        if(actualPosition == HEALTH) {
                            playerGainLife(player);
                            break;
                        }
                        
                        // if you change room : 
                        if(actualPosition == DOOR || actualPosition == BOSS_ROOM_DOOR || actualPosition == BONUS_ITEM_DOOR || actualPosition == ITEM_ROOM_DOOR ) {
                                axeX+=1;
                                player->positionX = 2;
                                changeOfRoom = 1;  
                            }
                    }

                    if(d->stages[stage].rooms[id].room[player->positionY][player->positionX] == ITEM && itemIsSet == 1) {
                        setItemEffects(d->stages[stage].rooms[id].object, player);            
                    }

                break;

                case '8': ;
                    // Shoot Up                 
                    if (shootParams->reload == 1){
                        if( shootParams->boss == NULL){
                            if( d->stages[stage].rooms[id].name == BASE_ROOM_NAME){
                                shootParams->boss = Boss;
                            }else {
                                shootParams->boss = bossVide;
                            }
                           
                        }
                        if (shootParams->monster == NULL) {
                        shootParams->monster = monsterVide;
                        }

                    pthread_t t2;
                    pthread_create(&t2, NULL, shootUp, shootParams);

                    }
                break;
                
                case '5': ;
                    // Shoot Down
                    if (shootParams->reload == 1){
                        if( shootParams->boss == NULL){
                            if( d->stages[stage].rooms[id].name == BASE_ROOM_NAME){
                                shootParams->boss = Boss;
                            }else {
                                shootParams->boss = bossVide;
                            }
                        }
                        if (shootParams->monster == NULL) {
                        shootParams->monster = monsterVide;
                        }
                    pthread_t t3;
                    pthread_create(&t3, NULL, shootDown, shootParams);
                    }

                break;
                
                case '4': ;
                    // Shoot Left
                    if (shootParams->reload == 1){
                        if( shootParams->boss == NULL){
                            if( d->stages[stage].rooms[id].name == BASE_ROOM_NAME){
                                shootParams->boss = Boss;
                            }else {
                                shootParams->boss = bossVide;
                            }
                        }
                        if (shootParams->monster == NULL) {
                        shootParams->monster = monsterVide;
                        }
                    pthread_t t4;
                    pthread_create(&t4, NULL, shootLeft, shootParams);
                    }
                break;

                case '6': ;
                    // Shoot Right
                    pthread_t t5;
                    if (shootParams->reload == 1){
                        if( shootParams->boss == NULL){
                            if( d->stages[stage].rooms[id].name == BASE_ROOM_NAME){
                                shootParams->boss = Boss;
                            }else {
                                shootParams->boss = bossVide;
                            }
                        }
                        if (shootParams->monster == NULL) {
                        shootParams->monster = monsterVide;
                        }
                    pthread_create(&t5, NULL, shootRight, shootParams);
                    }
                break;
                

			}

            if(bossActive == 1){

                    d->stages[stage].rooms[id].name = BASE_ROOM_NAME;

                    if(stage == 0){
                        InitialiseBossRoom(d, stage, id, 'J');   
                        Boss->idMonster = 0;
                        Boss->firstLetter = JAGGER_FIRST_LETTER;
                        Boss->name = "Jagger";
                        Boss->hpMax = 100;
                        Boss->shoot = 1;
                        shootParams->condition = 1;

                        if( shootParams->boss == NULL){
                            shootParams->boss = Boss;
                        }

                        pthread_create(&thread, NULL, Jagger, shootParams);
                        // if( Boss->dead == 1){
                        //     pthread_exit(&thread);
                        // }
                    }

                    if(stage == 1) {                         
                        InitialiseBossLeninaRoom(d, stage, id, 'L');                            
                        Boss->idMonster = 1;                         
                        Boss->firstLetter = LENINA_FIRST_LETTER;                         
                        Boss->name = "Lenina";                       
                        Boss->hpMax = 300; 
                        Boss->shoot = 1;                           
                        shootParams->condition = 1; 
                     
                        if( shootParams->boss == NULL) {                             
                            shootParams->boss = Boss;                         
                        }

                        pthread_create(&thread, NULL, Lenina, shootParams);   
                    } 

                    if(stage == 2) {
                        InitialiseBossRoom(d, stage, id, 'J');   
                        Boss->firstLetter = ATHINA_FIRST_LETTER;
                        Boss->name = "Athina";
                        Boss->hpMax = 450;
                        Boss->shoot = 1;
                        shootParams->condition = 1;
                        if( shootParams->boss == NULL){
                            shootParams->boss = Boss;
                        }

                        pthread_create(&thread, NULL, bossAthina, shootParams);
                    }
                    
                    bossActive = 0;     
                    BossInfinite = 1;    
            }

            gestionPassing(d, player, stage, id, NumberOfRoomsInt);
           
            if(changeOfRoom == 1) {
                *pId = gestionRoom(d, NumberOfRoomsInt, stage, axeX, axeY);   
            
                OptimiseDoors(d, stage, axeX, axeY, id, NumberOfRoomsInt );
                checkName(d, NumberOfRoomsInt, stage, axeX, axeY, id);
                

                GestionDoorsForMobRoom(d, stage, id, 0);
                
                if(d->stages[stage].rooms[iteration].name != NORMAL_ROOM_NAME) {
                    setMonstersInsideRoom(d, stage, iteration);
                }

                shootParams->id = id;                
                changeOfRoom = 0;
                (void)spawnMonsterVar;

            }

            
            if(BossInfinite == 1) {
                if(shootParams->boss->hpMax <=  0){

                    system("clear");

                    printf("-----------------------------------------------------------\n");
                    printf("\n");
                    printf("You killed the boss, you can now go to the next stage ( n )\n");
                    printf("\n");
                    printf("------------------------------------------------------------\n");
     
                    #ifdef _WIN32 
                    Sleep(25); 
                    #else 
                    usleep(3000000); 
                    #endif 

                    while(1){

                        int positionX_N = rand() % (d->stages[stage].rooms[id].width - 2) + 2;
                        int positionY_N = rand() % (d->stages[stage].rooms[id].height - 2) + 2;

                        if(d->stages[stage].rooms[id].room[positionY_N][positionX_N] == EMPTY && positionX_N % 2 == 0){
                            d->stages[stage].rooms[id].room[positionY_N][positionX_N] = NEXT_STAGE;
                            shootParams->condition = 0;
                            break;
                        }else{
                            continue;
                        }
                    }  
                    BossInfinite = 0;
                }  
            }

            if(d->stages[stage].rooms[id].name == ITEM_ROOM_NAME && itemIsSet == 0) {
                setItemInsideRoom(d, stage, id);
                itemIsSet = 1;
            }
    

            // printf("Axe Position X : %d / and Position Y : %d\n", axeX, axeY);
            printf("ETAGE : %d\n", stage);
            printf("Name : %c\n",d->stages[stage].rooms[id].name);
            printf("ID : %d\n", id);
            printf("AXE X : %d\n", axeX);
            printf("AXE Y : %d\n", axeY);
            // printf("ID : %d\n", id);
            if(d->stages[stage].rooms[id].name == BASE_ROOM_NAME && BossInfinite == 1){
                printf("Boss : %s\n", shootParams->boss->name);
                printf("Boss HP : %.f\n", shootParams->boss->hpMax);
            }
            printf("\n");
            printf("HP player: %.2f\n", player->hpMax);

            if(d->stages[stage].rooms[id].name == ITEM_ROOM_NAME) {
                printf("Room item : \n");
                displayObject(d->stages[stage].rooms[id].object);
            }

			for (int i = 0; i < d->stages[stage].rooms[id].height; i++) {
				for (int y = 0; y < d->stages[stage].rooms[id].width - 1; y++) {
					if (y % 2 == 0) {
						if(d-> stages[stage].rooms[id].room[i][y] == PLAYER){
					
							printf("%c ", d-> stages[stage].rooms[id].room[i][y]);
		
						}else{
							printf("%c ", d-> stages[stage].rooms[id].room[i][y]);
						}
					}
				}
				printf("\n");
				
			}

            printf("Player position : %d, %d / Player direction : %c / Iteration : %d \n", player->positionX, player->positionY, player->directionView, iteration);
            printf("DAMAGE  : %.1f\n", player->dmg);
            printf("SHIELD : %.1f\n", player->shield);
            printf("PIERCING SHOT : %s\n", (player->ps) ? "Yes" : "No");
            printf("SPECTRAL SHOT: %s\n", (player->ss) ? "Yes" : "No");
            printf("FLIGHT: %s\n\n", (player->flight) ? "Yes" : "No");

            if( * change == 1){
                condition = false;
            }

            printf("reload : %d\n",shootParams->reload);


            continue;
        }

    }

    // free(player);
    //free(shootParams);

}

void OptimiseDoors(Donjon * d, int stage, int axeX, int axeY, int id, int numberOfRooms) {

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
            if(d->stages[stage].stage[i][y] == PLAYER){

                for(int w = 0; w < numberOfRooms; w++) {

                    d->stages[stage].rooms[w].Door.doorLeft = 'X';
                    d->stages[stage].rooms[w].Door.doorRight = 'X';
                    d->stages[stage].rooms[w].Door.doorTop = 'X';
                    d->stages[stage].rooms[w].Door.doorBottom = 'X';

                    if(d->stages[stage].stage[i][w] == 'P'){
                        
                        if(d->stages[stage].stage[i + axeY][w + axeX + 1] != EMPTY){
                            DoorRight = 1;
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BONUS_ITEM_DOOR) {
                                Vr = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == ITEM_ROOM_DOOR) {
                                Ir = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BOSS_ROOM_DOOR) {
                                Br = 1;
                            }
                        }

                        if(d->stages[stage].stage[i + axeY][w + axeX - 1] != EMPTY){
                            DoorLeft = 1;
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BONUS_ITEM_DOOR) {
                                Vr = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == ITEM_ROOM_DOOR) {
                                Ir = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BOSS_ROOM_DOOR) {
                                Br = 1;
                            }
                        }

                        if(d->stages[stage].stage[i + axeY - 1][w + axeX - 1] != EMPTY){
                            DoorTop = 1;
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BONUS_ITEM_DOOR) {
                                Vr = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == ITEM_ROOM_DOOR) {
                                Ir = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BOSS_ROOM_DOOR) {
                                Br = 1;
                            }
                        }

                        if(d->stages[stage].stage[i + axeY + 1][w + axeX - 1] != EMPTY){
                            DoorBottom = 1;
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BONUS_ITEM_DOOR) {
                                Vr = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == ITEM_ROOM_DOOR) {
                                Ir = 1;
                            }
                            if(d->stages[stage].stage[i + axeY][w + axeX + 1] == BOSS_ROOM_DOOR) {
                                Br = 1;
                            }
                        }
                         
                    }
                }
            }
        }
    }
    
    char actualPosition;
    int roomHeight = d->stages[stage].rooms[t].height;
    int roomWidth = d->stages[stage].rooms[t].width;
    for(int i = 0; i < roomHeight; i++){
        for(int y = 0; y < roomWidth; y++){
            actualPosition = d->stages[stage].rooms[t].room[i][y];
            if(actualPosition == DOOR || actualPosition == BONUS_ITEM_DOOR || d->stages[stage].rooms[t].room[i][y] == ITEM_ROOM_DOOR || d->stages[stage].rooms[t].room[i][y] == BOSS_ROOM_DOOR){
                d->stages[stage].rooms[t].room[i][y] = WALL;
            }
        }
    }

    if(axeX == 0 && axeY == 0 ){
        for(int i = 0; i < roomHeight; i++){
            for(int y = 0; y < roomWidth; y++){
                actualPosition = d->stages[stage].rooms[t].room[i][y];
                if(i != 0 && i < d->stages[stage].rooms[t].height - 1 && y != 0 && y < d->stages[stage].rooms[t].width - 2){
                    if(actualPosition== DOOR || actualPosition == BONUS_ITEM_DOOR || actualPosition == ITEM_ROOM_DOOR || actualPosition == BOSS_ROOM_DOOR){
                        d->stages[stage].rooms[t].room[i][y] = EMPTY;
                    }
                }
            }
        }
    }


    for(int i = 0; i < roomHeight-1; i++){
        for(int y = 0; y < roomWidth; y++){

            // DoorLeft
            if( y < width/2 && d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] == WALL && DoorLeft == 1){
                

                if(Vl == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = BONUS_ITEM_DOOR;
                    d->stages[stage].rooms[t].Door.doorLeft = BONUS_ITEM_DOOR;
                }else  if(Il == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = ITEM_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorLeft = ITEM_ROOM_DOOR;
                }else if(Bl == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = BOSS_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorLeft = BOSS_ROOM_DOOR;
                }else{
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = DOOR;
                    d->stages[stage].rooms[t].Door.doorLeft = DOOR;
                }

                
            }

            // DoorRight
            if(y > width/2 && d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] == WALL && DoorRight == 1){
     
                if(Vr == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = BONUS_ITEM_DOOR;
                    d->stages[stage].rooms[t].Door.doorRight = BONUS_ITEM_DOOR;
                }else if(Ir == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = ITEM_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorRight = ITEM_ROOM_DOOR;
                }else if(Br == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = BOSS_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorRight = BOSS_ROOM_DOOR;
                }else{
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height/2][y] = DOOR;
                    d->stages[stage].rooms[t].Door.doorRight = DOOR;
                }

            }

            // DoorTop

            if(d->stages[stage].rooms[t].width/2 % 2 == 0){
                width = d->stages[stage].rooms[t].width/2;
            }else{
                width = d->stages[stage].rooms[t].width/2-1;
            }

            if(d->stages[stage].rooms[t].room[0][width] == WALL && DoorTop == 1){

                if(Vt == 1){
                    d->stages[stage].rooms[t].room[0][width] = BONUS_ITEM_DOOR;
                    d->stages[stage].rooms[t].Door.doorTop = BONUS_ITEM_DOOR;
                }else if(It == 1){
                    d->stages[stage].rooms[t].room[0][width] = ITEM_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorTop = ITEM_ROOM_DOOR;
                }else if(Bt == 1){
                    d->stages[stage].rooms[t].room[0][width] = BOSS_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorTop = BOSS_ROOM_DOOR;
                }else{
                    d->stages[stage].rooms[t].room[0][width] = DOOR;
                    d->stages[stage].rooms[t].Door.doorTop = DOOR;
                }
                                                                                       
            }

            // DoorBottom
             if(d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] == WALL && DoorBottom == 1){

                if(Vb == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = BONUS_ITEM_DOOR;
                    d->stages[stage].rooms[t].Door.doorBottom = BONUS_ITEM_DOOR;
                }else if(Ib == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = ITEM_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorBottom = ITEM_ROOM_DOOR;
                }else if(Bb == 1){
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = BOSS_ROOM_DOOR;
                    d->stages[stage].rooms[t].Door.doorBottom = BOSS_ROOM_DOOR;
                }else{
                    d->stages[stage].rooms[t].room[d->stages[stage].rooms[t].height-1][width] = DOOR;
                    d->stages[stage].rooms[t].Door.doorBottom = DOOR;
                }
                
                                                                                                     
            }


           
        }
    }
    
}

void checkName(Donjon *d, int numberOfRooms, int stage, int axeX, int axeY, int t) {

    for(int i = 0; i < numberOfRooms+2; i++){
        for(int y = 0; y < numberOfRooms+2; y++){
            if(d->stages[stage].stage[i][y] == PLAYER){
                
                if( d->stages[stage].stage[i + axeY][y + axeX] == NORMAL_ROOM_NAME){
                    d->stages[stage].rooms[t].name = NORMAL_ROOM_NAME;
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == ITEM_ROOM_NAME){
                    d->stages[stage].rooms[t].name = ITEM_ROOM_NAME;
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == BOSS_ROOM_NAME){
                    d->stages[stage].rooms[t].name = BOSS_ROOM_NAME;
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == BONUS_ITEM_ROOM){
                    d->stages[stage].rooms[t].name = BONUS_ITEM_ROOM;
                }

                if( d->stages[stage].stage[i + axeY][y + axeX] == PLAYER){
                    d->stages[stage].rooms[t].name = PLAYER;
                }

            }
        }
    }
}

void gestionPassing(Donjon *d, Player * player, int stage, int id, int NumberOfRoomsInt){

           for(int i = 0; i < d->stages[stage].rooms[id].height; i++){
                for(int y = 0; y < d->stages[stage].rooms[id].width; y++){
                    if(d->stages[stage].rooms[id].room[i][y] == PLAYER){
                        d->stages[stage].rooms[id].room[i][y] = EMPTY;
                    }
                }
            }

            d->stages[stage].rooms[id].room[player->positionY][player->positionX] = PLAYER;

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
            if(d->stages[stage].stage[i][y] == PLAYER){

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

void InitialiseBossRoom(Donjon * d, int stage, int id, char letter){

     for (int i = 0; i < d -> stages[stage].rooms[id].height; i++) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y++) {
            if (i == d -> stages[stage].rooms[id].height / 2 && y == d -> stages[stage].rooms[id].width / 2) {
                if (y % 2 == 0) {
                    d -> stages[stage].rooms[id].room[i][y] = letter;
                } else {
                    d -> stages[stage].rooms[id].room[i][y - 1] = letter;
                }
            }

        }
    }
}

void InitialiseBossLeninaRoom(Donjon * d, int stage, int id, char letter) {
    int width = d -> stages[stage].rooms[id].width;
    for (int y = 0; y < width; y+=1) {
        if (y == width / 2) {
            if (y % 2 == 0) {
                d -> stages[stage].rooms[id].room[1][y] = letter;
            } else {
                d -> stages[stage].rooms[id].room[1][y - 1] = letter;
            }
        }
    } // for

}

void GestionDoorsForMobRoom(Donjon *d, int stage, int id, int done){
    char actualPosition;
    if(done == 0 ){

            // lock the doors inside boss and normal rooms
            if( d->stages[stage].rooms[id].name != PLAYER && d->stages[stage].rooms[id].name != ITEM_ROOM_NAME  && d->stages[stage].rooms[id].name != BONUS_ITEM_DOOR ){
                for(int i = 0; i<d->stages[stage].rooms[id].height; i++){
                    for(int y = 0; y< d->stages[stage].rooms[id].width; y++){
                        actualPosition = d->stages[stage].rooms[id].room[i][y];
                        if( actualPosition == DOOR ){
                            d->stages[stage].rooms[id].room[i][y] = LOCKED_DOOR;
                        }
                        if(actualPosition == BONUS_ITEM_DOOR ){
                            d->stages[stage].rooms[id].room[i][y] = LOCKED_DOOR;
                        }
                        if(actualPosition == ITEM_ROOM_DOOR ){
                            d->stages[stage].rooms[id].room[i][y] = LOCKED_DOOR;
                        }
                        if(actualPosition == BOSS_ROOM_DOOR ){
                            d->stages[stage].rooms[id].room[i][y] = LOCKED_DOOR;
                        }


                    }
                }
        }

    }

    if(done == 1){

         for(int i = 0; i<d->stages[stage].rooms[id].height; i++){
                for(int y = 0; y< d->stages[stage].rooms[id].width; y++){
                    if(d->stages[stage].rooms[id].room[i][y] == LOCKED_DOOR  && i  == 0){
                        d->stages[stage].rooms[id].room[i][y] = d->stages[stage].rooms[id].Door.doorTop;
                    }
                    if( i == d->stages[stage].rooms[id].height - 1 || d->stages[stage].rooms[id].height == LOCKED_DOOR){ // WTF ??
                        if( d->stages[stage].rooms[id].room[i][y] == LOCKED_DOOR){
                            d->stages[stage].rooms[id].room[i][y] = d->stages[stage].rooms[id].Door.doorBottom;
                        }
                    }

                    if(d->stages[stage].rooms[id].room[i][y] == LOCKED_DOOR && y == 0){
                        d->stages[stage].rooms[id].room[i][y] = d->stages[stage].rooms[id].Door.doorLeft;
                    }

                    if(y > d->stages[stage].rooms[id].width/2  ){
                        if(d->stages[stage].rooms[id].room[i][y] == LOCKED_DOOR){
                            d->stages[stage].rooms[id].room[i][y] = d->stages[stage].rooms[id].Door.doorRight;
                        }
                    }
                }
        }
    }

}

void PurgeRoomOfBoss(Donjon *d, int stage, int id){

    for(int i = 0; i<d->stages[stage].rooms[id].height; i++){
        for(int y = 0; y< d->stages[stage].rooms[id].width; y++){
            if(d->stages[stage].rooms[id].room[i][y] != WALL && d->stages[stage].rooms[id].room[i][y] != LOCKED_DOOR){
                d->stages[stage].rooms[id].room[i][y] = EMPTY;
            }
        }
    }

}

void playerMoveUp(Donjon* donjon, int stage, int roomID, Player* player) {
    donjon->stages[stage].rooms[roomID].room[player->positionY][player->positionX] = EMPTY;
    player->positionY-=1;
}

void playerMoveDown(Donjon* donjon, int stage, int roomID, Player* player) {
    donjon->stages[stage].rooms[roomID].room[player->positionY][player->positionX] = EMPTY;
    player->positionY+=1;
}

void playerMoveRight(Donjon* donjon, int stage, int roomID, Player* player) {
    donjon->stages[stage].rooms[roomID].room[player->positionY][player->positionX] = EMPTY;
    player->positionX += 2;
}

void playerMoveLeft(Donjon* donjon, int stage, int roomID, Player* player) {
    donjon->stages[stage].rooms[roomID].room[player->positionY][player->positionX] = EMPTY;
    player->positionX -= 2;
}

void playerLoseLife(Player* player, float damageTaken) {
    if(player->shield > 0) { // player got shield
        if(damageTaken > player->shield) { // more damage than shield
            damageTaken -= player->shield;
            player->shield = 0;
            player->hpMax -= damageTaken;
            player->canTakeBonusItem = 0;
        } else { 
            player->shield -= damageTaken;
        }
    } else { // player does not have shield
        player->hpMax -= damageTaken;
        player->canTakeBonusItem = 0;
    }
}

void playerGainLife(Player* player) {
    int healthOrShield = 0 + rand() % 1;
    int amountLife = 1 + rand() % 2;

    if(healthOrShield) {
        player->hpMax += amountLife;
    } else {
        player->shield += amountLife;
    }
}


void setItemInsideRoom(Donjon* d, int stage, int id) {
    int roomHeight =  d -> stages[stage].rooms[id].height;
    int roomWidth =  d -> stages[stage].rooms[id].width;
    int itemPosX = roomHeight / 2;
    int itemPosY = roomWidth / 2;
    itemPosY = (itemPosY % 2 == 0) ? itemPosY : itemPosY-1;
    
    d -> stages[stage].rooms[id].object = getRandomObject(d->headObject);
    d -> stages[stage].rooms[id].room[itemPosX][itemPosY] = ITEM;
}

void setItemEffects(Object* item, Player* player) {
    player->dmg += item->damage;
    player->hpMax += item->hpMax;
    player->shield += item->shield;

    player->flight += item->flight;
    player->ps += item->piercingShot;
    player->ss += item->spectralShot;
}


/**
 * @file menu.c
 * @author  Nairod36
 * @brief Fonctions du menu
 * @version 0.1
 * @date 2022-11-5
 * 
 * @copyright Copyright (c) 2022
 */


#include<stdio.h>
#include <termios.h>          
#include <unistd.h>     
#include <sys/select.h>
#include <stdbool.h>
#include <fcntl.h>

#include "./include/Player.h"
#include "./include/menu.h"
#include "./include/lectureFichiers.h"
#include "./include/mystring.h"
#include "./include/userInput.h"
#include "./include/game.h"
#include "./include/Room.h"
#include "./include/shoot.h"

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60


void printGameBanner() {
    printf("===========================================================\n");
    printf("=========      THE BINDING OF BRIATTE        ==============\n");
    printf("===========================================================\n");
    printf("\n");
    printf("\n");
}

void menu_init(void) {
    system("clear");
    printGameBanner();
    printf("               Press 'g' to start the game\n\n");
    printf("               Press 'i' for the ITEMS menu\n\n");
    printf("               Press 'r' for the ROOMS menu\n\n");
    printf("               Press 'c' for the controls information\n\n");
    printf("               Press 'x' to exit the game\n\n\n\n");

    printf("========   Credit : Dorian-Alexandre-Matthias   ==========\n");
}

void menuCrudItem(void) {
    system("clear");
        printGameBanner();
        printf("-------- ITEMS MENU  --------\n");
        printf("Press s to see your current items\n");
        printf("Press a to add an item\n");
        printf("Press d to delete an item\n");
        printf("Press m to modify an item\n");

        printf("\nPress 'r' to go back\n");
}

void menuSeeItems(void) {
    system("clear");
    printGameBanner();
    printf("-------- YOUR ITEMS --------\n");

    FILE* fichier = fopen(CHEMIN_FICHIER_OBJECTS, "r");
    afficherFichier(fichier);
    fclose(fichier);

    printf("\nPress 'r' to go back\n");

}

void menuCreateItem(void){
    system("clear");
    printGameBanner();
    printf("-------- CREATE ITEM  --------\n");
    
    Object* head = objectsFileToObjectsList(); 
    if(head == NULL) {
        printf("Error while loading the head file. Contact the dev team :P.\n");
        printf("Press 'r' to go back.\n");
        return;
    }
    
    char name[20];
    askName(name);

    float hpMax;
    askHpMax(&hpMax);

    float shield;
    askShield(&shield);
    
    float damage;
    askDamage(&damage);
    
    int piercingShot = 0;
    askPiercingShot(&piercingShot);
    
    int spectralShot = 0;
    askSpectralShot(&spectralShot);
    
    int flight = 0;
    askFlight(&flight);

    Object* newItem = createObject(2, duplicateString(name), hpMax, shield, damage, piercingShot, spectralShot, flight);
    
    printf("New item : ");
    displayObject(newItem);
    printf("Do you want to add it (y/n) ?\n");
    int success = confirmation();
    if(success) {
        int res = addObject(head, newItem);
        if(res) {
            listToObjectsFile(head);
        } else {
            printf("Could not add the item.\n");
            freeAllObjects(head);
        }
    
        printf("New item added.\n");
    }     
    
    printf("\nPress 'r' to continue\n");
}

void menuDeleteItem(void) {
    system("clear");
    printGameBanner();
    printf("-------- DELETE ITEM  --------\n");
    
    Object* head = objectsFileToObjectsList();
    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_OBJECTS);
        printf("Press 'r' to go back\n");
        return;
    }

    int id;
    int success = 0;
    displayAllObjects(head);
    printf("Enter the id of the item you want to delete (see above) : \n");
    do {
        id = readInt();
        printf("id = %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    removeObject(&head, id);
    listToObjectsFile(head);
    freeAllObjects(head);

    printf("Item deleted.\n");
    printf("\nPress 'r' to continue\n");
}

void menuModifyItem(void){
    system("clear");
    printGameBanner();
    printf("-------- UPDATE ITEM  --------\n");

    
    Object* head = objectsFileToObjectsList();
    if(head == NULL) {
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_OBJECTS);
        printf("Press 'r' to go back\n");
        return;
    }

    int id;
    int success = 0;
    displayAllObjects(head);
    do {
        printf("Enter the id of the item you want to update (see above) : \n");
        id = readInt();
        printf("You selected the id %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    Object* item = getObjectById(head, id);
    if(item == NULL) {
        printf("Couldn't get the item of id : %d\n", id);
        printf("Press 'r' to continue\n");
        return;
    }

    success = 0;
    
    printf("Current item's name : %s.\nDo you want to modify the item's name (y/n) ?\n", item->name);
    success = confirmation();
    if(success) {
        char name[20];
        askName(name);
        item->name = duplicateString(name);
    }
    
    printf("Current item's HP MAX : %f.\nDo you want to modify the item's HP MAX (y/n) ?\n", item->hpMax);
    success = confirmation();
    if(success) {
        float hpMax;
        askHpMax(&hpMax);
        item->hpMax = hpMax;
    }

    printf("Current item's SHIELD: %f.\nDo you want to modify the item's SHIELD (y/n) ?\n", item->shield);
    success = confirmation();
    if(success) {
        float shield;
        askShield(&shield);
        item->shield = shield;
    }

    printf("Current item's DAMAGE: %f.\nDo you want to modify the item's DAMAGE (y/n) ?\n", item->damage);
    success = confirmation();
    if(success) {
        float damage;
        askDamage(&damage);
        item->damage = damage;
    }

    printf("Current item's PIERCING SHOT : %s.\nDo you want to modify the item's PIERCING SHOT (y/n) ?\n", 
        (item->piercingShot) ? "true" : "false");
    success = confirmation();
    if(success) {
        int ps;
        askPiercingShot(&ps);
        item->piercingShot = ps;
    }

    printf("Current item's SPECTRAL SHOT : %s.\nDo you want to modify the item's SPECTRAL SHOT (y/n) ?\n", 
        (item->spectralShot) ? "true" : "false");
    success = confirmation();
    if(success) {
        int ss;
        askSpectralShot(&ss);
        item->spectralShot= ss;
    }

    printf("Current item's FLIGHT : %s.\nDo you want to modify the item's FLIGHT (y/n) ?\n", 
        (item->flight) ? "true" : "false");
    success = confirmation();
    if(success) {
        int flight;
        askFlight(&flight);
        item->flight= flight;
    }

    printf("The item's stat now :\n");
    displayObject(item);

    listToObjectsFile(head);
    freeAllObjects(head);
    
    printf("\nPress 'r' to continue\n");
}

void menuCrudRoom(void){
    system("clear");
        printGameBanner();
        printf("-------- ROOMS MENU  --------\n");
        printf("Press 's' to see your rooms\n");
        printf("Press 'a' to add a room\n");
        printf("Press 'd' to delete a room\n");
        printf("Press 'm' to modify a room\n");

        printf("\nPress 'b' to go back\n");
}

void menuSeeRooms(void){
    system("clear");
    printGameBanner();
    printf("-------- YOUR ROOMS --------\n");
    

    FILE* fichier = fopen(CHEMIN_FICHIER_PIECES, "r");
    afficherFichier(fichier);
    fclose(fichier);

    printf("\nPress 'r' to go back\n");
}

void menuCreateRoom(void) {
    system("clear");
    printGameBanner();
    printf("-------- CREATE ROOM  --------\n");
    printf("Not possible for the moment. Contact the dev team :)\n");  
    printf("\n Press 'r' to continue\n");   

}

void menuDeleteRoom(void){
    system("clear");
    printGameBanner();
    printf("-------- DELETE ROOM  --------\n");

    CRUD_Room* head = roomsFileToRoomsList();
    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_PIECES);
        printf("Press 'r' to go back\n");
        return;
    }

    int id;
    int success = 0;
    displayAllRooms(head);
    printf("Enter the id of the room you want to delete (see above) : \n");
    do {
        id = readInt();
        printf("id = %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    removeCRUD_Room(&head, id);
    listToRoomsFile(head);
    freeAllRooms(head);

    printf("Room deleted.\n");
    printf("\nPress 'r' to continue\n");
}

void menuModifyRoom(void){
   system("clear");
    printGameBanner();
    printf("-------- UPDATE ROOM  --------\n");
    printf("Not possible for the moment. Contact the dev team :)\n");
    printf("\nPress 'b' to continue ...\n");

}

void menuControl(void){
    system("clear");
    printGameBanner();
    printf("--------------- Info control  ----------------\n");
    printf("Use z,q,s,d to move\n");
    printf("Use 8,4,5,6 to attack\n");
    printf("Use x to quit the game\n");

    printf("\nPress 'b' to continue ...\n");
    return;
}

void printProgress(double percentage) {

    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void SetColorAndPositionForPlayer(Donjon *d, Player *player, int stage, int id ) {

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



void GameRecur(Donjon *d, Monster * Boss, ShootParams * shootParams, Player * player, int stage, int * change, int NumberOfRoomsInt, int id, int axeX, int axeY, Monster * arrayMonster){

	gestionGame(d, shootParams, Boss, stage, change, player, NumberOfRoomsInt, id, axeX, axeY, arrayMonster);
				
    if(player->hpMax <= 0){
        system("clear");
        printf("===========================================================\n");
        printf("=========           YOU ARE DEAD             ==============\n");
        printf("===========================================================\n");
        printf("\n");

        #ifdef _WIN32 
        Sleep(10000); 
        #else 
        usleep(5000000); 
        #endif 

        axeX = player->stageAxeX;
        axeY = player->stageAxeY;
        player->hpMax = 100;
        GameRecur(d, Boss, shootParams, player, stage, change, NumberOfRoomsInt, id, axeX, axeY, arrayMonster);
    }


}


void menuGame(){

    bool condition = true, condition2 = true, etape = true;
	int c,c2;
		
    int stage;
    int change;

    menu_init();

	while (condition) {

		c = 'p';

		if (etape == true && kbhit()) {
			c = getchar();
		}
		if (c == 'x') {
			condition = false;
		}

		switch (c) {

			case 'g':

				stage = 0;
				change = 0;

                Player* player = malloc(sizeof(Player));
                    player->positionX = 1;
                    player->positionY = 1;
                    player->directionView = 'D';
                    int characterID = choseCharacter();
                    initialisePlayerStats(player, characterID);

                // Boucle pour chaque étage

				for(int i = 0; i < 3; i+=1) {

                    Donjon * d = malloc(sizeof(Donjon));
                    Monster * Boss = malloc(sizeof(Monster));
                    
                    Monster * arrayMonster = malloc(sizeof(Monster) * 10);

                    // Monster * arrayMonster = fichierMonsterToListeMonster();
                    
                    int id = 0;

                    ShootParams *shootParams = malloc(sizeof(struct ShootParams));
                    shootParams->reload = 1;
                    shootParams->player = player;
                    shootParams->d = d;
                    shootParams->stage = stage;
                    shootParams->id = id;
                    Boss->firstLetter = 'X';

                    if(stage == 0){
                        player->dmg = 3.5;
                        player->hpMax = 3;
                        player->shield = 0;
                    }

                    int axeX = 0;
                    int axeY = 0;

                    d->stages[stage].rooms[id].name = 'P';

                    int NumberOfRoomsInt = numberOfRooms();
                    InitialisationGame(d, stage);	
                    InitialiseOtherRoomsFromArms(d,stage, NumberOfRoomsInt);
                    SetColorAndPositionForPlayer(d, player, stage, id);

                    GameRecur(d, Boss, shootParams, player, stage, &change, NumberOfRoomsInt, id, axeX, axeY, arrayMonster);
    
					free(d -> stages[stage].stage);
					free(d);

					stage+=1;
					// printf("CHANGE : %d", change);
					change = 0;

					system("clear");
					printf("\n\n\n\n\n\n\n\n\n");
					printf("		Changement d'étage ...\n\n");

					for(int i = 0; i < 5; i+=1) {
						printProgress(i/5.0);
						#ifdef _WIN32 
						Sleep(100); 
						#else 
						usleep(30000); 
						#endif 
					}
				}
								
			
			case 'i':
			while (condition2)
			{
			etape = false;
				c2 = 'p';
				menuCrudItem();
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
					case 'a':
						menuCreateItem();
						condition2 = false;
						break;
					case 'd':
						menuDeleteItem();
						condition2 = false;

						break;
					case 'm':
						menuModifyItem();
						condition2 = false;

						break;

				}
			}
			break;
				

			case 'r':
			 while (condition2)
			 {
				etape = false;
				c2 = 'p';
				menuCrudRoom();
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
					case 'a':
						menuCreateRoom();
						condition2 = false;
						break;
					case 'd':
						menuDeleteRoom();
						condition2 = false;
						break;
					case 'm':
						menuModifyRoom();
						condition2 = false;
						break;
				}
			 }
				break;

			case 'c':
				menuControl();
		}
	}
}
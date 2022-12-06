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
#include <ctype.h> 
#include <string.h>
#include <stdlib.h>



#include "./include/menu.h"
#include "./include/lectureFichiers.h"
#include "./include/mystring.h"
#include "./include/userInput.h"
#include "./include/game.h"

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

    printf("========   Credit : Dorian-Alexandre-Matthias   ==========\n\n\n");
}

int menuSeeItems(void) {

    system("clear");
    printGameBanner();
    printf("-------- YOUR ITEMS --------\n");

    FILE* fichier = fopen(CHEMIN_FICHIER_OBJECTS, "r");
    afficherFichier(fichier);
    fclose(fichier);

    printf("\nPress 'r' to go back\n");

    return 0;

}

int menuCreateItem(void){
    system("clear");
    printGameBanner();
    printf("---------------- CREATE ITEM  ----------------\n\n");
    
    Object* head = objectsFileToObjectsList(); 
    if(head == NULL) {
        printf("Error while loading the head file. Contact the dev team :P.\n");
        printf("Press 'r' to go back.\n");
        return 1;
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
            return 2;
        }
    
        printf("New item added.\n");
    }     

    printf("\nPress 'R' to go back\n");

    while(1){
        char c = ' ';
        if(kbhit()){
            c = getchar();
        } 
            if(c == 'R' || c == 'r') {
                return 1;
            }
        sleep(1);
    }
}

int menuDeleteItem(void) {

    system("clear");
    printGameBanner();
    printf("------------ DELETE ITEM  ------------\n");
    
    Object* head = objectsFileToObjectsList();
    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_OBJECTS);
        printf("Press 'r' to go back\n");
        return 2;
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

    printf("Item deleted.\n\n");

    printf("\nPress 'R' to go back\n");

    while(1){
        char c = ' ';
        if(kbhit()){
            c = getchar();
        } 
            if(c == 'R' || c == 'r') {
                return 1;
            }
        sleep(1);
    }
}

int menuModifyItem(void){

    system("clear");
    printGameBanner();
    printf("-------- UPDATE ITEM  --------\n");

    
    Object* head = objectsFileToObjectsList();
    if(head == NULL) {
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_OBJECTS);
        printf("Press 'r' to go back\n");
        return 2;
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
        return 2;
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

    printf("\nPress 'R' to go back\n");
    
    while(1){
        char c = ' ';
        if(kbhit()){
            c = getchar();
        } 
            if(c == 'R' || c == 'r') {
                return 1;
            }
        sleep(1);
    }
    
}


int menuSeeRooms(void){

    system("clear");
    printGameBanner();
    printf("---------------- YOUR ROOMS ----------------\n\n");

    FILE* fichier = fopen(CHEMIN_FICHIER_PIECES, "r");
    afficherFichier(fichier);
    fclose(fichier);
    sleep(1);

    printf("\nPress 'R' to go back\n");

    while(1){
        char c = ' ';
        if(kbhit()){
            c = getchar();
        } 
            if(c == 'R' || c == 'r') {
                return 1;
            }
        sleep(1);
    }
}

void printRoom(int height, int length, char arr[height][length]){
    
        for(int i = 0; i < height; i++){
         printf("\n      ");
        for(int j = 0; j < length; j++){
            printf("%c", arr[i][j]);
        }   
    }

    printf("\n\n\n");
}

int menuCreateRoom(void) {

    char (*arr)[30] = malloc(sizeof(char[9][30]));


      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 30; j++) {
            arr[i][j] = ' ';
        }
    }

    system("clear");
    printGameBanner();
    printf("\n-------------- CREATE ROOM  ----------------\n\n");
    // printf("            Not possible for the moment. Contact the dev team :)\n"); 

    printf("          For Size Room of 9x15\n");

    int height = 9;
    int length = 30;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < length; j++){
           
            if(j%2 == 0){
                
                if(i == 0 || i == height - 1){
                    arr[i][j] = 'W';
                } 
            }      

            if(j%2 == 0 ){
                if(j == 0 || j == length - 2){
                    arr[i][j] = 'W';
                }  
            }
        }
    }

    printRoom(height, length, arr);

    int success = 0;
    int axeX = 0;
    int axeY = 0;
    int Rock = 0;
    int condition = true;

    while(1){
        printf("Voulez-vous ajoutez des obstacles à la salle ? (Y/N) \n");
        success = confirmation();
        if(success == 1){
            break;
        }else{
            printf("Voulez-vous ajoutez une salle vide ?\n");
            success = confirmation();
            if(success == 1){
                break;
            }else{
                continue;
                condition = false;
            }
        } 
        
    }


    while(condition){
        printf("Combien de rochers voulez-vous ajoutez ?\n");
        Rock = readInt();
        if(Rock <= 0 ) {
            printf("DO NOT ENTER 0 OR LESS IDIOT\n\n");
            continue;
        }else{
            break;
        }
    }

    for(int i = 0; i < Rock; i++ ){
            printf("\n");

            while(1){
                printf("AXE X pour créer le rocher [%d] :", i+1);
                axeX = readInt();
                if (isdigit(axeX)){
                    continue;
                }
                if(axeX % 2 == 0){
                    break;
                }else{
                    printf("AXE X pour créer le rocher [%d] :", i+1);
                    axeX = readInt();
                }
            }

            while(1){
                printf("AXE Y pour créer un rocher [%d] :", i+1);
                axeY = readInt();
                if (isdigit(axeY)){
                    continue;
                }
                break;
            }

             if(arr[axeX][axeY] != ' '){
                    printf("Impossible de créer un rocher dans un mur");
                    i--;
                    continue;
            }

            arr[axeY][axeX] = 'R';

            int numberOfRoomsInt = numberOfRooms();

            // const char* str1 = "hello there";


            char final[100];

            sprintf(final,"%s%d%s%d%s%d\n","[",height,"|",length/2,"]",numberOfRoomsInt-2);
            
                FILE *f = fopen(CHEMIN_FICHIER_PIECES, "a");
                if (f == NULL)
                {
                    printf("Error opening file!\n");
                }

                // printf("%s\n",final);

             /* Append data to file */
                fputs(final, f);

               // write final array to file

                for(int i = 0; i < height; i++){
                    for(int j = 0; j < length; j++){
                        fputc(arr[i][j], f);
                    }
                    fputc('\n', f);
                }

                fclose(f);
            
            
            // char array[5] = ["[",""]

            

        // for(int x = 0; x < height; x++){
        //     for(int j = 0; j < length; j++){
        //         if(axeX - 2 == 'W' && height / 2 == axeY ){
        //             printf("Impossible de créer un rocher à côté d'une potentiel porte");
        //             break;
        //         }
        //         if(axeX + 2 == 'W' && height / 2 == axeY ){
        //             printf("Impossible de créer un rocher à côté d'une potentiel porte");
        //             break;
        //         }
        //         // if(x == axeX && j == axeY){
        //             arr[i][j] = 'R';
        //         // }
        //     }
        // }
    }

    printRoom(height, length, arr);






    FILE * fp;

    fp = fopen("../resources/room.rtbob", "r");
    if (fp == NULL){
        return 2;
    }
    fclose(fp);

    printf("\nPress 'R' to go back\n");

    while(1){
        char c = ' ';
        if(kbhit()){
            c = getchar();
        } 
            if(c == 'R' || c == 'r') {
                return 1;
            }
        sleep(1);
    }

}

int menuDeleteRoom(void){

    system("clear");
    printGameBanner();
    printf("---------------- DELETE ROOM  ----------------\n\n");

    CRUD_Room* head = roomsFileToRoomsList();
    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_PIECES);
        printf("Press 'r' to go back\n");
        return 2;
    }

    int id;
    int success = 0;
    displayAllRooms(head);
    printf("\n\nEnter the id of the room you want to delete (see above) : \n");
    do {
        id = readInt();
        printf("id = %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    removeCRUD_Room(&head, id);
    listToRoomsFile(head);
    freeAllRooms(head);

    printf("Room deleted.\n\n");


    printf("\nPress 'R' to go back\n");

    while(1){
        char c = ' ';
        if(kbhit()){
            c = getchar();
        } 
            if(c == 'R' || c == 'r') {
                return 1;
            }
        sleep(1);
    }
}

int menuModifyRoom(void){
   system("clear");
    printGameBanner();
    printf("-------- UPDATE ROOM  --------\n");
    printf("Not possible for the moment. Contact the dev team :)\n");
    printf("\nPress 'b' to continue ...\n");

    return 0;

}

void menuCrudRoom(void){

        system("clear");
        printGameBanner();
        printf("-------------------- ROOMS MENU  -------------------\n\n");
        printf("            Press 's' to see your rooms\n");
        printf("            Press 'a' to add a room\n");
        printf("            Press 'd' to delete a room\n");
        printf("            Press 'm' to modify a room\n\n");

        printf("            Press 'b' to go back \n\n");
}


void menuCrudItem(void) {
    system("clear");
        printGameBanner();
        printf("-------------------- ITEMS MENU  -------------------- \n\n");
        printf("            Press s to see your current items\n");
        printf("            Press a to add an item\n");
        printf("            Press d to delete an item\n");
        printf("            Press m to modify an item\n\n");

        printf("            Press 'b' to go back\n\n");
}


void menuControl(void){
    system("clear");
    printGameBanner();
    printf("-------------------- Info control  --------------------\n\n");
    printf("                 Use z,q,s,d to move\n");
    printf("                 Use 8,4,5,6 to attack\n");
    printf("                 Use x to quit the game\n\n");

    printf("                 Press 'b' to go back \n\n");
}

void printProgress(double percentage) {

    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

void GameRecur(Donjon *d, Boss * boss, ShootParams * shootParams, Player * player, int characterID, int stage, int * change, int NumberOfRoomsInt, int id, int axeX, int axeY) {
    player->canTakeBonusItem = 1;
	gestionGame(d, shootParams, boss, stage, change, player, NumberOfRoomsInt, id, axeX, axeY);
				
    if(player->hpMax <= 0) { // player dead
        system("clear");
        printf("===========================================================\n");
        printf("=========                YOU ARE DEAD        ==============\n");
        printf("===========================================================\n");
        printf("\n");

        #ifdef _WIN32 
        Sleep(10000); 
        #else 
        usleep(5000000); 
        #endif 
        
        initialisePlayerStats(player, characterID);
        GameRecur(d, boss, shootParams, player, characterID, stage, change, NumberOfRoomsInt, id, axeX, axeY);
    }
}

void SetColorAndPositionForPlayer(Donjon *d, Player *player, int stage, int id) {

    for (int i = 0; i < d -> stages[stage].rooms[id].height; i+=1) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y+=1) {
            if (i == d -> stages[stage].rooms[id].height / 2 && y == d -> stages[stage].rooms[id].width / 2) {
                if (y % 2 == 0) {
                    d -> stages[stage].rooms[id].room[i][y] = 'P';
                } else {
                    d -> stages[stage].rooms[id].room[i][y + 1] = 'P';
                }
            }

        }
    }

    for (int i = 0; i < d -> stages[stage].rooms[id].height; i+=1) {
        for (int y = 0; y < d -> stages[stage].rooms[id].width; y+=1) {
            if (y % 2 == 0) {
                if (d -> stages[stage].rooms[id].room[i][y] == 'P') {
                    player -> positionX = y;
                    player -> positionY = i;
                }
            }
        }
    }

    for (int i = 0; i < d->stages[stage].rooms[id].height; i+=1) {
        for (int y = 0; y < d->stages[stage].rooms[id].width; y+=1) {
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

void menuGame() {

    bool condition = true, condition2 = true, condition3 = true, condition4 = true, etape = true;
	int c,c2;
		
    int stage;
    int change;
    
    int statusRoom = 0;
    int statusItem = 0;

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

                Monster * arrayMonster = fichierMonsterToListeMonster();

                Player* player = malloc(sizeof(Player));
                    player->positionX = 1;
                    player->positionY = 1;
                    player->directionView = 'D';
                    int characterID = choseCharacter();
                    initialisePlayerStats(player, characterID);

                // Boucle pour chaque étage

				for(int i = 0; i < 62; i+=1) {

                    Donjon * d = malloc(sizeof(Donjon));
                    Boss * Boss = malloc(sizeof(Monster));

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
                    InitialisationGame(d, stage, arrayMonster);	
                    InitialiseOtherRoomsFromArms(d,stage, NumberOfRoomsInt);
                    SetColorAndPositionForPlayer(d, player, stage, id);

                    GameRecur(d, Boss, shootParams, player, characterID, stage, &change, NumberOfRoomsInt, id, axeX, axeY);
    
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

            break;
			case 'i':
                while (condition2)
                {
                    etape = false;
                    c2 = 'p';
                    menuCrudItem();
                    statusItem = 0;
                    if (kbhit()) {
                        c2 = getchar();
                    }
                    switch (c2){
                        case 'a':
                            while(statusItem == 0){
                                statusItem = menuCreateItem();
                            }
                            break;
                        case 'd':
                            while(statusItem == 0){
                                statusItem = menuDeleteItem();
                            }
                            break;
                        case 'm':
                            while(statusItem == 0){
                                statusItem = menuModifyItem();
                            }
                        break;
                        case 'b':
                            menuGame();
                        break;
                    }

                    if(statusItem == 1){
                        continue;
                    }
                    if(statusItem == 2){
                         // Ecrire dans logs qu'il y'a une erreur
                        system("clear");
                        printf("Erreur");
                        sleep(2);
                        continue;
                    }
                    sleep(1);
                }
			break;
				

			case 'r':
			while (condition3){
				etape = false;
				c2 = 'p';
				menuCrudRoom();
                sleep(1);
                statusRoom = 0;
				if (kbhit()) {
					c2 = getchar();
				}
				switch (c2){
                    case 's':
                        while(statusRoom == 0){
                            statusRoom = menuSeeRooms();
                        }
                    break;
					case 'a':
                        while(statusRoom == 0){
						    statusRoom = menuCreateRoom();
                        }
					break;
					case 'd':
                        while(statusRoom == 0){
						    statusRoom = menuDeleteRoom();
						}
					break;
					case 'm':
                        while(statusRoom == 0){
						    statusRoom = menuModifyRoom();
						}
					break;
                    case 'b':
                        menuGame();
                    break;
				}

                if(statusItem == 1){
                    continue;
                }

                if(statusItem == 2){
                // Ecrire dans logs qu'il y'a une erreur
                    system("clear");
                    printf("Erreur");
                    sleep(2);
                    continue;
                }
                sleep(1);

                (void)statusRoom;
			}
			break;

			case 'c':
                while(condition4 == true){
                    menuControl();
                    sleep(1);
                    statusRoom = 0;
                    if (kbhit()) {
                        c2 = getchar();
                    }
                    switch (c2){
                        case 'b':
                            condition4 = false;
                            menuGame();
                        break;
                    }
                }
		}
	}
}
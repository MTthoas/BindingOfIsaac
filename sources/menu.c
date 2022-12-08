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
#include "myUtils.h"
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

    printf("========   Credit : Dorian-Alexandre-Matthias   ==========\n\n");
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
        for(int j = 0; j < length-1; j++){
           
            if(j%2 == 0){
                if(i == 0 || i == height - 1){
                    if(arr[i][j] != 'D'){
                        arr[i][j] = 'W';
                    }
                    if(j == length / 2){
                        arr[i][j] = 'D';
                    }
                }
            }else{
                if(i == 0 || i == height - 1){
                    if(j == length / 2  ){
                        arr[i][j-1] = 'D';
                    }
                }
            }      

            if(j%2 == 0 ){
                if(j == 0 || j == length - 2){
                    arr[i][j] = 'W';
                    if(i == height / 2){
                        arr[i][j] = 'D';
                    }
                }        
            }
        }
    }

    printRoom(height, length, arr);

    int success = 0;
    int axeX = 0;
    int axeY = 0;
    int Rock = 0;
    int Spikes = 0;
    int Gap = 0;
    int condition = true;

    // TO ADD ROCKS

    while(1){
        printf("Voulez-vous ajoutez des obstacles à la salle ? (Y/N) \n");
            success = confirmation();
            if(success == 1){
                break;
            }else{
                condition = false;
                break;
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
                axeX = axeX * 2;
                if (isdigit(axeX)){
                    continue;
                }
                if(axeX > length){
                    printf("AXE X trop grand\n");
                    continue;
                }
                if(axeX % 2 == 0 ){
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
                if(axeY > height){
                    printf("AXE Y trop grand\n");
                    continue;
                }
                break;
            }

             if(arr[axeY][axeX] != ' '){
                    printf("Impossible de créer un rocher dans un mur");
                    i--;
                    continue;
            }

            arr[axeY][axeX] = 'R';
    }

        printf("\n");
        printf("          Room after rocks instructions \n");
        // if(condition == true){
        //     arr[axeY][axeX] = 'R';
        // }  
        printRoom(height, length, arr);
        condition = true;

    // TO ADD SPIKES

    while(1){
        printf("Voulez-vous ajoutez des piques à la salle ? (Y/N) \n");
            success = confirmation();
            if(success == 1){
                break;
            }else{
                condition = false;
                break;
        } 
    }

        while(condition){
            printf("Combien de piques voulez-vous ajoutez ?\n");
            Spikes = readInt();
            if(Spikes <= 0 ) {
                printf("DO NOT ENTER 0 OR LESS IDIOT\n\n");
                continue;
            }else{
                break;
            }
        }

        for(int i = 0; i < Spikes; i++ ){
            printf("\n");

            while(1){
                printf("AXE X pour créer la pique [%d] :", i+1);
                axeX = readInt();
                axeX = axeX * 2;
                if (isdigit(axeX)){
                    continue;
                }
                if(axeX > length){
                    printf("AXE X trop grand\n");
                    continue;
                }
                if(axeX % 2 == 0){
                    break;
                }else{
                    printf("AXE X pour créer la pique [%d] :", i+1);
                    axeX = readInt();
                }
            }

            while(1){
                printf("AXE Y pour créer une pique [%d] :", i+1);
                axeY = readInt();
                if (isdigit(axeY)){
                    continue;
                }
                if(axeY > height){
                    printf("AXE Y trop grand\n");
                    continue;
                }
                break;
            }

             if(arr[axeY][axeX] != ' '){
                    printf("Impossible de créer une pique dans un mur");
                    i--;
                    continue;
            }

        arr[axeY][axeX] = 'R';

        }

        printf("\n");
        printf("          Room after spikes instructions \n");
        // if(condition == true){
        //     arr[axeY][axeX] = 'S';
        // }  
        printRoom(height, length, arr);
        condition = true;

    // TO ADD GAP

    while(1){
        printf("Voulez-vous ajoutez des trous à la salle ? (Y/N) \n");
            success = confirmation();
            if(success == 1){
                break;
            }else{
                condition = false;
                break;
        } 
    }

        while(condition){
            printf("Combien de trous voulez-vous ajoutez ?\n");
            Gap = readInt();
            if(Gap <= 0 ) {
                printf("DO NOT ENTER 0 OR LESS IDIOT\n\n");
                continue;
            }else{
                 arr[axeY][axeX] = 'R';
                break;
            }
        }

        for(int i = 0; i < Gap; i++ ){
            printf("\n");

            while(1){
                printf("AXE X pour créer le trou [%d] :", i+1);
                axeX = readInt();
                axeX = axeX * 2;
                if (isdigit(axeX)){
                    continue;
                }
                if(axeX > length){
                    printf("AXE X trop grand\n");
                    continue;
                }
                if(axeX % 2 == 0){
                     arr[axeY][axeX] = 'R';
                    break;
                }else{
                    printf("AXE X pour créer le trou [%d] :", i+1);
                    axeX = readInt();
                }
            }

            while(1){
                printf("AXE Y pour créer un trou [%d] :", i+1);
                axeY = readInt();
                if (isdigit(axeY)){
                    continue;
                }
                if(axeY > height){
                    printf("AXE Y trop grand\n");
                    continue;
                }
                break;
            }

             if(arr[axeY][axeX] != ' '){
                    printf("Impossible de créer un trou dans un mur");
                    i--;
                    continue;
            }
        }

        printf("\n");
        printf("          Room after gaps instructions \n");
        // if(condition == true){
        //     arr[axeY][axeX] = 'G';
        // }  
        printRoom(height, length, arr);
        condition = true;


    
    int numberOfRoomsInt = numberOfRooms();
    char final[100];

    sprintf(final,"%s%d%s%d%s%d\n","[",height,"|",length/2,"]",numberOfRoomsInt+1);
            
        FILE *f = fopen(CHEMIN_FICHIER_PIECES, "a");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            return 1;
        }

        fputs(final, f);

        for(int i = 0; i < height; i++){
            for(int j = 0; j < length-1; j++){
                fputc(arr[i][j], f);
            }
            fputc('\n', f);
        }
        fclose(f);
        
        return 1;


}

int menuDeleteRoom(void){

    system("clear");
    printGameBanner();
    printf("---------------- DELETE ROOM  ----------------\n\n");

    CRUD_Room* head = roomsFileToRoomsList();

    int numberOfRooms = getRoomsListSize(head);

    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_PIECES);
        printf("Press 'r' to go back\n");
        return 2;
    }

    int id;
    int success = 0;
    displayAllRooms(head);
    do {
        printf("\n\nEnter the id of the room you want to delete (see above) : \n");
        id = readInt();
        if(id < 0 || id >= numberOfRooms) {
            printf("Invalid id. Please try again.\n");
            continue;
        }
        break;
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
    
    CRUD_Room* head = roomsFileToRoomsList();
    int numberOfRooms = getRoomsListSize(head);

    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_PIECES);
        printf("Press 'r' to go back\n");
        return 2;
    }

    int id;
    int success = 0;
    displayAllRooms(head);
    do {
        printf("\n\nEnter the id of the room you want to modif (see above) : \n");
        id = readInt();
        if(id <= 0 || id > numberOfRooms) {
            continue;
        }else{
            success = 1;
        }
    } while(!success);

    CRUD_Room* room = getCRUD_RoomById(head, id);

    // // print room
    printf("\n\n");

    for(int i = 0 ; i < room->lines ; i += 1) {
        for(int j = 0 ; j < room->columns ; j += 1) {
            printf("%c",room->map[i][j]);
        }
        printf("\n");
    }

        int condition = true;
        int axeX = 2;
        int axeY = 2;
        char character = 'X';
        int placement = 0;

        while (condition) {

            int c = ' ';

            if (kbhit()) {
                c = getchar();
            }

            if(c != 'x'){

                system("clear");
                printGameBanner();  
                printf("           -------- UPDATE ROOM  --------\n");

                for(int i = 0 ; i < room->lines ; i += 1) {
                    printf("\n            ");
                    for(int j = 0 ; j < room->columns ; j += 1) {
                        if(i == axeY && j == axeX){
                            printf("%s", KRED);
                            room->map[i][j] = character;
                            printf("%c",room->map[i][j]);
                            printf("%s", KNRM);
                        }else{
                            printf("%c",room->map[i][j]);
                        }
                    }
                }

                printf("\n\n");
                printf("           Press R to place a rock\n");
                printf("           Press G to place a gap\n");
                printf("           Press S to place a spike\n");
                printf("           Press Space remove an element\n\n");

                printf("           Press b to save and exit\n");

                printf("\n\n");

                #ifdef _WIN32 
                Sleep(1); 
                #else 
                usleep(70000); 
                #endif 

                if(character == 'G' && placement == 0){
                    room->map[axeY][axeX] = 'G';
                    placement = 0;
                }else{
                        if(character == 'R' && placement == 0){
                            room->map[axeY][axeX] = 'R';
                            placement = 0;
                        }else{
                            if(character == 'S' && placement == 0){
                            room->map[axeY][axeX] = 'S';
                            placement = 0;
                            }else{
                                if(character == 'V' && placement == 0){
                                    room->map[axeY][axeX] = ' ';
                                    placement = 0;
                                }else{
                                    room->map[axeY][axeX] = ' ';
                                    placement = 0;
                                }
                            }
                        }
                }

                switch (c){

                    case 'G':
                        placement = 1;
                        character = 'G'; 
                        room->map[axeY][axeX] = 'G';
                    break;

                    case 'R':
                        placement = 1;
                        character = 'R'; 
                        room->map[axeY][axeX] = 'R';  
                    break;

                    case 'S':
                        placement = 1;
                        character = 'S'; 
                        room->map[axeY][axeX] = 'S';  
                    break;

                    case 'V':

                        room->map[axeY][axeX] = ' ';
                        character = 'V'; 
                        placement = 1;

                    break;


                    case 'z':

                        if(room->map[axeY-1][axeX] != 'D' && room->map[axeY-1][axeX] != 'W' && room->map[axeY-1][axeX] != 'S'){
                            axeY--;

                            if(room->map[axeY][axeX] == 'G'){
                                character = 'G';
                            }else{
                                if(room->map[axeY][axeX] == 'R'){
                                    character = 'R';
                                }else{
                                    if(room->map[axeY][axeX] == 'S'){
                                        character = 'S';
                                    }else{
                                    character = 'X';
                                    room->map[axeY][axeX] = 'X';
                                    }
                                }
                            }
                        }

                    break;

                    case 's':

                        if(room->map[axeY+1][axeX] != 'D' && room->map[axeY+1][axeX] != 'W' ){
                            axeY++;

                             if(room->map[axeY][axeX] == 'G'){
                                character = 'G';
                            }else{
                                if(room->map[axeY][axeX] == 'R'){
                                    character = 'R';
                                }else{
                                    if(room->map[axeY][axeX] == 'S'){
                                        character = 'S';
                                    }else{
                                    character = 'X';
                                    room->map[axeY][axeX] = 'X';
                                    }
                                }
                            }
                        }                   

                    break;
                    
                    case 'd':
                        
                        if(room->map[axeY][axeX+2] != 'D' && room->map[axeY][axeX+2] != 'W'){
                            axeX++;
                            axeX++;

                             if(room->map[axeY][axeX] == 'G'){
                                character = 'G';
                            }else{
                                if(room->map[axeY][axeX] == 'R'){
                                    character = 'R';
                                }else{
                                    if(room->map[axeY][axeX] == 'S'){
                                        character = 'S';
                                    }else{
                                    character = 'X';
                                    room->map[axeY][axeX] = 'X';
                                    }
                                }
                            }
                        }

                    break;

                    case 'q':

                        if(room->map[axeY][axeX-2] != 'D' && room->map[axeY][axeX-2] != 'W'){
                            axeX--;
                            axeX--;

                             if(room->map[axeY][axeX] == 'G'){
                                character = 'G';
                            }else{
                                if(room->map[axeY][axeX] == 'R'){
                                    character = 'R';
                                }else{
                                    if(room->map[axeY][axeX] == 'S'){
                                        character = 'S';
                                    }else{
                                    character = 'X';
                                    room->map[axeY][axeX] = 'X';
                                    }
                                }
                            }

                        }
                                     
                    break;

                    case 'b':

                        removeCRUD_Room(&head, id);
                        listToRoomsFile(head);
                        freeAllRooms(head);

                        char final[100];
                        int height = room->lines;
                        int length = room->columns;

                            sprintf(final,"%s%d%s%d%s%d\n","[",height,"|",length/2,"]",id+1);
                                    
                                FILE *f = fopen(CHEMIN_FICHIER_PIECES, "a");
                                if (f == NULL)
                                {
                                    printf("Error opening file!\n");
                                    return 1;
                                }

                                fputs(final, f);

                                for(int i = 0; i < height; i++){
                                    for(int j = 0; j < length-1; j++){
                                        fputc(room->map[i][j], f);
                                    }
                                    fputc('\n', f);
                                }
                                fclose(f);
                        
                        return 1;
                    break;

                }



            }


    }

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
        printf("=========            YOU ARE DEAD            ==============\n");
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

void displayWaitMonsters() {
    int randMessage = getRandomInt(0, 6, 20);
    system("clear");
    printf("===========================================================\n");
    printf("=========      THE BINDING OF BRIATTE        ==============\n");
    printf("===========================================================\n");
    printf("\n");
    if(randMessage == 0) {
        printf("=========         Loading monsters ...       ==============\n");
    } else if(randMessage == 1) {
        printf("=========         Building the dungeon ...   ==============\n");
    } else if(randMessage == 2) {
        printf("=========         Placing the mobs ...       ==============\n");
    } else if(randMessage == 3) {
        printf("=========         Calming Athina ...         ==============\n");
    } else if(randMessage == 4) {
        printf("=========         Prepare for hell ...       ==============\n");
    } else if(randMessage == 5) {
        printf("=========         Do not forget Jesus !      ==============\n");
    }     

}
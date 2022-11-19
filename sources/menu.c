/**
 * @file menu.c
 * @author  Nairod36
 * @brief Fonctions du menu
 * @version 0.1
 * @date 2022-11-5
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/Player.h"
#include "./include/menu.h"
#include "./include/cheminsFichiers.h"
#include "./include/lectureFichiers.h"
#include "./include/objects.h"
#include "./include/mystring.h"
#include "./include/userInput.h"

void printGameBanner() {
    printf("=================================================\n");
    printf("=========== THE BINDING OF BRIATTE ==============\n");
    printf("=================================================\n");
}

void menu_init(void) {
    system("clear");
    printGameBanner();
    printf("Press 'g' to start the game\n");
    printf("Press 'i' for the ITEMS menu\n");
    printf("Press 'r' for the ROOMS menu\n");
    printf("Press 'c' for the controls information\n");
    printf("----------- Dorian-Alexandre-Matthias ----------\n");
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

    FILE* fichier = fopen(CHEMIN_FICHIER_OBJETS, "r");
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
    printf("\n Press 'r' to continue\n");
}

void menuDeleteItem(void) {
    system("clear");
    printGameBanner();
    printf("-------- DELETE ITEM  --------\n");
    
    Object* head = objectsFileToObjectsList();
    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_OBJETS);
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
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_OBJETS);
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

    CRUD_Room* head = roomsFileToRoomsList(); 
    if(head == NULL) {
        printf("Couldn't load from %s\n.", CHEMIN_FICHIER_PIECES);
        printf("Press 'r' to go back.\n");
        return;
    }
    displayAllRooms(head);
    /*

    int lines;
    int columns;
    askRoomDimensions(&lines, &columns);
    columns *= 2; // to fill spaces

    CRUD_Room* newRoom = createEmptyCRUD_Room(lines, columns);

    printf("New room created and added : \n");
    displayCRUD_Room(newRoom);
    printf("Do you want to add it (y/n)?\n");
    int success = confirmation();
    if(success) {
        int res = addCRUD_Room(head, newRoom);
        if(res) {
            //displayAllRooms(head);
            listToRoomsFile(head);
        } else {
            printf("Could not add the room.\n");
            
        }
        freeAllRooms(head);
        printf("New room added\n");
    }
    */
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

    CRUD_Room* head = roomsFileToRoomsList();
    if(head == NULL) {
        printf("Couldn't open %s\n.", CHEMIN_FICHIER_PIECES);
        printf("Press 'r' to go back\n");
        return;
    }

    int id;
    int success = 0;
    displayAllRooms(head);
    do {
        printf("Enter the id of the room you want to update (see above) : \n");
        id = readInt();
        printf("You selected the id %d. Is it correct ? (y/n) \n", id);
        success = confirmation();
    } while(!success);

    CRUD_Room* room = getCRUD_RoomById(head, id);
    if(room == NULL) {
        printf("Couldn't get the room of id : %d\n", id);
        printf("Press 'r' to continue\n");
        return;
    }

    success = 1;
    int x, y; // position
    char element;
    do {
        system("clear");
        printGameBanner();
        printf("-------- UPDATE ROOM  --------\n");
        displayCRUD_Room(room);

        printf("\nSelect the position of the element you want to change in this room.\n");
        askPosition(&x, &y, room);
        printf("What element do you want to place at position (%d,%d) ?\n", x, y);
        askRoomElement(&element);
        room->map[x-1][y-1] = element;
        printf("Changes : \n");
        displayCRUD_Room(room);

        printf("\nContinue changes ?(y/n) ? \n");
        success = confirmation();
    } while(success);

    system("clear");
    printGameBanner();
    printf("-------- UPDATE ROOM  --------\n");
    displayCRUD_Room(room);
    printf("Validate changes ?\n");
    success = 0;
    success = confirmation();
    if(success) {
        listToRoomsFile(head);
    }

}

void menuControl(void){
    system("clear");
    printGameBanner();
    printf("--------------- Info control  ----------------\n");
    printf("Use z,q,s,d to move\n");
    printf("Use 8,4,5,6 to attack\n");
    printf("Use x to quit the game\n");

    printf("\nPress ENTER to continue ...\n");
    getchar();
    return;
}

/**
 * @file roomsForCRUD.c
 * @author TheGreat-Chain
 * @brief Functions used only by the menu. Rooms.c stuff are used by the game
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "./include/roomsForCRUD.h"
#include "./include/array.h"

#include <stdio.h>
#include <stdlib.h>

CRUD_Room* createCRUD_Room(int lines, int columns, char** map){
    CRUD_Room* room = malloc(sizeof(CRUD_Room));

    room->id = 1;
    room->lines = lines;
    room->columns = columns; 
    room->map = map;
    room->next = NULL;

    return room;
}

CRUD_Room* createEmptyCRUD_Room(int lines, int columns) {

    CRUD_Room* room = malloc(sizeof(CRUD_Room));

    char** map = malloc(lines * sizeof(char*));
    for(int i=0 ; i < lines ; i += 1) {
        map[i] = malloc(columns * sizeof(char));
    }
    
    // fill map
    for(int i=0 ; i < lines ; i += 1) {
        for(int j=0 ; j < columns ; j += 1) {
            if(i == 0 || i == lines-1) { // top and bottom
                if(j%2 == 1) {
                    map[i][j] = ' ';
                } else {
                    map[i][j] = 'W';
                }
            }

            else if(j == 0 || j == columns-2) { // left and right
                map[i][j] = 'W';
            }

            else {
                map[i][j] = ' ';
            }
        }
    } // for
    

    room->id = 1;
    room->lines = lines;
    room->columns = columns;
    room->map = map;
    room->next = NULL;

    return room;
}

void freeCRUD_Room(CRUD_Room* room) {
    //freeCharArray2D(room->map, room->lines, room->columns);
    free(room->map);
    free(room);
}

int freeAllRooms(CRUD_Room* head) {
    if(head == NULL || head->id != 1) { // not the first room
        return 0;
    }

    CRUD_Room* next;
    while(head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }

    return 1;
}

void displayCRUD_Room(CRUD_Room* room) {
    if(room == NULL) {
        printf("not any room\n");
        return;
    }

    printf("\n");
    printf("       [%d|%d]%d", room->lines, room->columns/2, room->id); // columns / 2 because of spaces

    for(int i = 0 ; i < room->lines ; i += 1) {
        printf("\n       ");
        for(int j = 0 ; j < room->columns ; j += 1) {
            printf("%c",room->map[i][j]);
        }
    }
}

void displayAllRooms(CRUD_Room* head) {
    if(head == NULL) {
        printf("Not any list :).\n");
        return;
    }

    CRUD_Room* current = head;
    while(current != NULL) { // tant qu'on n'est pas à la fin de la liste 
        displayCRUD_Room(current);
        current = current->next;
    }
}

CRUD_Room* duplicateCRUD_Room(CRUD_Room* room) {
    CRUD_Room* newRoom = malloc(sizeof(CRUD_Room) * 1);

    newRoom->id = room->id;
    newRoom->lines = room->lines;
    newRoom->columns = room->columns;
    newRoom->map = duplicateCharArray2D(room->map, room->lines, room->columns);
    newRoom->next = room->next;
    
    free(room);
    return newRoom;
}

int addCRUD_Room(CRUD_Room* head, CRUD_Room* newRoom) {
    CRUD_Room* current = head;

    if(head == NULL || head->id != 1) { // fail if null or not first
        return 0; 
    }

    while(current->next != NULL) { // aller a la fin de liste
        current = current->next;
    }

    current->next = duplicateCRUD_Room(newRoom);
    arrangeRoomsIds(head);
    return 1; // success
}

void arrangeRoomsIds(CRUD_Room* head) {
    int count = 1;
    CRUD_Room* current = head;
    while(current != NULL) {
        current->id = count;
        count += 1;
        current = current->next;
    }
}

// Void deleteSpecificRoom(CRUD_Room* head, int id) {
//     CRUD_Room* current = head;
//     CRUD_Room* previous;

//     if(head == NULL || head->id != 1) { // fail if null or not first
//         return;
//     }

//     if(current->id == id) { // supprimer premier element
//         head = current->next;
//         free(current);
//         return;
//     }



void removeCRUD_Room(CRUD_Room** ptr_head, int id) {
    CRUD_Room* tmp = *ptr_head;
    CRUD_Room* previous;

    if(tmp != NULL && tmp->id == id) { // supprimer premier element
        tmp->next->id = 1; // the second object becomes the first
        *ptr_head = tmp->next;
        free(tmp);
        arrangeRoomsIds(*ptr_head);
        return;
    }

    while(tmp != NULL && tmp->id != id) { // aller jusqu'à l'objet à delete
        
        previous = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL) { // id non présent
        return;
    }

    previous->next = tmp->next;
    arrangeRoomsIds(*ptr_head);
}

CRUD_Room* getCRUD_RoomById(CRUD_Room* head , int id) {
    CRUD_Room* result = head;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->next;
    }

    return NULL;
}

int getRoomsListSize(CRUD_Room* head) {
    CRUD_Room* current = head;

    if(current == NULL) {
        return 0;
    }

    int count = 0;
    while(current != NULL) {
        count += 1;
        current = current->next;
    }

    return count;
}

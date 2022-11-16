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
    room->columns = columns; //because of spaces
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

            else if(j == 0 || j == columns-1) { // left and right
                map[i][j] = 'W';
            }

            else {
                map[i][j] = ' ';
            }
        }
    }   
    

    room->id = 1;
    room->lines = lines;
    room->columns = columns;
    room->map = map;
    room->next = NULL;

    return room;
}

RoomsList* createRoomsList() {
    RoomsList* rooms = malloc(sizeof(RoomsList) * 1);
    return rooms;
}

void freeCRUD_Room(CRUD_Room* room) {
    //freeCharArray2D(room->map, room->lines, room->columns);
    free(room);
}

void freeRoomsList(RoomsList* roomsList) {
    CRUD_Room* current = roomsList->firstRoom;
    CRUD_Room* next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(roomsList);
}

void displayCRUD_Room(CRUD_Room* room) {
    if(room == NULL) {
        printf("not any room\n");
        return;
    }

    printf("[%d|%d]%d\n", room->lines, room->columns/2, room->id); // columns / 2 because of spaces

    for(int i = 0 ; i < room->lines ; i += 1) {
        for(int j = 0 ; j < room->columns ; j += 1) {
            printf("%c",room->map[i][j]);
        }
    }
}

void displayRoomsList(RoomsList* rooms) {
    if(rooms == NULL) {
        printf("Not any list :).\n");
        return;
    }

    CRUD_Room* current = rooms->firstRoom;
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

    return newRoom;
}

int addCRUD_Room(RoomsList* rooms, CRUD_Room* newRoom) {
    CRUD_Room* current = rooms->firstRoom;
    int index = 1; //formera l'id du nouvel objet

    if(current == NULL) { // empty list
        newRoom->id = index;
        rooms->firstRoom = duplicateCRUD_Room(newRoom);
        return index;
    }

    while(current != NULL) { // append new room
        index += 1;
        if(current->next == NULL) {
            newRoom->id = index;
            current->next = duplicateCRUD_Room(newRoom);
            return index;
        }
        current = current->next;
    }

    return 0;
}

void arrangeRoomsList(RoomsList* rooms) {
    int count = 1;
    CRUD_Room* current = rooms->firstRoom;
    while(current != NULL) {
        current->id = count;
        count += 1;
        current = current->next;
    }
}

void removeCRUD_Room(RoomsList* rooms, int id) {
    CRUD_Room* toDelete;
    if(rooms->firstRoom != NULL && rooms->firstRoom->id == id) { // supprimer premier element
        toDelete = rooms->firstRoom;
        rooms->firstRoom = rooms->firstRoom->next;
        arrangeRoomsList(rooms);
        freeCRUD_Room(toDelete);
        return;
    }

    CRUD_Room* current = rooms->firstRoom;
    while(current != NULL ) {

        if(current->next != NULL && current->next->id == id) { // suppression
            toDelete = current->next;
            current->next = current->next->next;
            arrangeRoomsList(rooms);
            freeCRUD_Room(toDelete);
            return;
        }
        
        current = current->next;
    }
}

CRUD_Room* getCRUD_RoomById(RoomsList* rooms , int id) {
    CRUD_Room* result = rooms->firstRoom;

    while(result != NULL) {
        if(result->id == id) {
            return result;
        }
        result = result->next;
    }

    return NULL;
}

int getRoomsListSize(RoomsList* rooms) {
    CRUD_Room* current = rooms->firstRoom;

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

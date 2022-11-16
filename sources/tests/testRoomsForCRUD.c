#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/array.h"
#include "../include/roomsForCRUD.h"

void test_createCRUD_Room(); //ok
void test_createEmptyCRUD_Room(); //ok
void test_freeCRUD_Room(); // not tested but ok
void test_freeRoomsList(); // not tested but ok
void test_createRoomsList(); // not tested but ok
void test_displayCRUD_Room(); //ok
void test_displayRoomsList(); // not tested but ok
void test_addCRUD_Room(); //ok
void test_duplicateCRUD_Room(); // not tested but ok
void test_removeCRUD_Room(); //ok
void test_getCRUD_RoomById(); // not tested but ok
void test_arrangeRoomsList(); //ok
void test_getRoomsListSize(); //ok


int main(void) {
    test_createEmptyCRUD_Room();
    //test_createCRUD_Room();
    //test_displayCRUD_Room();
    //test_addCRUD_Room();
    //test_removeCRUD_Room();
    //test_getRoomsListSize();

    return 0;
}

void test_getRoomsListSize() {
    printf("[TEST] getRoomsListSize()\n\n");

    //prepare
    CRUD_Room* r1 = createEmptyCRUD_Room(10, 9);
    CRUD_Room* r2 = createEmptyCRUD_Room(3, 7);
    CRUD_Room* r3 = createEmptyCRUD_Room(19, 21);

    RoomsList* rooms = createRoomsList();
    addCRUD_Room(rooms, r1);
    addCRUD_Room(rooms, r2);
    addCRUD_Room(rooms, r3);

    printf("Expect : %d\nResult : %d\n", 3, getRoomsListSize(rooms));

    removeCRUD_Room(rooms, 1);
    removeCRUD_Room(rooms, 1);
    removeCRUD_Room(rooms, 1);
    printf("Expect : %d\nResult : %d\n", 0, getRoomsListSize(rooms));
}

void test_removeCRUD_Room() {
    printf("[TEST] removeCRUD_Room()\n\n");

    //prepare
    CRUD_Room* r1 = createEmptyCRUD_Room(10, 9);
    CRUD_Room* r2 = createEmptyCRUD_Room(3, 7);
    CRUD_Room* r3 = createEmptyCRUD_Room(19, 21);

    RoomsList* rooms = createRoomsList();
    addCRUD_Room(rooms, r1);
    addCRUD_Room(rooms, r2);
    addCRUD_Room(rooms, r3);

    printf("Initial rooms : \n\n");
    displayRoomsList(rooms);

    //tests
    printf("\nTEST 1 - Remove room in the middle\n");
    removeCRUD_Room(rooms, 2);
    displayRoomsList(rooms);

    printf("\nTEST 2 - Remove first room\n");
    addCRUD_Room(rooms, r2);
    removeCRUD_Room(rooms, 1);
    displayRoomsList(rooms);

    printf("\nTEST 3 - Remove last room\n");
    addCRUD_Room(rooms, r2);
    removeCRUD_Room(rooms, 3);
    displayRoomsList(rooms);

}

void test_addCRUD_Room() {
    printf("[TEST] addCRUD_Room()\n\n");

    // room 1
    int lines = 14;
    int columns = 9;
    char** map = malloc(lines * sizeof(char*));
    for(int i=0 ; i < lines ; i += 1) {
        map[i] = malloc(columns * sizeof(char));
    }
    
    // fill map
    for(int i=0 ; i < lines ; i += 1) {
        for(int j=0 ; j < columns ; j += 1) {
            if(i == 0 || i == lines-1) { // top and bottom
                map[i][j] = 'W';
            }

            else if(j == 0 || j == columns-1) { // left and right
                map[i][j] = 'W';
            }

            else {
                map[i][j] = ' ';
            }
        }
    }
    map[lines/2][columns - 8] = 'G';
    CRUD_Room* r1 = createCRUD_Room(lines, columns, map);

    // room 2
    lines = 6;
    columns = 4;
    char** map2 = malloc(lines * sizeof(char*));
    for(int i=0 ; i < lines ; i += 1) {
        map2[i] = malloc(columns * sizeof(char));
    }
    
    // fill map
    for(int i=0 ; i < lines ; i += 1) {
        for(int j=0 ; j < columns ; j += 1) {
            if(i == 0 || i == lines-1) { // top and bottom
                map2[i][j] = 'W';
            }

            else if(j == 0 || j == columns-1) { // left and right
                map2[i][j] = 'W';
            }

            else {
                map2[i][j] = ' ';
            }
        }
    }
    map2[lines/2][columns - 2] = 'R';
    CRUD_Room* r2 = createCRUD_Room(lines, columns, map2);

    //test
    RoomsList* rooms = createRoomsList();
    addCRUD_Room(rooms, r1);
    addCRUD_Room(rooms, r2);

    printf("RESULT : \n");
    displayRoomsList(rooms);
}

void test_displayCRUD_Room() {
    printf("[TEST] displayCRUD_Room()\n\n");

    // prepare
    int lines = 14;
    int columns = 9;
    char** map = malloc(lines * sizeof(char*));
    for(int i=0 ; i < lines ; i += 1) {
        map[i] = malloc(columns * sizeof(char));
    }
    
    // fill map
    for(int i=0 ; i < lines ; i += 1) {
        for(int j=0 ; j < columns ; j += 1) {
            if(i == 0 || i == lines-1) { // top and bottom
                map[i][j] = 'W';
            }

            else if(j == 0 || j == columns-1) { // left and right
                map[i][j] = 'W';
            }

            else {
                map[i][j] = ' ';
            }
        }
    }
    map[lines/2][columns - 8] = 'G';

    //test
    CRUD_Room* room = createCRUD_Room(lines, columns, map);
    printf("     EXPECT : \n");
    printf("[%d][%d]1\n", lines, columns);
    displayCharArray2D(map, lines, columns);
    printf("     RESULT : \n");
    displayCRUD_Room(room);

}

void test_createCRUD_Room() {
    printf("[TEST] createCRUD_Room()\n\n");

    // prepare
        int lines = 7;
        int columns = 6;
        char** map = malloc(lines * sizeof(char*));
        for(int i=0 ; i < lines ; i += 1) {
            map[i] = malloc(columns * sizeof(char));
        }
        
        // fill map
        for(int i=0 ; i < lines ; i += 1) {
            for(int j=0 ; j < columns ; j += 1) {
                if(i == 0 || i == lines-1) { // top and bottom
                    map[i][j] = 'W';
                }

                else if(j == 0 || j == columns-1) { // left and right
                    map[i][j] = 'W';
                }

                else {
                    map[i][j] = ' ';
                }
            }
        }
    map[lines/2][columns - 8] = 'G';
    

    // test
    printf("     EXPECT : \n");
    printf("id = 1\n");
    printf("height = %d\n", lines);
    printf("width = %d\n", columns);
    printf("map = \n");
    displayCharArray2D(map, lines, columns);

    CRUD_Room* room = createCRUD_Room(lines, columns, map);
    
    printf("\n     RESULT : \n");
    if(room == NULL) {
        printf("No Room :)\n");
        return;
    }
    printf("id = %d\n", room->id);
    printf("height = %d\n", room->lines);
    printf("width = %d\n", room->columns);
    printf("map = \n");
    displayCharArray2D(room->map, room->lines, room->columns); 

    freeCharArray2D(map, lines, columns);
}

void test_createEmptyCRUD_Room() {
    printf("[TEST] createEmptyCRUD_Room()\n\n");

    // prepare 
    int lines = 15;
    int columns = 9;
    char** emptyMap = malloc(sizeof(char*) * lines);
    for(int i=0 ; i < lines ; i += 1) {
        emptyMap[i] = malloc(columns * sizeof(char));
    }

    // fill map
    for(int i=0 ; i < lines ; i+=1) {
        for(int j=0 ; j < columns ; j+=1) {
            if(i == 0 || i == lines-1) { // top and bottom
                emptyMap[i][j] = 'W';
            }

            else if(j == 0 || j == columns-1) { // left and right
                emptyMap[i][j] = 'W';
            }

            else {
                emptyMap[i][j] = ' ';
            }
        }
    } 

    //test 
    CRUD_Room* room = createEmptyCRUD_Room(lines, columns);

    printf("     EXPECT : \n");
    printf("id = 1\n");
    printf("height = %d\n", lines);
    printf("width = %d\n", columns);
    printf("map = \n");
    displayCharArray2D(emptyMap, lines, columns);

    printf("\n     RESULT : \n");
    if(room == NULL) {
        printf("No Room :)\n");
        return;
    }
    printf("id = %d\n", room->id);
    printf("height = %d\n", room->lines);
    printf("width = %d\n", room->columns);
    printf("map = \n");
    displayCRUD_Room(room); 

    freeCRUD_Room(room);
}
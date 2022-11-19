#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/array.h"
#include "../include/roomsForCRUD.h"

void test_createCRUD_Room(); // not tested specifically but OK
void test_createEmptyCRUD_Room(); //OK
void test_freeCRUD_Room(); // ok
void test_freeAllRooms(); // not tested specifically but OK
void test_displayCRUD_Room(); //OK
void test_displayAllRooms(); //OK
void test_duplicateCRUD_Room(); // not tested specifically but OK
void test_addCRUD_Room(); // ok
void test_arrangeRoomsIds(); // not tested specifically but OK
void test_removeCRUD_Room(); // ok
void test_getCRUD_RoomById(); // ok
void test_getRoomsListSize(); // ok

int main(void) {
    //test_createEmptyCRUD_Room();
    //test_displayCRUD_Room();
    //test_displayAllRooms();
    //test_addCRUD_Room();
    //test_removeCRUD_Room();
    //test_freeCRUD_Room();
    //test_getCRUD_RoomById();
    //test_getRoomsListSize();
    return 0;
}

void test_getRoomsListSize() {
    printf("[TEST] getRoomsListSize()\n\n");

    int lines = 4;
    int columns = 7;

    CRUD_Room* head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));

    printf("Attendu : 4\nRésultat : %d\n", getRoomsListSize(head));
}

void test_getCRUD_RoomById() {
    printf("[TEST] getCRUD_RoomById()\n\n");
    int lines = 4;
    int columns = 7;

    CRUD_Room* head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));

    printf("\nTEST 1 - Get une room qui n'existe pas\n");
    displayCRUD_Room(getCRUD_RoomById(head, 789));
    printf("\nTEST 2 - Get une room \n");
    displayCRUD_Room(getCRUD_RoomById(head, 2));


}

void test_freeCRUD_Room() {
    printf("[TEST] freeCRUD_Room()\n\n");
    int lines = 4;
    int columns = 7;

    CRUD_Room* head = createEmptyCRUD_Room(lines, columns*2);
   
    char** map = head->map;
    freeCRUD_Room(head);
    printf("Should print random things (or crash) :)\n");
    printf("%d %d\n", head->id, head->lines);
    map[1][1] = 'E';
}

void test_removeCRUD_Room() {
    printf("[TEST] removeCRUD_Room()\n\n");
    int lines = 4;
    int columns = 7;

    CRUD_Room* head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));

    printf("Liste initiale : \n"); displayAllRooms(head);
    printf("\nTEST 1 - Supprimer une room qui n'existe pas\n");
    removeCRUD_Room(&head, 78);
    displayAllRooms(head);

    freeAllRooms(head);

    printf("\nTEST 2 - Supprimer une room \n");
    head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    removeCRUD_Room(&head, 3);
    displayAllRooms(head);

    freeAllRooms(head);

    printf("\nTEST 3 - Supprimer 1e room \n");
    head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    removeCRUD_Room(&head, 3);
    displayAllRooms(head);

    freeAllRooms(head);


    printf("\nTEST 4 - Supprimer last room \n");
    head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    removeCRUD_Room(&head, 4);
    displayAllRooms(head);

}

void test_addCRUD_Room() {
    printf("[TEST] addCRUD_Room()\n\n");
    int lines = 4;
    int columns = 7;
    CRUD_Room* head = createEmptyCRUD_Room(lines, columns*2);
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    addCRUD_Room(head, createEmptyCRUD_Room(lines, columns*2));
    displayAllRooms(head);
}

void test_displayAllRooms() {
    printf("[TEST] displayCRUD_Room()\n");
    int lines = 4;
    int columns = 7;
    CRUD_Room* head = createEmptyCRUD_Room(lines, columns*2);
    head->next = createEmptyCRUD_Room(lines, columns*2);
    head->next->next = createEmptyCRUD_Room(lines, columns*2);

    displayAllRooms(head);
}

void test_createEmptyCRUD_Room() {
    printf("[TEST] displayCRUD_Room()\n");
    int lines = 4;
    int columns = 7;

    CRUD_Room* room = createEmptyCRUD_Room(lines, columns*2);
    printf("Affichage : \n");
    displayCRUD_Room(room);
}

void test_displayCRUD_Room() {
    printf("[TEST] displayCRUD_Room()\n");

    // prepare
    int lines = 4;
    int columns = 4;
    columns *= 2;
    char** map = malloc(sizeof(char*) * lines);
    for(int i=0 ; i < lines ; i+=1) {
        map[i] = malloc(sizeof(char) * columns);
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
    }

    CRUD_Room* room = createCRUD_Room(lines, columns, map);
    printf("Affichage : \n");
    displayCRUD_Room(room);
}
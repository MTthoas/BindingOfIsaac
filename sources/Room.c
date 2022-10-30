#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Room.h"
#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

/* Prototypes */

// char * copy_not_empty(const char * str);
// void NumberOfRooms();
// void newRooms(Room *s, RoomInSpace * v);
// int NumberOfDoorsByRoom(Room * s);
// void freeRoom(Room *s);
int numberOfRooms();
void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms);
void InitialiseRoom(struct Donjon * d, int stage, int number, int numberOfRooms);
char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);

void InitialisationGame() {

    Donjon * d = malloc(sizeof(Donjon));

    for (int i = 1; i <= NUMBER_STAGES_MAX; i++) {
        printf("Stage : %d\n", i);
        int NumberOfRoomsInt = numberOfRooms();
        printf("Nombre de salles : %d\n", NumberOfRoomsInt);

        newStageByNumber(d, i, NumberOfRoomsInt);
            
        for (int y = 1; y <= NumberOfRoomsInt; y++) {

            InitialiseRoom(d, i, y, NumberOfRoomsInt);

        }

            

        for (int k = 0; k < NumberOfRoomsInt + 1; k++) {
            for (int j = 0; j < NumberOfRoomsInt + 1; j++) {
                printf("%c", d -> stages[i].stage[k][j]);
            }
            printf("\n");
        }

        }

        (void) d;

    }

void InitialiseRoom(struct Donjon * d, int stage, int number, int numberOfRooms){

    // d-> stages[stage].rooms[number].room = malloc(sizeof(char) * (numberOfRooms + 1));

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = "[]";
    int * tab = 0;
    int iteration = 1;
    // int numberDoors = 0;

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL){
        printf("errot for reading file");
        exit(EXIT_FAILURE);
    }

    while ((read = getline( & line, & len, fp)) != -1) {

        if (strcspn(line, "[") == 0) {

            char * stockPtr = strtok(line, delim);

            tab = malloc(sizeof(int) * 3);
            stockPtr = strtok(stockPtr, "|");

            for (int j = 0; stockPtr != NULL; j++) {
                tab[j] = atoi(stockPtr);
                stockPtr = strtok(NULL, "|");
            }

            tab[2] = iteration;
            tab[1] = tab[1]*2;
            // tab[0] = tab[0];

            if (iteration == number) {
                

                d-> stages[stage].rooms[number].room = malloc(sizeof(char) * tab[0]);

                for (int i = 0; i < tab[0]; i++) {
                    d-> stages[stage].rooms[number].room[i] = malloc(sizeof(char) * tab[1]);
                }

                d-> stages[stage].rooms[number].room = RoomByNumber(tab[0], tab[1], number);
                d-> stages[stage].rooms[number].number = number;
                d-> stages[stage].rooms[number].height = tab[0];
                d-> stages[stage].rooms[number].width = tab[1];
                d-> stages[stage].rooms[number].numberOfDoors = NumberOfDoorsByRoom( d-> stages[stage].rooms[number].room, tab[0], tab[1]);

                // printf("Room number : %d\n", d-> stages[stage].rooms[number].number);
                // printf("Height : %d\n",tab[0]);
                // printf("Width : %d \n", tab[1]);
                // printf("NumberOfDoors : %d \n", d-> stages[stage].rooms[number].numberOfDoors);

                // for(int i = 0; i < tab[0]; i++){
                //     for(int j = 0; j < tab[1]; j++){
                //         printf("%c", d-> stages[stage].rooms[number].room[i][j]);
                //     }
                //     // printf("\n");
                // }

                    d-> stages[stage].rooms[number].doorTop = 0;
                    d-> stages[stage].rooms[number].doorBottom = 0;
                    d-> stages[stage].rooms[number].doorLeft = 0;
                    d-> stages[stage].rooms[number].doorRight = 0;

                for(int i  = 0; i< tab[0]; i++){
                    for(int j = 0; j < tab[1]; j++){
                        if(d-> stages[stage].rooms[number].room[i][j] == 'D' && i == 0){
                        d-> stages[stage].rooms[number].doorTop = 1;
                        }
                        if(d-> stages[stage].rooms[number].room[i][j] == 'D' && i == tab[0] - 1){
                        d-> stages[stage].rooms[number].doorBottom = 1;
                        }
                        if(d-> stages[stage].rooms[number].room[i][j] == 'D' && j == tab[1] - 2){
                        d-> stages[stage].rooms[number].doorRight = 1;
                        }
                        if(d-> stages[stage].rooms[number].room[i][j] == 'D' && j == 0){
                        d-> stages[stage].rooms[number].doorLeft = 1;
                        }
                    }
                }

                free(tab);
            }
            
            iteration++;
            // free(tab);

        }
    }

    fclose(fp);

    if (line)
        free(line);

    (void)d;
    (void)stage;
    (void)number;
    (void)numberOfRooms;
}



void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms) {

    d -> stages[stage].stage = malloc(sizeof(char * ) * numberOfRooms + 1);

    for (int i = 0; i < numberOfRooms + 1; i++) {
        d -> stages[stage].stage[i] = malloc(sizeof(char) * numberOfRooms + 1);
    }

    for (int i = 0; i < numberOfRooms + 1; i++) {
        for (int y = 0; y < numberOfRooms + 1; y++) {
            if (i == (numberOfRooms / 2) && y == (numberOfRooms / 2)) {
                d -> stages[stage].stage[i][y] = 'P';
            } else {
                d -> stages[stage].stage[i][y] = ' ';
            }
        }
    }

}

int numberOfRooms() {

    FILE * fp;
    size_t len = 0;
    ssize_t read;
    int iteration = 0;
    char * line = NULL;

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline( & line, & len, fp)) != -1) {
        if (strcspn(line, "[") == 0) {
            iteration++;
        }
    }

    fclose(fp);
    if (line)
        free(line);

    return iteration;


}


int NumberOfDoorsByRoom(char ** s, int height, int width){

    int iteration = 1;

    for(int i  = 0; i< height; i++){
        for(int y = 0; y < width; y++){
            if(s[i][y] == 'D'){
                iteration++;
            }
        }
    }
    return iteration;
}


char ** RoomByNumber(int height, int length, int number) {

    int iteration = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int num = 0;

    /* Malloc selon la hauteur du tableau */

    char ** lines = malloc(sizeof(char * ) * height);

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);


    while ((read = getline( & line, & len, fp)) != -1) {
        iteration++;

        /* Permet de cibler la room sélectionné */

        if (iteration > 2 + (number - 1) * (height + 1) && iteration <= 2 + (number - 1) * (height + 1) + height) {

            /* Sécurité pour éviter une fuite de mémoire */

            if (num == height) {
                char ** newlines = realloc(lines, sizeof(char * ) * height);
                if (!newlines) {
                    printf("error reallocating array\n");
                    break;
                }
                lines = newlines;
                printf("Test");
            }

            lines[num] = line;
            num++;

            line = NULL;
            len = 0;

        }

    };

    (void) length;

    fclose(fp);

    if (line)
        free(line);

    return lines;

}


// void freeRoom(Room *s){
//     free(s);
// }



// void newRooms(Room * s, RoomInSpace *  v){

//     (void)v;

//     s->rooms = malloc(sizeof(char * ) * s->numberOfRoomsReturned+1);

//     printf("Nombre de room : %d\n", s->numberOfRoomsReturned);

//     for(int i = 0; i< s->numberOfRoomsReturned+1; i++){
//         s->rooms[i] = malloc(sizeof(char) * s->numberOfRoomsReturned+1);
//     }

//     for(int i = 0; i < s->numberOfRoomsReturned+1; i++){
//         Room * room = newRoom(i+1);
//         int numberOfDoors = s->numberOfDoors;
//         printf("Number of door : %d", numberOfDoors);
//                 (void)numberOfDoors;
//                 (void)room;
//         // printf("%d", numberOfDoors);
//         for(int j = 0; j < s->numberOfRoomsReturned+1; j++){
//             if(i == ( s->numberOfRoomsReturned ) / 2  && j == (s->numberOfRoomsReturned) / 2 ){
//                 s->rooms[i][j] = 'P';

//             }else{
//                    s->rooms[i][j] = ' ';
//             }


//         }
//     }

//     for(int i = 0; i < s->numberOfRoomsReturned+1 ; i++){
//         for(int j = 0; j< s->numberOfRoomsReturned+1 ; j++){
//             printf("%c", s->rooms[i][j]);
//         }
//         printf("\n");
//     }





// }


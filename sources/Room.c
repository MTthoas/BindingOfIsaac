#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Room.h"
#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"
#include <time.h>

/* Prototypes */

// char * copy_not_empty(const char * str);
// void NumberOfRooms();
// void newRooms(Room *s, RoomInSpace * v);
// int NumberOfDoorsByRoom(Room * s);
// void freeRoom(Room *s);
int numberOfRooms();
void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms);
void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms);
char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);
void PlaceRoomsInStage(struct Donjon * d, int stage, int numberOfRooms);

void InitialisationGame() {

    Donjon * d = malloc(sizeof(Donjon));

    for (int i = 0; i < NUMBER_STAGES_MAX; i++) {

        printf("Stage : %d\n", i);
        int NumberOfRoomsInt = numberOfRooms();
        printf("Nombre de salles : %d\n", NumberOfRoomsInt);

        newStageByNumber(d, i, NumberOfRoomsInt);
        InitialiseRoom(d, i, NumberOfRoomsInt);
        printf("\n");

        // for(int i = 15; i < 9; i++){
        //     for(int j = 1; j < 15; j++){
        //         printf("%c", d-> stages[0].rooms[2].room[i][j]);
        //     }
        //     // printf("\n");
        // }
        
        // printf("%d\n", d->stages[i].rooms[5].doorLeft);
        //  printf("%d\n", d->stages[i].rooms[3].doorLeft);
        //   printf("%d\n", d->stages[i].rooms[4].doorLeft);
        //    printf("%d\n", d->stages[i].rooms[2].doorLeft);
        // PlaceRoomsInStage(d, i, NumberOfRoomsInt);

        // for (int k = 0; k < NumberOfRoomsInt + 1; k++) {
        //     for (int j = 0; j < NumberOfRoomsInt + 1; j++) {
        //         printf("%c", d -> stages[i].stage[k][j]);
        //     }
        //     printf("\n");
        // }

        }

        (void) d;

}

void searchSpecificRoom(struct Donjon * d, int roomNumber, char * specific){
(void)d;
(void)roomNumber;
(void)specific;

    printf("TEST : %s", specific);
}


void PlaceRoomsInStage(struct Donjon * d, int stage, int numberOfRooms) {

    
    srand( time( NULL ) );

      for (int i = 0; i < numberOfRooms + 1; i++) {
        for (int y = 0; y < numberOfRooms + 1; y++) {

            // Initialisation de la room principale

            if (i == (numberOfRooms / 2) && y == (numberOfRooms / 2)) {
                d -> stages[stage].stage[i][y] = 'P';
                d -> stages[stage].rooms[1].positionX = i;
                d -> stages[stage].rooms[1].positionY = y;

                for(int k = 1; k < numberOfRooms+1; k++) {

                    int iterationDoors = 0;

                    // Parce que c'est un carré
                    if(k==1){

                    for(int j = 0; j < 4; j++) {

                        if(j == 0 && d-> stages[stage].rooms[k].doorTop == 1){
                            printf("Possède une porte en haut Pour : room %d \n",  d-> stages[stage].rooms[k].number);
                            iterationDoors++;
                            // searchSpecificRoom(d, k, "T");
                        }

                        if(j == 1 && d-> stages[stage].rooms[k].doorLeft == 1){
                            printf("Possède une porte à gauche Pour : room %d \n",  d-> stages[stage].rooms[k].number);
                            iterationDoors++;
                        }

                        if(j == 2 && d-> stages[stage].rooms[k].doorRight == 1){
                            printf("Possède une porte à droite Pour : room %d \n",  d-> stages[stage].rooms[k].number);
                            iterationDoors++;
                        }

                        if(j == 3 && d-> stages[stage].rooms[k].doorBottom == 1){
                            printf("Possède une porte en bas Pour : room %d \n",  d-> stages[stage].rooms[k].number);
                            iterationDoors++;
                        }
                     
                        }

                        int * tabDoors = malloc(sizeof(int) * numberOfRooms+1);
                        int * tabStock = malloc(sizeof(int) * numberOfRooms);
                        int random;

                        for(int h = 0; h<numberOfRooms+1; h++){
                            tabDoors[h] = 0;
                        }

                        for(int v = 0; v < numberOfRooms; v++){
                            random = (rand() % numberOfRooms) + 1;

                            while(tabDoors[random] == random && random != 0){
                                random = (rand() % numberOfRooms);
                            }

                            tabDoors[random] = random;
                            tabStock[v] = random;
 
                        }

                        for(int h = 0; h<numberOfRooms; h++){
                            printf("tabDoors[%d] : %d\n", h, tabStock[h]);
                        }



                
                    }

                    
                }

            }
        }
    }

    // int iteration = 2;

    // for (int i = 0; i < numberOfRooms + 1; i++) {
    //     for (int y = 0; y < numberOfRooms + 1; y++) {

    //         // for(int j = 0; j< numberOfRooms; j++) {

    //             if(i == (numberOfRooms / 2) || i == (numberOfRooms / 2  )){

    //                 // Right
    //                 if( y == (numberOfRooms / 2) + 1){

    //                     // iteration++;

    //                     if( d -> stages[stage].rooms[iteration].doorLeft == 1){
    //                         d -> stages[stage].stage[i][y] = 'S';
    //                         d -> stages[stage].rooms[iteration].positionX = i;
    //                         d -> stages[stage].rooms[iteration].positionY = y;

    //                         iteration++;
    //                     }
                        
                        
    //                 }

    //                 // Left

    //                 if( y == (numberOfRooms / 2) -1){

    //                      if( d -> stages[stage].rooms[iteration].doorRight == 1){
    //                         d -> stages[stage].stage[i][y] = 'S';
    //                         d -> stages[stage].rooms[iteration].positionX = i;
    //                         d -> stages[stage].rooms[iteration].positionY = y;

    //                         iteration++;
    //                     }
    //                 }

                    
    //             }
    //         // }
    //     }
    // }



    // printf("%d\n",d -> stages[stage].rooms[1].positionX);
    // printf("%d\n",d -> stages[stage].rooms[1].positionX);

    // printf("%d\n",d -> stages[stage].rooms[1].number);
    //  printf("%d\n",d -> stages[stage].rooms[1].width);

    (void)d;
    (void)stage;
    (void)numberOfRooms;


}

void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms){

    // d-> stages[stage].rooms[number].room = malloc(sizeof(char) * (numberOfRooms + 1));

     FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = "[]";
    int * tab = 0;
    int iteration = 1;

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

            // for (int i = 0; i < 2; i++) {
            //     printf("Iteration : %d, tab[%d] : %d\n", iteration, i, tab[i]);
            // }
            // printf("\n");
            int width = tab[1]*2;
            int height = tab[0];

            if(iteration !=1){

                d-> stages[stage].rooms[iteration-1].room = malloc(sizeof(char) * height);
        
                for (int i = 0; i < tab[0]; i++) {
                    d-> stages[stage].rooms[iteration-1].room[i] = malloc(sizeof(char) * width);
                }

                printf("\nSTAGE %d / Room %d \n", stage, iteration);
                d-> stages[stage].rooms[iteration-1].room = RoomByNumber(height, width, iteration);
                d-> stages[stage].rooms[iteration-1].number = iteration;
                d-> stages[stage].rooms[iteration-1].width = width;
                d-> stages[stage].rooms[iteration-1].height = height;
                d-> stages[stage].rooms[iteration-1].numberOfDoors = NumberOfDoorsByRoom( d-> stages[stage].rooms[iteration-1].room, height, width);

                d-> stages[stage].rooms[iteration-1].doorTop = 0;
                    d-> stages[stage].rooms[iteration-1].doorBottom = 0;
                    d-> stages[stage].rooms[iteration-1].doorLeft = 0;
                    d-> stages[stage].rooms[iteration-1].doorRight = 0;

                for(int i  = 0; i< height; i++){
                    for(int j = 0; j < width; j++){
                        if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && i == 0){
                        d-> stages[stage].rooms[iteration-1].doorTop = 1;
                        }
                        if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && i == tab[0] - 1){
                        d-> stages[stage].rooms[iteration-1].doorBottom = 1;
                        }
                        if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && j == tab[1] - 2){
                        d-> stages[stage].rooms[iteration-1].doorRight = 1;
                        }
                        if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && j == 0){
                        d-> stages[stage].rooms[iteration-1].doorLeft = 1;
                        }
                    }
                }
            }

   
            iteration++;
            free(tab); 

        }     
        continue;

    }        

    fclose(fp);

    if (line)
        free(line);

    // (void)iteration;
    // (void)tab;
    // (void)delim;  
    // (void)d;
    // (void)stage;
    (void)numberOfRooms;   
                                   
     
}


void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms) {


    d -> stages[stage].stage = malloc(sizeof(char * ) * numberOfRooms + 1);

    for (int i = 0; i < numberOfRooms + 1; i++) {
        d -> stages[stage].stage[i] = malloc(sizeof(char) * numberOfRooms + 1);
    }

    for (int i = 0; i < numberOfRooms + 1; i++) {
        for (int y = 0; y < numberOfRooms + 1; y++) {
                d -> stages[stage].stage[i][y] = ' ';
            
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

    int iteration = 0;

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

    // print lines

    for (int i = 0; i < height; i++) {
        printf("%s", lines[i]);
    }

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


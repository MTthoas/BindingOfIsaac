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

int numberOfRooms();
void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms);
void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms);
char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);
int * RandomBetweenRange(int number);

// Initialisation de la game

void InitialisationGame() {

       srand(time(NULL));

    Donjon * d = malloc(sizeof(Donjon));

    for (int i = 0; i < NUMBER_STAGES_MAX; i++) {

        printf("Stage : %d\n", i);
        int NumberOfRoomsInt = numberOfRooms();
        printf("Nombre de salles : %d\n\n", NumberOfRoomsInt);

        newStageByNumber(d, i, NumberOfRoomsInt);
        InitialiseRoom(d, i, NumberOfRoomsInt);

        for (int v = 0; v < NumberOfRoomsInt + 1; v++) {

            for (int y = 0; y < NumberOfRoomsInt + 1; y++) {

                if(v == NumberOfRoomsInt / 2 && y == NumberOfRoomsInt / 2) {
                    d->stages[i].stage[v][y] = 'P';     
                    d->stages[i].id = 1;     

                    for(int u = 0; u < NumberOfRoomsInt; u++) {

                        int NumberOfDoors = NumberOfDoorsByRoom(d->stages[i].rooms[u].room, d->stages[i].rooms[u].height, d->stages[i].rooms[u].width);
                           
                            int * array = malloc(sizeof(int *) * NumberOfDoors);
                            // array = RandomBetweenRange( NumberOfDoors);

                            // for(int x = 0; x < NumberOfDoors; x++) {
                                
                            //     printf("%c ", d->stages[i].rooms[u].Doors[x]);


                            // }

                            //    int * randomNumber = RandomBetweenRange(NumberOfDoors);
                               printf(" <--- PORTES [%d] / Nombre de portes : %d \n", u+1, NumberOfDoors);
                               
                            //    for(int x = 0; x < NumberOfDoors; x++) {
                            //     printf("%d ", randomNumber[x]);
                            //    }

                               
                            // printf("\n");


                            // for(int j = 0; j < NumberOfDoors; j++) {

                            //     int random = randomNumber[j];

                            //     printf("%c ", d->stages[i].rooms[u].Doors[random]);
                                  
                            // }

                               

                            printf("\n");
                            printf("\n");
                            (void)array;
                            // free(randomNumber);
                            free(array);
                           
                        }
                }  

            }
            
        }



        printf("\n");
        

         for (int v = 0; v < NumberOfRoomsInt + 1; v++) {
            for (int y = 0; y < NumberOfRoomsInt + 1; y++) {
                printf("%c ", d->stages[i].stage[v][y]);
            }
            printf("\n");
        }








        printf("\n");


        }

        (void) d;

}

// Fonction pour calculer un ensemble de nombre entre min = 0 et max (inclus) = number
int * RandomBetweenRange(int number){

     int * tab = malloc(sizeof(int)* 4);
        int newNumber = 0;
        int iteration = 0;

        while(1) {
            
            int AlreadyInTab = 0;
            newNumber = rand() % number+1;

            // If newNumber is already in tab, we don't add it and continue the while loop

            for(int i = 0; i < number; i++) {
                if(tab[i] == newNumber) {
                    AlreadyInTab++;
                }
            }

            if(AlreadyInTab == 0) {
                tab[iteration] = newNumber;
                iteration++;
            }else{
                continue;
            }

            if(iteration == number) {
                break;
            }
        }

        for(int i = 0; i < number; i++) {
            tab[i] = tab[i] - 1;
        }
        
        return tab;
}

// Initialise une salle

void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = "[]";
    int * tab = 0;
    int iteration = 0;

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

            int width = tab[1]*2;
            int height = tab[0];

            if(iteration !=0){

                d-> stages[stage].rooms[iteration-1].room = malloc(sizeof(char) * height);
        
                for (int i = 0; i < tab[0]; i++) {
                    d-> stages[stage].rooms[iteration-1].room[i] = malloc(sizeof(char) * width);
                }

                // printf("\nSTAGE %d / Room %d \n", stage, iteration);
                d-> stages[stage].rooms[iteration-1].room = RoomByNumber(height, width, iteration);
                d-> stages[stage].rooms[iteration-1].number = iteration;
                d-> stages[stage].rooms[iteration-1].width = width;
                d-> stages[stage].rooms[iteration-1].height = height;
                d-> stages[stage].rooms[iteration-1].numberOfDoors = NumberOfDoorsByRoom( d-> stages[stage].rooms[iteration-1].room, height, width);

                // d-> stages[stage].rooms[iteration-1].doorTop = 0;
                //     d-> stages[stage].rooms[iteration-1].doorBottom = 0;
                //     d-> stages[stage].rooms[iteration-1].doorLeft = 0;
                //     d-> stages[stage].rooms[iteration-1].doorRight = 0;

                // printf("Width : %d\n",width);
                // printf("Height : %d\n",height);
                int iterationMallocDoors = 0;

                 for(int i  = 0; i< height; i++){

                    for(int j = 0; j < width+1; j++){

                        if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D'){
                            iterationMallocDoors++;
                        }
                    
                    }

                }

                 d-> stages[stage].rooms[iteration-1].Doors = malloc(sizeof(char) * iterationMallocDoors);
                 
                int iterationDoors = 0;

                for(int i  = 0; i< height; i++){

                    for(int j = 0; j < width+1; j++){

                        if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D'){

                            if(i == 0){
                                d-> stages[stage].rooms[iteration-1].Doors[iterationDoors] = 'T';
                                    iterationDoors++;
                            }
                            if(i == height-1){
                                d-> stages[stage].rooms[iteration-1].Doors[iterationDoors] = 'B';
                                    iterationDoors++;
                            }
                            if(j == 0){
                               d-> stages[stage].rooms[iteration-1].Doors[iterationDoors] = 'L';
                                   iterationDoors++;
                            }
                            if(j == width-4 || j == width-3 || j == width-2 || j == width-1 || j == width){
                                d-> stages[stage].rooms[iteration-1].Doors[iterationDoors] = 'R';
                                    iterationDoors++;
                            }

                            // printf("[i][j] : [%d][%d] \n", i, j);
                        }

                        // if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && i == 0){
                        // d-> stages[stage].rooms[iteration-1].doorTop = 1;
                        // }
                        // if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && i == height - 1){
                        // d-> stages[stage].rooms[iteration-1].doorBottom = 1;
                        // }
                        // if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && j == width - 2){
                        // d-> stages[stage].rooms[iteration-1].doorRight = 1;
                        // }
                        // if(d-> stages[stage].rooms[iteration-1].room[i][j] == 'D' && j == 0){
                        // d-> stages[stage].rooms[iteration-1].doorLeft = 1;
                        // }
                    }
                }

                // printf("DoorTop : %d \n", d-> stages[stage].rooms[iteration-1].doorTop);
                // printf("DoorBottom : %d \n", d-> stages[stage].rooms[iteration-1].doorBottom);
                // printf("DoorLeft : %d \n", d-> stages[stage].rooms[iteration-1].doorLeft);
                // printf("DoorRight : %d \n", d-> stages[stage].rooms[iteration-1].doorRight);


            }

            iteration++;
            free(tab); 

        }     
        continue;
    }        


    fclose(fp);

    if (line)
        free(line);

    (void)numberOfRooms;   
                                   
}

// Chercher dans le fichier mtbob la salle correspondante au numéro de la salle (number) et retourne un tableau de char correspondant à la salle

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

    // for(int i = 0; i < height; i++){
    //     printf("%s", lines[i]);
    // }

    return lines;

    // printf lines


    

}

// Initialise un étage
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

// Pour calculer le nombre de rooms dans un étage
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

// Pour calculer le nombre de portes par Room
int NumberOfDoorsByRoom(char ** s, int height, int width){

    int iteration = 0;

    for(int i  = 0; i< height; i++){
        for(int y = 0; y < width+1; y++){
            if(s[i][y] == 'D'){
                iteration++;
            }
        }
    }

    return iteration-1;
}





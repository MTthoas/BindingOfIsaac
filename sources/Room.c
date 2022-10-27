#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Room.h"

#define KRED  "\x1B[31m"

#define KNRM  "\x1B[0m"

/* Prototypes */

char ** RoomByNumber(int height, int length, int number);
char * copy_not_empty(const char * str);
void NumberOfRooms();
void newRooms(Room *s, RoomInSpace * v);
int NumberOfDoorsByRoom(Room * s);
void freeRoom(Room *s);

void InitialisationGame(){

    // Calculer le nombre de salle
    Room * s = malloc(sizeof(Room));
    NumberOfRooms(s);
    free(s);

    // Trouver le nombre de "D" par Room

    //  s->rooms = malloc(sizeof(char * ) * s->numberOfRoomsReturned+1);
    // printf("Nombre de room : %d\n", s->numberOfRoomsReturned);
        
    // for(int i = 0; i< s->numberOfRoomsReturned+1; i++){
    //     s->rooms[i] = malloc(sizeof(char) * s->numberOfRoomsReturned+1);
    // }

    // // Pour le nombre de tableau
    // for(int i = 0; i < s->numberOfRoomsReturned; i++){
    //        Room * room = newRoom(i+1);

    //        printf("Width : %d\n", room -> width);   
    //        printf("Height : %d\n", room -> height);
    //        printf("Doors : %d\n", NumberOfDoorsByRoom(room));
                   
    // }
}

void freeRoom(Room *s){
    free(s);
}


int NumberOfDoorsByRoom(Room * s){

    int iteration = 0;

    for(int i  = 0; i< s->height; i++){
        for(int y = 0; y < s->width; y++){
            if(s->room[i][y] == 'D'){
                iteration++;
            }
        }
    }
    return iteration;
}



void newRooms(Room * s, RoomInSpace *  v){

    (void)v;

    s->rooms = malloc(sizeof(char * ) * s->numberOfRoomsReturned+1);

    printf("Nombre de room : %d\n", s->numberOfRoomsReturned);
    
    for(int i = 0; i< s->numberOfRoomsReturned+1; i++){
        s->rooms[i] = malloc(sizeof(char) * s->numberOfRoomsReturned+1);
    }

    for(int i = 0; i < s->numberOfRoomsReturned+1; i++){
        Room * room = newRoom(i+1);
        int numberOfDoors = s->numberOfDoors;
        printf("Number of door : %d", numberOfDoors);
                (void)numberOfDoors;
                (void)room;
        // printf("%d", numberOfDoors);
        for(int j = 0; j < s->numberOfRoomsReturned+1; j++){
            if(i == ( s->numberOfRoomsReturned ) / 2  && j == (s->numberOfRoomsReturned) / 2 ){
                s->rooms[i][j] = 'P';

            }else{
                   s->rooms[i][j] = ' ';
            }
        

        }
    }

    for(int i = 0; i < s->numberOfRoomsReturned+1 ; i++){
        for(int j = 0; j< s->numberOfRoomsReturned+1 ; j++){
            printf("%c", s->rooms[i][j]);
        }
        printf("\n");
    }





}

void NumberOfRooms(Room * s){

    FILE * fp;
    size_t len = 0;
    ssize_t read;
    int iteration = 0;
    char * line = NULL;

     fp = fopen("/home/matthias/Bureau/BindingOfIsaac/resources/room.rtbob", "r");
     if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline( &line, & len, fp)) != -1) {
          if (strcspn(line, "[") == 0) {
            iteration++;
          }
    }

    s->numberOfRoomsReturned = iteration;

    fclose(fp);
    if (line)
        free(line);
}

void printRooms(Room room){
    int count = 0;

    for (int i = 0; i < room.numberOfRoomsReturned; i++) {
        for (int j = 0; j < room.numberOfRoomsReturned-1; j++) {
            printf("%d", room.rooms[i][j]);
            printf(" ");
            count++;
        }
        printf("\n");

    }

    printf("\n");
}

void printRoom(Room room) {

    int count = 0;

    printf("Number : %d / Height : %d / Width : %d \n",
        room.number,
        room.height,
        room.width);

    for (int i = 0; i < room.height; i++) {
        for (int j = 0; j < room.width-1; j++) {
            printf("%d", room.room[i][j]);
            printf(" ");
            count++;
        }
        printf("\n");

    }

    printf("\n");

}

/* Attribution à la structure Room de la room appelé ( number ) */

Room * newRoom(int number) {

    Room * s = malloc(sizeof(Room)); 

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = "[]";
    int * tab = 0;
    int iteration = 1;
    int numberDoors = 0;
    /* Ouverture du fichier & éxeption */

    fp = fopen("/home/matthias/Bureau/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    /* Tant qu'une vide n'est pas vide en Bytes */

    while ((read = getline( & line, & len, fp)) != -1) {

        /* Si la ligne commence par un "[", afin de prendre le "headers" de chaque Rooms 
            @[9|16]2
         */

        if (strcspn(line, "[") == 0) {

            /* Analyse du Header afin de stocker dans tab les données de chaque Headers, tab est reinitialisé à chaque itération 
                tab[0] = 9
                tab[1] = 16
                tab[2] = 2
            */

            char * stockPtr = strtok(line, delim);

            tab = malloc(sizeof(int) * 3);
            stockPtr = strtok(stockPtr, "|");

            for (int j = 0; stockPtr != NULL; j++) {
                tab[j] = atoi(stockPtr);
                stockPtr = strtok(NULL, "|");
            }

            tab[2] = iteration;

            /* Si le numéro de la room est égale à l'itération, alors on stocke les données dans la structure Room */

            if (iteration == number) {

             

               s -> room = RoomByNumber(tab[0], tab[1], tab[2]);
                s -> number = tab[2];
                s -> height = tab[0];
                s -> width = tab[1] * 2;

                   for(int i = 0; i<tab[0]; i++){
                    for(int y = 0; y<tab[1]*2; y++){
                        
                        if(s->room[i][y] == 'D'){
                            numberDoors++;
                        }
                    }
                }

                s-> numberOfDoors = numberDoors;
                
                // print RoomByNumber

                

            }

            iteration++;
            free(tab);
        }



    
    }
    
    s->numberOfRoomsReturned = iteration;

    fclose(fp);

    if (line)
        free(line);

    return s;

}

/* Fonction qui retourne un tableau de char sans les espaces */

char * copy_not_empty(const char * str) {
    size_t i;
    size_t j;
    char * new = malloc(strlen(str) + 1);

    for (i = j = 0; i < strlen(str); ++i) {
        if (str[i] != ' ')
            new [j++] = str[i];
    }
    for (; j <= i; j++)
        new [j] = 0;
    return new;
}

/* Fonction qui retourne la room sélectionné via le paramètre number 
    @param height : hauteur de la room
    @param length : longueur de la room
    @param number : numéro de la room
*/

char ** RoomByNumber(int height, int length, int number) {

    int iteration = 0;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int num = 0;

    /* Malloc selon la hauteur du tableau */

    char ** lines = malloc(sizeof(char * ) * height);

    fp = fopen("/home/matthias/Bureau/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    printf("\n");


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
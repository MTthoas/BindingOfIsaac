#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Room.h"

/* Prototypes */

char ** RoomByNumber(int height, int length, int number);
char * copy_not_empty(const char * str);

/* Print the Room */

void printRoom(Room room) {

    printf("Number : %d / Height : %d / Width : %d \n",
        room.number,
        room.height,
        room.width);

    for (int i = 0; i < room.height; i++) {
        for (int j = 0; j < room.width; j++) {
            printf("%c", room.room[i][j]);
        }
    }
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

    /* Ouverture du fichier & éxeption */

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
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
                printf("%d %d %d \n", tab[0], tab[1], tab[2]);

                s -> room = RoomByNumber(tab[0], tab[1], tab[2]);
                s -> number = tab[2];
                s -> height = tab[0];
                s -> width = tab[1] * 2;
                                                
            }

            iteration++;
            free(tab);
        }

    }

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

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
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
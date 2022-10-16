#define _GNU_SOURCE

#include <stdio.h>

#include <stdlib.h>

#include "parseRoom.h"

#include <string.h>

#include <ctype.h>

char ** RoomByNumber(int height, int length, int number);


int ** FetchRoom() {
    int ** matrix = malloc(sizeof(int * ) * 3);

    for (int i = 0; i < 3; i++) {
        matrix[i] = malloc(sizeof(int) * 3);
    }

    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            matrix[j][k] = 0;
        }
    }

    return matrix;
}

int numberOfRoom() {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char * stockPtr;

    char delim[] = "{}";

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < 1; i++) {
        if ((read = getline( & line, & len, fp)) != 1) {

            char * ptr = strtok(line, delim);

            stockPtr = ptr;

        };

    }

    fclose(fp);

    return atoi(stockPtr);

}

void Room(int number) {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char delim[] = "[]";
    // char delimSecond[] = "[]";
    // ssize_t read;

    printf("\n");

    fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int * tab = 0;
    int iteration = 1;
    char ** matrix;

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

            if (iteration == number) {
                printf("%d %d %d \n", tab[0], tab[1], tab[2]);

                matrix = RoomByNumber(tab[0], tab[1], tab[2]);
                 printf("\n");

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        printf("%d", matrix[i][j]);
                        printf("\t");
                    }
                    printf("\n");
                }


            }

            iteration++;
            free(tab);
        }

    }

    fclose(fp);

    if (line)
        free(line);

}

char ** RoomByNumber(int height, int length, int number) {

    char ** matrix;
    int i = 0;
    int j = 0;

    (void) number;

    matrix = malloc(sizeof(char * ) * length);

    for (i = 0; i < length; i++) {
        matrix[i] = malloc(sizeof(char * ) * height);
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < height; j++) {
            matrix[i][j] = 3;
        }
    }

    return matrix;

}
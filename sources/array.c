/**
 * @file array.c
 * @author TheGreat-Chain
 * @brief Multiple functions to manipulate arrays et dynamic arrays
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "include/array.h"
#include <stdio.h>
#include <stdlib.h>

char** createCharArray2D(int lines, int columns) {
    char** array = malloc(sizeof(char*) * lines);
    for(int i=0 ; i < lines ; i+=1) {
        array[i] = malloc(sizeof(char) * columns);
    }
    return array;
}

void clearIntArray(int *array, int size)
{
    for (int i = 0; i < size; i += 1) {
        array[i] = 0;
    }
}

void displayCharArray2D(char** array, int lines, int columns) {
    for(int i = 0 ; i < lines ; i += 1) {
        for(int j = 0 ; j < columns ; j += 1) {
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
}

void freeCharArray2D(char** array, int lines, int columns) {
    for(int i = 0 ; i < lines ; i += 1) {
        for(int j = 0 ; j < columns ; j += 1) {
            free(array[i]);
        }
    }
}

char** duplicateCharArray2D(char** array, int lines, int columns) {
    char** newArray = malloc(sizeof(char*) * lines);
    for(int i=0 ; i<lines ; i+=1) {
        newArray[i] = malloc(sizeof(char) * columns);
    }

    for(int i=0 ; i<lines ; i+=1) {
        for(int j=0 ; j < columns ; j+=1) {
            newArray[i][j] = array[i][j];
        }
    }

    return newArray;
}
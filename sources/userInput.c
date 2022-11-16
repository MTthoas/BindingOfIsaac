/**
 * @file userInput.c
 * @author your name (you@domain.com)
 * @brief functions to handle user inputs
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "include/userInput.h"

int readInput(char* string, int size) {
    char* startingPos = NULL;
 
    if (fgets(string, size, stdin) != NULL) { // 
        startingPos = strchr(string, '\n'); 
        if (startingPos != NULL) { // replace '\n' with '\0' because fgets always adds '\n' to the created string
            *startingPos = '\0'; 
        } else {
            clearSTDIN(); // if strlen(string) > size, we have to clean the buffer
        }
        
        return 1; // good
    }
    clearSTDIN();
    return 0; // error

}

void clearSTDIN() {
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

float readFloat() {
    char string[100] = {0}; 
 
    if (readInput(string, 100)) {
        return strtof(string, NULL);
    }

   return 0; // error
}

int confirmation() {
    char boolean[2];

    while(1) {
        readInput(boolean, 2);
        if(strcmp(boolean, "y") == 0 || strcmp(boolean, "Y") == 0) {
            return 1;
        } else if(strcmp(boolean, "n") == 0 || strcmp(boolean, "N") == 0) {
            return 0;
        }    
    }
}

int readInt() {
    char string[100] = {0}; 
 
    if (readInput(string, 100)) {
        return atoi(string);
    }

   return 0; // error
}

void askName(char* name) {
    int success = 0;
    do {
        printf("What's the item's NAME (max 20 characters) ?\n");
        readInput(name, 21);
        printf("NAME = %s. Is it correct ? (y/n) \n", name);
        success = confirmation();
    } while(!success); // handle error
}

void askHpMax(float* hpMax) {
    int success = 0;
    do {
        printf("How much bonus / penalty on HP-MAX stat ?\n");
        *hpMax = readFloat();
        printf("HP MAX = %f. Is it correct ? (y/n) \n", *hpMax);
        success = confirmation();
    } while(success != 1);
}

void askShield(float* shield) {
    int success = 0;
    do {
        printf("How much bonus / penalty on SHIELD stat ?\n");
        *shield = readFloat();
        printf("SHIELD = %f. Is it correct ? (y/n) \n", *shield);
        success = confirmation();
    } while(success != 1);
}

void askDamage(float* damage) {
    int success = 0;
     do {
        printf("How much bonus / penalty on DAMAGE stat ?\n");
        *damage = readFloat();
        printf("DAMAGE = %f. Is it correct ? (y/n) \n", *damage);
        success = confirmation();
    } while(success != 1);
}

void askPiercingShot(int* ps) {
    int success = 0;
    do {
        printf("Does the item provide PIERCING SHOT ability (y/n) ?\n");
        *ps = confirmation();
        printf("PIERCING SHOT = %s. Is it correct ? (y/n) \n", (*ps) ? "true" : "false");
        success = confirmation();
    } while(success != 1);
}

void askSpectralShot(int* ss) {
    int success = 0;
    do {
        printf("Does the item provide SPECTRAL SHOT ability (y/n) ?\n");
        *ss = confirmation();
        printf("SPECTRAL SHOT = %s. Is it correct ? (y/n) \n", (*ss) ? "true" : "false");
        success = confirmation();
    } while(success != 1);
}

void askFlight(int* flight) {
    int success = 0;
    do {
        printf("Does the item provide FLIGHT ability (y/n) ?\n");
        *flight = confirmation();
        printf("FLIGHT = %s. Is it correct ? (y/n) \n", (flight) ? "true" : "false");
        success = confirmation();
    } while(success != 1);
}

void askNumberOfRooms(int* nRooms, int max) {
    int success = 0;
     do {
        printf("How many rooms do you want to load during the game (max %d)?\n", max);
        *nRooms = readInt();
        if(*nRooms > max) {
            printf("You only created %d rooms.\n", max);
            continue;
        }
        printf("%d rooms. Is that correct (y/n) ? \n", *nRooms);
        success = confirmation();
    } while(success != 1);
}
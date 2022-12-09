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

#include "./include/userInput.h"


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

char readChar() {
    char string[100] = {0}; 
 
    if (readInput(string, 2)) {
        return string[strlen(string)-1];
    }

   return -1; // error
}

void askName(char* name) {
    int success = 0;
    do {
        printf("What's the item's NAME (max 20 characters) ?\n");
        readInput(name, 21);
        printf("NAME = %s. Is it correct ? (y/n) \n", name);
        success = confirmation();
    } while(!success); // handle error
    strcat(name, "\n");
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
        printf("FLIGHT = %s. Is it correct ? (y/n) \n", (*flight) ? "true" : "false");
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

// void askNumber(int* nRooms) {
//     int success = 0;
//      do {
//         printf("          How many obstacles do u want to add ??\n");
//         *nRooms = readInt();
//         if(*nRooms <= 0 ) {
//             printf("You only created %d rooms.\n", max);
//             continue;
//         }
//         printf("%d rooms. Is that correct (y/n) ? \n", *nRooms);
//         success = confirmation();
//     } while(success != 1);
// }

// void askNumberOfObstacles(int* number) {
//     int success = 0;
//      do {
//         printf("          How many obstacles do u want to add ??\n");
//         *number = readInt();
//         if(*number <= 0 ) {
//             printf("          DO NOT ENTER 0 IDIOT");
//             continue;
//         }
//         printf("          %d obstacles. Is that correct (y/n) ? \n", *number);
//         success = confirmation();
//     } while(success != 1);

// }

void askRoomDimensions(int* lines, int* columns) {
    int success = 0;
    do {
        printf("What the HEIGHT of your new room (min 3) ?\n");
        *lines = readInt();
        if(*lines < 3) {
            printf("Please make a bigger room.\n");
            continue;
        }
        printf("Your room will have a height of = %d. Is it correct ? (y/n) \n", *lines);
        success = confirmation();
    } while(success != 1);

    success = 0;

    do {
        printf("What the WIDTH of your new room (min 3) ?\n");
        *columns = readInt();
        if(*columns < 3) {
            printf("Please make a bigger room.\n");
            continue;
        }
        printf("Your room will have a width of = %d. Is it correct ? (y/n) \n", *columns);
        success = confirmation();
    } while(success != 1);
}

void askPosition(int* x, int* y, CRUD_Room* room) {
    int success = 0;
    int min = 2;
    int maxX = (room->lines/2)-1;
    int maxY = (room->columns/2)-1;

    do {
        printf("Enter the LINE number of the element you want to change. Between 2 and %d\n", maxX);
        *x = readInt();
        if(*x < min || *x > maxX) {
            printf("Please make a bigger room.\n");
            continue;
        }
        printf("Line n° : %d. Is it correct ? (y/n) \n", *x);
        success = confirmation();
    } while(success != 1);

    success = 0;

    do {
        printf("Enter the COLUMN number of the element you want to change. Between 2 and %d\n", maxY);
        *y = readInt();
        if(*y < min || *y > maxY) {
            printf("Please make a bigger room.\n");
            continue;
        }
        printf("Column n° : %d. Is it correct ? (y/n) \n", *y);
        success = confirmation();
    } while(success != 1);

}

void askRoomElement(char* element) {
    int success = 0;
    do {
        printf("Choose between :\n- W (Wall)\n- ' ' (empty)\n- R (rock)\n- G (gap)\n- D (door)\n- H (health)\n- S (spike)\n");
        *element = readChar();
        if(*element != 'W' || *element != 'R' || *element != 'G' || *element != 'H' || *element != 'S' || *element != 'w' || *element != 'r'  || *element != 'g' || *element != 'h' || *element != 's') {
            printf("Please writed one of the suggested characters\n");
            continue;
        }
        success = 1;
    } while(!success);
}
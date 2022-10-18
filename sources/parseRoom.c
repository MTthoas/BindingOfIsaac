#define _GNU_SOURCE

#include <stdio.h>

#include <stdlib.h>

#include "parseRoom.h"

#include <string.h>

#include <ctype.h>

char ** RoomByNumber(int height, int length, int number);
char *copy_not_empty(const char *str);


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

                char ** matrix = malloc(sizeof(char*) * tab[0]);

                matrix = RoomByNumber(tab[0], tab[1], tab[2]);

                 printf("\n");

                for( int i = 0; i < tab[0]; i++){
                    printf("%s", matrix[i]);  
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

char *copy_not_empty(const char *str)
{
  size_t i;
  size_t j;
  char *new = malloc(strlen(str) + 1);

  for (i = j = 0; i < strlen(str); ++i)
  {
    if (str[i] != ' ')
      new[j++] = str[i];
  }
  for (; j <= i; j++)
    new[j] = 0; // pad with nulbytes
  return new;
}

char ** RoomByNumber(int height, int length, int number) {

    // char ** matrix;
    // int i = 0;
    // int j = 0;

    int iteration = 0;
        
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int num = 0;

    // size_t numLines = 0;
    char **lines = malloc(sizeof(char*) * height);

    // int lines = 0;

     fp = fopen("/home/matthias/Bureau/Projet/BindingOfIsaac/resources/room.rtbob", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

          printf("\n");
            // printf("\n");

    while ((read = getline( &line, & len, fp)) != -1) {
       iteration++;

        if(iteration > 2 + (number - 1) * (height + 1) && iteration <= 2 + (number - 1) * (height + 1) + height){
           
            // printf("%d ", height);
            // printf("%d ", num);

            if (num == height) {
                 char **newlines = realloc(lines, sizeof(char*) * height);
                  if (!newlines) {
                    printf("error reallocating array\n");
                    break;
                }
                lines = newlines;
                printf("Test");
            }
            
            lines[ num ] = line;
            num++;

            line = NULL;
            len = 0;

        }
       
    };

    // free(lines);

    (void)length;

    fclose(fp);

    if (line)
        free(line);

    return lines;

}
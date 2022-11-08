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
int PickRoomNotUsed(struct Donjon * d, int NumberOfRoomsInt);
void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms);
void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms);
char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);
int * RandomBetweenRange(int number, int zero);
int NowRoomIsUsed(struct Donjon *d, int NumberOfRoomsInt, int id);

/**
 * @brief Ininitialise le jeu
 * 
 */

void InitialisationGame(Donjon * d) {

    srand(time(NULL));

    // On boucle sur le nombre d'étage

    for (int i = 0; i < NUMBER_STAGES_MAX; i++) {

        int NumberOfRoomsInt = numberOfRooms();


        printf("Stage : %d\n", i+1);
        printf("Nombre de salles : %d\n\n", NumberOfRoomsInt);


        newStageByNumber(d, i, NumberOfRoomsInt);
        InitialiseRoom(d, i, NumberOfRoomsInt);

        int * randomNumberRooms = RandomBetweenRange(NumberOfRoomsInt, 1);
        d->stages[i].randomNumberRooms = malloc(sizeof(int) * NumberOfRoomsInt);

        for (int y = 0; y < NumberOfRoomsInt; y++) {

            d->stages[i].randomNumberRooms[y] = randomNumberRooms[y];	

        }

        printf("\n");	

        for (int y = 0; y < NumberOfRoomsInt; y++) {

            int stock = 0;

            if(y==0){
                 d->stages[i].rooms[y].id = 0;
                 d->stages[i].rooms[y].roomUsed = 0;
                 stock = d->stages[i].randomNumberRooms[y];

            }else{
                
                if(d->stages[i].randomNumberRooms[y] != 0){

                    d->stages[i].rooms[y].roomUsed = 0;
                    d->stages[i].rooms[y].id = d->stages[i].randomNumberRooms[y];

                }else{

                    printf("%d",stock);
                    d->stages[i].rooms[y].id = stock;
                }

            }

            printf("ID de la salle %d: %d\n", y,d->stages[i].rooms[y].id);

        }

        free(randomNumberRooms);
        
        printf("\n");    
        // On boucle sur le nombre de rooms en X et Y pour gérer les étages

        for (int v = 0; v < NumberOfRoomsInt + 1; v++) {

            for (int y = 0; y < NumberOfRoomsInt + 1; y++) {

                // Si on est à la moitié de la boucle, on créer un P, la salle principale.

                if(v == NumberOfRoomsInt / 2 && y == NumberOfRoomsInt / 2) {
                    d->stages[i].stage[v][y] = 'P';     
                    d->stages[i].id = 1;     

                    for(int u = 0; u < NumberOfRoomsInt; u++) {

                        int NumberOfDoors = NumberOfDoorsByRoom(d->stages[i].rooms[u].room, d->stages[i].rooms[u].height, d->stages[i].rooms[u].width);
                           
                            int * array = malloc(sizeof(int *) * NumberOfDoors);
                            array = RandomBetweenRange( NumberOfDoors, 0);
                            
                                // for(int x = 0; x < NumberOfDoors; x++) {
                                    
                                //     int random = randomNumberRooms[x];
                                //     printf("%d ", random);

                                // }
                               
                                // Porte aléatoire

                               int * randomNumberDoors = RandomBetweenRange(NumberOfDoors, 0);

                               for(int j = 0; j < NumberOfDoors; j++) {

                                    int random = randomNumberDoors[j];
                                    char s = d->stages[i].rooms[u].Doors[random];

                                    printf("%c ", s);

                                    if(strcmp(&s, "N") == 0) {
                                        
                                       for(int v = 0; v < NumberOfRoomsInt; v++) {
                                           
                                        //    if(d->stages[i].randomNumberRooms[v])
                                       }

                                    } else if(strcmp(&s, "S") == 0) {
                                        d->stages[i].rooms[u].Doors[random] = 'N';
                                    } else if(strcmp(&s, "E") == 0) {
                                        d->stages[i].rooms[u].Doors[random] = 'W';
                                    } else if(strcmp(&s, "W") == 0) {
                                        d->stages[i].rooms[u].Doors[random] = 'E';
                                    }
                                    
                                }


                            printf(" <--- PORTES [%d] / Nombre de portes : %d \n", u+1, NumberOfDoors);
                            // printf("%d\n", d->stages[i].rooms[u].id = d->stages[i].randomNumberRooms[u]);
                               
                                // for(int x = 0; x < NumberOfDoors; x++) {
                                    
                                //     if(){
                                        
                                //     }

                                // }
                          
                            (void)array;
                            free(randomNumberDoors);
                            // free(randomNumber);
                            free(array);
                           
                        }
                }  

            }
            
        }

        printf("\n");


            for (int v = 0; v < NumberOfRoomsInt + 1; v++) {

                for (int y = 0; y < NumberOfRoomsInt + 1; y++) {

                    // Permet de se placer au centre
                   
                    if(d->stages[i].stage[v][y] == 'P') {

                            int * arraySecond = malloc(sizeof(int *) * 100);
                            arraySecond = RandomBetweenRange(100, 0);

                            int blockA = 0;
                            int blockB = 0;
                            int blockC = 0;
                            int blockD = 0;
                             int iteration = 0;
                             int addToVar = 0;
                             
                            for (int y = 0; y < NumberOfRoomsInt; y++) {

                                d->stages[i].rooms[y].roomUsed = 0;

                            }

                            printf("Room Panel :");
                            for(int t = 0; t < NumberOfRoomsInt; t++) {

                                printf("%d",d->stages[i].rooms[t].roomUsed);                

                            }

                            printf("\n");

                            for(int t = 0; t < NumberOfRoomsInt; t++) {

                                printf("ID : %d / ",d->stages[i].rooms[t].id);                

                            }


                            printf("\n");
                            printf("\n");

                            for(int t = 0; t < NumberOfRoomsInt; t++) {

                                printf("ROOM UTILISES [%d] : %d\n",t,d->stages[i].rooms[t].roomUsed);                

                            }

                                printf("\n");
                                   printf("\n");


                            // Left to player Zone
                            for(int j = 0; j+addToVar < 4; j++) {

                                if(j == 4 && iteration == 2){
                                    addToVar++;
                                    continue;
                                }

                                int numbe;
                                
                               if(arraySecond[j] < 25 && arraySecond[j] > 0 && blockA == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt);
                                    printf("ID OF ROOM : %d\n", numbe);

                                        d->stages[i].stage[v][y-1] = 'R';
                                        blockA = 1;
                                        iteration++;
                                    

                               }

                               if(arraySecond[j] < 50 && arraySecond[j] > 25 && blockB == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt);
                                    printf("ID OF ROOM : %d\n", numbe);

                                        d->stages[i].stage[v][y+1] = 'R';
                                        blockB = 1;
                                        iteration++;


                               }

                               if(arraySecond[j] < 75 && arraySecond[j] > 50 && blockC == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt);
                                    printf("ID OF ROOM : %d\n", numbe);
                                        
                                        d->stages[i].stage[v-1][y] = 'R';
                                        blockC = 1;
                                        iteration++;
                                    

    
                               }

                               if(arraySecond[j] < 100 && arraySecond[j] > 75 && blockD == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt);
                                    printf("ID OF ROOM : %d\n", numbe);

                                        d->stages[i].stage[v+1][y] = 'R';
                                        blockD = 1;
                                        iteration++;
                                    
        
                               }

                               printf("\n");
                               
                            }
                        
                            // Left to left player Zone
                            

                        
                        for(int t = 0; t < NumberOfRoomsInt; t++) {

                            printf("ROOM UTILISES [%d] : %d\n",t,d->stages[i].rooms[t].roomUsed);                

                        }

                        printf("\n");

                        printf("Iteration : %d",iteration);
                        
                    }

        

                }
            }

            for (int v = 0; v < NumberOfRoomsInt + 1; v++) {
                for (int y = 0; y < NumberOfRoomsInt + 1; y++) {

                    printf("%c ", d->stages[i].stage[v][y]);

                }
                printf("\n");
            }

        }

      

}

/**
 * @brief Fonction pour calculer un ensemble de nombre entre min = 0 et max (inclus) = number
 * 
 * @param number = max inclus
 * @return int* 
 */

int PickRoomNotUsed(struct Donjon * d, int NumberOfRoomsInt) {

    // int random = rand() % NumberOfRoomsInt + 1;
        
        while(1){

            // printf("ID de la salle %d: %d\n", i,d->stages[0].rooms[i].id);

                int random = rand() % NumberOfRoomsInt + 1;

                if(d->stages[0].rooms[random].roomUsed == 0 ){
                    printf("ICI CA PRINT\n");
                    d->stages[0].rooms[random].roomUsed = 1;
                    return d->stages[random].rooms[random].id;
                    
                }

                
        }


    return 0;

}

int NowRoomIsUsed(struct Donjon *d, int NumberOfRoomsInt, int id) {

    (void)d; (void)NumberOfRoomsInt; (void)id;

    return 0;

}

int * RandomBetweenRange(int number, int zero){
    

    (void)zero;

     int * tab = malloc(sizeof(int)* number);
        int newNumber = 0;
        int iteration = 0;

        if(number == 1) {
            tab[0] = 0;
            return tab;
        }

        while(1) {
            
            int AlreadyInTab = 0;
            newNumber = rand() % number+1;

           // Tant que le nombre est dans tab, on re-génère la variable random.

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

        // print tab

        // for(int i = 0; i < number; i++) {
        //     printf("%d ", tab[i]);
        // }
    
        return tab;
}

/**
 * @brief Fonction initialiser une room
 * 
 * @param d Structure générale
 * @param stage Etage précis
 * @param numberOfRooms Nombre de rooms
 */

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

    // Read => Une line par itération. Si on a plus de ligne, renvoi -1

    while ((read = getline( & line, & len, fp)) != -1) {

        // Si la premier paramètre détient le deuxième paramètre, renvoi 0

        if (strcspn(line, "[") == 0) { 

            // Permet d'isoler chaque valeur de la ligne : [5][5]2 pour faire en sorte que width = 5, height = 5

                char * stockPtr = strtok(line, delim);

                tab = malloc(sizeof(int) * 3);
                stockPtr = strtok(stockPtr, "|");

                for (int j = 0; stockPtr != NULL; j++) {
                    tab[j] = atoi(stockPtr);
                    stockPtr = strtok(NULL, "|");
                }

                int width = tab[1]*2;
                int height = tab[0];

            // Initialisation dans la mémoire de la salle, puis applcation dans la structure de différents paramètre pour la room en question.

            d-> stages[stage].rooms[iteration].room = malloc(sizeof(char) * height);
            free(d-> stages[stage].rooms[iteration].room = malloc(sizeof(char) * height));
            d-> stages[stage].rooms[iteration].room = malloc(sizeof(char) * height);

        
            for (int i = 0; i < tab[0]; i++) {
                d-> stages[stage].rooms[iteration].room[i] = malloc(sizeof(char) * width);
                free(d-> stages[stage].rooms[iteration].room[i]);
                d-> stages[stage].rooms[iteration].room[i] = malloc(sizeof(char) * width);
            }

            // printf("\nSTAGE %d / Room %d \n", stage, iteration+1);

            int iterationDoorsReturned = NumberOfDoorsByRoom( d-> stages[stage].rooms[iteration].room, height, width);

            d-> stages[stage].rooms[iteration].room = RoomByNumber(height, width, iteration+1);
            d-> stages[stage].rooms[iteration].number = iteration;
            d-> stages[stage].rooms[iteration].width = width;
            d-> stages[stage].rooms[iteration].height = height;
            d-> stages[stage].rooms[iteration].numberOfDoors = iterationDoorsReturned;

                // for (int i = 0; i < height; i++) {
                //     for (int j = 0; j < width; j++) {
                //         printf("%c", d-> stages[stage].rooms[iteration].room[i][j]);
                //     }
                // }

            d-> stages[stage].rooms[iteration].Doors = malloc(sizeof(char) * iterationDoorsReturned);
                 
                int iterationDoors = 0;

                // Permet d'indiquer si y'a une porte, à gauche, à droite, en haut ou en bas.

                for(int i  = 0; i< height; i++){

                    for(int j = 0; j < width; j++){

                        if(d-> stages[stage].rooms[iteration].room[i][j] == 'D'){

                            if(i == 0){
                                d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'T';
                                    iterationDoors++;
                                    // printf("[%d] [%d]\n", i, j);
                            }
                            if(i == height-1){
                                d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'B';
                                    iterationDoors++;
                                    // printf("[%d] [%d]\n", i, j);
                            }
                            if(j == 0){
                               d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'L';
                                   iterationDoors++;
                                //    printf("[%d] [%d]\n", i, j);
                            }
                            if(j == width-4 || j == width-3 || j == width-2 || j == width-1 || j == width){
                                d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'R';
                                    iterationDoors++;
                                    // printf("[%d] [%d]\n", i, j);
                            }

                        }
                    }
                }

            // // Affichage des portes

            // for(int i = 0; i < iterationMallocDoors; i++){
            //     printf("Door %d : %c \n", i+1, d-> stages[stage].rooms[iteration].Doors[i]);
            // }


            iteration++;
            free(tab); 
            free(stockPtr);

        }     
    }        


    fclose(fp);

    if (line)
        free(line);

    (void)numberOfRooms;   
                                   
}

/**
 * @brief Fonction qui retourne une room par son numéro
 * 
 * @param height Hauteur de la room
 * @param length Longueur de la room
 * @param number Numéro de la room
 * @return char** correspond à la room en question
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


    

}

/**
 * @brief Fonction qui créer un étage vide dans la mémoire et dans la structure correspondant au nombre de salle en X et en Y.
 * 
 * @param d 
 * @param stage 
 * @param numberOfRooms 
 */

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

/**
 * @brief Fonction qui retourne le nombre de room
 * 
 * @return int 
 */

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

/**
 * @brief Fonction qui retourne le nombre de portes d'une room
 * 
 * @param s Room, tableau à 2 dimensions
 * @param height hauteur
 * @param width longueur
 * @return int 
 */
int NumberOfDoorsByRoom(char ** s, int height, int width){

    int iteration = 0;

    for(int i  = 0; i< height; i++){
        for(int y = 0; y < width+1; y++){
            if(s[i][y] == 'D'){
                iteration++;
            }
        }
    }

    return iteration;
}





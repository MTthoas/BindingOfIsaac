#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Room.h"
#include "lectureFichiers.h"

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"


/* Prototypes */
int numberOfRooms();
int PickRoomNotUsed(struct Donjon * d, int NumberOfRoomsInt, int stage);
void newStageByNumber(struct Donjon * d, int stage, int numberOfRooms);
void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms);
char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);
int * RandomBetweenRange(int number, int zero);
int NowRoomIsUsed(struct Donjon *d, int NumberOfRoomsInt, int id);
void InitialisationGameByStagesOptionsForArms(Donjon * d, int stage, int numbe);
void InitialiseOtherRoomsFromArms(Donjon * d, int stage, int numberOfRooms);

/**
 * @brief Ininitialise le jeu
 * 
 */
void InitialisationGame(Donjon * d, int stageNum) {

    srand(time(NULL));

        d->headObject = objectsFileToObjectsList();
        int NumberOfRoomsInt = numberOfRooms();
        // printf("Stage : %d\n", i+1);
        printf("Nombre de salles : %d\n\n", NumberOfRoomsInt);
        newStageByNumber(d, stageNum, NumberOfRoomsInt+1);
        //printf("testfonction");
        // Générer l'ensemble des étage
        InitialiseRoom(d, stageNum, NumberOfRoomsInt);

        int * randomNumberRooms = RandomArrayForAttribution(NumberOfRoomsInt);
        d->stages[stageNum].randomNumberRooms = malloc(sizeof(int) * NumberOfRoomsInt);

        for (int y = 0; y < NumberOfRoomsInt; y++) {
            printf("Salle %d : %d\n", y, randomNumberRooms[y]); 
            d->stages[stageNum].randomNumberRooms[y] = randomNumberRooms[y];	
        }

        for (int y = 0; y < NumberOfRoomsInt; y++) {
            if(y == 0 ){
                 d->stages[stageNum].rooms[y].id = 0;
                 d->stages[stageNum].rooms[y].roomUsed = 1;
            }else{ 
                if(d->stages[stageNum].randomNumberRooms[y] != 0){
                    d->stages[stageNum].rooms[y].roomUsed = 0;
                    d->stages[stageNum].rooms[y].id = d->stages[stageNum].randomNumberRooms[y];
                }
            }
        }
        free(randomNumberRooms);
        printf("\n");    

        // On boucle sur le nombre de rooms en X et Y pour gérer les étages

        for (int v = 0; v < NumberOfRoomsInt + 1; v++) {
            for (int y = 0; y < NumberOfRoomsInt + 1; y++) {

                // Si on est à la moitié de la boucle, on créer un P, la salle principale.

                if(v == NumberOfRoomsInt / 2 && y == NumberOfRoomsInt / 2) {
                    d->stages[stageNum].stage[v][y] = 'P';     
                    d->stages[stageNum].id = 1;     

                    for(int u = 0; u < NumberOfRoomsInt; u++) {

                        int NumberOfDoors = NumberOfDoorsByRoom(d->stages[stageNum].rooms[u].room, d->stages[stageNum].rooms[u].height, d->stages[stageNum].rooms[u].width);                     
                            int * array = malloc(sizeof(int *) * NumberOfDoors);
                            array = RandomBetweenRange( NumberOfDoors, 0);
                            
                                // Porte aléatoire

                               int * randomNumberDoors = RandomBetweenRange(NumberOfDoors, 0);

                               for(int j = 0; j < NumberOfDoors; j++) {

                                    int random = randomNumberDoors[j];
                                    char s = d->stages[stageNum].rooms[u].Doors[random];

                                    printf("%c ", s);

                                    if(strcmp(&s, "N") == 0) {

                                    } else if(strcmp(&s, "S") == 0) {
                                        d->stages[stageNum].rooms[u].Doors[random] = 'N';
                                    } else if(strcmp(&s, "E") == 0) {
                                        d->stages[stageNum].rooms[u].Doors[random] = 'W';
                                    } else if(strcmp(&s, "W") == 0) {
                                        d->stages[stageNum].rooms[u].Doors[random] = 'E';
                                    }                          
                                }
                          
                            (void)array;
                            free(randomNumberDoors);
                            free(array);              
                        }
                }  
            } 
        }

          int iteration = 0;
          for (int v = 0; v < NumberOfRoomsInt + 1; v++) {

                for (int y = 0; y < NumberOfRoomsInt + 1; y++) {

                    // Permet de se placer au centre
                   
                    if(d->stages[stageNum].stage[v][y] == 'P') {

                            int * arraySecond = malloc(sizeof(int *) * 100);
                            arraySecond = RandomBetweenRange(100, 0);

                            int blockA = 0;
                            int blockB = 0;
                            int blockC = 0;
                            int blockD = 0;
                            int addToVar = 0;

                            printf("Number of Rooms : %d\n", NumberOfRoomsInt);
                             
                            for (int y = 0; y < NumberOfRoomsInt; y++) {

                                d->stages[stageNum].rooms[y].roomUsed = 0;

                            }

                            // Permet de placer les salles en dehors des salles initialiser à côté de la BossRoom.

                            for(int j = 0; j+addToVar < 4; j++) {

                                if(j == 4 && iteration == 2){
                                    addToVar++;
                                    continue;
                                }

                                int numbe;

                                //  Permet de faire un range aléatoire entre 4 possibilités
                                
                               if(arraySecond[j] < 25 && arraySecond[j] > 0 && blockA == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);

                                        d->stages[stageNum].stage[v][y-1] = 'R';
                                        blockA = 1;
                                        iteration++;
                                        d->stages[stageNum].rooms[numbe].AxeY = 0;
                                        d->stages[stageNum].rooms[numbe].AxeX = -1;
                               }

                               if(arraySecond[j] < 50 && arraySecond[j] > 25 && blockB == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);

                                        d->stages[stageNum].stage[v][y+1] = 'R';
                                        blockB = 1;
                                        iteration++;
                                         d->stages[stageNum].rooms[numbe].AxeY = 0;
                                         d->stages[stageNum].rooms[numbe].AxeX = 1;

                               }

                               if(arraySecond[j] < 75 && arraySecond[j] > 50 && blockC == 0 && iteration < 3){

                                   numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);
                                        
                                        d->stages[stageNum].stage[v-1][y] = 'R';
                                        blockC = 1;
                                        iteration++;
                                         d->stages[stageNum].rooms[numbe].AxeY = -1;
                                         d->stages[stageNum].rooms[numbe].AxeX = 0;
                               }

                               if(arraySecond[j] < 100 && arraySecond[j] > 75 && blockD == 0 && iteration < 3){

                                  numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);

                                        d->stages[stageNum].stage[v+1][y] = 'R';
                                        blockD = 1;
                                        iteration++;
                                        d->stages[stageNum].rooms[numbe].AxeY = 1;
                                        d->stages[stageNum].rooms[numbe].AxeX = 0;
  
                               }  
                            }
                    }
                }
            }

            int iterationByRoom = iteration;
            int itemRoom = 0;
            int bossRoom = 0;
            int exit = 0;
            int test = 0;

            for(int t = 2; t <= NumberOfRoomsInt-iteration + 2; t++) {

                printf("Number of room : %d\n", t);
                
                int iterationRoom = 0;
                int iterationTest = 0;

                while(iterationRoom == 0 && iterationByRoom <= NumberOfRoomsInt + 2 && bossRoom == 0 && exit == 0) {
      
                    int select = rand() % 3;

                    int randomHeight;
                    int randomLength;

                    if(t < 2){

                        randomHeight = 1 + rand() % (NumberOfRoomsInt+1);
                        randomLength = (rand() % (((NumberOfRoomsInt/2)+1) - (NumberOfRoomsInt/2) + 1)) + NumberOfRoomsInt/2;

                    }else{

                        // Eloigner la salle du boss le plus possible du centre

                        if(t == NumberOfRoomsInt-iteration + 1 ){

                        randomHeight = rand() % (NumberOfRoomsInt);
                        randomLength = rand() % (NumberOfRoomsInt);

                        }else{
 
                         // Générer aléatoirement la salle dans l'étage

                         randomHeight = 1 + rand() % (NumberOfRoomsInt-1);
                         randomLength = 1 + rand() % (NumberOfRoomsInt-1);

                        }
                    }

                    while(d->stages[stageNum].stage[randomHeight][randomLength] != 'R' && d->stages[stageNum].stage[randomHeight][randomLength] != 'I') {
                        randomHeight = rand() % NumberOfRoomsInt;
                        randomLength = rand() % NumberOfRoomsInt;           
                    }

                    iterationTest++;
                    printf("Iteration : %d\n", iterationTest);
                    if(iterationTest > 57) {
                        test = 1;
                    }

                    if(test == 1){
                        // t--;
                        test = 0;
                        break;
                    }

                    switch(select){                    
                        case 0:

                            if(d->stages[stageNum].stage[randomHeight][randomLength+1] == ' ' && itemRoom == 0 ){
                                if(d->stages[stageNum].stage[randomHeight][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' ' ){
                                    if(t == NumberOfRoomsInt-iteration ){
                                        d->stages[stageNum].stage[randomHeight][randomLength+1] = 'I';
                                         itemRoom = 1;
                                       
                                    }else{
                                        
                                        d->stages[stageNum].stage[randomHeight][randomLength+1] = 'R';

                                        
                                        
                                    
                                    }
                                        iterationRoom++;
                                        iterationByRoom++;
                                    break;
                                }
                            }else{

                                if(d->stages[stageNum].stage[randomHeight][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight][randomLength-1] != 'I' && d->stages[stageNum].stage[randomHeight][randomLength+1] == ' '   &&  d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' '
                                    && d->stages[stageNum].stage[randomHeight+2][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength+2] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration + 1 ){
                                            d->stages[stageNum].stage[randomHeight][randomLength+1] = 'B';
                                            iterationRoom++;
                                            iterationByRoom++;
                                            bossRoom = 1;
                         
                                        }
                                    }
                                }
                            }
           
                        break;

                        case 1:

                            if(d->stages[stageNum].stage[randomHeight][randomLength-1] == ' ' && itemRoom == 0 && d->stages[stageNum].stage[randomHeight][randomLength-1]){
                                if(d->stages[stageNum].stage[randomHeight][randomLength-2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' ' ){
                                    if(t == NumberOfRoomsInt-iteration){
                                        d->stages[stageNum].stage[randomHeight][randomLength-1] = 'I';
                                       
                                         itemRoom = 1;
                                    }else{
                                        
                                        d->stages[stageNum].stage[randomHeight][randomLength-1] = 'R';
                                      
        
                                    }
                                        iterationRoom++;
                                        iterationByRoom++;
                                    break;
                                }
                            }else{
                                if(d->stages[stageNum].stage[randomHeight][randomLength-1] == ' ' && d->stages[stageNum].stage[randomHeight][randomLength-2] == ' ' &&  d->stages[stageNum].stage[randomHeight][randomLength-1] != 'I'  &&  d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight][randomLength-2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' '
                                     && d->stages[stageNum].stage[randomHeight+2][randomLength-2] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength-2] == ' ' ){
                                         if(t == NumberOfRoomsInt-iteration + 1  ){
                                            d->stages[stageNum].stage[randomHeight][randomLength-1] = 'B';
                                             iterationRoom++;
                                            iterationByRoom++;
                                            bossRoom = 1;
                                        
                                        }
                                    }
                                }
                            
                            }

                        break;

                        case 2:

                            if(d->stages[stageNum].stage[randomHeight+1][randomLength] == ' ' && itemRoom == 0 ){
                                    if(d->stages[stageNum].stage[randomHeight+2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration){
                                            d->stages[stageNum].stage[randomHeight+1][randomLength] = 'I';
                                          
                                            itemRoom = 1;
                                        }else{
                                            
                                            d->stages[stageNum].stage[randomHeight+1][randomLength] = 'R';
                                                                                
                                        }
                                            iterationRoom++;
                                            iterationByRoom++;
                                        break;
                                }
                            }else{
                                if(d->stages[stageNum].stage[randomHeight+1][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength] != 'I' && d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight+2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' 
                                    && d->stages[stageNum].stage[randomHeight+2][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight+2][randomLength-2] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration + 1 ){
                                            d->stages[stageNum].stage[randomHeight+1][randomLength] = 'B';
                                                iterationRoom++;
                                                iterationByRoom++;
                                                bossRoom = 1;
                                        }
                                    }
                                }

                            }

                        break;

                        case 3:

                            if(d->stages[stageNum].stage[randomHeight-1][randomLength] == ' ' && itemRoom == 0 ){
                                if(d->stages[stageNum].stage[randomHeight-2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' ' ){
                                   if(t == NumberOfRoomsInt-iteration ){
                                        d->stages[stageNum].stage[randomHeight-1][randomLength] = 'I';
                                         itemRoom = 1;
                                         
                                    }else{
                                        
                                        d->stages[stageNum].stage[randomHeight-1][randomLength] = 'R';
                                        
                                        
                                    }
                                        iterationRoom++;
                                        iterationByRoom++;
                                    break;
                                }
                            }else{
                                if(d->stages[stageNum].stage[randomHeight-1][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength] != 'I' && d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight-2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' ' 
                                    &&  d->stages[stageNum].stage[randomHeight-2][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength-2] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration + 1){
                                            d->stages[stageNum].stage[randomHeight-1][randomLength] = 'B';
                                                iterationRoom++;
                                                iterationByRoom++;
                                                bossRoom = 1;
                                        }
                                    }
                                }
                            }
                        break;
                    }  
                }
            }

            for(int t = 0; t < 1; t++) {

                    int RoomPlaced = 0;

                    while(1){

                        if(RoomPlaced == 1){
                            break;
                        }
                        
                    int select = rand() % 3;

                    int randomHeight;
                    int randomLength;

                    randomHeight = rand() % NumberOfRoomsInt;
                    randomLength = rand() % NumberOfRoomsInt;

                    while(d->stages[stageNum].stage[randomHeight][randomLength] != 'B') {

                        randomHeight = rand() % NumberOfRoomsInt;
                        randomLength = rand() % NumberOfRoomsInt;

                    }

                        switch(select){
                            
                            case 0:

                                if(d->stages[stageNum].stage[randomHeight][randomLength-1] == ' '){
                                    if(d->stages[stageNum].stage[randomHeight][randomLength-2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' ' ){
                                
                                        d->stages[stageNum].stage[randomHeight][randomLength-1] = 'V';
                                              
                                        RoomPlaced = 1;
                                    }
                                }
            
                            break;

                            case 1:

                                if(d->stages[stageNum].stage[randomHeight][randomLength+1] == ' '){
                                    if(d->stages[stageNum].stage[randomHeight][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' ' ){
                                    
                                        d->stages[stageNum].stage[randomHeight][randomLength+1] = 'V';
                                       
                                            RoomPlaced = 1;
                                        
                                    }
                                }

                            break;

                            case 2:

                                if(d->stages[stageNum].stage[randomHeight+1][randomLength] == ' '){
                                        if(d->stages[stageNum].stage[randomHeight+2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' ){
                                            
                                                d->stages[stageNum].stage[randomHeight+1][randomLength] = 'V';
                                                  
                                                    RoomPlaced = 1;
                                    }
                                }

                            break;

                            case 3:

                                if(d->stages[stageNum].stage[randomHeight-1][randomLength] == ' '){
                                    if(d->stages[stageNum].stage[randomHeight-2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' ' ){
                                    
                                            d->stages[stageNum].stage[randomHeight+1][randomLength] = 'V';
                                               
                                                RoomPlaced = 1;
                                    }
                                }

                            break;
                        }                                  
                    }            
                }

            for (int v = 0; v < NumberOfRoomsInt + 2; v++) {
                for (int y = 0; y < NumberOfRoomsInt + 2; y++) {

                    printf("%c ", d->stages[stageNum].stage[v][y]);

                }
                printf("\n");
            }

}

/**
 * @brief Fonction pour calculer un ensemble de nombre entre min = 0 et max (inclus) = number
 * 
 * @param number = max inclus
 * @return int* 
 */

void InitialiseOtherRoomsFromArms(Donjon * d, int stage, int numberOfRooms){

    int iteration = 1;
    int numbe = 0;

    int varA = 0;
    int varB = 0;

       for(int i = 0; i < numberOfRooms+2; i++){
        for (int v = 0; v < numberOfRooms+2; v++) {
            if(d->stages[stage].stage[i][v] == 'P'){
                varA = i;
                varB = v;
                printf("Position of player : %d / %d\n", varA, varB);
            }
        }
    }



    for(int i = 0; i < numberOfRooms+2; i++){
        for (int v = 0; v < numberOfRooms+2; v++) {
            
            if(d -> stages[stage].stage[i][v] == 'R' && d -> stages[stage].stage[i+1][v] != 'P' && d -> stages[stage].stage[i-1][v] != 'P' && d -> stages[stage].stage[i][v+1] != 'P' && d -> stages[stage].stage[i][v-1] != 'P'){
                printf("Iteration : %d\n", iteration++);

                numbe = PickRoomNotUsed(d, numberOfRooms, stage);

                   d->stages[stage].rooms[numbe].AxeY = i - varA;
                   d->stages[stage].rooms[numbe].AxeX = v - varB;

                   printf("Axe Y : %d / Axe X : %d\n", d->stages[stage].rooms[numbe].AxeY, d->stages[stage].rooms[numbe].AxeX);
                
                // d->stages[stage].rooms[numbe].AxeY = varA -

                (void)numbe;
                (void)varA;
                (void)varB;
            }
              
        }

    }
}

void InitialisationGameByStagesOptionsForArms(Donjon *d, int stage, int numbe){

    for (int i = 0; i < d -> stages[stage].rooms[numbe].height; i++) {
		for (int y = 0; y < d -> stages[stage].rooms[numbe].width; y++) {


        }
    }

    (void)d;

}

int PickRoomNotUsed(struct Donjon * d, int NumberOfRoomsInt, int stage) {

        while(1){

                int random = 1 + rand() % (NumberOfRoomsInt - 1);

                if(random == NumberOfRoomsInt + 1){
                    continue;
                }

                if(d->stages[stage].rooms[random].roomUsed == 0 ){
                    // printf("ICI CA PRINT Random : %d \n", random);
                    d->stages[stage].rooms[random].roomUsed = 1;
                    
                    return random;
                    
                }         
        }

    return 0;

}

int NowRoomIsUsed(struct Donjon *d, int NumberOfRoomsInt, int id) {

    (void)d; (void)NumberOfRoomsInt; (void)id;

    return 0;

}

int * RandomArrayForAttribution(int number){

    int * tab = malloc(sizeof(int)* number);
    int newNumber = 0;
    int iteration = 1;

    if(number == 1) {
        tab[0] = 0;
        return tab;
    }

    tab[0] = 0;

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

    return tab;
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
    
        return tab;
}

/**
 * @brief Fonction initialiser une room
 * 
 * @param d Structure générale
 * @param stage Etage précis
 * @param numberOfRooms Nombre de rooms
 */

void InitialiseRoom(struct Donjon * d, int stage, int numberOfRooms) {

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char delim[] = "[]";
    int * tab = 0;
    int iteration = 0;

    fp = fopen("../resources/room.rtbob", "r");
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
            free(d-> stages[stage].rooms[iteration].room );
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

    fp = fopen("../resources/room.rtbob", "r");
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

    fp = fopen("../resources/room.rtbob", "r");
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
                iteration+=1;
            }
        }
    }

    return iteration;
}
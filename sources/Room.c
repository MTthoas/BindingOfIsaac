#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Room.h"
#include "lectureFichiers.h"
#include "myUtils.h"

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

/**
 * @brief Ininitialise le jeu
 * 
 */
int InitialiseStructureRandomStage(struct Donjon * d, int stageNum, int NumberOfRoomsInt){

        for (int v = 0; v < NumberOfRoomsInt + 1; v+=1) {
            for (int y = 0; y < NumberOfRoomsInt + 1; y+=1) {

                // Si on est à la moitié de la boucle, on créer un P, la salle principale.

                if(v == NumberOfRoomsInt / 2 && y == NumberOfRoomsInt / 2) {
                    d->stages[stageNum].stage[v][y] = 'P';     
                    d->stages[stageNum].id = 1;     

                    for(int u = 0; u < NumberOfRoomsInt; u+=1) {

                        int NumberOfDoors = NumberOfDoorsByRoom(d->stages[stageNum].rooms[u].room, d->stages[stageNum].rooms[u].height, d->stages[stageNum].rooms[u].width);                     
                            int * array = malloc(sizeof(int *) * NumberOfDoors);
                            array = RandomBetweenRange( NumberOfDoors, 0);
                            
                                // Porte aléatoire

                               int * randomNumberDoors = RandomBetweenRange(NumberOfDoors, 0);

                               for(int j = 0; j < NumberOfDoors; j+=1) {

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
          for (int v = 0; v < NumberOfRoomsInt + 1; v+=1) {

                for (int y = 0; y < NumberOfRoomsInt + 1; y+=1) {

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
                             
                            for (int y = 0; y < NumberOfRoomsInt; y+=1) {

                                d->stages[stageNum].rooms[y].roomUsed = 0;

                            }

                            // Permet de placer les salles en dehors des salles initialiser à côté de la BossRoom.

                            for(int j = 0; j+addToVar < 4; j+=1) {

                                if(j == 4 && iteration == 2){
                                    addToVar+=1;
                                    continue;
                                }

                                int numbe;

                                //  Permet de faire un range aléatoire entre 4 possibilités
                                
                               if(arraySecond[j] < 25 && arraySecond[j] > 0 && blockA == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);

                                        d->stages[stageNum].stage[v][y-1] = 'R';
                                        blockA = 1;
                                        iteration+=1;
                                        d->stages[stageNum].rooms[numbe].AxeY = 0;
                                        d->stages[stageNum].rooms[numbe].AxeX = -1;
                               }

                               if(arraySecond[j] < 50 && arraySecond[j] > 25 && blockB == 0 && iteration < 3){

                                    numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);

                                        d->stages[stageNum].stage[v][y+1] = 'R';
                                        blockB = 1;
                                        iteration+=1;
                                         d->stages[stageNum].rooms[numbe].AxeY = 0;
                                         d->stages[stageNum].rooms[numbe].AxeX = 1;

                               }

                               if(arraySecond[j] < 75 && arraySecond[j] > 50 && blockC == 0 && iteration < 3){

                                   numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);
                                        
                                        d->stages[stageNum].stage[v-1][y] = 'R';
                                        blockC = 1;
                                        iteration+=1;
                                         d->stages[stageNum].rooms[numbe].AxeY = -1;
                                         d->stages[stageNum].rooms[numbe].AxeX = 0;
                               }

                               if(arraySecond[j] < 100 && arraySecond[j] > 75 && blockD == 0 && iteration < 3){

                                  numbe = PickRoomNotUsed(d, NumberOfRoomsInt, stageNum);

                                        d->stages[stageNum].stage[v+1][y] = 'R';
                                        blockD = 1;
                                        iteration+=1;
                                        d->stages[stageNum].rooms[numbe].AxeY = 1;
                                        d->stages[stageNum].rooms[numbe].AxeX = 0;
  
                               }  
                            }
                    }
                }
            }

            return iteration;

}
int createRandomStageAroundSpawn(struct Donjon *d, int stageNum, int NumberOfRoomsInt, int iteration){

        int iterationByRoom = iteration;
            int itemRoom = 0;
            int bossRoom = 0;
            int exit = 0;

            for(int t = 2; t <= NumberOfRoomsInt-iteration + 2; t+=1) {

                printf("Number of room : %d\n", t);
                
                int iterationRoom = 0;
                int iterationTest = 0;
                int iterationEscape = 0;

                while(iterationRoom == 0 && iterationByRoom <= NumberOfRoomsInt + 2 && bossRoom == 0 && exit == 0) {
                
      
                    int select = rand() % 3;

                    int randomHeight;
                    int randomLength;

                    if(t < 2){

                        randomHeight = 1 + rand() % (NumberOfRoomsInt+1) - 1;
                        randomLength = (rand() % (((NumberOfRoomsInt/2)+1) - (NumberOfRoomsInt/2) + 1)) + NumberOfRoomsInt/2;

                        printf("While iteration0");   

                    }else{

                        // Eloigner la salle du boss le plus possible du centre

                        if(t == NumberOfRoomsInt-iteration + 1 ){

                        randomHeight = 1 + rand() % (NumberOfRoomsInt - 1);
                        randomLength = 1 + rand() % (NumberOfRoomsInt - 1 );

                        }else{
 
                         // Générer aléatoirement la salle dans l'étage

                         randomHeight = 1 + rand() % (NumberOfRoomsInt-1);
                         randomLength = 1 + rand() % (NumberOfRoomsInt-1); 

                        }
                    }

                    while(d->stages[stageNum].stage[randomHeight][randomLength] != 'R' && d->stages[stageNum].stage[randomHeight][randomLength] != 'I') {
                        randomHeight = rand() % NumberOfRoomsInt;
                        randomLength = rand() % NumberOfRoomsInt;    
                        iterationEscape++;
                        if(iterationEscape > 1000){
                            return 1;
                        }  
                    }
                    

                    iterationTest+=1;
                    printf("Iteration : %d\n", iterationTest);
                    if(iterationTest > 57) {
                        return 1;
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
                                        iterationRoom+=1;
                                        iterationByRoom+=1;
                                    break;
                                }
                            }else{

                                if(d->stages[stageNum].stage[randomHeight][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight][randomLength-1] != 'I' && d->stages[stageNum].stage[randomHeight][randomLength+1] == ' '   &&  d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' '
                                    && d->stages[stageNum].stage[randomHeight+2][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength+2] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration + 1 ){
                                            d->stages[stageNum].stage[randomHeight][randomLength+1] = 'B';
                                            iterationRoom+=1;
                                            iterationByRoom+=1;
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
                                        iterationRoom+=1;
                                        iterationByRoom+=1;
                                    break;
                                }
                            }else{
                                if(d->stages[stageNum].stage[randomHeight][randomLength-1] == ' ' && d->stages[stageNum].stage[randomHeight][randomLength-2] == ' ' &&  d->stages[stageNum].stage[randomHeight][randomLength-1] != 'I'  &&  d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight][randomLength-2] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' '
                                     && d->stages[stageNum].stage[randomHeight+2][randomLength-2] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength-2] == ' ' ){
                                         if(t == NumberOfRoomsInt-iteration + 1  ){
                                            d->stages[stageNum].stage[randomHeight][randomLength-1] = 'B';
                                             iterationRoom+=1;
                                            iterationByRoom+=1;
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
                                            iterationRoom+=1;
                                            iterationByRoom+=1;
                                        break;
                                }
                            }else{
                                if(d->stages[stageNum].stage[randomHeight+1][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength] != 'I' && d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight+2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight+1][randomLength-1] == ' ' 
                                    && d->stages[stageNum].stage[randomHeight+2][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight+2][randomLength-2] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration + 1 ){
                                            d->stages[stageNum].stage[randomHeight+1][randomLength] = 'B';
                                                iterationRoom+=1;
                                                iterationByRoom+=1;
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
                                        iterationRoom+=1;
                                        iterationByRoom+=1;
                                    break;
                                }
                            }else{
                                if(d->stages[stageNum].stage[randomHeight-1][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength] != 'I' && d->stages[stageNum].stage[randomHeight][randomLength] != 'I'){
                                    if(d->stages[stageNum].stage[randomHeight-2][randomLength] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength+1] == ' ' && d->stages[stageNum].stage[randomHeight-1][randomLength-1] == ' ' 
                                    &&  d->stages[stageNum].stage[randomHeight-2][randomLength+2] == ' ' && d->stages[stageNum].stage[randomHeight-2][randomLength-2] == ' ' ){
                                        if(t == NumberOfRoomsInt-iteration + 1){
                                            d->stages[stageNum].stage[randomHeight-1][randomLength] = 'B';
                                                iterationRoom+=1;
                                                iterationByRoom+=1;
                                                bossRoom = 1;
                                        }
                                    }
                                }
                            }
                        break;
                    }  
                }
            }

                int RoomPlaced = 0;
                int iterationStatus2 = 0;

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

                        iterationStatus2++;
                        if(iterationStatus2 > 1000){
                            return 1;
                        }
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

        return 0;          
               
}

void InitialisationGame(Donjon * d, int stageNum, Monster* arrayMonster) {

    srand(time(NULL));

        d->headObject = objectsFileToObjectsList();

        int NumberOfRoomsInt = numberOfRooms();
        newStageByNumber(d, stageNum, NumberOfRoomsInt+1);
        InitialiseRooms(d, stageNum, NumberOfRoomsInt, arrayMonster);
        int * randomNumberRooms = RandomArrayForAttribution(NumberOfRoomsInt);
        d->stages[stageNum].randomNumberRooms = malloc(sizeof(int) * NumberOfRoomsInt);

        for (int y = 0; y < NumberOfRoomsInt; y++) {
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

            int iteration = InitialiseStructureRandomStage(d, stageNum, NumberOfRoomsInt);
            int status = createRandomStageAroundSpawn(d, stageNum, NumberOfRoomsInt, iteration);
            while(status != 0){
                iteration = InitialiseStructureRandomStage(d, stageNum, NumberOfRoomsInt);
                status = createRandomStageAroundSpawn(d, stageNum, NumberOfRoomsInt, iteration);
            }

            int iterationRoom = 0;
            for (int v = 0; v < NumberOfRoomsInt + 2; v++) {
                for (int y = 0; y < NumberOfRoomsInt + 2; y++) {
                    printf("%c ", d->stages[stageNum].stage[v][y]);

                }
                printf("\n");
            }


            if(iterationRoom >= NumberOfRoomsInt ){
                InitialisationGame(d, stageNum, arrayMonster);
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

       for(int i = 0; i < numberOfRooms+2; i+=1){
        for (int v = 0; v < numberOfRooms+2; v+=1) {
            if(d->stages[stage].stage[i][v] == 'P'){
                varA = i;
                varB = v;
                printf("Position of player : %d / %d\n", varA, varB);
            }
        }
    }



    for(int i = 0; i < numberOfRooms+2; i+=1){
        for (int v = 0; v < numberOfRooms+2; v+=1) {
            
            if(d -> stages[stage].stage[i][v] == 'R' && d -> stages[stage].stage[i+1][v] != 'P' && d -> stages[stage].stage[i-1][v] != 'P' && d -> stages[stage].stage[i][v+1] != 'P' && d -> stages[stage].stage[i][v-1] != 'P'){
                printf("Iteration : %d\n", iteration+=1);

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

    for (int i = 0; i < d -> stages[stage].rooms[numbe].height; i+=1) {
		for (int y = 0; y < d -> stages[stage].rooms[numbe].width; y+=1) {


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

            for(int i = 0; i < number; i+=1) {
                if(tab[i] == newNumber) {
                    AlreadyInTab+=1;
                }
            }

            if(AlreadyInTab == 0) {
                tab[iteration] = newNumber;
                iteration+=1;
            }else{
                continue;
            }

            if(iteration == number) {
                break;
            }
        }

    return tab;
}

int * RandomBetweenRange(int number, int zero) {
    

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

            for(int i = 0; i < number; i+=1) {
                if(tab[i] == newNumber) {
                    AlreadyInTab+=1;
                }
            }

            if(AlreadyInTab == 0) {
                tab[iteration] = newNumber;
                iteration+=1;
            }else{
                continue;
            }

            if(iteration == number) {
                break;
            }
        }

        for(int i = 0; i < number; i+=1) {
            tab[i] = tab[i] - 1;
        }
    
        return tab;
}

/**
 * @brief Fonction initialiser toutes les room d'un étage
 * 
 * @param d Structure générale
 * @param stage Etage précis
 * @param numberOfRooms Nombre de rooms
 */

void InitialiseRooms(struct Donjon * d, int stage, int numberOfRooms, Monster* allMonsters) {

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

                for (int j = 0; stockPtr != NULL; j+=1) {
                    tab[j] = atoi(stockPtr);
                    stockPtr = strtok(NULL, "|");
                }

                int width = tab[1]*2;
                int height = tab[0];

            // Initialisation dans la mémoire de la salle, puis applcation dans la structure de différents paramètre pour la room en question.

            d-> stages[stage].rooms[iteration].room = malloc(sizeof(char) * height);
            free(d-> stages[stage].rooms[iteration].room );
            d-> stages[stage].rooms[iteration].room = malloc(sizeof(char) * height);

        
            for (int i = 0; i < tab[0]; i+=1) {
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
            initialiseMonstersInsideRoom(d, stage, iteration, allMonsters);
            setMonstersInsideRoom(d, stage, iteration);
            int iterationDoors = 0;

                // Permet d'indiquer si y'a une porte, à gauche, à droite, en haut ou en bas.

                for(int i  = 0; i< height; i+=1){

                    for(int j = 0; j < width; j+=1){

                        if(d-> stages[stage].rooms[iteration].room[i][j] == 'D'){

                            if(i == 0){
                                d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'T';
                                    iterationDoors+=1;
                                    // printf("[%d] [%d]\n", i, j);
                            }
                            if(i == height-1){
                                d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'B';
                                    iterationDoors+=1;
                                    // printf("[%d] [%d]\n", i, j);
                            }
                            if(j == 0){
                               d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'L';
                                   iterationDoors+=1;
                                //    printf("[%d] [%d]\n", i, j);
                            }
                            if(j == width-4 || j == width-3 || j == width-2 || j == width-1 || j == width){
                                d-> stages[stage].rooms[iteration].Doors[iterationDoors] = 'R';
                                    iterationDoors+=1;
                                    // printf("[%d] [%d]\n", i, j);
                            }

                        }
                    }
                }

            // // Affichage des portes

            // for(int i = 0; i < iterationMallocDoors; i+=1){
            //     printf("Door %d : %c \n", i+1, d-> stages[stage].rooms[iteration].Doors[i]);
            // }


            iteration+=1;
            free(tab); 
            free(stockPtr);

        }     
    }        


    fclose(fp);

    if (line)
        free(line);

    (void)numberOfRooms;   
                       
}

int setMonstersInsideRoom(Donjon* d, int stage, int roomId) {
    srand(time(NULL));
    int randomPositionX,randomPositionY; 
    int heightRoom = d->stages[stage].rooms[roomId].height - 1;
    int widthRoom = d->stages[stage].rooms[roomId].width - 2;
    int numberOfMonsters = d->stages[stage].rooms[roomId].numberOfMonsters;
    int freeSpace = 0;
    char** map = d->stages[stage].rooms[roomId].room;
    if(map == NULL) {
        return 0;
    }

    for(int i=0 ; i < numberOfMonsters ; i+=1) {
        freeSpace = 0;
        while (!freeSpace) {
            randomPositionY = getRandomInt(1, heightRoom);
            randomPositionX = getRandomInt(2, widthRoom);

            // place the monster where there is space and not near the player
            if (randomPositionX % 2 == 0 && d->stages[stage].rooms[roomId].room[randomPositionY][randomPositionX] == ' ' 
            && d->stages[stage].rooms[roomId].room[randomPositionY][randomPositionX - 2] != 'P' 
            && d->stages[stage].rooms[roomId].room[randomPositionY][randomPositionX + 2] != 'P' 
            && d->stages[stage].rooms[roomId].room[randomPositionY - 1][randomPositionX] != 'P' 
            && d->stages[stage].rooms[roomId].room[randomPositionY + 1][randomPositionX] != 'P' ) {
                freeSpace=1;
                // set monster position : 
                d->stages[stage].rooms[roomId].monsters[i].positionX = randomPositionX;
                d->stages[stage].rooms[roomId].monsters[i].positionY = randomPositionY;

                // draw monster inside map
                map[randomPositionY][randomPositionX] = d->stages[stage].rooms[roomId].monsters[i].firstLetter;
            }   
        }
    }

    return 1;
}

void initialiseMonstersInsideRoom(Donjon * d, int stage, int roomID, Monster* allMonsters) {
    int nbMonsters = getRandomInt(2, 5);
    int* uniqueNumbers = generateUniqueNumbers(nbMonsters-1, nbMonsters);
    int index = 0;

    Monster* roomMonsters = malloc(sizeof(Monster) * nbMonsters);
    Monster randomMonster;
    for(int i=0 ; i < nbMonsters-1 ; i+=1) {
        index = uniqueNumbers[i];
        randomMonster = allMonsters[index];
        roomMonsters[i] = *duplicateMonster(&randomMonster);
    }

    d->stages[stage].rooms[roomID].monsters = roomMonsters;
    d->stages[stage].rooms[roomID].numberOfMonsters = nbMonsters;
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
        iteration+=1;

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
            num+=1;

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

    for (int i = 0; i < numberOfRooms + 1; i+=1) {
        d -> stages[stage].stage[i] = malloc(sizeof(char) * numberOfRooms + 1);
    }

    for (int i = 0; i < numberOfRooms + 1; i+=1) {
        for (int y = 0; y < numberOfRooms + 1; y+=1) {
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
            iteration+=1;
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

    for(int i  = 0; i< height; i+=1){
        for(int y = 0; y < width+1; y+=1){
            if(s[i][y] == 'D'){
                iteration+=1;
            }
        }
    }

    return iteration;
}
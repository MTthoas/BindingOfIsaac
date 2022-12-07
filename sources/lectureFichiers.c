/**
 * @file lectureFichiers.c
 * @author TheGreat-Chain
 * @brief Fontions relatives à la lecture des fichiers des monstres, objects et pièces.
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "include/lectureFichiers.h"
#include "include/array.h"
#include "include/mystring.h"
#include "include/characters.h"

#include "include/monster.h"     
#include "include/userInput.h"

#include <ctype.h>
#include <string.h>
#include <unistd.h>

int choseCharacter() {
    char* filepath = CHEMIN_FICHIER_PERSONNAGES ;
    FILE* file = fopen(filepath, "r"); // ouverture fichier
    if(file == NULL) { 
        printf("Could not open character's file.\n--> The chosen player is Briatte.\n");
        sleep(2);
        return BRIATTE;   
    }

    struct Character {
        char* name;
        int usable;
    };
    typedef struct Character Character;

    
    char* original; // will be each line
    char* characterName; // will be the character name (eg : Briatte)
    char* usable; // will be 0 or 1
    char buffer[255];
    Character characters[3];
    int i = 0;

    while(fgets(buffer, 255, file)) {
        original = strdup(buffer); // original = "Briatte:1"
        usable = original; 
        characterName = strtok_r(usable, ":", &usable); // characterName = "Briatte", usable = "1"
    
        characters[i].name = malloc(sizeof(char) * strlen(characterName));
        characters[i].name = characterName;
        characters[i].usable = atoi(usable);
        i += 1;
    }

    system("clear");
    printf("\n\n\n\n==========================================================================\n");
    printf("|%50s", "CHOSE A CHARACTER");
    printf("%22s|\n", " ");
    printf("==========================================================================\n");
    
    for(int i = 0 ; i < 3 ; i+=1) {
        printf("                   ");
        printf("%d.%s %s\n\n", i+1, characters[i].name, (characters[i].usable) ? " " : "(locked)");
    }

    int choice = 0;
    do {
        choice = readInt();
        if(choice < 1 || choice > 3 || !(characters[choice-1].usable)) {
            if(choice == HENNOU) {
                printf("To unlock %s you have to unlock the bonus item room for the first time.\n", characters[choice-1].name);
            } else if(choice == CHEVAILLIER) {
                printf("To unlock %s you have to beat Athina.\n", characters[choice-1].name);
            }
            printf("Try again.\n");

        } else {
            break;
        } // if

    } while(1);
    
    return choice;
}



int listToRoomsFile(CRUD_Room* head) {
    char* filepath = CHEMIN_FICHIER_PIECES;
    FILE* file = fopen(filepath, "w"); 
    if(file == NULL) { 
        printf("Unable to open room.rtbob. Path : %s\n", filepath);
        return 0;
    }

    char* buffer_out = malloc(sizeof(char) * 256);
    
    int numRooms;
    int listSize = getRoomsListSize(head);
    if(listSize == 0) {
        return 0; // no rooms
    }
    askNumberOfRooms(&numRooms, listSize);
    sprintf(buffer_out, "{%d}\n", numRooms);
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), file);

    CRUD_Room* current = head;
    while(current != NULL) {
        for(int i = 0 ; i < current->lines ; i += 1) {
            if(i == 0) {
                sprintf(buffer_out, "[%d|%d]%d\n", current->lines, current->columns/2, current->id);
                fwrite(buffer_out, sizeof(char), strlen(buffer_out), file);
            }
            
            sprintf(buffer_out, "%s\n", current->map[i]);
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), file);
        }
        current = current->next;
    }

    fclose(file);
    free(buffer_out);
    freeAllRooms(head);
    return 1;
}

CRUD_Room* roomsFileToRoomsList() {
    char* filepath = CHEMIN_FICHIER_PIECES;
    FILE* file = fopen(filepath, "r"); 
    if(file == NULL) { 
        printf("Unable to open room.rtbob. Path : %s\n", filepath);
        return NULL;
    }

    rewind(file);

    // to create rooms
    CRUD_Room* head;

    int iteration = 1;
    int lines = 0;
    int columns = 0;
    char** map;
    char firstLetter;

    // to parse file
    char buffer[255];
    while(fgets(buffer, 255, file)) {
        firstLetter = toupper(buffer[0]);
        
        if(firstLetter == '[') { // new room
            parseRoomInfo(buffer, &lines, &columns);
            columns *= 2; // because of spaces
            columns -= 1;

            // prepare map
            map = malloc(sizeof(char*) * lines);

            for(int i=0 ; i < lines ; i+=1) {
                map[i] = malloc(sizeof(char) * columns);
            }

            fgets(buffer, 255, file); // skip [9|15]1 line

            for(int i = 0 ; i < lines ; i += 1) { // fill map
                for(int j = 0 ; j < columns ; j +=1) {
                    //printf("%c", buffer[j]);
                    map[i][j] = buffer[j];
                }
                fgets(buffer, 255, file);
            }          

            if(iteration == 1) {
                head = createCRUD_Room(lines, columns+1, map);
            } else {
                addCRUD_Room(head, createCRUD_Room(lines, columns+1, map));
            }
            iteration += 1;
            fseek(file, -strlen(buffer), SEEK_CUR); // go back one line
        } // if
        
    } // while

    //displayAllRooms(head);
    fclose(file);
    return head;
}

int parseRoomInfo(char* buffer, int* ptr_lines, int* ptr_columns) {
    char* original;
    char* token;
    char* theRest;

    original = strdup(buffer);
    theRest = original;
    token = strtok_r(theRest, "|", &theRest);

    char* lines = token + 1;
    *ptr_lines = atoi(lines);

    token = strtok_r(theRest, "]", &theRest);
    *ptr_columns = atoi(token);
    
    return 0;
}

int getNombreObjects(FILE* fichierObjects) {
    char token[256];
    int index = 0;
    char c = fgetc(fichierObjects);
    while(c != EOF) { // parcours du fichier
        if(c == '{') { //récupération du nb d'objects
            while(c != '}') {
                c = fgetc(fichierObjects);
                token[index] = c;
                index += 1;
            }
        token[index+1] = '\n'; // transformation en string
        return atoi(token);    
        c = fgetc(fichierObjects); 
        }    
    }
    return 0; 
}

int getNomberMonster(FILE* fichierMonster){
    char token[256];
    int index = 0;
    char c = fgetc(fichierMonster);
    while(c != EOF) { // parcours du fichier
        if(c == '{') { //récupération du nb d'objects
            while(c != '}') {
                c = fgetc(fichierMonster);
                token[index] = c;
                index += 1;
            }
        token[index+1] = '\n'; // transformation en string
        return atoi(token);    
        c = fgetc(fichierMonster); 
        }    
    }
    return 0; 
}

void afficherFichier(FILE* fichier) {
    rewind(fichier); 
    char c = fgetc(fichier);
    while(c != EOF) {
        printf("%c", c);
        c = fgetc(fichier);
    }
    printf("\n");
    return;
}

void listToObjectsFile(Object* head) {
    char* filepath = CHEMIN_FICHIER_OBJECTS;
    FILE* fichier = fopen(filepath, "w+"); // ouverture fichier
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier des objects.\n");
        return;
    }

    char* buffer_out = malloc(sizeof(char) * 256);

    // ecriture de l'indicateur du nombre d'objects :
    int listSize = getNumberObjects(head);
    if(listSize == 0) { // fin si pas d'objects dans la liste
        return;
    }
    sprintf(buffer_out, "{%d}\n", listSize);
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);

    // ecriture des objects :
    Object* courant = head;
    while(courant != NULL) {
        buffer_out = duplicateString("---\n");
        fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);

        sprintf(buffer_out, "name=%s", duplicateString(courant->name)); // nom
        fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);

        if(courant->hpMax != 0) {
            sprintf(buffer_out, "hpMax=%.1f\n", courant->hpMax); 
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);
        } 
        if(courant->shield != 0) {
            sprintf(buffer_out, "shield=%.1f\n", courant->shield); 
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);
        }
        if(courant->damage != 0) {
            sprintf(buffer_out, "damage=%.1f\n", courant->damage); 
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);
        }
        if(courant->piercingShot != 0) {
            sprintf(buffer_out, "ps=true\n"); 
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);
        }
        if(courant->spectralShot != 0) {
            sprintf(buffer_out, "ss=true\n"); 
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);
        }
        if(courant->flight != 0) {
            sprintf(buffer_out, "flight=true\n"); 
            fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);
        }

        courant = courant->next;
    }

    fclose(fichier);
    free(buffer_out);
    freeAllObjects(head);
}

int extensionType(char* filename) { 
    if(strlen(duplicateString(filename)) == 0) {
        return EXTENSION_INVALIDE;
    }
    
    char* prefix = strtok(duplicateString(filename), ".");
    if(strcmp(prefix, filename) == 0) { // pas de "."
        return EXTENSION_INVALIDE;
    }

    char* extension = strtok(NULL, ".");
    if(strcmp(extension, "mtbob") == 0) {
        return EXTENSION_FICHIER_MONSTRES;
    } else if(strcmp(extension, "itbob") == 0) {
        return EXTENSION_FICHIER_OBJET;
    } else if(strcmp(extension, "rtbob") == 0) {
        return EXTENSION_FICHIER_SALLES;
    } 

    return EXTENSION_INVALIDE;
}

int getNbLignesFichier(char* chemin_fichier) {
    FILE* fichier = fopen(chemin_fichier, "r");
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier %s\nFonction getNbLignesFichier().\n", chemin_fichier);
        return 0;
    } // ouverture fichier

    int nbLignes = 0;
    char buffer[255];
    while(fgets(buffer, 255, fichier)) {
        nbLignes += 1;
    }

    rewind(fichier);
    fclose(fichier);
    return nbLignes;
}

Object* objectsFileToObjectsList() {
    
    char* filepath = CHEMIN_FICHIER_OBJECTS;
    FILE* fichier = fopen(filepath, "r"); // ouverture fichier
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier des objects.\n");
        return NULL;
    }

    rewind(fichier);

    Object* head;

    int id = 1;
    char* name = "";
    float hpMax = 0;
    float shield = 0;
    float damage = 0;
    int piercingShot = 0;
    int spectralShot = 0;
    int flight = 0;
    int activated = 0;

    char buffer[255];
    char* stat = malloc(sizeof(char) * 255); 
    char* value = malloc(sizeof(char) * 255);
    int creatingObject = 1;
    char firstLetter;

    while(fgets(buffer, 255, fichier)) { // lecture fichier ligne par ligne
        firstLetter = buffer[0];
        //printf("%s", buffer);

        if(firstLetter == 'n' || firstLetter == '-' || firstLetter == 'h' || firstLetter == 'd' || firstLetter == 's' || firstLetter == 'p' || firstLetter == 'f' || firstLetter == EOF) {
            if(firstLetter == '-') { 
                creatingObject = (creatingObject) ? 0 : 1;

            } else { // construction object
                stat = strtok(buffer, "="); //ex : hpMax (depuis "hpMax=1")
                value = strtok(NULL, "="); //ex : 1 (depuis "hpMax=1")
                uppercase(stat);
                uppercase(value);

                if(strcmp(stat, "NAME") == 0) {
                    name = duplicateString(value);
                } else if((strcmp(stat, "HPMAX") == 0)) {
                    hpMax = atof(value);
                } else if((strcmp(stat, "SHIELD") == 0)) {
                    shield = atof(value);
                } else if((strcmp(stat, "DAMAGE") == 0)) {
                    damage = atof(value);
                } else if((strcmp(stat, "PS") == 0)) {
                    activated = (strcmp(value, "TRUE\n") == 0);
                    piercingShot = activated;
                } else if((strcmp(stat, "SS") == 0)) {
                    activated = (strcmp(value, "TRUE\n") == 0);
                    spectralShot = activated;
                } else if((strcmp(stat, "FLIGHT") == 0)) {
                    activated = (strcmp(value, "TRUE\n") == 0);
                    flight = activated;
                }
            }

            if(firstLetter == '-' && creatingObject == 1) { // ajout object
                if(id == 1) {
                    head = createObject(id, name, hpMax, shield, damage, piercingShot, spectralShot, flight);
                } else {
                    addObject(head, createObject(id, name, hpMax, shield, damage, piercingShot, spectralShot, flight));
                }

                id += 1;
            
                name = "";
                hpMax = 0;
                shield = 0;
                damage = 0;
                piercingShot = 0;
                spectralShot = 0;
                flight = 0;

                creatingObject = (creatingObject) ? 0 : 1;
            }   
        }
    }

    if(feof(fichier)) { 
        if(strcmp(name, "") != 0) {
            addObject(head, createObject(id, name, hpMax, shield, damage, piercingShot, spectralShot, flight));
        }
    } // ajout du dernier object
    
    fclose(fichier);
    return head;
}

Monster* fichierMonsterToListeMonster() {
    char* filepath = CHEMIN_FICHIER_MONSTRES;
    FILE* fichier = fopen(filepath, "r"); // ouverture fichier
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier des monsters.\n");
        return NULL;
    }

    rewind(fichier);
    int nbrMonster = getNomberMonster(fichier);
    Monster * arrayMonster = malloc(sizeof(Monster) * nbrMonster+1);
    
    int idMonster = 0;
    char* name = "";
    float hpMax = 0;
    int shoot = 0;
    int ss = 0;
    int flight = 0;
    int activated = 0;

    char buffer[255];
    char* stat = malloc(sizeof(char) * 255); 
    char* value = malloc(sizeof(char) * 255);
    int creatingMonster = 1;
    char firstLetter;

  

    while(fgets(buffer, 255, fichier)) { // lecture fichier ligne par ligne
        firstLetter = buffer[0];
        // printf("firstLetter %d\n", firstLetter);

        //printf("%s", buffer);

        if(firstLetter == 'n' || firstLetter == '-' || firstLetter == 'h' || firstLetter == 's' || firstLetter == 'f' || firstLetter == EOF) {
            if(firstLetter == '-') { 
                creatingMonster = (creatingMonster) ? 0 : 1;

            } else { // construction object
                stat = strtok(buffer, "="); //ex : hpMax (depuis "hpMax=1")
                value = strtok(NULL, "="); //ex : 1 (depuis "hpMax=1")
                uppercase(stat);
                uppercase(value);

                if(strcmp(stat, "NAME") == 0) {
                    name = duplicateString(value);
                } else if((strcmp(stat, "HPMAX") == 0)) {
                    hpMax = atof(value);
                    // printf("hpMax %f \n", hpMax);
                }  else if((strcmp(stat, "SHOOT") == 0)) {
                    // printf("value %s", value);
                    activated = (strcmp(value, "TRUE") == 0);
                    // printf("activated %d \n", activated);
                    shoot = activated;
                } else if((strcmp(stat, "SS") == 0)) {
                    activated = (strcmp(value, "TRUE\n") == 0);
                    ss = activated;
                } else if((strcmp(stat, "FLIGHT") == 0)) {
                    activated = (strcmp(value, "TRUE\n") == 0);
                    flight = activated;
                }
            }

            } 

            if(firstLetter == '-' && creatingMonster == 1) { // ajout object
                arrayMonster[idMonster] = createMonster(idMonster, name, hpMax, shoot,flight,ss);
                idMonster = idMonster + 1;
                creatingMonster = (creatingMonster) ? 0 : 1;
                // printf("idMonster %d\n", idMonster);
                // printf("%s", name);
            }   
        }
    

    if(feof(fichier)) { 
        if(strcmp(name, "") != 0) {
            arrayMonster[idMonster] = createMonster(idMonster, name, hpMax, shoot,flight,ss);
            idMonster = idMonster + 1;
               
        }
    } // ajout du dernier object
    
    fclose(fichier);
    return arrayMonster;
}




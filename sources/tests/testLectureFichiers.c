/**
 * @file testLectureFichiers.c
 * @author TheGreat-Chain
 * @brief Tests des fonctions de lectureFichiers.h
 * @version 0.1
 * @date 2022-10-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

#include "../include/mystring.h"
#include "../include/objects.h"
#include "../include/lectureFichiers.h"
#include "../include/array.h"
#include "../include/roomsForCRUD.h"

void test_extensionType(); //ok
void test_getNbLignesFichier(); //ok
void test_roomsFileToRoomsList(); //ok
void test_listToRoomsFile(); //ok

void test_objectsFileToObjectsList(); 
void test_listToObjectsFile(); // ok

int main(void) {
    //test_listToRoomsFile();
    //test_roomsFileToRoomsList();
    //test_extensionType();
    //test_getNbLignesFichier();
    //test_objectsFileToObjectsList();
    //test_listToObjectsFile();

    return 0;
}

void test_listToObjectsFile() {
    printf("[TEST] writing fichier objets\n");

    Object* head = objectsFileToObjectsList();
    displayAllObjects(head);
    printf("\n The above items should be written inside ./test.rtbob :)\n");
    listToObjectsFile(head);
}

void test_objectsFileToObjectsList() {
    printf("[TEST] parsing fichier objets\n");

    Object* head = objectsFileToObjectsList();
    displayAllObjects(head);
}

void test_listToRoomsFile() {
    printf("[TEST] listToRoomsFile() :\n\n");
    CRUD_Room* rooms = roomsFileToRoomsList();
    listToRoomsFile(rooms);
    printf("Check the test.rtbob file ;)\n");
}

void test_roomsFileToRoomsList() {
    printf("[TEST] roomsFileToRoomsList() :\n\n");
    CRUD_Room* rooms = roomsFileToRoomsList();
    displayAllRooms(rooms);
}


void test_getNbLignesFichier() {
    char* chemin = "./test.itbob";
    printf("Attendu : 10\nResultat : %d\n\n", getNbLignesFichier(chemin));
    chemin = "rkovnej";
    printf("\nAttendu : 0 (Impossible d'ouvrir le fichier)\nRésultat : %d\n", getNbLignesFichier(chemin));
}


void test_extensionType() {

    printf("[TEST] extensionType() :\n\n");
   
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "o.itbob", EXTENSION_FICHIER_OBJET, extensionType("o.itbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "m.rtbob", EXTENSION_FICHIER_MONSTRES, extensionType("m.mtbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "m.rtbob", EXTENSION_FICHIER_SALLES, extensionType("m.rtbob"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "", EXTENSION_INVALIDE, extensionType(""));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "sujet.pdf", EXTENSION_INVALIDE, extensionType("sujet.pdf"));
    printf("Fichier : %s\nAttendu : %d\nRésultat : %d\n\n", "jeidjioc", EXTENSION_INVALIDE, extensionType("jeidjioc"));

}

/*


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

ListeObjects* fichierObjectsToListeObjects() {
    char* filepath = "../../resources/items.itbob"; // CHEMIN_FICHIER_OBJETS
    FILE* fichier = fopen(filepath, "r"); // ouverture fichier
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier des objects.\n");
        return NULL;
    }

    rewind(fichier);
   
    ListeObjects* liste = createListeObjects(); // variables
    Object* o;
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
                } else if((strcmp(stat, "DMG") == 0)) {
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
                o = createObject(name, hpMax, shield, damage, piercingShot, spectralShot, flight);
                addObject(liste, o);
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
            o = createObject(name, hpMax, shield, damage, piercingShot, spectralShot, flight);
            addObject(liste, o);
        }
    } // ajout du dernier object
    
    fclose(fichier);
    return liste;
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

void listeToFichierObjects(ListeObjects* listeObjects) {
    char* filepath = "./test.itbob"; // CHEMIN_FICHIER_OBJETS
    FILE* fichier = fopen(filepath, "w+"); // ouverture fichier
    if(fichier == NULL) { 
        printf("Problème d'ouverture du fichier des objects.\n");
        return;
    }

    char* buffer_out = malloc(sizeof(char) * 256);

    // ecriture de l'indicateur du nombre d'objects :
    int listSize = getTailleListeObjects(listeObjects);
    if(listSize == 0) { // fin si pas d'objects dans la liste
        return;
    }
    sprintf(buffer_out, "{%d}\n", listSize);
    fwrite(buffer_out, sizeof(char), strlen(buffer_out), fichier);

    // ecriture des objects :
    Object* courant = listeObjects->premier;
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
}
*/
/**
 * @file lectureFichiers.c
 * @author TheGreat-Chain & Nairod36
 * @brief Fontions relatives à la lecture des fichiers des monstres et objects.
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "include/lectureFichiers.h"
#include "include/array.h"
#include "include/mystring.h"
#include "include/monster.h"
#include <unistd.h>     

#include <string.h>

int getNomberObjects(FILE* fichierObjects){
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

void listeToFichierObjects(ListeObjects* listeObjects) {
    char* filepath = CHEMIN_FICHIER_OBJECTS;
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
        return EXTENSION_FICHIER_OBJECT;
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

ListeObjects* fichierObjectsToListeObjects() {
    char* filepath = CHEMIN_FICHIER_OBJECTS;
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

    char buffer[255];
    char* stat = malloc(sizeof(char) * 255); 
    char* value = malloc(sizeof(char) * 255);
    int creatingMonster = 1;
    char firstLetter;

  

    while(fgets(buffer, 255, fichier)) { // lecture fichier ligne par ligne
        firstLetter = buffer[0];
        // printf("firstLetter %d\n", firstLetter);

        //printf("%s", buffer);

        if(firstLetter == 'n' || firstLetter == '-' || firstLetter == 'h' || firstLetter == 's' || firstLetter == 's' || firstLetter == 'f' || firstLetter == EOF) {
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
                }  else if((strcmp(stat, "SHOOT") == 0)) {
                    if ((strcmp(value, "TRUE\n") == 0)){   
                    shoot = 1;
                    }  
                } else if((strcmp(stat, "SS") == 0)) {
                    if((strcmp(value, "TRUE\n") == 0)){
                    ss = 1;
                    }
                } else if((strcmp(stat, "FLIGHT") == 0)) {
                    if((strcmp(value, "TRUE\n") == 0)){
                    flight = 1;
                    }
                }

            }

            if(firstLetter == '-' && creatingMonster == 1) { // ajout object
            //TODO faire une fonction simple qui malloc un monster et qui le retourne
                arrayMonster[idMonster] = createMonster(idMonster, name, hpMax, shoot,flight,ss);
                idMonster = idMonster + 1;
                creatingMonster = (creatingMonster) ? 0 : 1;
                // printf("idMonster %d\n", idMonster);
                // printf("%s", name);
            }   
        }
    }

    if(feof(fichier)) { 
        if(strcmp(name, "") != 0) {
            arrayMonster[idMonster] = createMonster(idMonster, name, hpMax, shoot,flight,ss);
            idMonster = idMonster + 1;
               
        }
    } // ajout du dernier object
    
    fclose(fichier);
    sleep(1);
    return arrayMonster;
}
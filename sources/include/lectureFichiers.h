/**
 * @file lectureFichiers.h
 * @author TheGreat-Chain
 * @brief Fontions relatives à la lecture des fichiers des monstres, objects et pièces.
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef LECTURE_FICHIERS_H

    #define LECTURE_FICHIERS_H

    #include "cheminsFichiers.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include "objects.h"
    #include "roomsForCRUD.h"
    #include "charactersId.h"

    /**
     * @brief Makes the user choose a player. Returns the id of the player selected. 
     * @return int 
     */
    int choseCharacter();

    typedef struct Monster Monster;

    /**
     * @brief Transforme le fichier des objects bonus en structure de type ListeObjects et retourne
     * l'adresse de l'espace mémoire alloué à la liste d'objects. 
     * 
     * retourne NULL si erreur dans le traitement du fichier. 
     * 
     * @return Object* Pointeur sur le premier objet de la liste
     */
    Object* objectsFileToObjectsList();


    /**
     * @brief Réécrit le fichier en fonction de liste chainée d'objets dont le premier objet 
     * est passé en paramètres 
     * 
     * @param Object* premier objet de la liste
     */
    void listToObjectsFile(Object* head);

    /**
     * @brief Retourne le nombre d'objects du fichier, lu à la première ligne entre les accolades.
     * 
     * @param fichierObjects fichier des objects (.itbob)
     * @return int nombre d'objects bonus
     */
    int getNombreObjects(FILE* fichierObjects);

    /**
     * @brief Permet d'afficher le contenu du fichier dans le terminal
     * 
     */
    void afficherFichier(FILE* fichier);

    #define EXTENSION_FICHIER_OBJET 1
    #define EXTENSION_FICHIER_MONSTRES 2
    #define EXTENSION_FICHIER_SALLES 3
    #define EXTENSION_INVALIDE 0

    /**
     * @brief Renvoie l'extension du fichier sous forme d'un entier tel quel :
     * 0 : fichier invalide,
     * 1 : fichier objects,
     * 2 : fichier monstres,
     * 3 : fichier salles
     * 
     * @param filename nom du fichier. ex : salles.rtbob
     * @return int 
     */
    int extensionType(char* filename);

    /**
     * @brief Ajoute "---" à la toute fin du fichier pour permettre à fichierObjectsToListeObjects() 
     * de parser le dernier object. 
     * Ne fait rien si le fichier en paramètre est le fichier des salles
     */
    void correctFile(char* cheminFichier);

    /**
     * @brief Récupérer le nombre de lignes écrites dans un fichier
     * 
     * @param chemin_fichier chemin du fichier 
     * @return int 
     */
    int getNbLignesFichier(char* chemin_fichier);

    /**
     * @brief Parses the .rtbob file and returns a pointer to RoomsList, handlable with functions written in roomsForCRUD.h
     * @return RoomsList pointer, NULL if failure (eg : file corrupted)
     */
    CRUD_Room* roomsFileToRoomsList();

    /**
     * @brief Writes into the .rtbob file thanks to the given head of the rooms list
     * @param head first room of the list
     * @return 0 if problem encountered, 1 otherwise
     */
    int listToRoomsFile(CRUD_Room* nhead);

    /**
     * @brief Get the number of lines and columns from a buffer that contains this information.
     * 
     * @param buffer 
     * @param ptr_lines 
     * @param ptr_columns 
     * @return int 1 if success, 0 otherwise
     */
    int parseRoomInfo(char* buffer, int* ptr_lines, int* ptr_columns);

    Monster* fichierMonsterToListeMonster();

    int choseCharacter();

#endif //LECTURE_FICHIERS_H
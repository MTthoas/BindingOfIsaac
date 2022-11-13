/**
 * @file lectureFichiers.h
 * @author TheGreat-Chain & Nairod36
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

    /**
     * @brief Transforme le fichier des objects bonus en structure de type ListeObjects et retourne
     * l'adresse de l'espace mémoire alloué à la liste d'objects. 
     * 
     * retourne NULL si erreur dans le traitement du fichier. 
     * 
     * @return ListeObjects* 
     */
    ListeObjects* fichierObjectsToListeObjects();

    /**
     * @brief Réécrit le fichier en fonction de la structure ListeObjects 
     * 
     * @param listeObjects 
     */
    void listeToFichierObjects(ListeObjects* listeObjects);

    /**
     * @brief Retourne le nombre d'objects du fichier, lu à la première ligne entre les accolades.
     * 
     * @param fichierObjects fichier des objects (.itbob)
     * @return int nombre d'objects bonus
     */
    int getNomberObjects(FILE* fichierObjects);

    /**
     * @brief Permet d'afficher le contenu du fichier dans le terminal
     * 
     */
    void afficherFichier(FILE* fichier);

    #define EXTENSION_FICHIER_OBJECT 1
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

#endif //LECTURE_FICHIERS_H
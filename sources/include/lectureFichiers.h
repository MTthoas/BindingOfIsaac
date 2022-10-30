/**
 * @file lectureFichiers.h
 * @author TheGreat-Chain
 * @brief Fontions relatives à la lecture des fichiers des monstres, objets et pièces.
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
    #include "objets.h"

    /**
     * @brief Transforme le fichier des objets bonus en structure de type ListeObjets et retourne
     * l'adresse de l'espace mémoire alloué à la liste d'objets. 
     * 
     * retourne NULL si erreur dans le traitement du fichier. 
     * 
     * @return ListeObjets* 
     */
    ListeObjets* fichierObjetsToListeObjets();

    /**
     * @brief Réécrit le fichier en fonction de la structure ListeObjets 
     * 
     * @param listeObjets 
     */
    void listeToFichierObjets(ListeObjets* listeObjets);

    /**
     * @brief Retourne le nombre d'objets du fichier, lu à la première ligne entre les accolades.
     * 
     * @param fichierObjets fichier des objets (.itbob)
     * @return int nombre d'objets bonus
     */
    int getNombreObjets(FILE* fichierObjets);

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
     * 1 : fichier objets,
     * 2 : fichier monstres,
     * 3 : fichier salles
     * 
     * @param filename nom du fichier. ex : salles.rtbob
     * @return int 
     */
    int extensionType(char* filename);

#endif //LECTURE_FICHIERS_H
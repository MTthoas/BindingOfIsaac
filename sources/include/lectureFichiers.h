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


    #include <stdlib.h>
    #include <stdio.h>
    #include "objets.h"

    /**
     * @brief Transforme le fichier des objets bonus en structure de type
     * ListeObjets.
     * 
     * @return ListeObjets* 
     */
    ListeObjets* fichierToListeObjets();

    /**
     * @brief A utiliser pour actualiser le fichier des objets bonus. 
     * Réécrit le fichier en fonction de la structure ListeObjets 
     * 
     * @param listeObjets 
     */
    void actualiserFichierObjets(ListeObjets* listeObjets);

    /**
     * @brief Retourne le nombre d'objets du fichier, lu à la première ligne entre les accolades.
     * 
     * @param fichierObjets fichier des objets (.itbob)
     * @return int nombre d'objets bonus
     */
    int getNombreObjets(FILE* fichierObjets);

    /**
     * @brief Retourne le pointeur vers tableau contenant tous les objets du fichier des objets.
     * 
     * @param fichierObjets fichier des objets bonus (.itbob)
     * @param nbObjets nombre d'objets dans le fichier des objets
     * 
     * @return Objet* 
     */
    Objet* getTabObjets(FILE* fichierObjets, int nbObjets);

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
     * @brief Renvoie 1 si fichier conforme, 0 sinon.
     * 
     * @param fichier fichier, toutes les extensions sont prises en charge 
     * @param extension nom du fichier
     * @return int 
     */
    int fichierValide(FILE* fichier, int extension);

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
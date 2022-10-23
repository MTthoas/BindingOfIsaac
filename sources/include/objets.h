/**
 * @file fichierObjets.h
 * @author TheGreat-Chain
 * @brief Structures et fonctions relatives aux objets de personnage
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef OBJETS_H
#define OBJETS_H

    /**
     * @brief Objets apportant des bonus de statistique au personnage.
     */
    typedef struct Objet {
        int id;
        char* name;
        int hpMax;
        int shield;
        int damage; //dégâts provoqués par les tirs
        int piercingShot; //tirs passent à travers les ennemis mais pas les rochers
        int spectralShot; //tirs passent à travers les rochers mais pas les ennemis
        int flight; //passer au dessus de trous rochers et pic
    } Objet;

    /**
     * @brief Liste de tous les objets du fichier des objets. 
     */
    typedef struct ListeObjets {
        int nombreObjets;
        Objet* tabObjets;
        
    } ListeObjets;

    /**
     * @brief Afficher le contenu de la liste des objets.
     * 
     * READ du CRUD
     * 
     * @param listeObjets 
     */
    void displayListeObjets(ListeObjets* listeObjets);

    /**
     * @brief Affiche l'objet et ses attributs dans le terminal.
     * 
     * @param objet objet à afficher
     */
    void displayObjet(Objet* objet);

    /**
     * @brief Ajouter un objet dans la liste des objets.
     * 
     * CREATE du CRUD
     * 
     * @param listeObjets 
     * @param newObjet 
     */
    void addObjet(ListeObjets* listeObjets, Objet* newObjet);

    /**
     * @brief Retire un objet de la structure de la liste des objets
     * 
     * REMOVE du CRUD
     * 
     * @param listeObjets 
     * @param idObjet 
     */
    void removeObjet(ListeObjets* listeObjets, int idObjet);

    /**
     * @brief Modifie un objet spécifié par un nouvel objet passé en paramètre.
     * TODO : free l'objet ayant l'id correspondant et pointer vers newObjet
     * UPDATE du CRUD
     * 
     * @param ListeObjets 
     * @param idObjetToReplace 
     * @param newObjet 
     */
    void modifyObjet(ListeObjets* listeObjets, int idObjetToReplace, Objet* newObjet);

    /**
     * @brief Retourne l'adresse de l'objet ayant l'id correspondant
     * 
     * @param ListeObjets 
     * @param id 
     * @return Objet* 
     */
    Objet* findObjetById(ListeObjets* ListeObjets, int id);



#endif //OBJETS_H
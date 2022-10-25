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
     * Element de la liste chaînée ListeObjets. Pointe sur l'objet suivant.
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

        Objet* suivant;

    } Objet;

    /**
     * @brief Liste de tous les objets du jeu. 
     * Liste chainée pointant vers le premier objet du jeu.
     * 
     */
    typedef struct ListeObjets {
        Objet* premier;
    } ListeObjets;

    /**
     * @brief Afficher le contenu de la liste des objets.
     * 
     * READ du CRUD
     * 
     * @param listeObjets 
     */
    void* displayListeObjets(ListeObjets* listeObjets);

    /**
     * @brief Affiche l'objet et ses attributs dans le terminal.
     * Tous les champs doivent être remplis sinon erreur de segmentation !
     * 
     * @param objet objet à afficher
     */
    void* displayObjet(Objet* objet);

    /**
     * @brief Ajouter un objet dans la liste des objets.
     * Retourne l'id du nouvel objet.
     * 
     * CREATE du CRUD
     * 
     * @param listeObjets 
     * @param newObjet 
     */
    int addObjet(ListeObjets* listeObjets, Objet* newObjet);

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
     * @brief Retourne l'adresse de l'objet de la liste ayant l'id correspondant.
     * Retourne NULL si l'id demandé n'existe pas.
     * 
     * @param ListeObjets 
     * @param id 
     * @return Objet* 
     */
    Objet* getObjetById(ListeObjets* ListeObjets, int id);


    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un objet dont la valeur des champs est identique
     * à ceux de l'objet en paramètre.
     * 
     * @param objet objet à copier
     * @return Objet* 
     */
    Objet* duplicateObject(Objet* objet);



#endif //OBJETS_H
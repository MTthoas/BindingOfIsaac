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
    typedef struct Objet Objet;
    struct Objet {
        int id;
        char* name;
        float hpMax;
        float shield;
        float damage; //dégâts provoqués par les tirs
        int piercingShot; //tirs passent à travers les ennemis mais pas les rochers
        int spectralShot; //tirs passent à travers les rochers mais pas les ennemis
        int flight; //passer au dessus de trous rochers et pic

        Objet* suivant;
    };

    /**
     * @brief Liste de tous les objets du jeu. 
     * Pointe vers le premier objet de la liste chainée.
     */
    typedef struct ListeObjets {
        Objet* premier;
    } ListeObjets;

    /**
     * @brief Alloue un espace mémoire pour une liste d'objet et renvoie son adresse. 
     * Pour ajouter des Objets dans la liste, utiliser addObjet().
     * 
     * @return ListeObjet* 
     */
    ListeObjets* createListeObjets();

    /**
     * @brief Constructeur d'objets
     * 
     * @param name 
     * @param hpMax 
     * @param shield 
     * @param damage 
     * @param piercingShot 
     * @param spectralShot 
     * @param flight 
     * 
     * @return Objet* adresse de l'objet suivant (NULL par défaut)
     */
    Objet* createObjet(char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight);

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
     * Retourne l'id du nouvel objet, 0 si l'objet n'a pas pu être ajouté.
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
    Objet* getObjetById(ListeObjets* , int );

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un objet dont la valeur des champs est identique
     * à ceux de l'objet en paramètre.
     * 
     * @param objet objet à copier
     * @return Objet* 
     */
    Objet* duplicateObjet(Objet* objet);

    /**
     * @brief Désalloue la mémoire allouée à un objet
     * 
     */
    void freeObjet(Objet*);
    
    /**
     * @brief Désalloue la mémoire allouée à une liste d'objets.
     * 
     */
    void freeListeObjets(ListeObjets*);

    /**
     * @brief Remet les identifiants des objets dans l'ordre.
     * A utiliser par exemple après une suppression.
     */
    void rangerListeObjets(ListeObjets*);

    /**
     * @brief Retourne le nombre d'éléments d'une liste d'objets
     * 
     * @return int 
     */
    int getTailleListeObjets(ListeObjets*);



#endif //OBJETS_H
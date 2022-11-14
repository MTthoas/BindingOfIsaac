/**
 * @file fichierobjets.h
 * @author TheGreat-Chain & Nairod36
 * @brief Structures et fonctions relatives aux objets de personnage
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 */


#ifndef objetS_H
#define objetS_H

    /**
     * @brief objets apportant des bonus de statistique au personnage.
     * Element de la liste chaînée Listeobjets. Pointe sur l'objet suivant.
     */
    typedef struct objet objet;
    struct objet {
        int id;
        char* name;
        float hpMax;
        float shield;
        float damage; //dégâts provoqués par les tirs
        int piercingShot; //tirs passent à travers les ennemis mais pas les rochers
        int spectralShot; //tirs passent à travers les rochers mais pas les ennemis
        int flight; //passer au dessus de trous rochers et pic

        objet* suivant;
    };

    /**
     * @brief Liste de tous les objets du jeu. 
     * Pointe vers le premier objet de la liste chainée.
     */
    typedef struct Listeobjets {
        objet* premier;
    } Listeobjets;

    /**
     * @brief Alloue un espace mémoire pour une liste d'objet et renvoie son adresse. 
     * Pour ajouter des objets dans la liste, utiliser addobjet().
     * 
     * @return Listeobjet* 
     */
    Listeobjets* createListeobjets();

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
     * @return objet* adresse de l'objet suivant (NULL par défaut)
     */
    objet* createobjet(char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight);

    /**
     * @brief Afficher le contenu de la liste des objets.
     * 
     * READ du CRUD
     * 
     * @param listeobjets 
     */
    void* displayListeobjets(Listeobjets* listeobjets);

    /**
     * @brief Affiche l'objet et ses attributs dans le terminal.
     * Tous les champs doivent être remplis sinon erreur de segmentation !
     * 
     * @param objet objet à afficher
     */
    void* displayobjet(objet* objet);

    /**
     * @brief Ajouter un objet dans la liste des objets.
     * Retourne l'id du nouvel objet, 0 si l'objet n'a pas pu être ajouté.
     * 
     * CREATE du CRUD
     * 
     * @param listeobjets 
     * @param newobjet 
     */
    int addobjet(Listeobjets* listeobjets, objet* newobjet);

    /**
     * @brief Retire un objet de la structure de la liste des objets
     * 
     * REMOVE du CRUD
     * 
     * @param listeobjets 
     * @param idobjet 
     */
    void removeobjet(Listeobjets* listeobjets, int idobjet);

    /**
     * @brief Modifie un objet spécifié par un nouvel objet passé en paramètre.
     * TODO : free l'objet ayant l'id correspondant et pointer vers newobjet
     * UPDATE du CRUD
     * 
     * @param Listeobjets 
     * @param idobjetToReplace 
     * @param newobjet 
     */
    void modifyobjet(Listeobjets* listeobjets, int idobjetToReplace, objet* newobjet);

    /**
     * @brief Retourne l'adresse de l'objet de la liste ayant l'id correspondant.
     * Retourne NULL si l'id demandé n'existe pas.
     * 
     * @param Listeobjets 
     * @param id 
     * @return objet* 
     */
    objet* getobjetById(Listeobjets* , int );

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un objet dont la valeur des champs est identique
     * à ceux de l'objet en paramètre.
     * 
     * @param objet objet à copier
     * @return objet* 
     */
    objet* duplicateobjet(objet* objet);

    /**
     * @brief Désalloue la mémoire allouée à un objet
     * 
     */
    void freeobjet(objet*);
    
    /**
     * @brief Désalloue la mémoire allouée à une liste d'objets.
     * 
     */
    void freeListeobjets(Listeobjets*);

    /**
     * @brief Remet les identifiants des objets dans l'ordre.
     * A utiliser par exemple après une suppression.
     */
    void rangerListeobjets(Listeobjets*);


    /**
     * @brief Retourne le nombre d'éléments d'une liste d'objets
     * 
     * @return int 
     */
    int getTailleListeobjets(Listeobjets*);




#endif //objetS_H

/**
 * @file fichierObjects.h
 * @author TheGreat-Chain
 * @brief Structures et fonctions relatives aux objects de personnage
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef OBJETS_H
#define OBJETS_H

    /**
     * @brief Objects apportant des bonus de statistique au personnage.
     * Element de la liste chaînée ListeObjects. Pointe sur l'object suivant.
     */
    typedef struct Object Object;
    struct Object {
        int id;
        char* name;
        float hpMax;
        float shield;
        float damage; //dégâts provoqués par les tirs
        int piercingShot; //tirs passent à travers les ennemis mais pas les rochers
        int spectralShot; //tirs passent à travers les rochers mais pas les ennemis
        int flight; //passer au dessus de trous rochers et pic

        Object* next;
    };

    /**
     * @brief Constructeur d'objects
     * 
     * @param id
     * @param name 
     * @param hpMax 
     * @param shield 
     * @param damage 
     * @param piercingShot 
     * @param spectralShot 
     * @param flight 
     * 
     * @return Object* adresse de l'object suivant (NULL par défaut)
     */
    Object* createObject(int id, char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight);

    /**
     * @brief Affiche tous les objets à partir de celui passé en paramètres
     * 
     * READ du CRUD
     * 
     * @param firstObject premier maillon de la liste chainee
     */
    void displayAllObjects(Object* head);

    /**
     * @brief Affiche l'object et ses attributs dans le terminal.
     * Tous les champs doivent être remplis sinon erreur de segmentation !
     * 
     * @param object object à afficher
     */
    void displayObject(Object* object);

    /**
     * 
     * CREATE du CRUD. Ajoute un objet à la liste commençant par head. Toujours donner le premier objet. 
     * Réarrange les id et duplique (et donc désalloue) l'objet donné
     * 
     * @param head first object 
     * @param newObject 
     * 
     * @return 1 success, 0 otherwise
     */
    int addObject(Object* head, Object* newObject);

    /**
     * @brief Removes the object of the given id from the linked list
     * 
     * @param ptr_head pointer of first object
     * @param id id of object to remove
     */
    void removeObject(Object** ptr_head, int id);

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un object dont la valeur des champs est identique
     * à ceux de l'object en paramètre. Désalloue l'objet à l'adresse passée en paramètres pour éviter les fuites mémoires.
     * 
     * @param object object à copier
     * @return Object* 
     */
    Object* duplicateObject(Object* object);

    /**
     * @brief Retourne le nombre d'objets de la liste chaînée 
     * 
     * @return int 0 si liste vide, -1 si l'objet n'est pas le premier, un entier sinon
     */
    int getNumberObjects(Object* head);

    /**
     * @brief Free all objects of the linked list
     * 
     * @param head object of id 1.
     * @return int 
     */
    int freeAllObjects(Object* head);

    /**
     * @brief Remet les id dans l'ordre
     * 
     * @param head 
     * @return int 
     */
    int arrangeObjectsIds(Object* head);

    /**
     * @brief Get the Object with the given id
     * 
     * @param head first object of the list
     * @param id 
     * @return Object* 
     */
    Object* getObjectById(Object* head, int id);



#endif //OBJETS_H
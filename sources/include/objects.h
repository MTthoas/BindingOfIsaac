/**
 * @file fichierObjects.h
 * @author TheGreat-Chain & Nairod36
 * @brief Structures et fonctions relatives aux objects de personnage
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 */


#ifndef OBJECTS_H
#define OBJECTS_H

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

        Object* suivant;
    };

    /**
     * @brief Liste de tous les objects du jeu. 
     * Pointe vers le premier object de la liste chainée.
     */
    typedef struct ListeObjects {
        Object* premier;
    } ListeObjects;

    /**
     * @brief Alloue un espace mémoire pour une liste d'object et renvoie son adresse. 
     * Pour ajouter des Objects dans la liste, utiliser addObject().
     * 
     * @return ListeObject* 
     */
    ListeObjects* createListeObjects();

    /**
     * @brief Constructeur d'objects
     * 
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
    Object* createObject(char* name, float hpMax, float shield, float damage, int piercingShot, int spectralShot, int flight);

    /**
     * @brief Afficher le contenu de la liste des objects.
     * 
     * READ du CRUD
     * 
     * @param listeObjects 
     */
    void* displayListeObjects(ListeObjects* listeObjects);

    /**
     * @brief Affiche l'object et ses attributs dans le terminal.
     * Tous les champs doivent être remplis sinon erreur de segmentation !
     * 
     * @param object object à afficher
     */
    void* displayObject(Object* object);

    /**
     * @brief Ajouter un object dans la liste des objects.
     * Retourne l'id du nouvel object, 0 si l'object n'a pas pu être ajouté.
     * 
     * CREATE du CRUD
     * 
     * @param listeObjects 
     * @param newObject 
     */
    int addObject(ListeObjects* listeObjects, Object* newObject);

    /**
     * @brief Retire un object de la structure de la liste des objects
     * 
     * REMOVE du CRUD
     * 
     * @param listeObjects 
     * @param idObject 
     */
    void removeObject(ListeObjects* listeObjects, int idObject);

    /**
     * @brief Modifie un object spécifié par un nouvel object passé en paramètre.
     * TODO : free l'object ayant l'id correspondant et pointer vers newObject
     * UPDATE du CRUD
     * 
     * @param ListeObjects 
     * @param idObjectToReplace 
     * @param newObject 
     */
    void modifyObject(ListeObjects* listeObjects, int idObjectToReplace, Object* newObject);

    /**
     * @brief Retourne l'adresse de l'object de la liste ayant l'id correspondant.
     * Retourne NULL si l'id demandé n'existe pas.
     * 
     * @param ListeObjects 
     * @param id 
     * @return Object* 
     */
    Object* getObjectById(ListeObjects* , int );

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un object dont la valeur des champs est identique
     * à ceux de l'object en paramètre.
     * 
     * @param object object à copier
     * @return Object* 
     */
    Object* duplicateObject(Object* object);

    /**
     * @brief Désalloue la mémoire allouée à un object
     * 
     */
    void freeObject(Object*);
    
    /**
     * @brief Désalloue la mémoire allouée à une liste d'objects.
     * 
     */
    void freeListeObjects(ListeObjects*);

    /**
     * @brief Remet les identifiants des objects dans l'ordre.
     * A utiliser par exemple après une suppression.
     */
    void rangerListeObjects(ListeObjects*);


    /**
     * @brief Retourne le nombre d'éléments d'une liste d'objects
     * 
     * @return int 
     */
    int getTailleListeObjects(ListeObjects*);




#endif //OBJECTS_H

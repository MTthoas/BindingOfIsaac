/**
 * @file test.h
 * @author TheGreat-Chain
 * @brief toutes les fonctions à tester
 * @version 0.1
 * @date 2022-10-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

    #define EXTENSION_FICHIER_OBJET 1
    #define EXTENSION_FICHIER_MONSTRES 2
    #define EXTENSION_FICHIER_SALLES 3
    #define EXTENSION_INVALIDE 0

    void test_extensionType();
    void test_displayObjet();
    void test_displayListeObjets();
    void test_addObjet();
    void test_duplicateObject();
    void test_copierEtGrandirListeObjets();

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
    int extensionType(char* filename); // testé OK

    /**
     * @brief Objets apportant des bonus de statistique au personnage. Un objet dont l'id est à 0 indique l'absence d'objet.
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
        /**
         * @brief Nombre d'objets effectivement dans le tableau.
         * 
         */
        int nombreObjets;

        /**
         * @brief Capacité totale du tableau d'objets.
         * 
         */
        int capacite;

        /**
         * @brief Tableau des objets bonus utilisés dans le jeu.
         * 
         */
        Objet* tabObjets;
        
    } ListeObjets;

    /**
     * @brief Afficher le contenu de la liste des objets.
     * 
     * READ du CRUD
     * 
     * @param listeObjets 
     */
    void* displayListeObjets(ListeObjets* listeObjets); // testé ok

    /**
     * @brief Affiche l'objet et ses attributs dans le terminal.
     * 
     * @param objet objet à afficher
     */
    void* displayObjet(Objet* objet); // testé OK

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un objet dont la valeur des champs est identique
     * à ceux de l'objet en paramètre.
     * 
     * @param objet objet à copier
     * @return Objet* 
     */
    Objet* duplicateObject(Objet* objet);

    /**
     * @brief Ajouter un objet dans la liste des objets. 
     * Retourne l'id du nouvel objet, mais retourne 0 si la liste est pleine.
     * 
     * CREATE du CRUD
     * 
     * @param listeObjets 
     * @param newObjet 
     */
    int addObjet(ListeObjets* listeObjets, Objet* newObjet);

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
    Objet* getObjetById(ListeObjets* ListeObjets, int id);

    /**
     * @brief Crée un nouvel espace mémoire pour une liste objet plus grande que celle passée en
     * paramètres, recopie ses valeurs et retourne l'adresse de cet espace mémoire.
     * 
     * @param listeObjets listeObjets à dupliquer et grandir
     * @return Objet* 
     */
    ListeObjets* copierEtGrandirListeObjets(ListeObjets* listeObjets);




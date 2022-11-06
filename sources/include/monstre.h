#include <stdio.h>
#include <stdlib.h>

struct monstre {
    char* name;
    int hpMax;
    int shoot;
    int flight;
    int ss;
};

#ifndef MONSTRE_H
#define MONSTRE_H

    /**
     * @brief Monstres
     * Element de la liste chaînée ListeMonstres. Pointe sur l'monstre suivant.
     */
    typedef struct Monstre Monstre;
    struct Monstre {
        int id;
        char* name;
        float hpMax;
        int shoot;
        int flight;
        int ss;
        Monstre* suivant;
    };

    /**
     * @brief Liste de tous les Monstres du jeu. 
     * Pointe vers le premier monstre de la liste chainée.
     */
    typedef struct ListeMonstres {
        Monstre* premier;
    } ListeMonstres;

    /**
     * @brief Alloue un espace mémoire pour une liste de monstre et renvoie son adresse. 
     * Pour ajouter des Monstres dans la liste, utiliser addMonstre().
     * 
     * @return ListeMonstre* 
     */
    ListeMonstres* createListeMonstres();

    /**
     * @brief Constructeur d'Monstres
     * 
     * @param name 
     * @param hpMax 
     * @param shoot 
     * @param flight 
     * @param ss      * 
     * @return Monstre* adresse de l'monstre suivant (NULL par défaut)
     */
    Monstre* createMonstre(char* name, float hpMax, float shoot, float flight, int ss);

    /**
     * @brief Afficher le contenu de la liste des Monstres.
     * 
     * READ du CRUD
     * 
     * @param listeMonstres 
     */
    void* displayListeMonstres(ListeMonstres* listeMonstres);

    /**
     * @brief Affiche le monstre et ses attributs dans le terminal.
     * Tous les champs doivent être remplis sinon erreur de segmentation !
     * 
     * @param monstre monstre à afficher
     */
    void* displayMonstre(Monstre* monstre);

    /**
     * @brief Ajouter un monstre dans la liste des Monstres.
     * Retourne l'id du nouvel monstre, 0 si l'monstre n'a pas pu être ajouté.
     * 
     * CREATE du CRUD
     * 
     * @param listeMonstres 
     * @param newMonstre 
     */
    int addMonstre(ListeMonstres* listeMonstres, Monstre* newMonstre);

    /**
     * @brief Retire un monstre de la structure de la liste des Monstres
     * 
     * REMOVE du CRUD
     * 
     * @param listeMonstres 
     * @param idMonstre 
     */
    void removeMonstre(ListeMonstres* listeMonstres, int idMonstre);

    /**
     * @brief Modifie un monstre spécifié par un nouveau monstre passé en paramètre.
     * TODO : free le monstre ayant l'id correspondant et pointer vers newMonstre
     * UPDATE du CRUD
     * 
     * @param ListeMonstres 
     * @param idMonstreToReplace 
     * @param newMonstre 
     */
    void modifyMonstre(ListeMonstres* listeMonstres, int idMonstreToReplace, Monstre* newMonstre);

    /**
     * @brief Retourne l'adresse du monstre de la liste ayant l'id correspondant.
     * Retourne NULL si l'id demandé n'existe pas.
     * 
     * @param ListeMonstres 
     * @param id 
     * @return Monstre* 
     */
    Monstre* getMonstreById(ListeMonstres* , int );

    /**
     * @brief Retourne l'adresse d'un nouvel espace mémoire alloué à un monstre dont la valeur des champs est identique
     * à ceux du monstre en paramètre.
     * 
     * @param monstre monstre à copier
     * @return Monstre* 
     */
    Monstre* duplicateMonstre(Monstre* monstre);

    /**
     * @brief Désalloue la mémoire allouée à un monstre
     * 
     */
    void freeMonstre(Monstre*);
    
    /**
     * @brief Désalloue la mémoire allouée à une liste de Monstres.
     * 
     */
    void freeListeMonstres(ListeMonstres*);

    /**
     * @brief Remet les identifiants des Monstres dans l'ordre.
     * A utiliser par exemple après une suppression.
     */
    void rangerListeMonstres(ListeMonstres*);



#endif //MONSTRE_H
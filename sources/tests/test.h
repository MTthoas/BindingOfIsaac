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
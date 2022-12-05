/**
 * @file room.h
 * @author MTthoas
 * @brief Declaration fonctions et structures des Rooms, Donjons et stages
 * @version 0.5
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef H_ROOM
#define H_ROOM

#define NUMBER_ROOM_MAX 30
#define NUMBER_STAGES_MAX 62

#include "objects.h"
#include "Player.h"
#include "monster.h"

/**
 * @brief To save coordinates of an element inside a double array / a map ...
 */
typedef struct Coordinates { 
        int x; // abscisses
        int y; // ordonnees
} Coordinates;

struct Door{
    char doorTop;
    char doorBottom; 
    char doorLeft;
    char doorRight;
};

// Structure Donjon
typedef struct Donjon{

    char name[256];
    int numberStage;
    Object* headObject; // first object of object linked list
    Monster* monsters;

    // Structure Etages
    struct Stage{

        char** stage;
        int id;
        int axeX;
        int axeY;
        int numberOfVoisins;
        char name[256];
        int numberOfRooms;
        int * randomNumberRooms;

        // Structure Salles
        struct Room{
            char name;
            int id;
            char** room;
            int AxeX;
            int AxeY;
            int number;
            int width; // columns
            int height; // rows
            char * Doors;
            int numberOfDoors;
            int doorTop;
            int doorBottom; 
            int doorLeft;
            int doorRight;
            int numberOfRoomsReturned;
            int roomUsed;
            int numberOfMonsters; // number of monsters inside this room
            Monster * monsters; // array of monsters in this room
            Object * object; // an object of the donjon objects linked list
         
            struct Door Door;

        }rooms[NUMBER_ROOM_MAX];

    }stages[NUMBER_STAGES_MAX];
    
} Donjon;

// Room* newRoom(int number);

// void newRooms(Room * s, RoomInSpace * v);

int * RandomArrayForAttribution(int number);
void InitialisationGame(Donjon * d, int stageNum, Monster* arrayMonster);
int numberOfRooms();
int PickRoomNotUsed(Donjon * d, int NumberOfRoomsInt, int stage);
void newStageByNumber(Donjon * d, int stage, int numberOfRooms);

char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);
int * RandomBetweenRange(int number, int zero);
int NowRoomIsUsed(Donjon *d, int NumberOfRoomsInt, int id);
void InitialisationGameByStagesOptionsForArms(Donjon * d, int stage, int numbe);
void InitialiseOtherRoomsFromArms(Donjon * d, int stage, int numberOfRooms);

/**
 * @brief put an array of random monsters inside the "monsters" field of rooms.
 * 
 * @param d 
 * @param stage 
 * @param roomID 
 * @param allMonsters 
 */
void initialiseMonstersInsideRoom(Donjon * d, int stage, int roomID, Monster* allMonsters);

/**
 * @brief Fonction initialiser toutes les room d'un étage
 * 
 * @param d Structure générale
 * @param stage Etage précis
 * @param numberOfRooms Nombre de rooms
 */
void InitialiseRooms(struct Donjon * d, int stage, int numberOfRooms, Monster* monster);

/**
 * @brief Draws and sets the monsters inside the specified room of the dungeon
 * @return 0 if fail, 1 otherwise
 */
int setMonstersInsideRoom(Donjon* d, int stage, int roomID);



#endif
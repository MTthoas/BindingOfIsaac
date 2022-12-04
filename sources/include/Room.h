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
#define NUMBER_STAGES_MAX 10

#include "objects.h"
#include "Player.h"
#include "monster.h"

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
            Monster * newArrayMonster;
            Object* object; // an object of the donjon objects linked list
         
            struct Door Door;

        }rooms[NUMBER_ROOM_MAX];

    }stages[NUMBER_STAGES_MAX];
    
} Donjon;

// Room* newRoom(int number);

// void newRooms(Room * s, RoomInSpace * v);

int * RandomArrayForAttribution(int number);
void InitialisationGame(Donjon * d, int stageNum);
int numberOfRooms();
int PickRoomNotUsed(Donjon * d, int NumberOfRoomsInt, int stage);
void newStageByNumber(Donjon * d, int stage, int numberOfRooms);
void InitialiseRoom(Donjon * d, int stage, int numberOfRooms);
char ** RoomByNumber(int height, int length, int number);
int NumberOfDoorsByRoom(char ** s, int height, int width);
int * RandomBetweenRange(int number, int zero);
int NowRoomIsUsed(Donjon *d, int NumberOfRoomsInt, int id);
void InitialisationGameByStagesOptionsForArms(Donjon * d, int stage, int numbe);
void InitialiseOtherRoomsFromArms(Donjon * d, int stage, int numberOfRooms);
void spawnMonster(Donjon * d, Monster * monster, int stage, int id );  


#endif
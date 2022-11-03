#ifndef H_ROOM
#define H_ROOM

#define NUMBER_ROOM_MAX 30
#define NUMBER_STAGES_MAX 1

// Structure Donjon
struct Donjon{

    char name[256];
    int numberStage;

    // Structure Etages
    struct Stage{

        char** stage;
        int id;
        int axeX;
        int axeY;
        int numberOfVoisins;
        char name[256];
        int numberOfRooms;

        // Structure Salles
        struct Room{
            char** room;
            int positionX;
            int positionY;
            int number;
            int width;
            int height;
            int VoisinRight;
            int VoisinLeft;
            char * Doors;
            int VoisinBottom;
            int VoisinTop;
            int numberOfDoors;
            int doorTop;
            int doorBottom; 
            int doorLeft;
            int doorRight;
            int numberOfRoomsReturned;
            int roomPlaced;

        }rooms[NUMBER_ROOM_MAX];

    }stages[NUMBER_STAGES_MAX];
    
};


typedef struct Donjon Donjon;

// Room* newRoom(int number);

// void newRooms(Room * s, RoomInSpace * v);


// void printRoom(Room room);
// void printRooms(Room room);
void InitialisationGame();
// int NumberOfDoorsByRoom(Room * s);
// void numberOfRooms(Room *s);
// void freeRoom(Room *s);


#endif
/**
 * @file roomsForCRUD.h
 * @author TheGreat-Chain
 * @brief Structures and functions used by the rooms menu
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ROOMS_CRUD_H
#define ROOMS_CRUD_H


    /**
     * @brief Room used by the room menu in order to modify room.rtbob file.
     */
    typedef struct CRUD_Room CRUD_Room;
    struct CRUD_Room {
        int id;
        int lines;
        int columns;

        char** map; // array with the elements (doors, gaps, spikes, ...)

        CRUD_Room* next;
    };

    /**
     * @brief Beginning of chained list of CRUD_Rooms
     */
    typedef struct RoomsList {
            CRUD_Room* firstRoom;
    } RoomsList;

    /**
     * @brief Create a Rooms List object
     * 
     * @return RoomsList*
     */
    RoomsList* createRoomsList();

    /**
     * @brief Create a CRUD_Room object with the given elements
     * 
     * @param lines 
     * @param columns should be x2 because of spaces
     * @param roomElements 
     * @return CRUD_Room* 
     */
    CRUD_Room* createCRUD_Room(int lines, int columns, char** roomElements);

    /**
     * @brief Create a CRUD_Room with only doors and walls
     * 
     * @param height 
     * @param width 
     * @return CRUD_Room* 
     */
    CRUD_Room* createEmptyCRUD_Room(int height, int width);

    /**
     * @brief Displays one room
     */
    void displayCRUD_Room(CRUD_Room*);

    /**
     * @brief Displays all the rooms of a list
     */
    void displayRoomsList(RoomsList*);

    /**
     * @brief Adds the given room to the rooms list
     * 
     * @return int id of new room
     */
    int addCRUD_Room(RoomsList*, CRUD_Room*);

    /**
     * @brief Removes the room with the given id from the list
     */
    void removeCRUD_Room(RoomsList*, int);

    /**
     * @brief Get the room corresponding the the given id
     * 
     * @return CRUD_Room* id, NULL if not found
     */
    CRUD_Room* getCRUD_RoomById(RoomsList* , int);

    /**
     * @brief Duplicates a room
     * 
     * @return CRUD_Room 
     */
    CRUD_Room* duplicateCRUD_Room(CRUD_Room*);

    /**
     * @brief Desallocate memory allocated to one Room
     * 
     */
    void freeCRUD_Room(CRUD_Room*);

     /**
     * @brief Desallocate memory allocated to the all the rooms of a room list 
     * 
     */
    void freeRoomsList(RoomsList*);

    /**
     * @brief Reorders the ids of Rooms.
     * Use after a room deletion for example
     */
    void arrangeRoomsList(RoomsList*);

    /**
     * @brief Returns the number of rooms in the rooms list 
     * @return int number of rooms
     */
    int getRoomsListSize(RoomsList*);


    

#endif
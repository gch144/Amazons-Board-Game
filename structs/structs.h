#ifndef STRUCTS_H
#define STRUCTS_H

#define PLAYER_NICKNAME "jacky"

#define BOARD Board *board

typedef struct {
    int treasure; //0-5
    int artifact; //0-none, 1-horse, 2-broken arrow, 3-spear 
    int occupation; // 0-unoccupied, 1-8- id of a player, 9-arrow/spear
} Cell;

typedef struct {
    int id;
    char name[15];
    int score;
    int amazonsNotPlaced;
} Player;

typedef struct {
    int length;
    Player *list;
} PlayerList;

typedef struct{
    int height;
    int width;
    Cell **btable;
} Board;

//added by gaurav for implementation of botLogic.c
typedef struct coordinates                 //added by gaurav for implementation of botLogic.c
{
    //position along width and height
    int pos_w;  //x-axis
    int pos_h;  //y-axis
} _coords;


#endif // !STRUCTS_H

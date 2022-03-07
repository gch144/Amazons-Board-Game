#pragma once
#ifndef BOT_H
#define BOT_H
#include "../structs/structs.h"
typedef struct move {
    int amazonid;
    int new_pos_h;
    int new_pos_w;
} _move;
int botLogic(Player* player, BOARD);
int botLogicSpecificAmazon(Player* player, BOARD, int existingh, int existingw, int amazonid);
int bot_throwObject(int objType, int fromRowNum, int fromColNum, BOARD, Player* player);
int botAmzPlace(Player* player,BOARD);
#endif
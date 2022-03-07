#include "../structs/structs.h"
#include "misc.h"

/**
 * @brief function that checks if specific amazon can make any move
 * 
 * @param col - column number (0 indexed)
 * @param row - row number (0 indexed)
* @param BOARD - Board structure
 * @return int - 1 if amazon can make minimal move, 0 if it can't
 */
int canAmazonMakeMinimalMove(int col, int row, BOARD){
    for (int r=row-1;r<=row+1;r++){
        for(int c=col-1;c<=col+1;c++){
            if (c!=col || r!=row){ //only if its a neighbour, not a amazon itself
                if (isCellFree(r, c, board)==1){
                    return 1;
                }
            }
        }
    }
    //if no cell was free
    return 0;
}


/**
 * @brief function that checks if any of the player's amazons can make a valid move
 * 
 * @param pId - player id
 * @param BOARD - Board structure
 * @return int - 1 if player can make at least one move, 0 if he can't
 */
int canPlayerMove(int pId, BOARD){
    for (int row=0;row<board->height;row++){
        for(int cell=0;cell<board->width;cell++){
            if (board->btable[row][cell].occupation == pId){
                //here is a cell with players amazon
                if (canAmazonMakeMinimalMove(cell, row, board)==1){
                    return 1;
                }
            }
        }
    }
    return 0;
}


/**
 * @brief function that checks if any of the players can make a valid move
 * 
 * @param p - list of the players
 * @param BOARD - Board structure
 * @return int - 1 if there exists a player that can make a valid move, 0 if there is no player that can make at least one valid move
 */
int canAnyPlayerMove(PlayerList *p, BOARD){
    for(int i=0;i<p->length;i++){
        //printf("pid: %d name:%s:\n", (*plist)[i].id, (*plist)[i].name);
        if (canPlayerMove(p->list[i].id, board) == 1){
            //player able to move found
            return 1;
        }
    }
    //no player is able to move
    return 0;
}
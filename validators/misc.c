#include "../structs/structs.h"

/**
 * @brief function that validates if given cell is within board boundaries
 * 
 * @param col - int, 0 indexed
 * @param row - int, 0 indexed
 * @param colMax - int 
 * @param rowMax - int
 * @return int 1 if cell is valid, 0 if it isn't
 */
int vc(int col, int row, int colMax, int rowMax){//validate Cell
    if (col>=0 && col<colMax && row>=0 && row<rowMax){
        //cell is valid (is on the board)
        return 1;
    }
    return 0;
}

/**
 * @brief function that checks if given cell is free (if there is no player or arrow)
 * 
 * @param rowNum - int - 0 indexed
 * @param colNum - int - 0 indexed
 * @return int 1 if cell is free, 0 if it is not
 */
int isCellFree(int rowNum, int colNum, BOARD){
    if (vc(colNum, rowNum, board->width, board->height)==1){
        if (board->btable[rowNum][colNum].occupation == 0){
            return 1;
        } 
    }
    return 0;
}

/**
 * @brief function that checks if given player id is in given cell
 * 
 * @param col - int, 0 indexed
 * @param row - int, 0 indexed
 * @param pid - player id
 * @return int 1 if player is an owner, 0 if he is't
 */
int isPlayerOwner(int col, int row, int pid, BOARD){
    if(board->btable[row][col].occupation == pid){
        return 1;
    }
    return 0;
}
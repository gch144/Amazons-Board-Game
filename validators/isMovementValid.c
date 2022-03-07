#include <stdlib.h>
#include "../structs/structs.h"



/**
 * @brief function that checks if movement is valid - checks if there are no obstacles on the way
 * 
 * @param fromCol - int, 0 indexed
 * @param fromRow - int, 0 indexed
 * @param toCol - int, 0 indexed
 * @param toRow - int, 0 indexed
 * @return int 0 if movement is not valid, 1 if it is
 */
int isMovementValid(int fromCol, int fromRow, int toCol, int toRow, BOARD){
    int rowDiff = abs(toRow-fromRow);
    int colDiff = abs(toCol-fromCol);

    if(rowDiff!=0 && colDiff!=0 && colDiff!=rowDiff){//its not vertical, horizontal or diagonal movement
        return 0;
    }

    if(rowDiff==0 && colDiff==0){//its not a movement!
        return 0;
    }

    //check if there are no obstacles on the way

    if(rowDiff==0){//horizontal movement
        int start, end;
        if(fromCol<toCol){
            start=fromCol;
            end=toCol;
        } else {
            start=toCol;
            end=fromCol;
        }

        int obstacles=0;
        for(int i=start;i<=end;i++){
            if(board->btable[toRow][i].occupation!=0){
                obstacles++;
            }
        }
        if (obstacles>1){
            return 0;
        }
    }

    if(colDiff==0){//horizontal movement
        int start, end;
        if(fromRow<toRow){
            start=fromRow;
            end=toRow;
        } else {
            start=toRow;
            end=fromRow;
        }

        int obstacles=0;
        for(int i=start;i<=end;i++){
            if(board->btable[i][toCol].occupation!=0){
                obstacles++;
            }
        }
        if (obstacles>1){
            return 0;
        }
    }

    //diagonal movement
    if (colDiff==rowDiff){
        int startCol, endCol, startRow, endRow;

        //align left to right
        if(fromCol<toCol){
            startCol=fromCol;
            startRow=fromRow;
            endCol=toCol;
            endRow=toRow;
        } else {
            startCol=toCol;
            startRow=toRow;
            endCol=fromCol;
            endRow=fromRow;
        }

        //there are 2 types of diagonal movement, like "/" or "\"
        if(startRow>endRow){// its "/"
            int obstacles=0;
            for(int i=0;i<=colDiff;i++){
                if(board->btable[startRow-i][startCol+i].occupation!=0){
                    obstacles++;
                }
            }
            if (obstacles>1){
                return 0;
            }
        } else {// its "\"
            int obstacles=0;
            for(int i=0;i<=colDiff;i++){
                if(board->btable[startRow+i][startCol+i].occupation!=0){
                    obstacles++;
                }
            }
            if (obstacles>1){
                return 0;
            }
        }
    }
    return 1;
}
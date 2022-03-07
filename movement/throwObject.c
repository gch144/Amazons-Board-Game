#include <stdio.h>
#include "../structs/structs.h"
#include "../validators/getCoords.h"
#include "../validators/isMovementValid.h"
#include "../validators/misc.h"
#include "../modifiers/occupation.h"

void throwObject(int objType, int fromRowNum, int fromColNum, BOARD, Player *player, int status){//first arg: 0-arrow, 1-spear //0 indexed
    switch(status){
        case 2:
            printf("\nincorrect! - please enter correct coordinates: ");
            break;
        case 3:
            printf("\nincorrect! - you cant shoot into cell that is already occupied - please enter correct coordinates: ");
            break;
        case 4:
            printf("\nincorrect! - you cant shoot only ortogonally or diagonally - please enter correct coordinates: ");
            break;
        default:
            switch(objType){
                case 1:
                    printf("\nPlayer %d - %s - Please enter coordinates of where you want to shoot your spear: ", player->id, player->name);
                    break;
                case 0:
                    printf("\nPlayer %d - %s - Please enter coordinates of where you want to shoot your arrow: ", player->id, player->name);
                    break;
            }
    }
    

    int toRowNum, toColNum;//1 indexed
    getCoords(&toRowNum, &toColNum, board->width, board->height);//1 indexed
    if (toRowNum==-1 || toColNum==-1){//1 indexed
        return throwObject(objType, fromRowNum, fromColNum, board, player, 2);
    }
    
    //switching to 0 index
    toRowNum--;
    toColNum--;
    

    //check if cell is free
    if(isCellFree(toRowNum, toColNum, board)==0){//0 indexed
        return throwObject(objType, fromRowNum, fromColNum, board, player, 3);
    }

    //check if movement is valid (only for arrow)
    if (objType==0){
        if(isMovementValid(fromColNum, fromRowNum, toColNum, toRowNum, board)==0){
            return throwObject(objType, fromRowNum, fromColNum, board, player, 4);
        }
    }
    
    //throw
    occupy(toRowNum, toColNum, 9, board);//3rd arg stands for "player id", here just 9 for arrow/spear
}
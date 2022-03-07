#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../structs/structs.h"
#include "./stats.h"
#include "Bot.h"
//#include "../validators/getCoords.h" //replaced by rand
#include "../validators/isMovementValid.h"
#include "../validators/misc.h"
#include "../modifiers/occupation.h"

int bot_throwObject(int objType, int fromRowNum, int fromColNum, BOARD, Player* player) {//first arg: 0-arrow, 1-spear 2-ArrowHorse
 


    _move* moves; int numofpossibleMoves = 0;

    moves = malloc(board->height * board->width * globalvar_TotalAmazonCountPerPlayer*sizeof(_move));


   

    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
        {
            if (objType == 1)
            {
                if (isCellFree(i, j, board))   //while this loop is continuing numofpossiblemoveschanges and acts like an index
                {
                    moves[numofpossibleMoves].amazonid = -1; //because we're throwing this time
                    moves[numofpossibleMoves].new_pos_h = i;    //+1 or no?
                    moves[numofpossibleMoves].new_pos_w = j;    //+1 or no?
                    numofpossibleMoves++;
                }
            }
            else if(objType==0)
            {
                if (isMovementValid(fromColNum, fromRowNum, j, i, board) && isCellFree(i, j, board))
                {
                    moves[numofpossibleMoves].amazonid = -1; //because we're throwing this time
                    moves[numofpossibleMoves].new_pos_h = i;    //+1 or no?
                    moves[numofpossibleMoves].new_pos_w = j;    //+1 or no?
                    numofpossibleMoves++;
                }
            }
            else if (objType == 2)  //ForArrow+Horse
            {
                if (isMovementValid(fromColNum, fromRowNum, j, i, board) && isCellFree(i, j, board))
                {
                    if (canAmazonMakeMinimalMove(i,j,board))        //checks if the amazon can make a move after shooting arrow because they have a horse
                    {
                        moves[numofpossibleMoves].amazonid = -1; //because we're throwing this time
                        moves[numofpossibleMoves].new_pos_h = i;    //+1 or no?
                        moves[numofpossibleMoves].new_pos_w = j;    //+1 or no?
                        numofpossibleMoves++;
                    }
                }
            }

        }
    }


    //randomly picking any of the possible throws
    if (numofpossibleMoves != 0)
    {
        srand(time(NULL));
        int indexofmoveChosen = (rand() % numofpossibleMoves);
        for (int i = 0, j = rand() % 3; i <= 2; i++) //to increase "randomness" or at least the sense of it
        {
            indexofmoveChosen = (rand() % numofpossibleMoves);
        }
        _move selectedMove = moves[indexofmoveChosen];
        free(moves); moves = NULL;

        occupy(selectedMove.new_pos_h, selectedMove.new_pos_w, 9, board);//3rd arg stands for "player id", here just 9 for arrow/spear
    }
    else
    {
        printf("No space for arrow! \n");
        return -3;
    }
    return 0;
}
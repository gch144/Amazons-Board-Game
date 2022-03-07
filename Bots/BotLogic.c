#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../structs/structs.h"
#include "../validators/misc.h"
#include "../validators/isMovementValid.h"
#include "Bot.h"
//#include "./validators/getCoords.h"
#include "../validators/canMove.h"
#include "../utils/utils.h"
#include "../outputs/printBoard.h"
#include "../modifiers/treasure.h"
#include "../modifiers/occupation.h"
#include "../modifiers/artifacts.h"
#include "Stats.h"             //change\merge here and in fillplayers to botlogic.h



int botLogic(Player* player, BOARD) 
{
    //Finding all amazons belonging to the bot
    _coords* amazons; amazons = malloc(globalvar_TotalAmazonCountPerPlayer*sizeof(_coords));        //FIXED Forgot to multiply by sizeof
    for (int i = 0,index=0; i < board->height||index>=globalvar_TotalAmazonCountPerPlayer; i++)
    {
        for (int j = 0; j < board->width; j++)
        {
            if (board->btable[i][j].occupation == player->id)           //should it be i+1?
            {
                amazons[index].pos_h = i;
                amazons[index].pos_w = j;
            }
        }
    }

    //Generating all possible moves
    if (canPlayerMove(player->id, board)==0)  //This should never be reached anyway because of checks in main.C
    {
        return -1;
    }



    _move* moves; 
    moves = malloc(board->height * board->width*globalvar_TotalAmazonCountPerPlayer*sizeof(_move));       

    int numofpossibleMoves = 0;

    for (int amz = 0; amz < globalvar_TotalAmazonCountPerPlayer; amz++)
    {
        if (canAmazonMakeMinimalMove(amazons[amz].pos_w, amazons[amz].pos_h, board)==0)
        {
            break;
        }
 
        for (int i = 0; i < board->height; i++)
        {
            for (int j = 0; j < board->width; j++)
            {  
                if ((isMovementValid(amazons[amz].pos_w,amazons[amz].pos_h,j,i,board)==1)&&(isCellFree(i,j,board)==1))   //while this loop is continuing numofpossiblemoveschanges and acts like an index
                {
                    if (canAmazonMakeMinimalMove(i, j, board))//checks if amazon can shoot from new position(especially for horses) //this function also works for shooting arrows
                    {
                        moves[numofpossibleMoves].amazonid = amz;
                        moves[numofpossibleMoves].new_pos_h = i;
                        moves[numofpossibleMoves].new_pos_w = j;
                        numofpossibleMoves++;
                    }
                }
            }
        }
    }

    if (numofpossibleMoves == 0)
    {
        return -3001;
    }


    //randomly picking any of the possible moves
    srand(time(NULL));
    int indexofmoveChosen=(rand() % numofpossibleMoves);
    for (int i = 0, j = rand() % 3; i <= 2; i++) //to increase "randomness" or at least the sense of it
    {
        indexofmoveChosen = (rand() % numofpossibleMoves);
    }
    _move selectedMove = moves[indexofmoveChosen];
    free(moves); moves = NULL;


    //plays one of the possible moves
    occupy(selectedMove.new_pos_h, selectedMove.new_pos_w , player->id, board);
    removeOccupation(amazons[selectedMove.amazonid].pos_h, amazons[selectedMove.amazonid].pos_w, board); //FIXED BY changing amazonid=amzn instead of amzn+1 above;
    free(amazons); amazons = NULL;


    //handle treasures
    int treasureValue = removeTreasureFromCell(selectedMove.new_pos_h, selectedMove.new_pos_w, board);//removes treasure from board and returns value of treasure 
    addTreasureToPlayer(player, treasureValue);


    //handle artifacts
    clrscr();
    int artifact = removeArtifactFromCell(selectedMove.new_pos_h, selectedMove.new_pos_w, board);//removes artifact from board and returns value of artifact 

    switch (artifact) {
    case 0://none
        bot_throwObject(0, selectedMove.new_pos_h, selectedMove.new_pos_w, board, player);//first arg: 0-arrow, 1-spear, 2-ArrowHorse
        break;
    case 1://horse (shoot an arrow and move again)
        bot_throwObject(2, selectedMove.new_pos_h, selectedMove.new_pos_w, board, player);//first arg: 0-arrow, 1-spear, 2-ArrowHorse
        clrscr();
        return botLogicSpecificAmazon(player,board,selectedMove.new_pos_h,selectedMove.new_pos_w, selectedMove.amazonid);  //Gives another move to player// make more elegant? //EDIT TO MAKE SURE THE SAME AMAZON IS MOVED ONLY
        break;
    case 2://broken arrow
        //nothing to do here
        break;
    case 3://spear
        bot_throwObject(1, selectedMove.new_pos_h, selectedMove.new_pos_w, board, player);//first arg: 0-arrow, 1-spear
        break;
    }
    return 0;
}













int botLogicSpecificAmazon(Player* player, BOARD, int existingh,int existingw,int amazonid)
{
    //Finding all amazons belonging to the bot
    _coords* amazons; amazons = malloc(globalvar_TotalAmazonCountPerPlayer * sizeof(_coords));        //FIXED Forgot to multiply by sizeof
    for (int i = 0, index = 0; i < board->height || index >= globalvar_TotalAmazonCountPerPlayer; i++)
    {
        for (int j = 0; j < board->width; j++)
        {
            if (board->btable[i][j].occupation == player->id)           //should it be i+1?
            {
                amazons[index].pos_h = i;
                amazons[index].pos_w = j;
            }
        }
    }

    //Generating all possible moves
    if (canPlayerMove(player->id, board) == 0)  //This should never be reached anyway because of checks in main.C
    {
        return -3001;
    }

    _move* moves; int numofpossibleMoves = 0;

    moves = malloc(board->height * board->width * globalvar_TotalAmazonCountPerPlayer * sizeof(_move));


    if (canAmazonMakeMinimalMove(existingw, existingh, board))
    {
        for (int i = 0; i < board->height; i++)
        {
            for (int j = 0; j < board->width; j++)
            {
                if ((isMovementValid(existingw,existingh, j, i, board) == 1) && (isCellFree(i, j, board) == 1))   //while this loop is continuing numofpossiblemoveschanges and acts like an index
                {
                    if ((isMovementValid(existingw,existingh, j, i, board) == 1) && (isCellFree(i, j, board) == 1))   //while this loop is continuing numofpossiblemoveschanges and acts like an index
                    {
                        if (canAmazonMakeMinimalMove(i, j, board))//checks if amazon can shoot from new position(especially for horses) //this function also works for shooting arrows
                        {
                            moves[numofpossibleMoves].amazonid = amazonid;
                            moves[numofpossibleMoves].new_pos_h = i;
                            moves[numofpossibleMoves].new_pos_w = j;
                            numofpossibleMoves++;
                        }
                    }
                }
            }
        }
    }
    else
    {
        return -3003; //-30003 means that the amazon attempted to be moved can't move again. It shouldn't be reached at all due to previous checks.
    }
       
    for (int i = 0; i < board->height; i++)
       {
            for (int j = 0; j < board->width; j++)
            {
                if ((isMovementValid(existingw,existingh, j, i, board) == 1) && (isCellFree(i, j, board) == 1))   //while this loop is continuing numofpossiblemoveschanges and acts like an index
                {
                    if (canAmazonMakeMinimalMove(i, j, board))//checks if amazon can shoot from new position(especially for horses) //this function (for amazons) also works for arrows
                    {
                        moves[numofpossibleMoves].amazonid = amazonid;
                        moves[numofpossibleMoves].new_pos_h = i;
                        moves[numofpossibleMoves].new_pos_w = j;
                        numofpossibleMoves++;
                    }
                }
            }
        }

    if (numofpossibleMoves == 0)
    {
        return -3001;
    }


    //randomly picking any of the possible moves
    srand(time(NULL));
    int indexofmoveChosen = (rand() % numofpossibleMoves);
    for (int i = 0, j = rand() % 3; i <= 2; i++) //to increase "randomness" or at least the sense of it
    {
        indexofmoveChosen = (rand() % numofpossibleMoves);
    }
    _move selectedMove = moves[indexofmoveChosen];
    free(moves); moves = NULL;


    //plays one of the possible moves
    occupy(selectedMove.new_pos_h, selectedMove.new_pos_w, player->id, board);
    removeOccupation(amazons[selectedMove.amazonid].pos_h, amazons[selectedMove.amazonid].pos_w, board); //FIXED BY changing amazonid=amzn instead of amzn+1 above;
    free(amazons); amazons = NULL;


    //handle treasures
    int treasureValue = removeTreasureFromCell(selectedMove.new_pos_h, selectedMove.new_pos_w, board);//removes treasure from board and returns value of treasure 
    addTreasureToPlayer(player, treasureValue);


    //handle artifacts
    clrscr();
    int artifact = removeArtifactFromCell(selectedMove.new_pos_h, selectedMove.new_pos_w, board);//removes artifact from board and returns value of artifact 

    switch (artifact) {
    case 0://none
        bot_throwObject(0, selectedMove.new_pos_h, selectedMove.new_pos_w, board, player);//first arg: 0-arrow, 1-spear, 2-ArrowHorse
        break;
    case 1://horse (shoot an arrow and move again)
        bot_throwObject(2, selectedMove.new_pos_h, selectedMove.new_pos_w, board, player);//first arg: 0-arrow, 1-spear, 2-ArrowHorse
        clrscr();//
        return botLogicSpecificAmazon(player, board, selectedMove.new_pos_h, selectedMove.new_pos_w,amazonid);  //Gives another move to player// make more elegant? //EDIT TO MAKE SURE THE SAME AMAZON IS MOVED ONLY
        break;
    case 2://broken arrow
        //nothing to do here
        break;
    case 3://spear
        bot_throwObject(1, selectedMove.new_pos_h, selectedMove.new_pos_w, board, player);//first arg: 0-arrow, 1-spear, 2-ArrowHorse
        break;
    }
    return 0;
}
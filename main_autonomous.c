#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs/structs.h"
#include "structs/structs.h"
#include "outputs/printBoard.h"
#include "validators/isMovementValid.h"
#include "validators/canMove.h"
#include "outputs/player.h"
#include "fileIO/fileOutput.h"
#include "fileIO/fileInput.h"
#include "Bots/Bot.h"
//#define DEBUG
#define FINAL


int main(int argc, char *argv[])
{
    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i], "name")==0)                                           //CHECKS IF THE PHASE IS SETTING NAME
        {         
            printf("%s\n", PLAYER_NICKNAME);                                     //SETS NICKNAME
            return 0;
        }
    }


    char * phase = strtok(argv[1], "=");
    phase = strtok(0, "=");
    printf( "phase: %s\n", phase );

    int amazons = 0;
    int inputArgumentIndex = 2;
    if (strcmp(phase, "placement") == 0) 
    {
        inputArgumentIndex++;

        char* amazonsStr = strtok(argv[2], "=");
        amazonsStr = strtok(0, "=");
        amazons = atoi(amazonsStr);

        printf("amazons: %d\n", amazons);
    }

    char * inputFileName = argv[inputArgumentIndex];
    printf( "inputFileName: %s\n", inputFileName );
    
    char * outputFileName = argv[inputArgumentIndex+1];
    printf( "outputFileName: %s\n", outputFileName );
    if (strcmp(inputFileName, outputFileName) != 0)
    {
        FILE* source, * target;
        source = fopen(inputFileName, "r");
        target = fopen(outputFileName, "w");
        char ch;
        while ((ch = fgetc(source)) != EOF)
            fputc(ch, target);
        fclose(source); fclose(target);
    }


    //board initialisation 
    Board board;
    int boardStatus = mapFileToBoardState(&board, inputFileName);
    if (boardStatus == 2)
    {
        saveStateToFile(&board, &players, outputFileName);
        return 2;
    }
    #ifdef DEBGUG
        printBoard(&board);
    #endif

    //players initialisation 
    PlayerList players;
    int playerState = mapFileToPlayerState(&players, inputFileName);
    if (playerState == 2) {
        saveStateToFile(&board, &players, outputFileName);
        return 2;
    }

    listPlayers(&players);


    Player* ourbot = &players.list[0];  //it's edited later.
    for (int i = 0; i < players.length; i++)
    {
        if (strcmp(players.list[i].name, PLAYER_NICKNAME) == 0)
        {
            ourbot = &players.list[i];
        }
    }

    if(strcmp(phase,"placement")==0)  //does actual placement
    {
        //is this correct way to decide number of amazons remaining?
        int amazonsplaced = 0;
        for (int i = 0; i < board.height; i++)              //earlier, this was board.width too which might have been the problem
        {
            for (int j = 0; j < board.width; i++)
            {
                if (board.btable[i][j].occupation == ourbot->id)
                {
                    amazonsplaced++;
                }
            }
        }
        ourbot->amazonsNotPlaced = (amazons - amazonsplaced);
        if (ourbot->amazonsNotPlaced == 0)
        {
            saveStateToFile(&board, &players, outputFileName);
            return -2009;
        }
        else
        {
            botAmzPlace(ourbot, &board);
            saveStateToFile(&board, &players, outputFileName);
            return 0;
        }
    }

        //ensuring that current player can move

    if (canPlayerMove(ourbot->id, &board) == 0)
    {
        #ifdef DEBUG
            printf("\nCan't move!\n");
        #endif
        saveStateToFile(&board, &players, outputFileName);
        return -3001;             //return code -3001 means that the autonomous player cannot move. This should only occur if the program handling the eexecution gives turn to the bot when it can't move.
    }
    botLogic(ourbot, &board);

    #ifdef DEBUG
      printf("\nMove made!\n");
    #endif
    
     saveStateToFile(&board, &players, outputFileName);

    return 0;
}

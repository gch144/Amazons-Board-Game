#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../structs/structs.h"
#include "../validators/misc.h"
#include "Bot.h"
//#include "../validators/getCoords.h"
#include "../validators/misc.h"
#include "../validators/canMove.h"
#include "../utils/utils.h"
#include "../outputs/printBoard.h"
#include "../modifiers/treasure.h"
#include "../modifiers/occupation.h"
#include "../modifiers/artifacts.h"      
#include "Stats.h"             



int botAmzPlace(Player* player, BOARD) {


    ////////////////////////////////////////////////////
    _coords* potentialplacements; potentialplacements = malloc(board->height * board->width*(sizeof(_coords)));

    int num_of_possible_placements=0;
    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
        {
            if (isCellFree(i, j, board))   //while this loop is continuing numofpossiblemoveschanges and acts like an index
            {
                   potentialplacements[num_of_possible_placements].pos_h = i;
                   potentialplacements[num_of_possible_placements].pos_w = j;
                   num_of_possible_placements++;
            }
        }
    }
    srand(time(NULL));
    int indexofmoveChosen = (rand() % num_of_possible_placements);
    for (int i = 0, j = rand() % 3; i <= 2; i++) //to increase "randomness" or at least the sense of it
    {
        indexofmoveChosen = (rand() % num_of_possible_placements);
    }
    _coords selectedPlace = potentialplacements[indexofmoveChosen];
    free(potentialplacements); potentialplacements = NULL;


    //occupy coordinates
    removeTreasuresAndArtifacts(selectedPlace.pos_h, selectedPlace.pos_w, board);     //remove treasures and artifacts
    occupy(selectedPlace.pos_h, selectedPlace.pos_w, player->id, board);          //occupy the cell with players id //FIXED!
    player->amazonsNotPlaced--;             //reduce players amazons left
    return 0;
}
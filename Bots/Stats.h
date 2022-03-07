#pragma once
#include <stdio.h>
#include "../structs/structs.h"
#include "../validators/misc.h"
#include "../validators/isMovementValid.h"
#include "../movement/throwObject.h"
#include "../validators/getCoords.h"
#include "../validators/canMove.h"
#include "../utils/utils.h"
#include "../outputs/printBoard.h"
#include "../modifiers/treasure.h"
#include "../modifiers/occupation.h"
#include "../modifiers/artifacts.h"


//global statistics;
int globalvar_TotalAmazonCountPerPlayer;
//int total_turns = 0;
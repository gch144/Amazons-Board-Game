#include <stdio.h>
#include "../structs/structs.h"
#include "../validators/misc.h"
#include "../validators/isMovementValid.h"
#include "../movement/throwObject.h"
#include "../validators/getCoords.h"  //edit this to proper headerfile
#include "../utils/utils.h"
#include "../outputs/printBoard.h"
#include "../modifiers/treasure.h"
#include "../modifiers/occupation.h"
#include "../modifiers/artifacts.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <math.h>

int botgetCoords(int* rowNum, int* colNum, int maxWidth, int maxHeight) {
    char coords[10];
    scanf("%s", coords);

    //validating cols
    if (coords[0] < 65 || coords[0]>65 + maxWidth) {
        //column out of range
        *rowNum = -1;
        *colNum = -1;
        return 1;
    }
    *colNum = coords[0] - 64;


    //counting and validating row
    int numLen = 0;
    for (int i = 1; i < 10; i++) {
        if (coords[i] == 0) {
            break;
        }
        if (coords[i] < 48 || coords[i]>57) {
            //row is not a number
            *rowNum = -1;
            *colNum = -1;
            return 1;
        }
        numLen++;
    }

    //converting inputter string to number (row)
    *rowNum = 0;
    for (int i = 1; i <= numLen; i++) {
        *rowNum += (int)((pow(10, numLen - i) * (coords[i] - 48)));
    }

    //validating row
    if (*rowNum<1 || *rowNum>maxHeight) {
        *rowNum = -1;
        *colNum = -1;
        return 1;
    }
    else
    {
        return -1;
    }
}
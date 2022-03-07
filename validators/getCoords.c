#include <stdio.h>
#include <math.h>


/**
 * @brief function that reads and validates user input
 * 
 * @param rowNum - int, 0 indexed
 * @param colNum - int, 0 indexed
 * @param maxWidth - int
 * @param maxHeight - int
 * @return int 1 if user input was not correct
 */
int getCoords(int *rowNum, int *colNum, int maxWidth, int maxHeight){
    char coords[10];
    scanf("%s", coords);

    //validating cols
    if (coords[0]<'A' || coords[0]>'A'+maxWidth){
        //column out of range
        *rowNum=-1;
        *colNum=-1;
        return 1;
    }
    *colNum=coords[0]-'A'+1;


    //counting and validating row
    int numLen = 0;
    for(int i=1;i<10;i++){
        if(coords[i]==0){
            break;
        } 
        if(coords[i]<'0' || coords[i]>'9'){
            //row is not a number
            *rowNum=-1;
            *colNum=-1;
            return 1;
        }
        numLen++;
    }

    //converting inputter string to number (row)
    *rowNum=0;
    for(int i=1;i<=numLen;i++){
        *rowNum+= (pow(10, numLen-i) * (coords[i]-'0'));
    }

    //validating row
    if (*rowNum<1 || *rowNum>maxHeight){
        *rowNum=-1;
        *colNum=-1;
        return 1;
    }
}
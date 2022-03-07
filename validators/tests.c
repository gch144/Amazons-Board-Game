#include <assert.h>
#include <stdlib.h>
#include "../structs/structs.h"
#include "./misc.h"
#include "./canMove.h"

int testValidators(){

Board board;
board.height=5;
board.width=10;
board.btable = malloc(sizeof(Cell) * board.height);

for (int row=0;row<board.height;row++){
    board.btable[row] = malloc(sizeof(Cell) * board.width);
}

///// misc.c functions /////

//vc function
assert(vc(1, 1, 2, 2)==1);
assert(vc(3, 7, 4, 8)==1);
assert(vc(2, 4, 5, 10)==1);
assert(vc(0, 0, 1, 1)==1);
assert(vc(1, 1, 1, 1)==0);
assert(vc(-1, 1, 1, 1)==0);
assert(vc(-1, -2, 1, 1)==0);
assert(vc(5, 1, 3, 2)==0);
assert(vc(5, 6, 2, 3)==0);

//isCellFree function
board.btable[0][2].occupation = 4;
board.btable[1][5].occupation = 0;

assert(isCellFree(40, 50, &board)==0);
assert(isCellFree(5, -1, &board)==0);
assert(isCellFree(5, -1, &board)==0);
assert(isCellFree(0, 2, &board)==0);
assert(isCellFree(1, 5, &board)==1);

//isPlayerOwner function
board.btable[4][7].occupation = 4;
board.btable[4][8].occupation = 5;
assert(isPlayerOwner(7, 4, 4,  &board)==1);
assert(isPlayerOwner(8, 4, 4,  &board)==0);


///// canMove.c functions /////

//canAmazonMakeMinimalMove function
board.btable[0][0].occupation = 2;
board.btable[0][1].occupation = 2;
board.btable[0][2].occupation = 2;

board.btable[1][0].occupation = 2;
board.btable[1][1].occupation = 1;
board.btable[1][2].occupation = 2;

board.btable[2][0].occupation = 2;
board.btable[2][1].occupation = 2;
board.btable[2][2].occupation = 2;

assert(canAmazonMakeMinimalMove(1, 1, &board)==0);

board.btable[1][2].occupation = 0;
assert(canAmazonMakeMinimalMove(1, 1, &board)==1);

board.btable[1][2].occupation = 2;
board.btable[0][2].occupation = 0;
assert(canAmazonMakeMinimalMove(1, 1, &board)==1);

board.btable[0][0].occupation = 1;
board.btable[0][1].occupation = 2;
board.btable[1][0].occupation = 2;
board.btable[1][1].occupation = 2;
assert(canAmazonMakeMinimalMove(0, 0, &board)==0);

board.btable[1][1].occupation = 0;
assert(canAmazonMakeMinimalMove(0, 0, &board)==1);

return 1;
}
#ifndef CANMOVE_H
#define CANMOVE_H

int canAmazonMakeMinimalMove(int col, int row, Board *board);
int canPlayerMove(int pId, Board *board);
int canAnyPlayerMove(PlayerList *p, Board *board);

#endif // !CANMOVE_H
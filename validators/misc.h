#ifndef MISC_H
#define MISC_H

int isCellFree(int rowNum, int colNum, Board *board);
int vc(int col, int row, int colMax, int rowMax);
int isPlayerOwner(int col, int row, int pid, Board *board);

#endif // !MISC_H

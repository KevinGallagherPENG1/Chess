#include "defs.h"

//Returns 1 if square is on board
int SqOnBoard(const int sq){
    return FilesBrd[sq] == OFFBOARD? 0 : 1;
}

//Returns 1 if side is valid
int SideValid(const int side){
    return(side == WHITE || side == BLACK) ? 1 : 0;
}

//Returns 1 if file / rank is valid
int FileRankValid(const int fr){
    return (fr >= 0 && fr <= 7) ? 1 : 0;
}

//Returns 1 if piece value is greater than empty
int PieceValidEmpty(const int pce){
    return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

//Returns 1 if piece value is greater than a pawn
int PieceValid(const int pce){
    return (pce >= wP && pce <= bK) ? 1 : 0;
}

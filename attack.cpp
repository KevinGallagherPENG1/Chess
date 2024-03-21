#include "defs.h"

//These correspond to the positions that each piece can move to (horizontal, vertical, diagonal, etc)
const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

//Takes in square, which side is attacking, and the board, returns if that specific square is being attacked by any piece
int SqAttacked(const int sq, const int side, const S_BOARD *pos){
    int pce, index, t_sq, dir;

    //Pawns
    if(side == WHITE){
        //Check diagonal above sq to see if pawn is there
        if(pos->pieces[sq - 11] == wP || pos->pieces[sq - 9] == wP)
            return TRUE;    
    } else{
        //Similarly for black side, except addition in this case
        if(pos->pieces[sq + 11] == bP || pos->pieces[sq + 9] == bP)
            return TRUE;
    }

    //Knights
    for(index = 0; index < 8; index++){
        //Find piece that is on the board on all the possible positions that an attacking knight could be on
        pce = pos->pieces[sq + KnDir[index]];
        //Find if that pce is a knight and if that piece color is equal to the side
        if(IsKn(pce) && PieceCol[pce] == side)
            return true;
    }

    //Rooks, queen
    for(index = 0; index < 4; index++){
        //Get current direction
        dir = RkDir[index];
        //Temp square to hold direction of attack
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];

        //While that position isnt offboard or empty
        while(pce != OFFBOARD){
            if(pce != EMPTY){
                //If that piece is a rook or a queen, return TRUE
                if(IsRQ(pce) && PieceCol[pce] == side)
                    return TRUE;
                break;
            }
            //Otherwise, continue on
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    //Bishops, queen
    for(index = 0; index < 4; index++){
        //Get current direction
        dir = BiDir[index];
        //Temp square to hold direction of attack
        t_sq = sq + dir;
        pce = pos->pieces[t_sq];

        //While that position isnt offboard or empty
        while(pce != OFFBOARD){
            if(pce != EMPTY){
                //If that piece is a bishop or queen, return TRUE
                if(IsBQ(pce) && PieceCol[pce] == side)
                    return TRUE;
                break;
            }
            //Otherwise, continue on
            t_sq += dir;
            pce = pos->pieces[t_sq];
        }
    }

    //King
    for(index = 0; index < 8; index++){
        //Get all possible pieces that could be a king attacking the square
        pce = pos->pieces[sq + KiDir[index]];
        if(IsKi(pce) && PieceCol[pce] == side)
            return TRUE;
    }

    //Nothing is attacking square
    return FALSE;


}

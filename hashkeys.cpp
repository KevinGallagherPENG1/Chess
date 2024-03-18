#include "defs.h"
#include "stdio.h"

U64 GeneratePosKey(const S_BOARD *pos){
    //With a pointer to the position on the board, we will generate a unique key for that position

    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    //pieces
    //For every piece on the board, set the piece array equal to what that square is
    for(sq = 0; sq < BRD_SQ_NUM; sq++){
        piece = pos->pieces[sq];

        //If piece is a part of the actual board and it isnt empty
        if(piece != NO_SQ && piece != EMPTY && piece != OFFBOARD){
            //Make sure the piece is a legal piece
            ASSERT(piece >= wP && piece <= bK);
            //Hash in whatever number is in the PieceKeys array
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    //Hash in what side it is
    if(pos->side == WHITE)
        finalKey ^= SideKey;
    
    //Hash in if the enPas square is set
    if(pos->enPas != NO_SQ){
        //Make sure the enPas square is a legal board place
        ASSERT(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);
        //Hash in the enPas square
        finalKey ^= PieceKeys[EMPTY][pos->enPas];
    }

    //Make sure castle perm is legal
    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    //Hash in castle perms
    finalKey ^= CastleKeys[pos->castlePerm];

    return finalKey;
}
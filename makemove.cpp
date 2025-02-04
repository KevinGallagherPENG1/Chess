<<<<<<< HEAD
#include "stdio.h"
#include "defs.h"
=======
#include "defs.h"
#include "stdio.h"
>>>>>>> master

#define HASH_PCE(pce, sq) (pos->posKey ^= (PieceKeys[(pce)][(sq)]))
#define HASH_CA (pos->posKey ^= (CastleKeys[(pos->castlePerm)]))
#define HASH_SIDE (pos->posKey ^= (SideKey))
#define HASH_EP (pos->posKey ^= (PieceKeys[EMPTY][(pos->enPas)]))

<<<<<<< HEAD
=======

//Castling perms are 1111 (15 in decimal)
//& with castle perm will help determine if permissions still exist for each side
//Each bit will be taken out if and when needed
>>>>>>> master
const int CastlePerm[120] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

<<<<<<< HEAD
static void ClearPiece(const int sq, S_BOARD *pos){
    ASSERT(SqOnBoard(sq));

    int pce = pos->pieces[sq];

    ASSERT(PieceValid(pce));

    int col = PieceCol[pce];
    int index = 0;
    int t_pceNum = -1;

    //Hash pce and sq out of poskey
    HASH_PCE(pce, sq);

    pos->pieces[sq] = EMPTY;
    pos->material[col] -= PieceVal[pce];

    if(PieceBig[pce]){
            pos->bigPce[col]--;
        if(PieceMaj[pce]){
            pos->majPce[col]--;
        } else { 
            pos->minPce[col]--;
        }
    } else {
=======
//Clears a piece from the board
static void ClearPiece(const int sq, S_BOARD *pos){
    printf("\nPASSED sq:%d\n", sq);
    ASSERT(SqOnBoard(sq));
    ASSERT(CheckBoard(pos));

    printf("\n\nSQUARE:%s\n", PrSq(sq));

    //Get piece
    int pce = pos->pieces[sq];

    printf("\nPCE:%d\n", pce);

    ASSERT(PieceValid(pce));

    int col = PieceCol[pce];        //Color of piece
    int index = 0;                  
    int t_pceNum = -1;              //Used for piece lists

    ASSERT(SideValid(col));

    HASH_PCE(pce, sq);

    //Remove piece from square
    pos->pieces[sq] = EMPTY;
    //Remove score of piece from material score
    pos->material[col] -= PieceVal[pce];

    //See what type of piece the piece is
    if(PieceBig[pce]){
        pos->bigPce[col]--;
        if(PieceMaj[pce]){
            pos->majPce[col]--;
        } else {
            pos->minPce[col]--;
        }
    } else { //Its a pawn
>>>>>>> master
        CLRBIT(pos->pawns[col], SQ64(sq));
        CLRBIT(pos->pawns[BOTH], SQ64(sq));
    }

<<<<<<< HEAD
    //Remove pce from pList
    //Find pce
=======
    /*
        pos->pceNum[wP] == 5    //looping from 0 to 4
        pos->pList[pce][0] = sq0
        pos->pList[pce][1] = sq1
        pos->pList[pce][2] = sq2
        pos->pList[pce][3] = sq3
        pos->pList[pce][4] = sq4

        sq == sq3, so t_pceNum = 3
    */
>>>>>>> master
    for(index = 0; index < pos->pceNum[pce]; ++index){
        if(pos->pList[pce][index] == sq){
            t_pceNum = index;
            break;
        }
    }

    ASSERT(t_pceNum != -1);
<<<<<<< HEAD

    //Remove pceNum of pce and shift up the rest of the array
    pos->pceNum[pce]--;
    pos->pList[pce][t_pceNum] = pos->pList[pce][pos->pceNum[pce]];
}

static void AddPiece(const int sq, S_BOARD *pos, const int pce){
    ASSERT(PieceValid(pce));
    ASSERT(SqOnBoard(sq));

    int col = PieceCol[pce];

    HASH_PCE(pce, sq);
    
    pos->pieces[sq] = pce;

    if(PieceBig[pce]){
            pos->bigPce[col]++;
=======
    ASSERT(t_pceNum >= 0 && t_pceNum < 10);

    pos->pceNum[pce]--;     //pos->pceNum[wP] == 4
    pos->pList[pce][t_pceNum] = pos->pList[pce][pos->pceNum[pce]];      //pos->pList[wP][3] = pos->pList[wP][4] = sq4

    /*
        pos->pceNum[wP] == 5    //looping from 0 to 4
        pos->pList[pce][0] = sq0
        pos->pList[pce][1] = sq1
        pos->pList[pce][2] = sq2
        pos->pList[pce][3] = sq4
        //sq3 got removed
    */
}

static void AddPiece(const int sq, S_BOARD *pos, const int pce){
    ASSERT(SqOnBoard(sq));
    ASSERT(PieceValid(pce));

    int col = PieceCol[pce];

    ASSERT(SideValid(col));

    HASH_PCE(pce, sq);

    pos->pieces[sq] = pce;

    //See what type of piece the piece is
    if(PieceBig[pce]){
        pos->bigPce[col]++;
>>>>>>> master
        if(PieceMaj[pce]){
            pos->majPce[col]++;
        } else {
            pos->minPce[col]++;
        }
<<<<<<< HEAD
    } else {
        SETBIT(pos->pawns[col], SQ64(sq));
        SETBIT(pos->pawns[BOTH], SQ64(sq));
    }

    pos->material[col] += PieceVal[pce];
    pos->pList[pce][pos->pceNum[pce]++] = sq;
=======
    } else { //Its a pawn
        SETBIT(pos->pawns[col], SQ64(sq));
        SETBIT(pos->pawns[BOTH], SQ64(sq));
    }
    pos->material[col] += PieceVal[pce];
    pos->pList[pce][pos->pceNum[pce]++] = sq;           //@@ ??
>>>>>>> master
}

static void MovePiece(const int from, const int to, S_BOARD *pos){
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));

    int index = 0;
    int pce = pos->pieces[from];
    int col = PieceCol[pce];

<<<<<<< HEAD
#ifdef DEBUG
    int t_PieceNum = FALSE;
#endif
=======
    ASSERT(SideValid(col));
    ASSERT(PieceValid(pce));

    #ifdef DEBUG
    int t_PieceNum = FALSE;
    #endif
>>>>>>> master

    HASH_PCE(pce, from);
    pos->pieces[from] = EMPTY;

    HASH_PCE(pce, to);
    pos->pieces[to] = pce;

    if(!PieceBig[pce]){
        CLRBIT(pos->pawns[col], SQ64(from));
        CLRBIT(pos->pawns[BOTH], SQ64(from));
        SETBIT(pos->pawns[col], SQ64(to));
        SETBIT(pos->pawns[BOTH], SQ64(to));
    }

<<<<<<< HEAD
    for(index = 0; index < pos->pceNum[pce]; ++index){
        if(pos->pList[pce][index] == from){
            pos->pList[pce][index] = to;
#ifdef DEBUG
            t_PieceNum = TRUE;
#endif  
=======
    //Cycle through all of those pieces and move the specific piece
    for(index = 0; index < pos->pceNum[pce]; ++index){
        if(pos->pList[pce][index] == from){
            pos->pList[pce][index] = to;
            #ifdef DEBUG
            t_PieceNum = TRUE;
            #endif
>>>>>>> master
            break;
        }
    }
    ASSERT(t_PieceNum);
}

int MakeMove(S_BOARD *pos, int move){
    ASSERT(CheckBoard(pos));

    int from = FROMSQ(move);
    int to = TOSQ(move);
    int side = pos->side;

    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
<<<<<<< HEAD
    ASSERT(SideValid(side));
    ASSERT(PieceValid(pos->pieces[from]));

    //Update history
    pos->history[pos->hisPly].posKey = pos->posKey;

    if(move & MFLAGEP){
        if(side == WHITE){
            ClearPiece((to - 10), pos);
        } else {
=======
    ASSERT(SideValid(side));   
    ASSERT(PieceValid(pos->pieces[from]));
    ASSERT(pos->hisPly >= 0 && pos->hisPly < MAXGAMEMOVES);
	//ASSERT(pos->ply >= 0 && pos->ply < MAXDEPTH);

    pos->history[pos->hisPly].posKey = pos->posKey;

    //En passant move
    if(move & MFLAGEP){
        if(side == WHITE){
            printf("\n1\n");
            ClearPiece((to - 10), pos);
        } else {
            printf("\n2\n");
>>>>>>> master
            ClearPiece((to + 10), pos);
        }
    } else if(move & MFLAGCA){
        switch(to){
            case C1:    MovePiece(A1, D1, pos);     break;
            case C8:    MovePiece(A8, D8, pos);     break;
            case G1:    MovePiece(H1, F1, pos);     break;
            case G8:    MovePiece(H8, F8, pos);     break;
<<<<<<< HEAD
            default:    ASSERT(FALSE);              break;      //This means to square is wrong.
        }
    } 

    if(pos->enPas != NO_SQ)
        HASH_EP;
    
    HASH_CA;
=======
            default:    ASSERT(FALSE);              break;
        }
    }

    if(pos->enPas != NO_SQ) HASH_EP;        //Hash out En Passant
    HASH_CA;                                //Hash out castle
>>>>>>> master

    pos->history[pos->hisPly].move = move;
    pos->history[pos->hisPly].fiftyMove = pos->fiftyMove;
    pos->history[pos->hisPly].enPas = pos->enPas;
    pos->history[pos->hisPly].castlePerm = pos->castlePerm;

    pos->castlePerm &= CastlePerm[from];
    pos->castlePerm &= CastlePerm[to];
    pos->enPas = NO_SQ;

<<<<<<< HEAD
    HASH_CA;
=======
    HASH_CA;                                //Hash in castle perms


>>>>>>> master

    int captured = CAPTURED(move);
    pos->fiftyMove++;

<<<<<<< HEAD
=======
    //@@ERRORS???
>>>>>>> master
    if(captured != EMPTY){
        ASSERT(PieceValid(captured));
        ClearPiece(to, pos);
        pos->fiftyMove = 0;
<<<<<<< HEAD
   }

   pos->hisPly++;
   pos->ply++;

   if(PiecePawn[pos->pieces[from]]){
    pos->fiftyMove = 0;
    if(move & MFLAGPS){
        if(side == WHITE){
            pos->enPas = from + 10;
            ASSERT(RanksBrd[pos->enPas] == RANK_3);
        } else {
            pos->enPas = from - 10;
            ASSERT(RanksBrd[pos->enPas] == RANK_6);
        }
        HASH_EP;
    }
   }

   MovePiece(from, to, pos);

   int prPce = PROMOTED(move);
   if(prPce != EMPTY){
    ASSERT(PieceValid(prPce) && !PiecePawn[prPce]);
    ClearPiece(to, pos);
    AddPiece(to, pos, prPce);
   }

   if(PieceKing[pos->pieces[to]]){
    pos->KingSq[pos->side] = to;
   }

   pos->side ^= 1;
   HASH_SIDE;

   ASSERT(CheckBoard(pos));

   if(SqAttacked(pos->KingSq[side], pos->side, pos)){
    TakeMove(pos);
    return FALSE;
   }

   return TRUE;
=======
    }

    pos->hisPly++;
    pos->ply++;

    ASSERT(pos->hisPly >= 0 && pos->hisPly < MAXGAMEMOVES);
	//ASSERT(pos->ply >= 0 && pos->ply < MAXDEPTH);

    if(PiecePawn[pos->pieces[from]]){
        pos->fiftyMove = 0;
        if(move & MFLAGPS){
            if(side == WHITE){
                pos->enPas = from + 10;     //Set en pas square
                ASSERT(RanksBrd[pos->enPas] == RANK_3);
            } else {
                pos->enPas = from - 10;
                ASSERT(RanksBrd[pos->enPas] == RANK_6);
            }
            HASH_EP;
        }
    }

    MovePiece(from , to, pos);
    
    int prPce = PROMOTED(move);

    if(prPce != EMPTY){
        ASSERT(PieceValid(prPce) && !PiecePawn[prPce]);
        printf("\n4\n");
        ClearPiece(to, pos);
        AddPiece(to, pos, prPce);
    }

    if(PieceKing[pos->pieces[to]]){
        pos->KingSq[pos->side] = to;
    }

    //Changes side
    pos->side ^= 1;
    HASH_SIDE;

    ASSERT(CheckBoard(pos));

    //If the previous side left their king in check, THATS BAD! Remove this move :(
    if(SqAttacked(pos->KingSq[side], pos->side, pos)){
        TakeMove(pos);
        return FALSE;
    }

    return TRUE;
>>>>>>> master
}

void TakeMove(S_BOARD *pos){
    ASSERT(CheckBoard(pos));

    pos->hisPly--;
    pos->ply--;

<<<<<<< HEAD
=======
    ASSERT(pos->hisPly >= 0 && pos->hisPly < MAXGAMEMOVES);
	//ASSERT(pos->ply >= 0 && pos->ply < MAXDEPTH);

>>>>>>> master
    int move = pos->history[pos->hisPly].move;
    int from = FROMSQ(move);
    int to = TOSQ(move);

    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));

    if(pos->enPas != NO_SQ) HASH_EP;
    HASH_CA;

    pos->castlePerm = pos->history[pos->hisPly].castlePerm;
    pos->fiftyMove = pos->history[pos->hisPly].fiftyMove;
    pos->enPas = pos->history[pos->hisPly].enPas;

    if(pos->enPas != NO_SQ) HASH_EP;
    HASH_CA;

    pos->side ^= 1;
    HASH_SIDE;

<<<<<<< HEAD
    
    if(move & MFLAGEP){
        if(pos->side == WHITE){
            AddPiece((to - 10), pos, bP);
        } else {
            AddPiece((to + 10), pos, wP);
        }
    } else if(move & MFLAGCA){
=======
    if(MFLAGEP & move){
        if(pos->side == WHITE){
            AddPiece(to - 10, pos, bP);
        } else {
            AddPiece(to + 10, pos, wP);
        }
    } else if(MFLAGCA & move){
>>>>>>> master
        switch(to){
            case C1:    MovePiece(D1, A1, pos);     break;
            case C8:    MovePiece(D8, A8, pos);     break;
            case G1:    MovePiece(F1, H1, pos);     break;
            case G8:    MovePiece(F8, H8, pos);     break;
<<<<<<< HEAD
            default:    ASSERT(FALSE);              break;      //This means to square is wrong.
        }
    } 
=======
            default:    ASSERT(FALSE);              break;
        }
    }
>>>>>>> master

    MovePiece(to, from, pos);

    if(PieceKing[pos->pieces[from]]){
        pos->KingSq[pos->side] = from;
    }

    int captured = CAPTURED(move);
    if(captured != EMPTY){
        ASSERT(PieceValid(captured));
        AddPiece(to, pos, captured);
    }

    if(PROMOTED(move) != EMPTY){
        ASSERT(PieceValid(PROMOTED(move)) && !PiecePawn[PROMOTED(move)]);
<<<<<<< HEAD
        ClearPiece(from, pos);
        AddPiece(from, pos, (PieceCol[PROMOTED(move)] == WHITE ? wP : bP));
    }

=======
        printf("\n5\n");
        ClearPiece(from, pos);
        AddPiece(from, pos, (PieceCol[PROMOTED(move)] == WHITE ? wP : bP));
    }
>>>>>>> master
    ASSERT(CheckBoard(pos));
}
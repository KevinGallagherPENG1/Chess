#include "stdio.h"
#include "defs.h"

<<<<<<< HEAD
#define MOVE(f,t,ca,pro,fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFFBOARD)

const int LoopSlidePiece[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
const int LoopSlideIndex[2] = {0, 4};
const int LoopNonSlidePiece[6] = {wN, wK, 0, bN, bK, 0};
const int LoopNonSlideIndex[2] = {0, 3};

const int PceDir[13][8] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {-8, -19, -21, -12, 8, 19, 21, 12},
    {-9, -11, 11, 9, 0, 0, 0, 0},
    {-1, -10, 1, 10, 0, 0, 0, 0},
    {-1, -10, 1, 10, -9, -11, 11, 9},
    {-1, -10, 1, 10, -9, -11, 11, 9},
    {0, 0, 0, 0, 0, 0},
    {-8, -19, -21, -12, 8, 19, 21, 12},
    {-9, -11, 11, 9, 0, 0, 0, 0},
    {-1, -10, 1, 10, 0, 0, 0, 0},
    {-1, -10, 1, 10, -9, -11, 11, 9},
    {-1, -10, 1, 10, -9, -11, 11, 9}
};

const int NumDir[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

//Adds a non capture move to the movelist
static void AddQuietMove(const S_BOARD *pos, int move, S_MOVELIST *list){
=======
//Generates moves!

#define MOVE(f,t,ca,pro,fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))
#define SQOFFBOARD(sq) (FilesBrd[sq] == OFFBOARD)

const int LoopSlidePce[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
const int LoopSlideIndex[2] = {0, 4};
const int LoopNonSlidePce[6] = {wN, wK, 0, bN, bK, 0};
const int LoopNonSlideIndex[2] = {0, 3};

//Holds directions of each possible move a piece can make, indexed by piece type and direction
const int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

//How many directions a piece has
const int NumDir[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};


//No captures
static void AddQuietMove(const S_BOARD *pos, int move, S_MOVELIST *list){
    ASSERT(SqOnBoard(FROMSQ(move)));
    ASSERT(SqOnBoard(TOSQ(move)));
    ASSERT(CheckBoard(pos));
    //ASSERT(pos->ply >= 0 && pos->ply < MAXDEPTH);
    
>>>>>>> master
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

<<<<<<< HEAD
//Adds a capture move to the movelist
static void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list){
=======
//Caputures a piece
static void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list){
    ASSERT(SqOnBoard(FROMSQ(move)));
    ASSERT(SqOnBoard(TOSQ(move)));
    ASSERT(PieceValid(CAPTURED(move)));
	ASSERT(CheckBoard(pos));

>>>>>>> master
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

<<<<<<< HEAD
//Adds an En Passant move to the movelist
static void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list){
=======
static void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list){
    ASSERT(SqOnBoard(FROMSQ(move)));
    ASSERT(SqOnBoard(TOSQ(move)));
    ASSERT(CheckBoard(pos));
	ASSERT((RanksBrd[TOSQ(move)]==RANK_6 && pos->side == WHITE) || (RanksBrd[TOSQ(move)]==RANK_3 && pos->side == BLACK));


>>>>>>> master
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

static void AddWhitePawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list){
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
<<<<<<< HEAD
=======
    ASSERT(CheckBoard(pos));
>>>>>>> master

    if(RanksBrd[from] == RANK_7){
        AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
<<<<<<< HEAD
    } else {
=======
    } else { 
>>>>>>> master
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

static void AddWhitePawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list){
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
<<<<<<< HEAD
=======
    ASSERT(CheckBoard(pos));
>>>>>>> master

    if(RanksBrd[from] == RANK_7){
        AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
<<<<<<< HEAD
    } else {
=======
    } else { 
>>>>>>> master
        AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

static void AddBlackPawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list){
    ASSERT(PieceValidEmpty(cap));
<<<<<<< HEAD
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
=======
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));
>>>>>>> master

    if(RanksBrd[from] == RANK_2){
        AddCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
<<<<<<< HEAD
    } else {
=======
    } else { 
>>>>>>> master
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

static void AddBlackPawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list){
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));
<<<<<<< HEAD
=======
    ASSERT(CheckBoard(pos));
>>>>>>> master

    if(RanksBrd[from] == RANK_2){
        AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
<<<<<<< HEAD
    } else {
=======
    } else { 
>>>>>>> master
        AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list){
<<<<<<< HEAD
    ASSERT(CheckBoard(pos));
    
    list->count = 0;
    
    int pce = EMPTY;
    int side = pos->side;
    int sq = 0; int t_sq = 0;
    int pceNum = 0;
    int dir = 0;
    int index = 0;
    int pceIndex = 0;

    if(side == WHITE){
        //Loop through all white pawns
        for(pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum){
            sq = pos->pList[wP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Basic move and starting double move
            if(pos->pieces[sq + 10] == EMPTY){
                AddWhitePawnMove(pos, sq, (sq + 10), list);
=======
   ASSERT(CheckBoard(pos));

   list->count = 0;

   int pce = EMPTY;
   int side = pos->side;
   int sq = 0; 
   int t_sq = 0;
   int pceNum = 0;
   int dir = 0;
   int index = 0;
   int pceIndex = 0;


   if(side == WHITE){
        //Loop through each white pawn
        for(pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum){
            //Find what square pawn is on
            sq = pos->pList[wP][pceNum];
            ASSERT(SqOnBoard(sq));

            //If the square ahead of the pawn is empty
            if(pos->pieces[sq + 10] == EMPTY){
                AddWhitePawnMove(pos, sq, (sq + 10), list);
                //If is a pawn start, pawn can jump two squares
>>>>>>> master
                if(RanksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY){
                    AddQuietMove(pos, MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), list);
                }
            }

<<<<<<< HEAD
            //Regular diagonal capture moves
            if(!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK){
                AddWhitePawnCapMove(pos, sq, (sq + 9), pos->pieces[sq + 9], list);
            }
=======
            //Pawns capture diagonally, check if piece is ONBOARD and is BLACK
            if(!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK){
                AddWhitePawnCapMove(pos, sq, (sq + 9), pos->pieces[sq + 9], list);
            }

>>>>>>> master
            if(!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK){
                AddWhitePawnCapMove(pos, sq, (sq + 11), pos->pieces[sq + 11], list);
            }

<<<<<<< HEAD
            //En Passant Moves
            //@@ CHECK THE CAP IN MOVE FOR ERRATA
            if(sq + 9 == pos->enPas){
                AddEnPassantMove(pos, MOVE(sq, (sq + 9), EMPTY, EMPTY, MFLAGEP), list);
            }

            if(sq + 11 == pos->enPas){
                AddEnPassantMove(pos, MOVE(sq, (sq + 11), EMPTY, EMPTY, MFLAGEP), list);
            }

=======
            //En passant moves
            if(pos->enPas != NO_SQ){
                if(sq + 9 == pos->enPas){
                    AddEnPassantMove(pos, MOVE(sq, sq + 9, EMPTY, EMPTY, MFLAGEP), list);
                }
                if(sq + 11 == pos->enPas){
                    AddEnPassantMove(pos, MOVE(sq, sq + 11, EMPTY, EMPTY, MFLAGEP), list);
                }
            }
>>>>>>> master
        }

        //Castling
        if(pos->castlePerm & WKCA){
            if(pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY){
                if(!SqAttacked(E1, BLACK, pos) && !SqAttacked(F1, BLACK, pos)){
                    AddQuietMove(pos, MOVE(E1, G1, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }
<<<<<<< HEAD
=======

>>>>>>> master
        if(pos->castlePerm & WQCA){
            if(pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY){
                if(!SqAttacked(E1, BLACK, pos) && !SqAttacked(D1, BLACK, pos)){
                    AddQuietMove(pos, MOVE(E1, C1, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }


<<<<<<< HEAD
    } else {    //Side is black
        for(pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum){
            sq = pos->pList[bP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Basic move and starting double move
            if(pos->pieces[sq - 10] == EMPTY){
                AddBlackPawnMove(pos, sq, (sq - 10), list);
=======
   } else { //Side is black

        //Pawns
        for(pceNum = 0; pceNum < pos->pceNum[bP]; pceNum++){
            //Find what square pawn is on
            sq = pos->pList[bP][pceNum];
            ASSERT(SqOnBoard(sq));

             //If the square ahead of the pawn is empty
            if(pos->pieces[sq - 10] == EMPTY){
                AddBlackPawnMove(pos, sq, (sq - 10), list);

                //If is a pawn start, pawn can jump two squares
>>>>>>> master
                if(RanksBrd[sq] == RANK_7 && pos->pieces[sq - 20] == EMPTY){
                    AddQuietMove(pos, MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), list);
                }
            }

<<<<<<< HEAD
            //Regular diagonal capture moves
            if(!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE){
                AddBlackPawnCapMove(pos, sq, (sq - 9), pos->pieces[sq - 9], list);
            }
            if(!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE){
                AddBlackPawnCapMove(pos, sq, (sq - 11), pos->pieces[sq - 11], list);
            }

            //En Passant Moves
            //@@ CHECK THE CAP IN MOVE FOR ERRATA
            if(sq - 9 == pos->enPas){
                AddEnPassantMove(pos, MOVE(sq, (sq - 9), EMPTY, EMPTY, MFLAGEP), list);
            }

            if(sq - 11 == pos->enPas){
                AddEnPassantMove(pos, MOVE(sq, (sq - 11), EMPTY, EMPTY, MFLAGEP), list);
            }
        
=======
            //Pawns capture diagonally, check if piece is ONBOARD and is WHITE
            if(!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE){
                AddBlackPawnCapMove(pos, sq, sq - 9, pos->pieces[sq - 9], list);
            }

            if(!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE){
                AddBlackPawnCapMove(pos, sq, sq - 11, pos->pieces[sq - 11], list);
            }

            //En passant moves
            if(pos->enPas != NO_SQ){
                if(sq - 9 == pos->enPas){
                    AddEnPassantMove(pos, MOVE(sq, sq - 9, EMPTY, EMPTY, MFLAGEP), list);
                }

                if(sq - 11 == pos->enPas){
                    AddEnPassantMove(pos, MOVE(sq, sq - 11, EMPTY, EMPTY, MFLAGEP), list);
                }
            }
>>>>>>> master
        }

        //Castling
        if(pos->castlePerm & BKCA){
            if(pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY){
                if(!SqAttacked(E8, WHITE, pos) && !SqAttacked(F8, WHITE, pos)){
                    AddQuietMove(pos, MOVE(E8, G8, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }
<<<<<<< HEAD
=======

>>>>>>> master
        if(pos->castlePerm & BQCA){
            if(pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY){
                if(!SqAttacked(E8, WHITE, pos) && !SqAttacked(D8, WHITE, pos)){
                    AddQuietMove(pos, MOVE(E8, C8, EMPTY, EMPTY, MFLAGCA), list);
                }
            }
        }
<<<<<<< HEAD
    }


    // LOOP FOR SLIDE PIECES
    pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePiece[pceIndex++];

    while(pce != 0){
        ASSERT(PieceValid(pce));

        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];

=======


   }


    /* Loop for slide pieces */
    pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePce[pceIndex++];

    while(pce != 0){
        ASSERT(PieceValid(pce));
        
        for(pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++){
            sq = pos->pList[pce][pceNum];
            ASSERT(SqOnBoard(sq));
           
>>>>>>> master
            for(index = 0; index < NumDir[pce]; index++){
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                while(!SQOFFBOARD(t_sq)){
<<<<<<< HEAD
                    //BLACK ^ 1 == WHITE      WHITE ^ 1 == BLACK
=======
>>>>>>> master
                    if(pos->pieces[t_sq] != EMPTY){
                        if(PieceCol[pos->pieces[t_sq]] == side ^ 1){
                            AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                        }
                        break;
                    }
                    AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
<<<<<<< HEAD
                    t_sq += dir;
                }
            }
        }

        pce = LoopSlidePiece[pceIndex++];
    }

    // LOOP FOR NON SLIDE PIECES
    pceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePiece[pceIndex++];

    while(pce != 0){
        ASSERT(PieceValid(pce));

        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            printf("Piece:%c on %s\n", PceChar[pce], PrSq(sq));

=======
                    t_sq += dir;        //Slide the piece!
                }                
            }
        }

        pce = LoopSlidePce[pceIndex++];
    }

    /* Loop for non slide pieces */

    pceIndex = LoopNonSlideIndex[side];
    pce = LoopNonSlidePce[pceIndex++];

    while(pce != 0){
        ASSERT(PieceValid(pce));
        

        for(pceNum = 0; pceNum < pos->pceNum[pce]; pceNum++){
            sq = pos->pList[pce][pceNum];
            ASSERT(SqOnBoard(sq));
            //printf("Piece:%c on %s\n", PceChar[pce], PrSq(sq));

            //Loop through all directions a piece has
>>>>>>> master
            for(index = 0; index < NumDir[pce]; index++){
                dir = PceDir[pce][index];
                t_sq = sq + dir;

<<<<<<< HEAD
=======
                //If offboard, go to next target square
>>>>>>> master
                if(SQOFFBOARD(t_sq)){
                    continue;
                }

<<<<<<< HEAD
                //BLACK ^ 1 == WHITE      WHITE ^ 1 == BLACK
                if(pos->pieces[t_sq] != EMPTY){
                    if(PieceCol[pos->pieces[t_sq]] == side ^ 1){
=======
                //If occupied, check what color the piece on the t_sq is
                if(pos->pieces[t_sq] != EMPTY){
                    //WHITE ^ 1 == BLACK        BLACK ^ 1 == WHITE
                    if(PieceCol[pos->pieces[t_sq]] == (side ^ 1)){
>>>>>>> master
                        AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), list);
                    }
                    continue;
                }
                AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), list);
<<<<<<< HEAD

            }
        }

        pce = LoopNonSlidePiece[pceIndex++];
    }



}
=======
            }
        }
        pce = LoopNonSlidePce[pceIndex++];
    }

}
>>>>>>> master

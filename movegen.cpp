#include "stdio.h"
#include "defs.h"

#define MOVE(f,t,ca,pro,fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFFBOARD)

int LoopSlidePiece[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
int LoopSlideIndex[2] = {0, 4};
int LoopNonSlidePiece[6] = {wN, wK, 0, bN, bK, 0};
int LoopNonSlideIndex[2] = {0, 3};

int PceDir[13][8] = {
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

int NumDir[13] = {0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8};

//Adds a non capture move to the movelist
void AddQuietMove(const S_BOARD *pos, int move, S_MOVELIST *list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

//Adds a capture move to the movelist
void AddCaptureMove(const S_BOARD *pos, int move, S_MOVELIST *list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

//Adds an En Passant move to the movelist
void AddEnPassantMove(const S_BOARD *pos, int move, S_MOVELIST *list){
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void AddWhitePawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list){
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));

    if(RanksBrd[from] == RANK_7){
        AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), list);
    } else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void AddWhitePawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list){
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));

    if(RanksBrd[from] == RANK_7){
        AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), list);
    } else {
        AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void AddBlackPawnCapMove(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list){
    ASSERT(PieceValidEmpty(cap));
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));

    if(RanksBrd[from] == RANK_2){
        AddCaptureMove(pos, MOVE(from, to, cap, bQ, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), list);
        AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), list);
    } else {
        AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), list);
    }
}

void AddBlackPawnMove(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list){
    ASSERT(SqOnBoard(from));
    ASSERT(SqOnBoard(to));

    if(RanksBrd[from] == RANK_2){
        AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), list);
        AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), list);
    } else {
        AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), list);
    }
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list){
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
                if(RanksBrd[sq] == RANK_2 && pos->pieces[sq + 20] == EMPTY){
                    AddQuietMove(pos, MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), list);
                }
            }

            //Regular diagonal capture moves
            if(!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK){
                AddWhitePawnCapMove(pos, sq, (sq + 9), pos->pieces[sq + 9], list);
            }
            if(!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq + 11]] == BLACK){
                AddWhitePawnCapMove(pos, sq, (sq + 11), pos->pieces[sq + 11], list);
            }

            //En Passant Moves
            //@@ CHECK THE CAP IN MOVE FOR ERRATA
            if(sq + 9 == pos->enPas){
                AddEnPassantMove(pos, MOVE(sq, (sq + 9), EMPTY, EMPTY, MFLAGEP), list);
            }

            if(sq + 11 == pos->enPas){
                AddEnPassantMove(pos, MOVE(sq, (sq + 11), EMPTY, EMPTY, MFLAGEP), list);
            }

        }

        //Castling
        if(pos->castlePerm & WKCA){
            if(pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY){
                if(!SqAttacked(E1, BLACK, pos) && !SqAttacked(F1, BLACK, pos)){
                    printf("WKCA movegen\n");
                }
            }
        }
        if(pos->castlePerm & WQCA){
            if(pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY){
                if(!SqAttacked(E1, BLACK, pos) && !SqAttacked(D1, BLACK, pos)){
                    printf("WKQA movegen\n");
                }
            }
        }


    } else {    //Side is black
        for(pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum){
            sq = pos->pList[bP][pceNum];
            ASSERT(SqOnBoard(sq));

            //Basic move and starting double move
            if(pos->pieces[sq - 10] == EMPTY){
                AddBlackPawnMove(pos, sq, (sq - 10), list);
                if(RanksBrd[sq] == RANK_7 && pos->pieces[sq - 20] == EMPTY){
                    AddQuietMove(pos, MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), list);
                }
            }

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
        
        }

        //Castling
        if(pos->castlePerm & BKCA){
            if(pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY){
                if(!SqAttacked(E8, WHITE, pos) && !SqAttacked(F8, WHITE, pos)){
                    printf("BKCA movegen\n");
                }
            }
        }
        if(pos->castlePerm & BQCA){
            if(pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY){
                if(!SqAttacked(E8, WHITE, pos) && !SqAttacked(D8, WHITE, pos)){
                    printf("BKQA movegen\n");
                }
            }
        }
    }


    // LOOP FOR SLIDE PIECES
    pceIndex = LoopSlideIndex[side];
    pce = LoopSlidePiece[pceIndex++];

    while(pce != 0){
        ASSERT(PieceValid(pce));
        printf("sliders pceIndex:%d pce:%d\n", pceIndex, pce);

        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            printf("Piece:%c on %s\n", PceChar[pce], PrSq(sq));

            for(index = 0; index < NumDir[pce]; index++){
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                while(!SQOFFBOARD(t_sq)){
                    //BLACK ^ 1 == WHITE      WHITE ^ 1 == BLACK
                    if(pos->pieces[t_sq] != EMPTY){
                        if(PieceCol[pos->pieces[t_sq]] == side ^ 1){
                            printf("\t\tCapture on %s\n", PrSq(t_sq));
                        }
                        break;
                    }
                    printf("\t\tNormal move on %s\n", PrSq(t_sq));
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
        printf("non sliders pceIndex:%d pce:%d\n", pceIndex, pce);

        for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum){
            sq = pos->pList[pce][pceNum];
            printf("Piece:%c on %s\n", PceChar[pce], PrSq(sq));

            for(index = 0; index < NumDir[pce]; index++){
                dir = PceDir[pce][index];
                t_sq = sq + dir;

                if(SQOFFBOARD(t_sq)){
                    continue;
                }

                //BLACK ^ 1 == WHITE      WHITE ^ 1 == BLACK
                if(pos->pieces[t_sq] != EMPTY){
                    if(PieceCol[pos->pieces[t_sq]] == side ^ 1){
                        printf("\t\tCapture on %s\n", PrSq(t_sq));
                    }
                    continue;
                }
                printf("\t\tNormal move on %s\n", PrSq(t_sq));

            }
        }

        pce = LoopNonSlidePiece[pceIndex++];
    }



}

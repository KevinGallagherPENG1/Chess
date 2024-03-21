#include "stdio.h"
#include "defs.h"

/*
120 bit board
 0   1   2   3   4   5   6   7   8   9
10  11  12  13  14  15  16  17  18  19
20  21  22  23  24  25  26  27  28  29
30  31  32  33  34  35  36  37  38  39
40  41  42  43  44  45  46  47  48  49
50  51  52  53  54  55  56  57  58  59
60  61  62  63  64  65  66  67  68  69 
70  71  72  73  74  75  76  77  78  79
80  81  82  83  84  85  86  87  88  89
90  91  92  93  94  95  96  97  98  99
100 101 102 103 104 105 106 107 108 109
110 111 112 113 114 115 116 117 118 119

For 120, 0 - 19 are OFFBOARD, as well as any number ending in 0 or 9
Only 21 - 28, 31 - 38 ... 91 - 98 are valid board places
100 - 119 are also offboard

64 bit board

     a  b  c  d  e  f  g  h

1    0  1  2  3  4  5  6  7
2    8  9 10 11 12 13 14 15
3   16 17 18 19 20 21 22 23
4   24 25 26 27 28 29 30 31
5   32 33 34 35 36 37 38 39
6   40 41 42 43 44 45 46 47 
7   48 49 50 51 52 53 54 55 
8   56 57 58 59 60 61 62 63

This is a standard chess board, 8 x 8
No OFFBOARD positions
*/

int CheckBoard(const S_BOARD *pos){
    //Setting up temp variables to mirror what given pos has
    int t_pceNum[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int t_bigPce[2] = {0, 0};
    int t_majPce[2] = {0, 0};
    int t_minPce[2] = {0, 0};
    int t_material[2] = {0, 0};

    int sq64, t_piece, t_pce_num, sq120, color, pcount;

    //For the pawns
    U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

    //Fill the pawns
    t_pawns[WHITE] = pos->pawns[WHITE];
    t_pawns[BLACK] = pos->pawns[BLACK];
    t_pawns[BOTH] = pos->pawns[BOTH];

    //Check piece lists...
    //Go through every piece
    for(t_piece = wP; t_piece <= bK; t_piece++){
        //Go through the amount of pieces for that specific piece
        for(t_pce_num = 0; t_pce_num < pos->pceNum[t_piece]; t_pce_num++){
            //Get the square that the piece corresponds to in the pList
            sq120 = pos->pList[t_piece][t_pce_num];
            //Assert that the position piece array at that square is equal to the piece in question
            ASSERT(pos->pieces[sq120] == t_piece);
        }
    }

    //Go through the 64 squares rather than 120
    //This is to increment big, min, and major pieces
    for(sq64 = 0 ; sq64 < 64; sq64++){
        sq120 = SQ120(sq64);                                //Convert to 120 bit square
        t_piece = pos->pieces[sq120];                       //Get the piece at that square
        t_pceNum[t_piece]++;                                //Increment num of that piece
        color = PieceCol[t_piece];                          //Get color of piece

        if(PieceBig[t_piece] == TRUE) t_bigPce[color]++;    //Increment big, min, maj
        if(PieceMin[t_piece] == TRUE) t_minPce[color]++;
        if(PieceMaj[t_piece] == TRUE) t_majPce[color]++;

        t_material[color] += PieceVal[t_piece];             //Update material
    }

    //Assert that all piece types, going through each amount of each piece on the board is equal to the actual amount of pieces on the board
    for(t_piece = wP; t_piece <= bK; t_piece++)
        ASSERT(t_pceNum[t_piece] == pos->pceNum[t_piece]);

    //Ensure amount of pawns is the same as the pos
    pcount = CNT(t_pawns[WHITE]);
    ASSERT(pcount == pos->pceNum[wP]);
    pcount = CNT(t_pawns[BLACK]);
    ASSERT(pcount == pos->pceNum[bP]);
    pcount = CNT(t_pawns[BOTH]);
    ASSERT(pcount == (pos->pceNum[bP] + pos->pceNum[wP]));

    //Check squares for the bitboards
    while(t_pawns[WHITE]){
        //Get the 64 square representation of the white pawns ULL
        //Assert that those squares are indeed, white pawns
        sq64 = POP(&t_pawns[WHITE]);
        ASSERT(pos->pieces[SQ120(sq64)] == wP);
    }

    while(t_pawns[BLACK]){
        sq64 = POP(&t_pawns[BLACK]);
        ASSERT(pos->pieces[SQ120(sq64)] == bP);
    }

    while(t_pawns[BOTH]){
        sq64 = POP(&t_pawns[BOTH]);
        ASSERT((pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP));
    }

    //Material scores should be same as pos
    ASSERT(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK]);
    //Min, maj, big pieces should be same as pos
    ASSERT(t_minPce[WHITE] == pos->minPce[WHITE] && t_minPce[BLACK] == pos->minPce[BLACK]);
    ASSERT(t_majPce[WHITE] == pos->majPce[WHITE] && t_majPce[BLACK] == pos->majPce[BLACK]);
    ASSERT(t_bigPce[WHITE] == pos->bigPce[WHITE] && t_bigPce[BLACK] == pos->bigPce[BLACK]);

    //Assert that side is white or black, not BOTH
    ASSERT(pos->side == WHITE || pos->side == BLACK);
    //A new posKey should be the same as the posKey
    ASSERT(GeneratePosKey(pos) == pos->posKey);

    //Check the enPas sq, if its white's turn, the enPas square must be on rank 6, if its black's turn, enPas square must be rank 3
    ASSERT(pos->enPas == NO_SQ || (RanksBrd[pos->enPas] == RANK_6 && pos->side == WHITE)
                               || (RanksBrd[pos->enPas] == RANK_3 && pos->side == BLACK));
    
    //Assert that the white and black kingSq contains a wK or bK
    ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
    ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);

    return TRUE;
}

void UpdateListsMaterial(S_BOARD *pos){
    int piece, sq, index, color;

    for(index = 0; index < BRD_SQ_NUM; index++){
        sq = index;
        piece = pos->pieces[index];
        if(piece != OFFBOARD && piece != EMPTY){
            color = PieceCol[piece];

            if(PieceBig[piece] == TRUE) pos->bigPce[color]++;
            if(PieceMin[piece] == TRUE) pos->minPce[color]++;
            if(PieceMaj[piece] == TRUE) pos->majPce[color]++;

            pos->material[color] += PieceVal[piece];

            //Piece list: pList[piece][pceNum]
            //pList[wP][0] = a1;
            //pList[wP][1] = a2;
            pos->pList[piece][pos->pceNum[piece]] = sq;
            pos->pceNum[piece]++;

            //If piece is king, update kingSq
            if(piece == wK) pos->KingSq[WHITE] = sq;
            if(piece == bK) pos->KingSq[BLACK] = sq;

            //If piece is pawn, set bit for pawn to pawn, make sure sq is in 64 bit format
            if(piece == wP){
                SETBIT(pos->pawns[WHITE], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            } else if(piece == bP){
                SETBIT(pos->pawns[BLACK], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            }


        }
    }
}

//Parses FEN into our board
int ParseFen(char *fen, S_BOARD * pos){
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = RANK_8;                      //Rank that we are starting from in FEN
    int file = FILE_A;                      //File that we are starting from in FEN
    int piece = 0;                          //Counter for pieces (if any)
    int count = 0;                          //Counter for blank spaces (if any)
    int i = 0;                              //Used for for loop
    int sq64 = 0;
    int sq120 = 0;

    ResetBoard(pos);


    while((rank >= RANK_1) && *fen){
        count = 1;

        switch(*fen){
            case 'p' : piece = bP; break;
            case 'r' : piece = bR; break;
            case 'n' : piece = bN; break;
            case 'b' : piece = bB; break;
            case 'k' : piece = bK; break;
            case 'q' : piece = bQ; break;
            case 'P' : piece = wP; break;
            case 'R' : piece = wR; break;
            case 'N' : piece = wN; break;
            case 'B' : piece = wB; break;
            case 'K' : piece = wK; break;
            case 'Q' : piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;
            
            default:
                printf("FEN ERROR \n");
                return -1;
        }//End of switch

        for(i = 0; i < count; i++){
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);

            if(piece != EMPTY)
                pos->pieces[sq120] = piece;

            file++;
        }
        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');

    pos->side = (*fen == 'w' ? WHITE : BLACK);
    fen += 2;

    for(i = 0; i < 4; i++){
        if (*fen == ' ')
            break;

        switch(*fen){
            case 'K' : pos->castlePerm |= WKCA; break;
            case 'Q' : pos->castlePerm |= WQCA; break;
            case 'k' : pos->castlePerm |= BKCA; break;
            case 'q' : pos->castlePerm |= BQCA; break;
            default  :                          break;
        }//End of switch
        fen++;
    }
    fen++;

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    if(*fen != '-'){
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank >= RANK_1 && rank <= RANK_8);

        pos->enPas = FR2SQ(file, rank);
    }

    pos->posKey = GeneratePosKey(pos);
    UpdateListsMaterial(pos);

    return 0;
}

//This will basically reset the entire board
void ResetBoard(S_BOARD *pos){
    int index = 0;
    
    //Reset all squares to OFFBOARD
    for(index = 0; index < BRD_SQ_NUM; index++)
        pos->pieces[index] = OFFBOARD;

    //Reset all actual board squares to EMPTY
    for(index = 0; index < 64; index++)
        pos->pieces[SQ120(index)] = EMPTY;

    //Set amount of pieces to 0
    for(index = 0; index < 3; index++){
        pos->bigPce[index] = 0;
        pos->majPce[index] = 0;
        pos->minPce[index] = 0;
        pos->pawns[index] = 0ULL;
    }

    //Set num of pieces to 0
    for(index = 0; index < 13; index++)
        pos->pceNum[index] = 0;

    //Set king squares to NO_SQ
    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

    //Set which side's turn it is to BOTH (nonsensical)
    pos->side = BOTH;
    //No active enPas square
    pos->enPas = NO_SQ;
    //0 moves in
    pos->fiftyMove = 0;

    //0 moves made
    pos->ply = 0;
    pos->hisPly = 0;

    //No castle perms
    pos->castlePerm = 0;

    //Reset posKey
    pos->posKey = 0ULL;
}

void PrintBoard(const S_BOARD *pos){

    int sq, file, rank, piece;

    printf("\nGame Board:\n\n");

    for(rank = RANK_8; rank >= RANK_1; rank--){
        printf("%d  ", rank + 1);
        for(file = FILE_A; file <= FILE_H; file++){
            sq = FR2SQ(file, rank);             //Get square we are on
            piece = pos->pieces[sq];            //Get piece on square
            printf("%3c", PceChar[piece]);      //Print that piece
        }
        printf("\n");
    }

    printf("\n   ");

    for(file = FILE_A; file <= FILE_H; file++)
        printf("%3c", 'a' + file);
    printf("\n");

    printf("side:%c\n", SideChar[pos->side]);
    printf("enPas:%d\n", pos->enPas);
    printf("castle:%c%c%c%c\n",
            pos->castlePerm & WKCA ? 'K' : '-',
            pos->castlePerm & WQCA ? 'Q' : '-',
            pos->castlePerm & BKCA ? 'k' : '-',
            pos->castlePerm & BQCA ? 'q' : '-'
            );
    printf("PosKey:%llX\n", pos->posKey);
}
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include "defs.h"

//Testing board / FEN
//@@ there is some warning here, Im sure its fine...
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define TESTFENILLEGAL "8/3q4/8/8/4Q3/8/8/8 w - - 0 2 "
#define PAWNMOVESW "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define PAWNMOVESB "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b - e3 0 1"
#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1"
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1"
#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1"
#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
#define CASTLE2 "3rk2r/8/8/8/8/8/6p1/R3K2R b KQk - 0 1"

//To test if squares are being attacked
//Looks good
/*
void ShowSqAtBySide(const int side, const S_BOARD *pos){
    int rank = 0;
    int file = 0;
    int sq = 0;

    printf("\n\nSquares attacked by:%c\n", SideChar[side]);
    for(rank = RANK_8; rank >= RANK_1; rank--){
        for(file = FILE_A; file <= FILE_H; file++){
            sq = FR2SQ(file, rank);

            if(SqAttacked(sq, side, pos) == TRUE)
                printf("X");
            else 
                printf("-");
        }
        printf("\n");
    }
    printf("\n\n");
}
*/

int main(){

    AllInit();


    S_BOARD board[1];
    S_MOVELIST list[1];

    ParseFen(CASTLE2, board);
    GenerateAllMoves(board, list);

    /*
    //ParseFen(PAWNMOVESW, board);
    ParseFen(PAWNMOVESB, board);
    GenerateAllMoves(board, list);

    */

    /*
    ParseFen(PAWNMOVESB, board);
    PrintBoard(board);

    S_MOVELIST list[1];
    
    GenerateAllMoves(board, list);

    PrintMoveList(list);

    */


    /*
    int move = 0;
    int from = A2; int to = H7;
    int cap = wR; int prom = bQ;

    move = ( (from) | (to << 7) | (cap << 14) | (prom << 20));

    printf("from:%d to:%d cap:%d prom:%d\n", FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));
    
    printf("Algebraic from:%s\n", PrSq(from));
    printf("Algebraic to:%s\n", PrSq(to));
    printf("Algebraic move:%s\n", PrMove(move));

    */



    /*
    U64 playBitBoard = 0ULL;

    //These work! Testing FEN parsing
    S_BOARD board[1];


    ParseFen(FEN4, board);
    PrintBoard(board);
    ASSERT(CheckBoard(board));




    
    //Seems alright.
    int move = 0;
    int from = 6; int to = 12;
    int cap = wR; int prom = bR;

    move = ((from ) | (to << 7) | (cap << 14) | (prom << 20));

    printf("\ndec:%d", move);
    printf("\nhex:%X", move);

    printf("\nFrom:%d to:%d cap:%d prom:%d\n", FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));

    move |= MFLAGPS;

    printf("is Pawn Start:%s", (move & MFLAGPS) ? "YES" : "NO");
    */

    //Testing SqAtBy
    //Looks good
    /*
    ParseFen(TESTFENILLEGAL, board);
    PrintBoard(board);

    printf("\n\nWhite Attacking:\n");
    ShowSqAtBySide(WHITE, board);

    printf("\n\nBlack Attacking:\n");
    ShowSqAtBySide(BLACK, board);

    */

    /*
    //Checking checkBoard, it Works :)
    ParseFen(FEN4, board);

    PrintBoard(board);

    //Checks out! Its good
    ASSERT(CheckBoard(board));

    //Lets force a fail
    board->pceNum[wP]--;

    ASSERT(CheckBoard(board));
    //IT WORKS :)
    */

    //Bitboards look good!
    /*
    ParseFen(FEN4, board);

    PrintBoard(board);
    printf("\nwP:\n");
    printBitBoard(board->pawns[WHITE]);
    printf("\nbP\n");
    printBitBoard(board->pawns[BLACK]);
    printf("\nall P: \n");
    printBitBoard(board->pawns[BOTH]);
    */

    /*
    ParseFen(START_FEN, board);
    PrintBoard(board);
    ParseFen(FEN1, board);
    PrintBoard(board);
    ParseFen(FEN2, board);
    PrintBoard(board);
    ParseFen(FEN3, board);
    PrintBoard(board);
    */
    


    /*
    //Testing hashkeys
    int pieceOne = rand();
    int pieceTwo = rand();
    int pieceThree = rand();
    int pieceFour = rand();

    //Print in hexadecimal
    printf("Piece 1:%X\n", pieceOne);
    printf("Piece 2:%X\n", pieceTwo);
    printf("Piece 3:%X\n", pieceThree);
    printf("Piece 4:%X\n", pieceFour);

    int key = pieceOne ^ pieceTwo ^ pieceThree ^ pieceFour;
    int tempKey = pieceOne;
    tempKey ^= pieceThree;
    tempKey ^= pieceFour;
    tempKey ^= pieceTwo;

    //These are the same!
    printf("Key: %X\n", key);
    printf("Temp key: %X\n", tempKey);
    
    //To remove a piece, xor it with the same piece
    tempKey ^= pieceThree;
    printf("Temp key (3 out): %X\n", tempKey);
    
    tempKey ^= pieceThree;
    printf("Temp key (3 in): %X\n", tempKey);
    */

    //These work! Testing Set and Clear mask
    /*
    int index = 0;
    
    for(index; index < 64; index++){
        std::cout << "Index: " <<index;
        printBitBoard(SetMask[index]);
    }

    for(index = 0; index < 64; index++){
        std::cout << "Index: " <<index;
        printBitBoard(ClearMask[index]);
    }
    */

    /*
    SETBIT(playBitBoard, 61);
    printBitBoard(playBitBoard);

    CLRBIT(playBitBoard, 61);
    printBitBoard(playBitBoard);

    */


    //These work! Another test of pop...
    /*
    U64 playBitBoard = 0ULL;

    playBitBoard |= (1ULL << SQ64(D2));    
    playBitBoard |= (1ULL << SQ64(D3));
    playBitBoard |= (1ULL << SQ64(D4)); 

    int sq64 = 0;

    while(playBitBoard){
        sq64 = POP(&playBitBoard);
        std::cout << "Popped: " << sq64;
        printBitBoard(playBitBoard);
    }
    */

    //These work! Testing more bitboards.cpp, namely Count and Pop
    /*
    U64 playBitBoard = 0ULL;

    playBitBoard |= (1ULL << SQ64(D2));    
    playBitBoard |= (1ULL << SQ64(D3));
    playBitBoard |= (1ULL << SQ64(D4)); 

    printBitBoard(playBitBoard);

    int count = CNT(playBitBoard);

    std::cout << "Count: " << count;
    
    int index = POP(&playBitBoard);

    std:: cout << "Index: " << index;

    printBitBoard(playBitBoard);

    count = CNT(playBitBoard);

    std::cout << "Count: " << count;
    */
     
    //These work! Testing bitboards.cpp
    /*
    U64 playBitBoard = 0ULL; 

    std::cout << "Start: \n\n";
    printBitBoard(playBitBoard);

    //Shift the ULL by the amount D2
    playBitBoard |= (1ULL << SQ64(D2));
    std::cout << "D2 Added:\n\n";
    printBitBoard(playBitBoard);

    //Shift the ULL by the amount G2
    playBitBoard |= (1ULL << SQ64(G2));
    std::cout << "G2 Added:\n\n";
    printBitBoard(playBitBoard);
    */

    //These work! Testing init.cpp
    /*
    for(int index = 0; index < BRD_SQ_NUM; index++){
        if(index % 10 == 0) printf("\n");
        printf("%5d", Sq120ToSq64[index]);
    }

    std::cout << "\n" << std::endl;

    for(int index = 0; index < 64; index++){
        if(index % 8 == 0) printf("\n");
        printf("%5d", Sq64ToSq120[index]);
    }
    */

   
    return 0;
}
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
#define PAWNMOVES "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define PAWNMOVESB "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b - e3 0 1"
#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1"
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1"
#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1"
#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
#define CASTLE2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

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

/*
void printBin(int move){
    int index = 0;
    printf("As binary:\n");

    for(index = 27; index >= 0; index--){
        if( (1<<index) & move) printf("1");
        else printf("0");
        if(index != 28 && index % 4 == 0) printf(" ");
    }
    printf("\n");
}
*/


int main(){

    AllInit();
    
    S_BOARD board[1];
    S_MOVELIST list[1];

    ParseFen(START_FEN, board);
    GenerateAllMoves(board, list);

    PerftTest(3, board);




    /*
    //THE HAUNTED CODE TEST!!!

    int MoveNum = 0;
    int move = 0;

    PrintBoard(board);
    getchar();



    for(MoveNum = 0; MoveNum <list->count; ++MoveNum){
        move = list->moves[MoveNum].move;

        if(!MakeMove(board, move)){
            continue;
        }

        printf("\nMADE:%s\n", PrMove(move));
        PrintBoard(board);

        TakeMove(board);
        printf("\nTAKEN:%s\n", PrMove(move));
        PrintBoard(board);

        getchar();
    }

*/  

    
    
    /*
    ParseFen(FEN4, board);
    PrintBoard(board);
    ASSERT(CheckBoard(board));

    int move = 0; 
    int from = 6;
    int to = 12;
    int cap = wR; int prom = bR;

    move = ((from) | (to << 7) | (cap << 14) | (prom << 20));

    printf("\ndec%d hex:%X\n", move, move);
    printBin(move);

    printf("from:%d to:%d cap:%d prom%d\n", FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));
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
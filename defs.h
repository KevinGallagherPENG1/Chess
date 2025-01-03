#ifndef DEFS_H
#define DEFS_H

#include "stdlib.h"

#define DEBUG 

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed ", #n); \
printf("On %s ", __DATE__); \
printf("AT %s ", __TIME__); \
printf("In File %s ", __FILE__); \
printf("At Line %d\n", __LINE__); \
exit(1); \
}
#endif

typedef unsigned long long U64;

#define NAME "Vice 1.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048
#define MAXPOSITIONMOVES 256        //Maximum moves for a single position

//Forsyth-Edwards Notation
//rook, knight, bishop, etc... lowercase is black, uppercase is white
//                                                  Which side's turn to move
//                                                             | Castling perms
//                                                             |  |   en Passant square
//                     number of consecutive blank spaces      |  |   | Halfmoves (used for fifty move rule)               
//                                   |                         |  |   | | Full moves
//                                   |                         |  |   | | |           
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

//List of all the pieces
enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};

//Ranks and files
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};

//Colors
enum {WHITE, BLACK, BOTH};

//Squares of the board
enum {  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
        A2 = 31, B2, C2, D2, E2, F2, G2, H2,
        A3 = 41, B3, C3, D3, E3, F3, G3, H3,
        A4 = 51, B4, C4, D4, E4, F4, G4, H4,
        A5 = 61, B5, C5, D5, E5, F5, G5, H5,
        A6 = 71, B6, C6, D6, E6, F6, G6, H6,
        A7 = 81, B7, C7, D7, E7, F7, G7, H7, 
        A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD };

//0 for false, 1 for true
enum {FALSE, TRUE};

//Castling permission, White king castling (castling king side) = 1, white queen castling (castling queen side) = 2, etc
enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};

//History of the game
struct S_UNDO{
    int move;                           //Move that was just about to be made
    int castlePerm;                     //Castle permission before move
    int enPas;                          //En passant square before move
    int fiftyMove;                      //Fifty move status before move
    U64 posKey;                         //Position key
};

//Stores the moves available
struct S_MOVE{
    int move;                           //Stores all info for the move
    int score;                          //Score of the moves
};

//List of moves we store
struct S_MOVELIST{
    S_MOVE moves[MAXPOSITIONMOVES];
    int count;
};

/// @brief Contains all info for a chess board
struct S_BOARD {
    int pieces[BRD_SQ_NUM];             //120 int array for all the pieces and protective border squares
    U64 pawns[3];                       //Will set a single bit to 1 in a 64 bit number to indicate where a pawn is, each group of 8 bits is a row, 
                                        //3 total == 1 for white, 1 for black, 1 for both
    int KingSq[2];                      //Specifically to hold where the kings are
    int side;                           //Current side to move
    int enPas;                          //Holds if enPassant move is possible
    int fiftyMove;                      //For tracking draws
    int ply;                            //How many moves we are in (depth)
    int hisPly;                         //How many moves have been made
    int castlePerm;                     //Int to store if castling is possible
    U64 posKey;                         //Unique key generated for each position
    int pceNum[13];                     //Number of pieces on board, indexed by piece type
    int bigPce[2];                      //Number of big pieces (anything that isnt a pawn), indexed by color
    int majPce[2];                      //Number of Major Pieces (rooks, queens), indexed by color
    int minPce[2];                      //Number of minor pieces (bishops, knights), indexed by color
    int material[2];                    //Holds material score for black and white
    S_UNDO history[MAXGAMEMOVES];       //History of the game
    int pList[13][10];                  //Piece list, Each type of piece and Amount of Pieces
};

//======================================
//GAME MOVES
//======================================
/*

0000 0000 0000 0000 0001 0001   --> 0x000011 (hex, each number represents a block of 4 bits)
0000 0000 0000 0000 1010 1111   --> 0x0000AF

Allows us to use bitshifting, andwise operations to tell us all this information
0000 0000 0000 0000 0000 0111 1111   --> From sq                      0x7F
0000 0000 0000 0011 1111 1000 0000   --> To sq                  >> 7  0x7F
0000 0000 0011 1100 0000 0000 0000   --> Piece captured         >> 14 0xF
0000 0000 0100 0000 0000 0000 0000   --> Is En Passant capture?       0x40000
0000 0000 1000 0000 0000 0000 0000   --> Is Pawn start?               0x80000
0000 1111 0000 0000 0000 0000 0000   --> Is Promoted piece?     >> 20 0xF
0001 0000 0000 0000 0000 0000 0000   --> Is Castle move?              0x1000000
*/

#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)


#define MFLAGEP 0x4000                   //Move flag En Passant
#define MFLAGPS 0x8000                   //Move flag Pawn Start
#define MFLAGCA 0x1000000                //Move flag Castle
#define MFLAGCAP 0x7C000                 //Move flag Capture
#define MFLAGPROM 0xF00000               //Move flag Promotion

//======================================
//MACROS
//======================================

//Given a File and Rank, returns the 120 bit board position of the file and rank
//@@ ATTENTION THIS COULD BE WEIRD!!!! ITS TAKING ENUM LIST AND ASSUMING IT WILL BE INT 
//@@ BE SURE TO CHECK WITHIN INIT.CPP
//@@ Used to be #define FR2SQ(f, r) ((21 + (f)) + ((r) * 10))
//@@ Simply moved to init.cpp for brevity
//@@ Added inline so that it would hopefully work...

inline int FR2SQ(int f, int r){
    return ((21 + (f)) + ((r) * 10));
} 


//Simply a shortcut for 120 to 64
#define SQ64(sq120) (Sq120ToSq64[sq120])
//Simply a shortcut for 64 to 120
#define SQ120(sq64) (Sq64ToSq120[sq64])

//Pops a bit from b
#define POP(b) PopBit(b)
//Counts all the bits in b
#define CNT(b) CountBits(b)

//Clears bit at position sq in the bb (sets to 0)
#define CLRBIT(bb, sq) ((bb) &= ClearMask[(sq)]);
//Sets bit at position sq in the bb (sets to 1)
#define SETBIT(bb, sq) ((bb) |= SetMask[(sq)]);

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])


//======================================
//GLOBAL
//======================================

//For converting 64 bit board position to our 120 bit board position
extern int Sq120ToSq64[BRD_SQ_NUM]; 
//For converting 120 bit board position to 64 bit board position
extern int Sq64ToSq120[64];

//Setting bits to 1
extern U64 SetMask[64];
//Clear bits to 0
extern U64 ClearMask[64];

extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16];

extern char PceChar[];                          //Holds a character for each piece (Uppercase is White, lowecase is Black)
extern char SideChar[];                         //w for White, b for black, - for neither
extern char RankChar[];                         //Holds ranks of board (1-8)
extern char FileChar[];                         //Holds files of board (a-h)

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];
extern int PiecePawn[13];

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

//Which piece is which, based on their movement
extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13];
extern int PieceBishopQueen[13];
extern int PieceSlides[13];

//======================================
//FUNCTIONS
//======================================

//init.cpp
extern void AllInit();

//bitboards.cpp
extern void printBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);

//hashkeys.cpp
extern U64 GeneratePosKey(const S_BOARD *pos);

//board.cpp
extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern void UpdateListsMaterial(S_BOARD *pos);
extern int CheckBoard(const S_BOARD *pos);

//attack.cpp
extern int SqAttacked(const int sq, const int side, const S_BOARD *pos);

//io.cpp
extern char *PrSq(const int sq);
extern char *PrMove(const int move);
extern void PrintMoveList(const S_MOVELIST *list);

//validate.cpp
extern int SqOnBoard(const int sq);
extern int SideValid(const int side);
extern int FileRankValid(const int fr);
extern int PieceValidEmpty(const int pce);
extern int PieceValid(const int pce);

//movegen.cpp
extern void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list);

//makemove.cpp
extern int MakeMove(S_BOARD *pos, int move);
extern void TakeMove(S_BOARD *pos); 
#endif
#include "defs.h"

/// @brief Checks if a square is on the board
/// @param sq Square to check
/// @return 0 if OFFBOARD, 1 if on board
int SqOnBoard(const int sq){
    return FilesBrd[sq] == OFFBOARD ? 0 : 1;
}

/// @brief Checks if side is WHITE or BLACK
/// @param side Side to check
/// @return 1 if side is WHITE or BLACK, 0 if otherwise
int SideValid(const int side){
    return (side == WHITE || side == BLACK) ? 1 : 0;
}

/// @brief Checks if file or rank is valid
/// @param fr File or Rank to check
/// @return 1 if a-h or 1-7, 0 if otherwise
int FileRankValid(const int fr){
    return(fr >= 0 && fr <= 7) ? 1 : 0;
}

/// @brief Checks if a piece is valid (containing empty)
/// @param pce Pce to check
/// @return 1 if greater than empty and less than bK, 0 otherwise
int PieceValidEmpty(const int pce){
    return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

/// @brief Checks if a piece is valid
/// @param pce Pce to check
/// @return 1 if greater than a pawn and less than a king, 0 otherwise
int PieceValid(const int pce){
    return (pce >= wP && pce <= bK) ? 1 : 0;
}
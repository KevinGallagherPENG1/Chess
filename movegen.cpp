#include "stdio.h"
#include "defs.h"

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

void GenerateAllMoves(const S_BOARD *pos, int move, S_MOVELIST *list){
    list->count = 0;
}
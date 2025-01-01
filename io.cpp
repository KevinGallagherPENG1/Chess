#include "stdio.h"
#include "defs.h"

//For writing Algebraic positions of moves.


char *PrSq(const int sq){
    //For using this information outside of function
    static char SqStr[3];

    int file = FilesBrd[sq];
    int rank = RanksBrd[sq];

    sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));

    return SqStr;
}

char *PrMove(const int move){
    static char MvStr[6];

    int ff = FilesBrd[FROMSQ(move)];    //File from
    int rf = RanksBrd[FROMSQ(move)];    //Rank from
    int ft = FilesBrd[TOSQ(move)];      //File to
    int rt = RanksBrd[TOSQ(move)];      //Rank to

    int promoted = PROMOTED(move);

    if(promoted){
        char pchar = 'q';                               //Assume Promoted piece is queen
        if(IsKn(promoted)){
            pchar = 'n';
        } else if(IsRQ(promoted) && !IsBQ(promoted)){   //If is rook or queen but not bishop, then its a rook
            pchar = 'r';
        } else if(!IsRQ(promoted) && IsBQ(promoted)){   //If is bishop or queen but not rook, then its a bishop
            pchar = 'b';
        }
        sprintf(MvStr, "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
        } else{
            sprintf(MvStr, "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
        }

    return MvStr;
}

// Prints each move from a movelist 
void PrintMoveList(const S_MOVELIST *list){
    int index = 0;
    int score = 0;
    int move = 0;
    
    printf("MoveList:\n", list->count);

    for(index = 0; index < list->count; index++){
        move = list->moves[index].move;
        score = list->moves[index].score;

        printf("Move:%d > %s (score:%d)\n", index + 1, PrMove(move), score);
    }
    printf("MoveList Total %d Moves:\n\n", list->count);
}
#include "defs.h"
#include "stdio.h"

long leafNodes;

void Perft(int depth, S_BOARD *pos){
    ASSERT(CheckBoard(pos));

    if(depth == 0){
        leafNodes++;
        return;
    }

    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);

    for(int MoveNum = 0; MoveNum < list->count; ++MoveNum){
        if(!MakeMove(pos, list->moves[MoveNum].move)){
            continue;
        }
        Perft(depth - 1, pos);
        TakeMove(pos);
    }
    return;
}

void PerftTesT(int depth, S_BOARD *pos){
    ASSERT(CheckBoard(pos));

    PrintBoard(pos);
    printf("\nStarting Test to Depth:%d\n", depth);
    leafNodes = 0;

    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);

    int move;
    int MoveNum;

    for(MoveNum = 0; MoveNum < list->count; ++MoveNum){
        move = list->moves[MoveNum].move;

        if(!MakeMove(pos, move)){
            continue;
        }

        long cumnodes /*cumulative nodes, get your head outta the gutter*/ = leafNodes;
        Perft(depth - 1, pos);
        TakeMove(pos);
        long oldnodes = leafNodes - cumnodes;
        printf("Move %d : %s : $ld\n", MoveNum + 1, PrMove(move), oldnodes);
    }

    printf("\nTest Complete : %ld nodes visited\n", leafNodes);

    return;
}
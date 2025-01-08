#include "stdio.h"
#include "defs.h"

<<<<<<< HEAD
//Prints a square to the screen
char *PrSq(const int sq){
=======
//For writing Algebraic positions of moves.


char *PrSq(const int sq){
    //For using this information outside of function
>>>>>>> master
    static char SqStr[3];

    int file = FilesBrd[sq];
    int rank = RanksBrd[sq];

    sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));

    return SqStr;
}

<<<<<<< HEAD
//Prints a move to the screen
char *PrMove(const int move){
    static char MvStr[6];

    int ff = FilesBrd[FROMSQ(move)];
    int rf = RanksBrd[FROMSQ(move)];
    int ft = FilesBrd[TOSQ(move)];
    int rt = RanksBrd[TOSQ(move)];

    int promoted = PROMOTED(move);

    if(promoted){
        char pchar = 'q';
        if(IsKn(promoted)){
            pchar = 'n';
        } else if(IsRQ(promoted) && !IsBQ(promoted)){
            pchar = 'r';
        } else if(!IsRQ(promoted) && IsBQ(promoted)){
            pchar = 'b';
        }
        sprintf(MvStr,"%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
    } else {
        sprintf(MvStr,"%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
    }

    return MvStr;
}

=======
char *PrMove(const int move) {

	static char MvStr[6];

	int ff = FilesBrd[FROMSQ(move)];
	int rf = RanksBrd[FROMSQ(move)];
	int ft = FilesBrd[TOSQ(move)];
	int rt = RanksBrd[TOSQ(move)];

	int promoted = PROMOTED(move);

	if(promoted) {
		char pchar = 'q';
		if(IsKn(promoted)) {
			pchar = 'n';
		} else if(IsRQ(promoted) && !IsBQ(promoted))  {
			pchar = 'r';
		} else if(!IsRQ(promoted) && IsBQ(promoted))  {
			pchar = 'b';
		}
		sprintf(MvStr, "%c%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt), pchar);
	} else {
		sprintf(MvStr, "%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt));
	}

	return MvStr;
}

// Prints each move from a movelist 
>>>>>>> master
void PrintMoveList(const S_MOVELIST *list){
    int index = 0;
    int score = 0;
    int move = 0;
<<<<<<< HEAD

    printf("MoveList:\n", list->count);

    for(index; index < list->count; index++){
=======
    
    printf("MoveList:\n", list->count);

    for(index = 0; index < list->count; index++){
>>>>>>> master
        move = list->moves[index].move;
        score = list->moves[index].score;

        printf("Move:%d > %s (score:%d)\n", index + 1, PrMove(move), score);
    }
    printf("MoveList Total %d Moves:\n\n", list->count);
}
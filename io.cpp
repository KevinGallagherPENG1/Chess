#include "stdio.h"
#include "defs.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
//Prints a square to the screen
char *PrSq(const int sq){
=======
>>>>>>> nastyBugfix
//For writing Algebraic positions of moves.


char *PrSq(const int sq){
    //For using this information outside of function
<<<<<<< HEAD
=======
//Prints a square to the screen
char *PrSq(const int sq){
>>>>>>> nastyBugfix
=======
>>>>>>> master
>>>>>>> nastyBugfix
    static char SqStr[3];

    int file = FilesBrd[sq];
    int rank = RanksBrd[sq];

    sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));

    return SqStr;
}

<<<<<<< HEAD
<<<<<<< HEAD
char *PrMove(const int move){
    static char MvStr[6];

    int ff = FilesBrd[FROMSQ(move)];    //File from
    int rf = RanksBrd[FROMSQ(move)];    //Rank from
    int ft = FilesBrd[TOSQ(move)];      //File to
    int rt = RanksBrd[TOSQ(move)];      //Rank to
=======
=======
>>>>>>> nastyBugfix
//Prints a move to the screen
char *PrMove(const int move){
    static char MvStr[6];

    int ff = FilesBrd[FROMSQ(move)];
    int rf = RanksBrd[FROMSQ(move)];
    int ft = FilesBrd[TOSQ(move)];
    int rt = RanksBrd[TOSQ(move)];
<<<<<<< HEAD
>>>>>>> nastyBugfix
=======
>>>>>>> nastyBugfix

    int promoted = PROMOTED(move);

    if(promoted){
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
=======
>>>>>>> nastyBugfix
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
<<<<<<< HEAD
>>>>>>> nastyBugfix
=======
>>>>>>> nastyBugfix

    return MvStr;
}

<<<<<<< HEAD
<<<<<<< HEAD
// Prints each move from a movelist 
=======
>>>>>>> nastyBugfix
=======
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
>>>>>>> nastyBugfix
void PrintMoveList(const S_MOVELIST *list){
    int index = 0;
    int score = 0;
    int move = 0;
<<<<<<< HEAD
<<<<<<< HEAD
    
    printf("MoveList:\n", list->count);

    for(index = 0; index < list->count; index++){
=======
=======
>>>>>>> nastyBugfix

    printf("MoveList:\n", list->count);

    for(index; index < list->count; index++){
<<<<<<< HEAD
>>>>>>> nastyBugfix
=======
=======
    
    printf("MoveList:\n", list->count);

    for(index = 0; index < list->count; index++){
>>>>>>> master
>>>>>>> nastyBugfix
        move = list->moves[index].move;
        score = list->moves[index].score;

        printf("Move:%d > %s (score:%d)\n", index + 1, PrMove(move), score);
    }
    printf("MoveList Total %d Moves:\n\n", list->count);
}
#include "defs.h"
#include "stdlib.h"
#include "stdio.h"

//For creating a 64 bit random number
#define RAND_64 (   (U64) rand() | \
                    (U64) rand() << 15 | \
                    (U64) rand() << 30 | \
                    (U64) rand() << 45 | \
                    ((U64) rand() & 0xf) << 60 )


int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

//Piece keys, one for each piece and then for each square
U64 PieceKeys[13][120];
U64 SideKey;
//0 0 0 0 = 0 - 15
U64 CastleKeys[16];

//Stores which sq is which file / rank
int FilesBrd[BRD_SQ_NUM];
int RanksBrd[BRD_SQ_NUM];


void InitFilesRanksBrd(){
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;

    //Initialize everything to OFFBOARD
    for(index = 0; index < BRD_SQ_NUM; index++){
        FilesBrd[index] = OFFBOARD;
        RanksBrd[index] = OFFBOARD;
    }

    for(rank = RANK_1; rank <= RANK_8; rank++){
        for(file = FILE_A; file <= FILE_H; file++){
            sq = FR2SQ(file, rank);
            FilesBrd[sq] = file;
            RanksBrd[sq] = rank;
        }
    }

    /*These work!

    printf("FilesBrd\n");
    for(index = 0; index < BRD_SQ_NUM; index++){
        if(index % 10 == 0 && index != 0) printf("\n");
        printf("%4d", FilesBrd[index]);
    }
    
    printf("RanksBrd\n");
    for(index = 0; index < BRD_SQ_NUM; index++){
        if(index % 10 == 0 && index != 0) printf("\n");
        printf("%4d", RanksBrd[index]);
    }
    */

}

void InitHashKeys(){
    int index = 0;
    int index2 = 0;

    for(index = 0; index < 13; index++){
        for(index2 = 0; index2 < 120; index2++){
            PieceKeys[index][index2] = RAND_64;
        }
    }

    SideKey = RAND_64;

    for(index = 0; index < 16; index++)
        CastleKeys[index] = RAND_64;
}

void InitBitMasks(){
    int index = 0;

    //Initialize everything to 0
    for(index; index < 64; index++){
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }

    //Sets the ascending indices of SetMask, ie 1 = 0000....0001, 2 = 0000....0010, etc, 
    //Sets clear mask to NOT (~) SetMask,    ie 1 = 1111....1110, 2 = 1111....1101, etc
    for(index = 0; index < 64; index++){
        SetMask[index] |= (1ULL << index);
        ClearMask[index] = ~SetMask[index];
    }
}

void InitSq120To64(){
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;


    //@@ CHECK ALL FOR LOOPS, if something is wrong, it used to be ++(increment) rather than (increment)++

    //Set value of every index in the 64 bit board to 65, which shouldnt be returned
    for(index = 0; index < BRD_SQ_NUM; index++)
        Sq120ToSq64[index] = 65;                

    //Likewise, 120 should never be returned from the 120 bit board
    for(index = 0; index < 64; index++)
        Sq64ToSq120[index] = 120;

    //Go through every rank and then every file within the rank
    for(rank = RANK_1; rank <= RANK_8; rank++){
        for(file = FILE_A; file <= FILE_H; file++){
            sq = FR2SQ(file, rank);
            Sq64ToSq120[sq64] = sq;             //Set 64 to square 120
            Sq120ToSq64[sq] = sq64;             //Set 120 to square 64
            sq64++;
        }
    }
    
    
}

void AllInit(){
    InitSq120To64();
    InitBitMasks();
    InitHashKeys();
    InitFilesRanksBrd();
}
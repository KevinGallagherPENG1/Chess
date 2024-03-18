#include "stdio.h"
#include "defs.h"

//Mystery array! Not really, its useful for all the positions within the BB, and comes into play with the return statement of the PopBit function
const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28, 
    58, 20, 37, 17, 36, 8
};

//Takes the first bit (least significant bit), and returns the index that the bit was set at, and sets the bit to 0
int PopBit(U64 *bb){
    //Calculate the XOR of bb and (*bb - 1), which is bb but flipped
    //IE: bb = 0000....0011, bb-1 = 0000....0010, *bb ^ (*bb - 1) = 0000....0001
    U64 b = *bb ^ (*bb - 1);                             

    //Fold the resulting 64 bit number into a 32 bit number, 0xffffffff ensures only the lower 32 bits of b are used in the first part of XOR (^)
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));

    //This will clear the least significant 1 in bb,
    //IE: *bb == 0100, *bb-1 = 0011, (*bb &= *bb-1) = 0000
    //IE: *bb == 1010, *bb-1 = 1001, (*bb &= *bb-1) = 1000 
    *bb &= (*bb - 1);

    //Magic number multiplication trickery! 
    //This is designed to make each unique bit position in the original 64 bit number
    //Is mapped to a unique index between 0-63, without needing to manually do this
    return BitTable[(fold * 0x783a9b23) >> 26];
}

//Returns the amount of bits that are 1 within the bitboard
int CountBits(U64 b){
    int r;
    for(r = 0; b; r++, b &= b -1);       //R is incremented if 1 is found, and b &= b - 1 essentially flips all the bits
    return r;
}

void printBitBoard(U64 bb){
    U64 shiftMe = 1ULL;

    int rank = 0;
    int file = 0;
    int sq = 0;
    int sq64 = 0;

    printf("\n");
    //Go through the board in order...
    /*
      A B C D E F G H 
    8 - - - - - - - - 
    7 - - - - - - - - 
    6 - - - - - - - -
    5 - - - - - - - - 
    4 - - - - - - - -
    3 - - - - - - - -
    2 - - - - - - - -
    1 - - - - - - - - 
    */
    for(rank = RANK_8; rank >= RANK_1; rank--){
        for(file = FILE_A; file <= FILE_H; file++){
            sq = FR2SQ(file, rank);     //120 based
            sq64 = SQ64(sq);            //64 based

            //If a bit exists on the bb, print X
            if((shiftMe << sq64) & bb)
                printf("X");
            else
                printf("-");

        }
        printf("\n");
    }
    printf("\n\n");
}
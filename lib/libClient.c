#include "../include/libClient.h"
#include <string.h>



void displayRouletteTable(){
    printf("----------------------------------------------------------------------\n");   
    printf("|   |"BLCK"  3 "RESET"|"RED"  6 "RESET"|"BLCK"  9 "RESET"|"RED" 12 "RESET"|"BLCK" 15 "RESET"|"RED" 18 "RESET"|"BLCK" 21 "RESET"|"RED" 24 "RESET"|"BLCK" 27 "RESET"|"RED" 30 "RESET"|"BLCK" 33 "RESET"|"RED" 36 "RESET"|2TO1|\n");
    printf("|   |-----------------------------------------------------------------\n");    
    printf("|"GRN" 0 "RESET"|"RED"  2 "RESET"|"BLCK"  5 "RESET"|"RED"  8 "RESET"|"BLCK" 11 "RESET"|"RED" 14 "RESET"|"BLCK" 17 "RESET"|"RED" 20 "RESET"|"BLCK" 23 "RESET"|"RED" 26 "RESET"|"BLCK" 29 "RESET"|"RED" 32 "RESET"|"BLCK" 35 "RESET"|2TO1|\n");
    printf("|   |-----------------------------------------------------------------\n");   
    printf("|   |"BLCK"  1 "RESET"|"RED"  4 "RESET"|"BLCK"  7 "RESET"|"RED" 10 "RESET"|"BLCK" 13 "RESET"|"RED" 16 "RESET"|"BLCK" 19 "RESET"|"RED" 22 "RESET"|"BLCK" 25 "RESET"|"RED" 28 "RESET"|"BLCK" 31 "RESET"|"RED" 34 "RESET"|2TO1|\n");
    printf("----------------------------------------------------------------------\n");
    printf("    |       1st12       |       2nd12       |       3rd12       |     \n");
    printf("    -------------------------------------------------------------     \n");
    printf("    |  1TO18  |   EVEN  |"RED"   RED   "RESET"|"BLCK"  BLACK  "RESET"|   ODD   | 19TO36  |     \n");
    printf("    -------------------------------------------------------------     \n");
}
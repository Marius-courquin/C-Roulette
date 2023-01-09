#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif

#ifndef CLIENT
#include "client.h"
#define CLIENT 1
#endif




static int betTypeMultiplicator [12] = {
    3,
    3,
    3,
    4,
    4,
    4,
    2,
    2,
    2,
    2,
    2,
    2
};

static int blackNumbers[18] = {
    2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35
};

static int redNumbers[18] = {
    1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36
};

static char betType[12][7] = {
    "2TO1",
    "2TO2",
    "2TO3",
    "1st12",
    "2nd12",
    "3rd12",
    "1TO18",
    "EVEN",
    "RED",
    "BLACK",
    "ODD",
    "19TO36"
};

typedef int (*func)(int);



void displayRouletteTable();
int checkComposition(int betTab[],int compositionCount, int *multiplicator);
int checkBetValue(char *string, int *multiplicator);
int bet(clientData *client,betData **betList, int *nbOfBetInProgress );
void addNewBet(betData **betList, int *nbOfBetInProgress,int amount, char *bet, int multiplicator);
int inputBet(clientData *client) ;
int containSeparatorField(char *str, char separator);
void displayBetInProgress(betData *betList, int betInProgress);
void checkBetResult(int *drawResult, betData *betList, int *nbOfBetInProgress, clientData *client);
void displayBetResult (int result);
int checkIfResultIsRed(int result);
int checkIfResultIsBlack(int result);
int checkResult2to1 (int result);
int checkResult2to2 (int result);
int checkResult2to3 (int result);
int checkResult1st12(int result);
int checkResult2nd12(int result);
int checkResult3rd12(int result);
int checkResult1to18 (int result);
int checkResult19to36 (int result);
int checkResultEven(int result);
int checkResultOdd(int result);
int decomposition(int *result,int *compositionCount,char *string);
int computeGain(int drawResult,betData *betList,int arrayLen);
int checkDigitOnly(char *str);
void displayUserInGame();
void writeBestBet(int gain, char *username);
void displayBestBet();
static func functionsArray[12] = {
    &checkResult2to1,
    &checkResult2to2,
    &checkResult2to3,
    &checkResult1st12,
    &checkResult2nd12,
    &checkResult3rd12,
    &checkResult1to18,
    &checkResultEven,
    &checkIfResultIsRed,
    &checkIfResultIsBlack,
    &checkResultOdd,
    &checkResult19to36
};
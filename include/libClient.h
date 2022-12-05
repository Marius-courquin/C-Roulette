#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif

#ifndef CLIENT
#include "client.h"
#define CLIENT 1
#endif


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

void displayRouletteTable();
int checkComposition(int betTab[],int compositionCount);
int checkBetValue(char *string);
void bet(clientData *client,betData **betList, int *nbOfBetInProgress );
void addNewBet(betData **betList, int *nbOfBetInProgress,int amount, char *bet);
int inputBet(clientData *client) ;
int containSeparatorField(char *str, char separator);
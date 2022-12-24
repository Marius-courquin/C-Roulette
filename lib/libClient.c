#include "../include/libClient.h"
#include "../include/libUtils.h"
#include "../include/libUserStorage.h"
#include <string.h>


int resultReceived = 0;

void displayRouletteTable(){
    printf("----------------------------------------------------------------------\n");   
    printf("|   |"RED"  3 "RESET"|"BLCK"  6 "RESET"|"RED"  9 "RESET"|"RED" 12 "RESET"|"BLCK" 15 "RESET"|"RED" 18 "RESET"|"RED" 21 "RESET"|"BLCK" 24 "RESET"|"RED" 27 "RESET"|"RED" 30 "RESET"|"BLCK" 33 "RESET"|"RED" 36 "RESET"|2TO1|\n");
    printf("|   |-----------------------------------------------------------------\n");    
    printf("|"GRN" 0 "RESET"|"BLCK"  2 "RESET"|"RED"  5 "RESET"|"BLCK"  8 "RESET"|"BLCK" 11 "RESET"|"RED" 14 "RESET"|"BLCK" 17 "RESET"|"BLCK" 20 "RESET"|"RED" 23 "RESET"|"BLCK" 26 "RESET"|"BLCK" 29 "RESET"|"RED" 32 "RESET"|"BLCK" 35 "RESET"|2TO2|\n");
    printf("|   |-----------------------------------------------------------------\n");   
    printf("|   |"RED"  1 "RESET"|"BLCK"  4 "RESET"|"RED"  7 "RESET"|"BLCK" 10 "RESET"|"BLCK" 13 "RESET"|"RED" 16 "RESET"|"RED" 19 "RESET"|"BLCK" 22 "RESET"|"RED" 25 "RESET"|"BLCK" 28 "RESET"|"BLCK" 31 "RESET"|"RED" 34 "RESET"|2TO3|\n");
    printf("----------------------------------------------------------------------\n");
    printf("    |       1st12       |       2nd12       |       3rd12       |     \n");
    printf("    -------------------------------------------------------------     \n");
    printf("    |  1TO18  |   EVEN  |"RED"   RED   "RESET"|"BLCK"  BLACK  "RESET"|   ODD   | 19TO36  |     \n");
    printf("    -------------------------------------------------------------     \n");
}

int containSeparatorField(char *str, char separator){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == separator){
            return 1;
        }
    }
    return 0;
}
int checkBetValue(char *string, int *multiplicator){
    char *token;
    int result;
    
    if (containSeparatorField(string, ':') == 0) {
        for(int i = 0; i < 12; i++){
            if(strcmp(string, betType[i]) == 0) {
                *multiplicator = betTypeMultiplicator[i];
                return 1;
            }
        }
        result = atoi(string);
        if(result == 0){
            if(strcmp(string, "0") == 0){
                *multiplicator = 36;
                return 1;
            }
            return -1;
        }
        if(result >= 0 && result <= 36) {
            *multiplicator = 36;
            return 1;
        }
        return -1;
    }
    else{ //if token is a composition of 2 to 6 values
        token = strtok(string, ":");
        int compositionCount = 0;
        int result[6];
        while(token != NULL){
            result[compositionCount] = atoi(token);
            if(result[compositionCount] == 0){ //possible error
                if(strcmp(token, "0") == 0) //ok it's a 0
                    result[compositionCount] =  0;
                else //error
                    return -1;
                
            }
            if(result[compositionCount] < 0 && result[compositionCount] > 36)
                return -1;
            token = strtok(NULL, ":");
            compositionCount++;
        }
        return checkComposition(result, compositionCount, multiplicator);
    }
}

int checkComposition(int betTab[],int compositionCount, int *multiplicator){
            if(compositionCount >= 2 && compositionCount <= 4 || compositionCount == 6){
                switch(compositionCount){
                    case 2 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) || ( abs(betTab[1] - betTab[0]) == 3 ) ) {
                            *multiplicator = 18;
                            return 1;
                        }
                            
                        else
                            return -1;
                        
                    break;
                    case 3 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) && (abs(betTab[2] - betTab[1]) == 1 ) ) {
                            *multiplicator = 12;
                            return 1;
                        }
                        else
                            return -1;
                    case 4 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) && (abs(betTab[2] - betTab[3]) == 1)){
                            if( (abs(betTab[0] - betTab[2]) == 3) && (abs(betTab[1] - betTab[3]) == 3)) {
                                *multiplicator = 9;
                                return 1;
                            }
                            else
                                return -1;
                        }
                        else
                            return -1;
                    case 6 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) && (abs(betTab[1] - betTab[2]) == 1) && (abs(betTab[2] - betTab[3]) == 1)){
                            if((abs(betTab[3] - betTab[4]) == 1 ) && (abs(betTab[4] - betTab[5]) == 1)) {
                                *multiplicator = 6;
                                return 1;
                            }
                            else
                                return -1;
                        }
                        else
                            return -1;
                    break;

                }
        }
        else
            return -1;  
}

void bet(clientData *client,betData **betList, int *nbOfBetInProgress ) {
    betData newBet;
    char userInput[20];
    int multiplicator = 0;
betting :
    displayRouletteTable();
    printf("Available money : %d$\n", client->money);
    displayBetInProgress(*betList, *nbOfBetInProgress);
    printf("What do you want to bet on ? ( END to stop the bet )\n");
    strcpy(userInput, "");
    fgets(userInput, 20, stdin);
    userInput[strlen(userInput)-1] = '\0';
    if (strcmp(userInput, "END") == 0) {
        clearTerminal();
        displayBetInProgress(*betList, *nbOfBetInProgress);
        printf("End of the bet !\n");
        printf("Waiting for the draw !\n");
    }
    else if(checkBetValue(userInput, &multiplicator) == -1){
        clearTerminal();
        printf("Invalid bet !\n");
        goto betting;
        
    }
    else {
        int money = inputBet(client);
        addNewBet(betList,nbOfBetInProgress, money, userInput, multiplicator);
        clearTerminal();
        updateUserInformation(client->name, client->money);
        goto betting;
    }  

}

int inputBet(clientData *client) {
    char userInput[20];
moneyInput : 
    printf("How much do you want to bet ?\n");
    fgets(userInput, 20, stdin);
    userInput[strlen(userInput)-1] = '\0';
    
    if(atoi(userInput) > client->money) {
        printf("You don't have enough money to bet that much !\n"); 
        goto moneyInput;   
    } 
    else {
        client->money -= atoi(userInput);
        return atoi(userInput);
    }
}

void addNewBet(betData **betList, int *nbOfBetInProgress,int amount, char *bet, int multiplicator) {
    *betList = (betData*)realloc(*betList, sizeof(betData) * (*nbOfBetInProgress + 1));
    betList[*nbOfBetInProgress]->amount = amount;
    betList[*nbOfBetInProgress]->bet = bet;
    betList[*nbOfBetInProgress]->multiplicator = multiplicator;
    *nbOfBetInProgress = *nbOfBetInProgress + 1;
}
/**
int computeGain(int drawResult,betData *betList,int lenTab){
    for(int i =  0; i < lenTab;i++){
        if(isDigit(betList[i].bet))
    }
}*/

void displayBetInProgress(betData *betList, int betInProgress) {
    if (betInProgress > 0) {
        printf("Bet in progress : ");
        for (int i = 0; i < betInProgress; i++) {
            printf("%d. %d$ on %s   ", i + 1, betList[i].amount, betList[i].bet);
        }
        printf("\n");
    }
}

void drawResultReceived() {
    resultReceived = 1;
}

int getResultReceived() {
    return resultReceived;
}

// void checkBetResult(int *drawResult, betData *betList, int *nbOfBetInProgress, clientData *client) {
//     if (resultReceived == 1) {
//         for (int i = 0; i < *nbOfBetInProgress; i++) {
//             if (isDigit(betList[i].bet)) {
//                 if (atoi(betList[i].bet) == *drawResult) {
//                     client->money += betList[i].amount * betList[i].multiplicator;
//                 }
//             } else {
//                 if (checkBetValue(betList[i].bet, &betList[i].multiplicator) == 1) {
//                     client->money += betList[i].amount * betList[i].multiplicator;
//                 }
//             }
//         }
//         updateUserInformation(client->name, client->money);
//         free(betList);
//         *nbOfBetInProgress = 0;
//         resultReceived = 0;
//     }
// }

void displayBetResult (int result) {
    if(checkIfResultIsRed(result) == 1) {
        printf("The result is : "RED"%d !\n"RESET, result);
    }
    else if(checkIfResultIsBlack(result) == 1) {
        printf("The result is : "BLCK"%d !\n"RESET, result);
    }
    else {
        printf("The result is : "GRN"%d !\n"RESET, result);
    }
}

int checkIfResultIsRed(int result) {
    for (int i = 0; i < 18; i++) {
        if (result == redNumbers[i]) {
            return 1;
        }
    }
    return 0;
}

int checkIfResultIsBlack(int result) {
    for (int i = 0; i < 18; i++) {
        if (result == blackNumbers[i]) {
            return 1;
        }
    }
    return 0;
}
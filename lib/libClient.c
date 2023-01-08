#include "../include/libClient.h"
#include "../include/libUtils.h"
#include "../include/libUserStorage.h"
#include "../include/libSharedMemory.h"
#include <string.h>


extern int sharedMemoryId;


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
int checkDigitOnly(char *str){
    if(strlen(str) == 0)
        return 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] < '0' || str[i] > '9'){
            return 0;
        }
    }
    return 1;
}

int checkBetValue(char *string, int *multiplicator){
    int result;
    if (containSeparatorField(string, ':') == 0) {
        for(int i = 0; i < 12; i++){
            if(strcmp(string, betType[i]) == 0) {
                *multiplicator = betTypeMultiplicator[i];
                return 1;
            }
        }
        if(checkDigitOnly(string) == 0)
            return -1;
        result = atoi(string);
        if(result == 0){
            if(strcmp(string, "0") == 0){
                *multiplicator = 36;
                return 1;
            }
            else
                return -1;
        }
        if(result >= 0 && result <= 36) {
            *multiplicator = 36;
            return 1;
        }
        else
            return -1;
    }
    else{ //if token is a composition of 2 to 6 values
        int compositionCount = 0;
        int result[6];
        if(decomposition(result,&compositionCount,string) == -1)
            return -1;
        else
            return checkComposition(result, compositionCount, multiplicator);
    }
}
int decomposition(int *result,int *compositionCount,char *string){
    char stringCopy[strlen(string)];
    strcpy(stringCopy, string);
    char *token = strtok(stringCopy, ":");
    while(token != NULL){
        if(checkDigitOnly(token) == 0)
            return -1;
        result[*compositionCount] = atoi(token);
        if(result[*compositionCount] == 0){ //possible error
            if(strcmp(token, "0") == 0) //ok it's a 0
                result[*compositionCount] =  0;
            else //error
                return -1;
            
        }
        if(result[*compositionCount] < 0 && result[*compositionCount] > 36){
            *compositionCount = -1;
            return -1;

        }
        token = strtok(NULL, ":");
        *compositionCount+=1;
    }
    return 1;
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
                            if( (abs(betTab[0] - betTab[2]) == 2) && (abs(betTab[1] - betTab[3]) == 2)) {
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
void displayUserInGame(){
    serverData sharedMemoryContent = readSharedMemory(sharedMemoryId);
    printf("User In Game : %d\n",sharedMemoryContent.nbClient);
}
int bet(clientData *client,betData **betList, int *nbOfBetInProgress ) {
    betData newBet;
    char userInput[20];
    int multiplicator = 0;
betting :
    displayUserInGame();
    displayRouletteTable();
    printf("Available money : %d$\n", client->money);
    displayBetInProgress(*betList, *nbOfBetInProgress);
    printf("What do you want to bet on ? ( END to stop the bet / QUIT to leave the table)\n");
    strcpy(userInput, "");
    fgets(userInput, 20, stdin);
    userInput[strlen(userInput)-1] = '\0';
    if (strcmp(userInput, "END") == 0) {
        clearTerminal();
        displayBetInProgress(*betList, *nbOfBetInProgress);
        printf("End of the bet !\n");
        printf("Waiting for the draw !\n");
        return 0;
    }
    else if (strcmp(userInput, "QUIT") == 0) {
        if (*nbOfBetInProgress > 0) {
            clearTerminal();
            printf("You can't leave the table while you have bet !\n");
            goto betting;
        }
        printf("You left the table !\n");
        return -1;
    }
    else if(checkBetValue(userInput, &multiplicator) == -1){
        clearTerminal();
        printf("Invalid bet !\n");
        goto betting;
    }
    else {
        int money = inputBet(client);
        addNewBet(betList,nbOfBetInProgress, money, userInput, multiplicator);
        updateUserInformation(client->name, client->money);
        clearTerminal();
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
    else if(atoi(userInput) <= 0) {
        printf("You can't bet that much !\n");
        goto moneyInput;
    } 
    else {
        client->money -= atoi(userInput);
        return atoi(userInput);
    }
}

void addNewBet(betData **betList, int *nbOfBetInProgress,int amount, char *bet, int multiplicator) {
    *betList = (betData*)realloc(*betList, sizeof(betData) * (*nbOfBetInProgress + 1));
    (*betList)[*nbOfBetInProgress].amount = amount;
    strcpy((*betList)[*nbOfBetInProgress].bet,bet);
    (*betList)[*nbOfBetInProgress].multiplicator = multiplicator;
    *nbOfBetInProgress = *nbOfBetInProgress + 1;
}

int computeGain(int drawResult,betData *betList,int arrayLen){
    int gain = 0;
    int composition[6];
    int compositionLen = 0;
    int flagWin = 0;
    for(int i =  0; i < arrayLen;i++){
        for(int j = 0; j < 12; j++){
            if(strcmp(betList[i].bet, betType[j]) == 0){
                if (functionsArray[j](drawResult) == 1){
                    gain += betList[i].amount * betList[i].multiplicator;
                    flagWin = 1;
                    break;
                }
            }
        }
       decomposition(composition,&compositionLen,betList[i].bet);
        if(compositionLen > 0){
            for(int k = 0; k < compositionLen; k++){
                if(composition[k] == drawResult){
                    gain += (betList[i].amount) * (betList[i].multiplicator);
                    composition[k] = 0;
                    flagWin = 1;
                    break;
                }
            }
        }
        else{
            if(atoi(betList[i].bet) == drawResult){
                gain += betList[i].amount * betList[i].multiplicator;
                flagWin = 1;
            }
        }
        if(flagWin == 1){
            printf("You won "GRN"%d$ "RESET" on "RED"%s"RESET"\n",betList[i].amount * betList[i].multiplicator,betList[i].bet);
            flagWin = 0;
        }
        compositionLen = 0;
    }
    if(gain > 0)
        printf("The total gain is : "GRN"%d$"RESET"\n",gain);
    else if(arrayLen == 0) {
        printf("You have not bet this round !\n");
        printf(RED"NO BET = NO GAIN !"RESET"\n");
    }
    else{
        printf(RED"You lost !\n"RESET);
    }
    return gain;
}

void displayBetInProgress(betData *betList, int betInProgress) {
    if (betInProgress > 0) {
        printf("Bet in progress : ");
        for (int i = 0; i < betInProgress; i++) {
            printf("%d. %d$ on %s   ", i + 1, betList[i].amount, betList[i].bet);
        }
        printf("\n");
    }
}

void writeBestBet(int gain, char *username){
    serverData sharedMemoryContent = readSharedMemory(sharedMemoryId);
    if(gain > 0 && sharedMemoryContent.client.gain < gain){
        sharedMemoryContent.client.gain = gain;
        strcpy(sharedMemoryContent.client.username,username);
        writeSharedMemory(sharedMemoryContent,sharedMemoryId);
    }
}

void displayBestBet(){
    serverData sharedMemoryContent = readSharedMemory(sharedMemoryId);
    if (sharedMemoryContent.client.gain > 0)
        printf("Best bet : "GRN" %s "RESET" with "RED"%d$ "RESET" \n",sharedMemoryContent.client.username,sharedMemoryContent.client.gain);
}

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

int checkResult1to18 (int result){
    for(int i = 0; i <= 18 ; i++){
        if (i == result)
            return 1;
    }
    return 0;
}
int checkResult19to36 (int result){
    for(int i = 19; i <= 36 ; i++){
        if (i == result)
            return 1;
    }
    return 0;
}
int checkResult2to1 (int result) {
    for(int i = 3; i <= 36 ; i+=2){
        if (i == result)
            return 1;
    }
    return 0;
}
int checkResult2to2(int result) {
    for(int i = 2; i <= 35 ; i+=2){
        if (i == result)
            return 1;
    }
    return 0;
}
int checkResult2to3(int result) {
    for(int i = 1; i <= 34 ; i+=2){
        if (i == result)
            return 1;
    }
    return 0;
}
int checkResult1st12(int result){
    for(int i = 0; i <= 12 ; i++){
        if (i == result)
            return 1;  
    }
    return 0;
}
int checkResult2nd12(int result){
    for(int i = 13; i <= 24 ; i++){
        if (i == result)
            return 1;  
    }
    return 0;
}
int checkResult3rd12(int result){
    for(int i = 25; i <= 36 ; i++){
        if (i == result)
            return 1;  
    }
    return 0;
}
int checkResultEven(int result){
    if(result % 2 == 0)
        return 1;
    else
        return 0;
}
int checkResultOdd(int result){;
    if(result % 2 != 0)
        return 1;
    else
        return 0;
}

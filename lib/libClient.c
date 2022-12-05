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

int containSeparatorField(char *str, char separator){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == separator){
            return 1;
        }
    }
    return 0;
}
int checkBetValue(char *string){
    char *token;
    int result;
    
    if (containSeparatorField(string, ':') == 0) {
        for(int i = 0; i < 12; i++){
            if(strcmp(string, betType[i]) == 0)
                return 1;
        }
        result = atoi(string);
        if(result == 0){
            if(strcmp(string, "0") == 0){
                return 1;
            }
            return -1;
        }
        if(result >= 0 && result <= 36)
            return 1;
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
        return checkComposition(result, compositionCount);
    }
}

int checkComposition(int betTab[],int compositionCount){
            if(compositionCount >= 2 && compositionCount <= 4 || compositionCount == 6){
                switch(compositionCount){
                    case 2 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) || ( abs(betTab[1] - betTab[0]) == 3 ) )
                            return 1;
                        else
                            return -1;
                        
                    break;
                    case 3 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) && (abs(betTab[2] - betTab[1]) == 1 ) )
                            return 1;
                        else
                            return -1;
                    case 4 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) && (abs(betTab[2] - betTab[3]) == 1)){
                            if( (abs(betTab[0] - betTab[2]) == 3) && (abs(betTab[1] - betTab[3]) == 3))
                                return 1;
                            else
                                return -1;
                        }
                        else
                            return -1;
                    case 6 :
                        if( (abs(betTab[1] - betTab[0]) == 1 ) && (abs(betTab[1] - betTab[2]) == 1) && (abs(betTab[2] - betTab[3]) == 1)){
                            if((abs(betTab[3] - betTab[4]) == 1 ) && (abs(betTab[4] - betTab[5]) == 1))
                                return 1;
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
betting :
    displayRouletteTable();
    printf("Available money : %d$\n", client->money);
    printf("What do you want to bet on ? ( END to stop the bet )\n");
    fgets(userInput, 20, stdin);
    userInput[strlen(userInput)-1] = '\0';
    if (strcmp(userInput, "END") == 0) {
        system("clear");
        if (nbOfBetInProgress > 0) {
            displayBetInProgress(betList, nbOfBetInProgress);
        }
        printf("End of the bet !\n");
        printf("Waiting for the draw !\n");
    }
    else if(checkBetValue(userInput) == -1){
        printf("Invalid bet !\n");
        goto betting;
    }
    else {
        int money = inputBet(client);
        addNewBet(betList,nbOfBetInProgress, money,userInput);
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
        system("clear");
        printf("You don't have enough money to bet that much !\n"); 
        goto moneyInput;   
    } 
    else {
        client->money -= atoi(userInput);
        system("clear");
        return atoi(userInput);
    }
}

void addNewBet(betData **betList, int *nbOfBetInProgress,int amount, char *bet) {
    *betList = (betData*)realloc(*betList, sizeof(betData) * (*nbOfBetInProgress + 1));
    betList[*nbOfBetInProgress]->amount = amount;
    betList[*nbOfBetInProgress]->bet = bet;
    *nbOfBetInProgress = *nbOfBetInProgress + 1;
}
/**


int computeGain(int drawResult,betData *betList,int lenTab){
    for(int i =  0; i < lenTab;i++){
        if(isDigit(betList[i].bet))
    }
}*/
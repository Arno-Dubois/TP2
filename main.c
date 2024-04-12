#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct line {
    char lineName[32];
    struct line *nextLine;
}line;
line *lineHead = NULL;

typedef struct stop {
    char stopName[32];
    struct stop *nextStop;
    struct line *linelist;
}stop;
stop *stopHead = NULL;

void createStop(char stopName[], char lineName[][32]) {
    stop *newStop = malloc(sizeof(stop));
    strcpy(newStop -> stopName, stopName);
    newStop -> nextStop = NULL;
    

    line *lastNewStopLine = NULL;
    
    for (int loopThroughLineName = 0; strcmp(lineName[loopThroughLineName], "\0") != 0; ++loopThroughLineName) {
        line *newStopLineList = malloc(sizeof(line));
        strcpy(newStopLineList -> lineName, lineName[loopThroughLineName]);
        
        if(lastNewStopLine != NULL) {
            lastNewStopLine->nextLine = newStopLineList;
            
        }
        if(loopThroughLineName == 1)
            lineHead = lastNewStopLine;
        lastNewStopLine = newStopLineList;
        

    }
    
    newStop -> linelist = lineHead;

    
    stop *findLastStop = stopHead;
    stop *previousStop = NULL;
    while(findLastStop != NULL) {
        
        previousStop = findLastStop;
        findLastStop = findLastStop -> nextStop;
    }
    findLastStop = newStop;
    if(previousStop != NULL)
        previousStop -> nextStop = findLastStop;
    if(stopHead == NULL)
        stopHead = findLastStop;
    
}

void findWay(stop *requestedStop) {
    
    line *getRequestedLine = requestedStop -> linelist;
    

    char found = 0;
    while(getRequestedLine != NULL) {
        

        line *getFirstStopLine = stopHead -> linelist;
        if(getFirstStopLine!=NULL&&strcmp(getRequestedLine -> lineName, getFirstStopLine -> lineName) == 0) {
            
            found = 1;
            break;
        }
        while(getFirstStopLine != NULL && strcmp(getRequestedLine -> lineName, getFirstStopLine -> lineName) != 0) {
            
            getFirstStopLine = getFirstStopLine -> nextLine;
        }
        getRequestedLine = getRequestedLine -> nextLine;
    }
    if(found != 1)
        printf("No linked line");
    else
        printf("Linked line found");
}

int main(void) {
    char newStopLineList[][32] = {"Rouge", "Violette", "\0"};
    createStop("Jean-Louis", newStopLineList);
    char JP[][32] = {"Violette", "Bleu", "\0"};
    createStop("Jean-Pasquale", JP);
    char BP[][32] = {"Bleu", "Orange", "\0"};
    createStop("Blaze-Pasquale", BP);
    

    stop *findRequestedStop = NULL;
    while(findRequestedStop == NULL) {
        char stopDestinationSelected[32];
        printf("Choose your stop destination\n");
        scanf("%s", &stopDestinationSelected);
        fflush(stdin);

        findRequestedStop = stopHead;
        while (findRequestedStop != NULL && strcmp(stopDestinationSelected, findRequestedStop -> stopName) != 0) {
            
            findRequestedStop = findRequestedStop->nextStop;
        }
        if(findRequestedStop == NULL)
            printf("No destination %s found, please retry\n", stopDestinationSelected);
        else
            findWay(findRequestedStop);

    };

    return 0;
}

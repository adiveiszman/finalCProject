#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define TICKET_LEN 6

typedef struct ticketNode {
    int ticket[TICKET_LEN];
    int hits;
    struct ticketNode* next;
} TicketNode;

typedef struct ticketList {
    TicketNode* head;
    TicketNode* tail;
} TicketList;

typedef struct participantNode {
    char* name;
    TicketList* tickets;
    int avgHits;
    struct participant* next;
} ParticipantNode;

typedef struct participantList {
    ParticipantNode* head;
    ParticipantNode* tail;
} ParticipantList;

typedef struct hitNode {
    int hitNum;
    int ticketCounter;
    struct hitNode* next;
} HitNode;

typedef struct hitList {
    HitNode* head;
    HitNode* tail;
} HitList;

////////////Scanning functions////////////
//This function prints the main menu
void mainMenu();
//This function is the lotto loop
void lottoLoop(int userChoice);
//This function starts a new lotto simulation (option 1)
void startNewSimulation();
//This function scans number of participant for current lotto and validate it
void scanNumOfParticipants(int* numOfParticipants);
//This function shows last lotto results (option 2)
void viewLastResults(); 
//This function starts single participant menu
void singleParticipantMenu(ParticipantList* participantsList);
//This function produces single participant tickets by choise between manual - 1 / auto - 2 
void produceParticipantTickets(int lottoChoice, TicketList* ticketList, int* ticketsNum);
//This function scans number of tickets for participant
void scanTicketsNum(int* ticketsNum);
//This function scans ticket list for participant
void scanTicketList(TicketList* ticketList, int ticketsNum);
//This function generates a ticket list (for auto choice)
void generateTicketList(TicketList* ticketList, int ticketsNum);
//This function generates a ticket by random numbers
void generateTicket(int* ticket);
//This function prints a given ticket
void printTicket(int* ticket);
//This function validates a given number is valid
bool isValidTicketNum(int num);
//This function generated a random number for a ticket
int generateRandomTicketNum();
//This function scans a participant name
void scanParticipantName(char** participantNm);
//This function inserts a new HitNode with data to the end of the HitList
void insertDataToEndHitList(HitList* lst, int hitNum, int ticketCounter);
//This function creates new HitNode and returns it
HitNode* createNewHitNode(int hitNum, int ticketCounter, HitNode* next);
//This function inserts a HitNode to the end of the HitList
void insertNodeToEndHitNode(HitList* lst, HitNode* newTail);
//This function inserts a new HitNode with data to the end of the TicketList
void insertDataToEndTicketList(TicketList* lst, int* ticket, int hits);
//This function creates new TicketNode and returns it
TicketNode* createNewTicketNode(int* ticket, int hits, TicketNode* next);
//This function inserts a TicketNode to the end of the TicketList
void insertNodeToEndTicketNode(TicketList* lst, TicketNode* newTail);
//This function inserts a new ParticipantNode with data to the end of the ParticipantList
void insertDataToEndParticipantList(ParticipantList* lst, char* name, TicketList* tickets, int avgHits);
//This function creates new ParticipantNode and returns it
ParticipantNode* createNewParticipantNode(char* name, TicketList* tickets, int avgHits, ParticipantNode* next);
//This function inserts a ParticipantNode to the end of the ParticipantList
void insertNodeToEndParticipantNode(ParticipantList* lst, ParticipantNode* newTail);
//This function initiates an empty HitList
void makeEmptyHitList(HitList* lst);
//This function initiates an empty TicketList
void makeEmptyTicketList(TicketList* lst);
//This function initiates an empty ParticipantList
void makeEmptyParticipantList(ParticipantList* lst);
//This funcrtion checks if HitList is empty
bool isEmptyHitList(HitList lst);
//This funcrtion checks if TicketList is empty
bool isEmptyTicketList(TicketList lst);
//This funcrtion checks if ParticipantList is empty
bool isEmptyParticipantList(ParticipantList lst);
//This function free HitList
void freeHitList(HitList* lst);
//This function free TicketList
void freeTicketList(TicketList* lst);
//This function free ParticipantList
void freeParticipantList(ParticipantList* lst);
//This function checks if a memory allocation succeeded
void checkMemoryAllocation(void* ptr);




bool isChoiceValid(int userChoice);
ParticipantList* buildParticipantList(int numOfParticipants);
int* GenerateWinningTicket();
void updateParticipantsList(ParticipantList* participants, int* winningTicket);// update for each participant num of hit for each ticket + avg hit for each participant
void updateParticipantHits(ParticipantNode* participant);//use inside updateParticipantsList
void sortTicketList(TicketList* lst);
void printResults(ParticipantList* lst, int* winningTicket);

void saveLastGame(ParticipantList* lst, int numOfParticipants, char* fileName);
ParticipantList* bulidParticipantsListFromFile(char* fileName);
void freePaticipantsList(ParticipantList* lst);

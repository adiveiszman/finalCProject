#include "mainFunc.h"

void mainMenu() {
	int userChoice;

	printf("Welcome to our lotto!\n"
		"Press 1 for starting a new lotto simulation.\n"
		"Press 2 for last lottery results.\n"
		"Press 3 for exit.\n");
	scanf("%d", &userChoice);

	lottoLoop(userChoice);
}

void lottoLoop(int userChoice) {
	switch (userChoice) {
	case(1):
		startNewSimulation();
		break;
	case(2):
		viewLastResults();
		break;
	case(3):
		printf("Thanks for using our lotto simulation :)");
		break;
	default:
		printf("Your input is invalid.\n");
		mainMenu();
		break;
	}
}

void startNewSimulation() {
	ParticipantList participantsList;
	int numOfParticipants, i, *winningTicket[TICKET_LEN];

	makeEmptyParticipantList(&participantsList);
	scanNumOfParticipants(&numOfParticipants);

	for (i = 0; i < numOfParticipants; i++) {
		singleParticipantMenu(&participantsList);
	}

	generateTicket(winningTicket);
}

void scanNumOfParticipants(int* numOfParticipants) {
	int num;

	printf("Please enter number of participants:\n");
	scanf("%d", &num);

	//more validation ??????????????
	while (num < 1) {
		printf("Your input is invalid.\n"
			"Please enter number of participants:\n");
		scanf("%d", &num);
	}

	*numOfParticipants = num;
}

void singleParticipantMenu(ParticipantList* participantsList) {
	char* participantNm;
	int lottoChoice, ticketsNum;
	TicketList ticketList;

	makeEmptyTicketList(&ticketList);

	printf("Please enter participant name:\n");
	scanParticipantName(&participantNm);

	printf("Press 1 for manual lotto mode.\n"
		"Press 2 for automatic lotto mode.\n");
	scanf("%d", &lottoChoice);

	produceParticipantTickets(lottoChoice, &ticketList, &ticketsNum);
	insertDataToEndParticipantList(participantsList, participantNm, &ticketList, 0);
}

void produceParticipantTickets(int lottoChoice, TicketList* ticketList, int* ticketsNum) {
	int newLottoChoice;

	switch (lottoChoice) {
	case(1):
		scanTicketsNum(ticketsNum);
		scanTicketList(ticketList, *ticketsNum);
		break;
	case(2):
		scanTicketsNum(ticketsNum);
		generateTicketList(ticketList, *ticketsNum);
		break;
	default:
		printf("Your input is invalid.\n"
			"Please enter a valid mode:\n");
		scanf("%d", &newLottoChoice);
		produceParticipantTickets(newLottoChoice, ticketList, ticketsNum);
		break;
	}
}

void scanTicketsNum(int* ticketsNum) {
	printf("Please enter required tickets number:\n");
	scanf("%d", ticketsNum);

	//more validation ??????????????
	while (ticketsNum < 1) {
		printf("Your input is invalid.\n"
			"Please enter required tickets number:\n");
		scanf("%d", ticketsNum);
	}
}

void scanTicketList(TicketList* ticketList, int ticketsNum) {
	int i, j, num, ticket[TICKET_LEN];

	for (i = 0; i < ticketsNum; i++) {
		printf("Ticket number %d:\n", i + 1);
		printf("Please enter 6 digits- ");
		for (j = 0; j < TICKET_LEN; j++) {
			scanf("%d", &num);

			if (isValidTicketNum(num)) {
				ticket[j] = num;
			}
			else {
				printf("Your input is invalid, please try again.\n");
				j--;
			}
		}
		insertDataToEndTicketList(ticketList, ticket, 0);
	}
}

void generateTicketList(TicketList* ticketList, int ticketsNum) {
	int i, ticket[TICKET_LEN];

	for (i = 0; i < ticketsNum; i++) {
		printf("Ticket number %d:\n", i + 1);
		generateTicket(ticket);
		printTicket(ticket);
		insertDataToEndTicketList(ticketList, ticket, 0);
	}
}

void generateTicket(int* ticket) {
	int i, num;

	for (i = 0; i < TICKET_LEN; i++) {
		num = generateRandomTicketNum();

		if (isValidTicketNum(num)) {
			ticket[i] = num;
		}
		else {
			i--;
		}
	}
}

void printTicket(int* ticket) {
	int i;

	for (i = 0; i < TICKET_LEN; i++) {
		printf("%d ", ticket[i]);
	}
	printf("\n");
}

bool isValidTicketNum(int num) {
	//to do
}

//to fix - generating same numbers because of fast running
int generateRandomTicketNum() {
	int num;

	srand(time(NULL));
	num = 1 + rand() % 16;

	return num;
}

void scanParticipantName(char** participantNm) {
	char* name;
	char c;
	int logicalSize = 0, physicalSize = 2;

	name = (char*)malloc(sizeof(char) * (physicalSize + 1));
	checkMemoryAllocation(name);

	scanf(" %c", &c);
	while (c != '\n') {
		if (logicalSize >= physicalSize) {
			physicalSize = physicalSize * 2;
			name = (char*)realloc(name, sizeof(char) * (physicalSize + 1));
			checkMemoryAllocation(name);
		}

		name[logicalSize] = c;
		logicalSize++;
		scanf("%c", &c);
	}

	name[logicalSize] = '\0';
	name = (char*)realloc(name, sizeof(char) * (logicalSize + 1));

	checkMemoryAllocation(name);
	*participantNm = name;
}

void viewLastResults() {

}

void insertDataToEndHitList(HitList* lst, int hitNum, int ticketCounter) {
	HitNode* newTail;

	newTail = createNewHitNode(hitNum, ticketCounter, NULL);
	insertNodeToEndHitNode(lst, newTail);
}

HitNode* createNewHitNode(int hitNum, int ticketCounter, HitNode* next) {
	HitNode* node = (HitNode*)malloc(sizeof(HitNode));
	checkMemoryAllocation(node);

	node->hitNum = hitNum;
	node->ticketCounter = ticketCounter;
	node->next = next;

	return node;
}

void insertNodeToEndHitNode(HitList* lst, HitNode* newTail) {
	if (isEmptyHitList(*lst)) {
		lst->head = lst->tail = newTail;
	}
	else {
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void insertDataToEndTicketList(TicketList* lst, int* ticket, int hits) {
	TicketNode* newTail;

	newTail = createNewTicketNode(ticket, hits, NULL);
	insertNodeToEndTicketNode(lst, newTail);
}

TicketNode* createNewTicketNode(int* ticket, int hits, TicketNode* next) {
	TicketNode* node = (TicketNode*)malloc(sizeof(TicketNode));
	checkMemoryAllocation(node);

	for (int i = 0; i < TICKET_LEN; i++) {
		node->ticket[i] = ticket[i];
	}

	node->hits = hits;
	node->next = next;

	return node;
}

void insertNodeToEndTicketNode(TicketList* lst, TicketNode* newTail) {
	if (isEmptyTicketList(*lst)) {
		lst->head = lst->tail = newTail;
	}
	else {
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void insertDataToEndParticipantList(ParticipantList* lst, char* name, TicketList* tickets, int avgHits) {
	ParticipantNode* newTail;

	newTail = createNewParticipantNode(name, tickets, avgHits, NULL);
	insertNodeToEndParticipantNode(lst, newTail);
}

ParticipantNode* createNewParticipantNode(char* name, TicketList* tickets, int avgHits, ParticipantNode* next) {
	ParticipantNode* node = (ParticipantNode*)malloc(sizeof(ParticipantNode));
	checkMemoryAllocation(node);

	node->name = (char*)malloc(strlen(name) * sizeof(char));
	checkMemoryAllocation(node->name);

	strcpy(node->name, name);
	node->tickets = tickets;
	node->avgHits = avgHits;
	node->next = next;

	return node;
}

void insertNodeToEndParticipantNode(ParticipantList* lst, ParticipantNode* newTail) {
	if (isEmptyParticipantList(*lst)) {
		lst->head = lst->tail = newTail;
	}
	else {
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void makeEmptyHitList(HitList* lst) {
	lst->head = lst->tail = NULL;
}

void makeEmptyTicketList(TicketList* lst) {
	lst->head = lst->tail = NULL;
}

void makeEmptyParticipantList(ParticipantList* lst) {
	lst->head = lst->tail = NULL;
}

bool isEmptyHitList(HitList lst) {
	return (lst.head == NULL);
}

bool isEmptyTicketList(TicketList lst) {
	return (lst.head == NULL);
}

bool isEmptyParticipantList(ParticipantList lst) {
	return (lst.head == NULL);
}

void freeHitList(HitList* lst) {
	HitNode* curr = lst->head, *saver;

	while (curr != NULL) {
		saver = curr->next;
		free(curr);
		curr = saver;
	}
}

void freeTicketList(TicketList* lst) {
	TicketNode* curr = lst->head, *saver;

	while (curr != NULL) {
		free(curr->ticket);
		saver = curr->next;
		free(curr);
		curr = saver;
	}
}

void freeParticipantList(ParticipantList* lst) {
	ParticipantNode* curr = lst->head, *saver;

	while (curr != NULL) {
		free(curr->name);
		freeTicketList(curr->tickets);
		saver = curr->next;
		free(curr);
		curr = saver;
	}
}

void checkMemoryAllocation(void* ptr) {
	if (ptr == NULL) {
		printf("Memory allocation failed!");
		exit(1);
	}
}

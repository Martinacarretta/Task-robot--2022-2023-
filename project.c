/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1
Names and nius: Martina Carretta - 1673930 and Meritxell Carvajal - 1671647
Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include "project1.h" // header with all data structures

//---------------------------------------------------------------------------------------------------------------------------------------General
enum EventType GenerateEventType() // WARNING: do not change this function
{
	return rand()%3; //creates a random number between 0 and 2
}

int CheckArguments (int argc, char ** argv)
{
	if (argc != 2) {  // check the input introduced by the user
        printf("Not the correct format for the program\n");
        return 1;
    }
    else {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------Books
struct Book * GenerateBook() // WARNING: do not change this function
{
	struct Book * book = malloc(sizeof(struct Book)); // reserve memory for a book
	int bookNum = rand()%8;

	strcpy (book -> author, authors[bookNum]); // initialize the book's fields
	strcpy (book -> title, titles[bookNum]);
	int year=rand()%40+1980;
	book -> year = year;
	return book;
}

void PrintBooks() // function to print a list of books
{
	if (booksHead == NULL) { // in case there are no books
        printf ("List: (-)\n");
    }
    else {
        printf ("List: ");
        struct Book * current = booksHead;
        printf("%s '%s' %d, ", current -> author, current -> title, current -> year);
        while (current -> next != NULL) {
            current = current -> next;
            printf("%s '%s' %d, ", current -> author, current -> title, current -> year);
        }
    }
    printf("\n\n");
}

void SortingBooks(struct Book * book) // function to search for a book
{
    //booksHead is the first book in the list
    //book is the book we want to introduce
    //current is the pointer to the current book of the list being analyzed
    struct Book * current = booksHead;
    if (booksHead == NULL) { // empty list
        booksHead = book;
        booksHead -> next = NULL;
    }
    else if (strcmp (book -> author, booksHead -> author)<0){ // Beginning of the list
        book -> next = booksHead;
        booksHead = book;
    }
    else if (strcmp (book -> author, booksHead -> author)==0){ 
        //printf("Book already in list\n");
    }
    else { // Not the first position, we have to traverse the list to find position
        while ((current -> next != NULL) && strcmp(book -> author, current -> next -> author)>0) {
            current = current -> next;
        }
        if (current -> next == NULL) { // Insert at the end of the list
            current -> next = book;
            book -> next = NULL;
        } 
        else if (strcmp(book -> author, current -> next -> author)==0) { // Node with same data already exists
            //printf("Book already in list\n");
        } 
        else { // Insert in the middle of the list
            book -> next = current -> next;
            current -> next = book;
        }
    }
}

void RemoveSortingBooks() // remove a list of books at the end of the program
{
    int i = 0;
    if (booksHead != NULL) { //there are books
        i++;
        struct Book * temp = booksHead;
        while (temp -> next != NULL){
            i++;
            temp = booksHead -> next;
            free(booksHead);
            booksHead = temp;
        }
        free(booksHead); //we free the bookHead book (which should be the only one remaining)
    }
    printf("Removing books... \n");
    printf("      %d books have been removed\n\n", i);
}

//--------------------------------------------------------------------------------------------------------------------------------------------Stack
struct Plate * GeneratePlate() // WARNING: do not change this function
{
	struct Plate * plate = malloc(sizeof(struct Plate)); // reserve memory for a Plate
	enum PlateType type = rand()%3; // initialize the plate's fields
	enum Colors color = rand()%4;
	plate -> type = type;
	plate -> color = color;
	return plate;
}

void InitStacks() // function to initialize all stacks of plates 
{
    struct Plate * dinner_top = NULL;
    struct Plate * soup_top = NULL; 
    struct Plate * dessert_top = NULL; 
    Top_ofPlateStacks [0] = dinner_top; //we put the pointer as an element in the list
    Top_ofPlateStacks [1] = soup_top;
    Top_ofPlateStacks [2] = dessert_top;
    CurrentState [0] = 0; //We put the number of initial plates as elements in the array
    CurrentState [1] = 0;
    CurrentState [2] = 0;
}

void PrintPlates() // function to print all stacks of different plates
{
    printf("In the stack of dinner plates there are %d plates\n", CurrentState [0]);
    printf("In the stack of soup plates there are %d plates\n", CurrentState [1]);
    printf("In the stack of dessert plates there are %d plates\n", CurrentState [2]);
    printf("The total number of plates that are in stacks and not in the wardrobe is %d\n\n", CurrentState [0] + CurrentState [1] +CurrentState [2]);
}

void RemoveStack(int numstack) // function to remove a given stack when its MAX_CAPACITY is reached
{
    free(Top_ofPlateStacks[numstack]); //free memory
    Top_ofPlateStacks[numstack] = NULL; //set element of array (pointer) pointing to NULL
    CurrentState[numstack] = 0; //setting to 0 the counter of elements in stack
}

void SimulateManagingPlate(struct Plate * plate) // function to simulate putting a generated plate to a corresponding stack 
{
    //printf("%d\n", plate -> type); to verify where should the current plate go
    if (plate -> type == 0){
        if (CurrentState[0] < MAX_CAPACITY){
            plate -> next = Top_ofPlateStacks[0]; //the new plate has a pointer to the old top plate
            Top_ofPlateStacks[0] = plate; //the new plate becomes the top plate
            CurrentState[0]++; //we update the number of plates in the stack
        }
        else{ //stack is full
            RemoveStack(0);
            Top_ofPlateStacks[0] = plate;
            plate -> next = NULL;
            CurrentState[0]++;
        }
    }
    else if (plate -> type == 1){
        if (CurrentState[1] < MAX_CAPACITY){
            plate -> next = Top_ofPlateStacks[1]; //the new plate has a pointer to the old top plate
            Top_ofPlateStacks[1] = plate; //the new plate becomes the top plate
            CurrentState[1] ++; //we update the number of plates in the stack
        }
        else{ //stack is full
            RemoveStack(1);
            Top_ofPlateStacks[1] = plate;
            plate -> next = NULL;
            CurrentState[1]++;
        }
    }
    else { //(plate -> type = 2)
        if (CurrentState[2] < MAX_CAPACITY){
            plate -> next = Top_ofPlateStacks[2]; //the new plate has a pointer to the old top plate
            Top_ofPlateStacks[2] = plate; //the new plate becomes the top plate
            CurrentState[2] ++; //we update the number of plates in the stack
        }
        else{ //stack is full
            RemoveStack(2);
            Top_ofPlateStacks[2] = plate;
            plate -> next = NULL;
            CurrentState[2]++;
        }
    }
}

void CleanPlateStacks() // clean all stacks before the end of the program
{
    int total = CurrentState [0] + CurrentState [1] +CurrentState [2]; //used to print
    if (Top_ofPlateStacks[0] != NULL) { //there are books
        struct Plate * temp = Top_ofPlateStacks[0];
        while (temp -> next != NULL){
            temp = Top_ofPlateStacks[0] -> next;
            free(Top_ofPlateStacks[0]);
            Top_ofPlateStacks[0] = temp;
        }
        free(Top_ofPlateStacks[0]); //we free the top of plates (which should be the only one remaining)
    }
    if (Top_ofPlateStacks[1] != NULL) { //there are books
        struct Plate * temp = Top_ofPlateStacks[1];
        while (temp -> next != NULL){
            temp = Top_ofPlateStacks[1] -> next;
            free(Top_ofPlateStacks[1]);
            Top_ofPlateStacks[1] = temp;
        }
        free(Top_ofPlateStacks[1]); //we free the top of plates (which should be the only one remaining)
    }
    if (Top_ofPlateStacks[2] != NULL) { //there are books
        struct Plate * temp = Top_ofPlateStacks[2];
        while (temp -> next != NULL){
            temp = Top_ofPlateStacks[2] -> next;
            free(Top_ofPlateStacks[2]);
            Top_ofPlateStacks[2] = temp;
        }
        free(Top_ofPlateStacks[2]); //we free the top of plates (which should be the only one remaining)
    }
    printf("Cleaning all stacks of plates...\n");
    printf("      %d plates have been removed\n\n", total);
}

//-----------------------------------------------------------------------------------------------------------------------------------------Shopping
int market = 0;
struct Shopping * GenerateShopping() // WARNING: do not change this function
{
	struct Shopping * shopping = malloc(sizeof(struct Shopping)); // reserve memory for a Shopping
	int n = rand()%5+1; // initialize the shopping's fields
	shopping -> numberThingsToBuy = n;
	nextRobotID++;
	shopping -> robot_id = nextRobotID;
	return shopping;
}

void PrintShopping() // function to print a list of robots in a shopping queue
{
    if (queueFirst == NULL) { // in case there are no books
        printf ("List: (-)\n");
    }
    else {
        printf ("List of robots in queue: \n");
        struct Shopping * current = queueFirst;
        printf("    things to buy: %d id: %d\n", current -> numberThingsToBuy, current -> robot_id);
        while (current -> next != NULL) {
            current = current -> next;
            printf("    things to buy: %d id: %d\n", current -> numberThingsToBuy, current -> robot_id);
        }
    }
    printf("\n");
}


void AddToQueue(struct Shopping * shopping) // function to add a robot to a shopping queue
{
    if (queueFirst == NULL){ //no robots in queue
        queueFirst = queueLast = shopping;
    }
    else {
        queueLast -> next = shopping;
        shopping -> next = NULL;
        queueLast = shopping;
    }
}

void Dequeue () // function to remove a robot from the queue and serve it
{
    market = queueFirst -> numberThingsToBuy; //resetting things we have to buy
    if (queueFirst -> next == NULL){ // We have only 1 element
        free(queueFirst);
        queueFirst = queueLast = NULL; // stack is empty
    }
    else { 
        struct Shopping * temp = queueFirst -> next; //we hold the second element
        free (queueFirst);
        queueFirst = temp; //second element becomes first element
    }
}

void UpdateShopping () // function to simulate the time the robot is in the queue
{
    if (market == 0 && queueFirst != NULL) {
        Dequeue();
    } 
    else{
        market = market-1;
    }
}

void SimulateGoForShopping(struct Shopping * shopping) // function to simulate a robot going for shopping
{
    AddToQueue(shopping);
    if (market <= 0) {
        Dequeue();
    }

    //add to shopping cue
}

void CleanShoppingQueue(/*...*/) // function to clean shopping queue before the end of the program
{
    int i = 0;
    while (queueFirst != NULL) { //there are robots
        if (queueFirst -> next == NULL){ // We have only 1 element
            free(queueFirst);
            queueFirst = queueLast = NULL; // stack is empty
        }
        else { 
            struct Shopping * temp = queueFirst -> next; //we hold the second element
            free (queueFirst);
            queueFirst = temp; //second element becomes first element
        }
        i++;
    }
    printf("Cleaning shopping queue...\n");
    printf("      %d robots have been removed\n", i);
}

//----------------------------------------------------------------------------------------------------------------------------------------------main
void SimulationLoop(int EventNumbers) // This is the main loop of the program. It generates and consumes events.
{
    int eventType; // declare and initialize necessary variables
    struct Book * book;
    struct Plate * plate;
    struct Shopping * shopping;
    InitStacks();
	
	for (int i=0; i < EventNumbers; i++) {//repeats process EvenNumbers times
		if (market >= 0){
            UpdateShopping(); //resta 1 de market
        }
        eventType = GenerateEventType(); // generate event type
		if (eventType == 0) { // event type 0:
            //printf("books, %d\n", i); // only used to make sure the program is working
            book = GenerateBook(); // generate book 
			SortingBooks (book); //Simulate sorting books
        }
		if (eventType == 1) { // event type 1: sorting dishes
            //printf("dishes, %d\n", i);
			plate = GeneratePlate(); // generate plate
			SimulateManagingPlate(plate); // Simulate managing plate
        }
		if (eventType == 2) {// event type 2:
            //printf("shopping, %d\n", i);
			shopping = GenerateShopping(); // generate shopping
			SimulateGoForShopping(shopping); // Simulate shopping
		}
	}
    PrintBooks();
    PrintPlates();
    PrintShopping();
    printf("STATISTICS WHEN CLEANING THE SIMULATION: \n");
	RemoveSortingBooks();
    CleanPlateStacks();
    CleanShoppingQueue();
}

void main (int argc, char ** argv)
{
	int EventNumbers, correct;
	printf ("Starting... \n");
	correct = CheckArguments(argc, argv);
	if (correct == 0){
        EventNumbers = atoi(argv[1]); // initialize EventNumbers 
        SimulationLoop(EventNumbers);
    }
}
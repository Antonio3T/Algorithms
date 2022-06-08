






#include <stdio.h>
#include <stdlib.h>

/*
struct Node
{
	int Data;
	struct Node* next;
};
*/
 
// With this there's no need to write "struct Node", just type NODE instead

typedef struct Node
{
	int Data;
	struct Node* next;
}NODE;


#define DATA(Node) ((Node)->Data); // instead of First -> Data = 1 type DATA (First) = 1, for example
#define NEXT(Node) ((Node)->next); // instead of First -> Next = Second type NEXT (First) = Second, for example

typedef NODE* List; // instead of NODE* just type List

void PrintList(struct Node* list); // with the new redefined parameters it would be "List list" or without the latter "NODE* list"
void DefineBeginning(struct Node** list, int value);
void DefineLastNumber(struct Node** list, int value);
void DeleteValue(struct Node** list, int value);
void DeleteList(struct Node** list);
int SizeOfList(struct Node list);


void main() {

	struct Node* First = NULL; // or struct Node * First = NULL, * Second = NULL, * Third=NULL
	struct Node* Second = NULL;
	struct Node* Third = NULL;

	First = (struct Node*)malloc(sizeof(struct Node));
	Second = (struct Node*)malloc(sizeof(struct Node));
	Third = (struct Node*)malloc(sizeof(struct Node));

	First->Data = 1;
	First->next = Second;
	Second->Data = 2;
	Second->next = Third;
	Third->Data = 3;
	Third->next = NULL;
	
	// showing the list
	/*
	struct Node* temp = First;
	
	while (temp != NULL) 
	{
		printf("%d \n", temp->Data);
		temp = temp->next;
	}
	*/
	//PrintList(First);
	
	// adding a new number to the beginning of the list
	/*
	struct Node* newn = (struct Node*)malloc(sizeof(struct Node));

	newn->Data = 4;
	newn->next = First;
	First = newn;
	*/
	//PrintList(First);

	//DefineBeginning(&First, 3);
	//DefineLastNumber(&Third, 3);
	//DeleteValue(&First, 3);
	//DeleteValue(&First, 3);
	//DeleteValue(&First, 3);
	//PrintList(First);
	//DeleteList(&First);

	PrintList(First);
}

void PrintList(struct Node* list)
{
	if (list == NULL) {
		printf("Empty list \n");
		return;
	}

	// it doesn't need a temporary value because the list is a copy, in this case, of "First"

	while (list != NULL) {
		printf("%d \n", list->Data);
		list = list->next;
	}
}

void DefineBeginning(struct Node** list, int value) 
{
	struct Node* newn = (struct Node*)malloc(sizeof(struct Node));
	newn->Data = value;
	newn->next = *list; // same as "First" used before but instead has to be used with a pointer
	*list = newn;
}

void DefineLastNumber(struct Node** list, int value)
{
	struct Node* newn = (struct Node*)malloc(sizeof(struct Node));
	struct Node* temp = *list; // it needs a temporary pointer so it finds the end of the list
	newn->Data = value;
	newn->next = NULL;

	if (*list == NULL) {
		*list = newn;
		return;
	}
	// runs thru the list
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = newn;
}

void DeleteValue(struct Node** list, int value)
{
	struct Node* prev = NULL, * temp;

	temp = *list;
	if (temp != NULL && temp->Data == value) { // means it's the first element of the list
		*list = temp->next;
		free(temp);
		return;
	}

	while (temp != NULL && temp->Data != value) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) // verify if it found any value
		return;
	// if it did find, do this next
	prev->next = temp->next;
	free(temp);
}

void DeleteList(struct Node** list)
{
	struct Node* temp = *list;
	struct Node* nextt;

	while (temp != NULL) {
		nextt = temp->next;
		free(temp);
		temp = nextt;
	}

	*list = NULL;
}

int SizeOfList(struct Node list)
{
	
}
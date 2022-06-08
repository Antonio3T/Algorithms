






#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum STATUS {ERROR = 0, OK = 1} STATUS;

#define MAX 50

typedef struct Node {
	void* Data;
	struct Node* next;
} NODE;

typedef struct ListNode {
	void* Data;
	struct Node* next;
} LISTNODE;

typedef LISTNODE* LIST;

#define DATA(Node) ((Node)->Data)
#define NEXT(Node) ((Node)->next)

typedef struct Worker
{
	char name[MAX], department[MAX];
	float paycheck;
	BOOLEAN regular;
} WORKER;

typedef WORKER* LISTWORKER;

LISTNODE* NewNode(void*);
LISTNODE* DefineBeginning(LIST*, void*);
STATUS ReadFile(LIST*, char*);
float TotalPaycheck(LIST list);
BOOLEAN TurnToRegular(LIST list);
void DeleteNonRegular(LIST list);

void main()
{
	LIST list;
	WORKER worker;

	if (!ReadFile(&list, "Workers.txt"));
		return 0;


	float total;

	//ReadFile(&a, "Workers.txt");
	//total = TotalPaycheck(a);
	//printf("%.2f", total);

	//free(&list);
	return 1;
}

LISTNODE* NewNode(void* Data)
{
	LISTNODE* NewNode;

	if ((NewNode = (LISTNODE*)malloc(sizeof(LISTNODE))) != NULL) {
		DATA(NewNode) = Data;
		NEXT(NewNode) = NULL;
	}
	return NewNode;
}

LISTNODE* DefineBeginning(LIST* list, void* Data)
{
	LISTNODE* NewNode;

	if ((NewNode = (LISTNODE*)malloc(sizeof(LISTNODE))) != NULL) {
		NEXT(NewNode) = *list;
		*list = NewNode;
	}
	return NewNode;
}

STATUS ReadFile(LIST* list, char* filename)
{
	FILE* fp;

	WORKER worker, * ptr;
	int aux;

	if ((fp = fopen(filename, "r")) != NULL) {
		while (!feof(fp)) {
			fscanf(fp, "%[^\n];%[^\n];%f;%d;\n", worker.name, worker.department, &worker.paycheck, &aux);
			if ((ptr = (WORKER*)malloc(sizeof(WORKER))) != NULL && DefineBeginning(list, ptr) != NULL) {
				strcpy(ptr->name, worker.name);
				strcpy(ptr->department, worker.department);
				ptr->paycheck = worker.paycheck;
				if (aux) ptr->regular = TRUE;
				else ptr->regular = FALSE;
			}
			else return ERROR;
		}
		fclose(fp);
		return OK;
	}
	else return ERROR;
}

void RemoveFirstNode(LIST* list)
{
	LISTNODE* node;

	node = NEXT(*list);
	free(DATA(*list));
	free(*list);
	*list = node;
}

void FreeList(LIST* list)
{
	while (*list != NULL) {
		RemoveFirstNode(list);
	}
}

float TotalPaycheck(LIST list)
{
	float total = 0.0;
	
	while (list != NULL) {
		total = total + ((WORKER*)DATA(list))->paycheck;
		list = NEXT(list);
	}

	return total;
}

BOOLEAN TurnToRegular(LIST list)
{
	char* name[MAX];

	printf("What's the name of the employee? \n");
	gets(name);

	while (list != NULL && strcmp(((WORKER*)DATA(list))->name, name)) {
		list = NEXT(list);
	}

	if (list != NULL && !strcmp(((WORKER*)DATA(list))->name)) {
		((WORKER*)DATA(list))->regular = TRUE;
	}
}

void DeleteNonRegular(LIST* list)
{
	LIST listt = *list;
	LIST prev = NULL;

	if (list == NULL)
		return FALSE;

	if (!(prev = (NODE*)malloc(sizeof(NODE))))
		return FALSE;

	while (listt != NULL && (((WORKER*)DATA(listt))->regular) == FALSE) {
		*list = NEXT(listt);
		free(listt);
		listt = *list;
	}

	while (listt != NULL) {
		while (listt != NULL && (((WORKER*)DATA(listt))->regular) != FALSE) {
			prev = listt;
			listt = NEXT(listt);
		}

		if (listt == NULL)
			return TRUE;

		NEXT(prev) = NEXT(listt);

		free(listt);
		listt = NEXT(prev);
	}
	return TRUE;
}
//
//
//
//
//
//
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//
//typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
//typedef enum STATUS { ERROR = 0, OK = 1} STATUS;
////typedef enum {ERROR, OK} STATUS;
//
//#define MAX 50
//
//typedef struct Node {
//	void* Data;
//	struct Node* next;
//}NODE;
//
//typedef NODE* LIST;
//
//#define DATA(Node) ((Node)->Data)
//#define NEXT(Node) ((Node)->next)
//
//typedef struct Station {
//	char desig[MAX];
//	float cost;
//	BOOLEAN active, node;
//}STATION;
//
//void PrintList(LIST list);
//STATUS DefineBeginning(LIST* list, void* value);
//STATUS DefineLast(LIST* list, void* value);
//void DeleteValue(LIST* list, char* value);
//void DeleteList(LIST* list);
////int SizeOfList(NODE list);
//STATUS ReadFile(LIST* list, char* filename);
//STATION* ReadStationData();
//STATUS NewStation(LIST* list);
//STATUS SaveFile(LIST list, char* filename);
//BOOLEAN ActivateStation(LIST list, char* Name);
//BOOLEAN ADStation(LIST list, char* Name, BOOLEAN ad);
//
//float TotalCost(LIST list);
//int SizeOfList(LIST list);
//BOOLEAN ChangePrice(LIST list);
//STATUS SpecificPrice(LIST* list);
//void DeleteInactiveStations(LIST* list);
//
//void main()
//{	
//	/*
//	STATION* est1, * est2;
//
//	est1 = (STATION*)malloc(sizeof(STATION));
//	strcpy_s(est1->desig, MAX, "Name of the station");
//	est1->cost = 2.0;
//	est1->active = TRUE;
//	est1->no = FALSE;
//
//	est2 = (STATION*)malloc(sizeof(STATION));
//	strcpy_s(est2->desig, MAX, "Name of the station");
//	est2->cost = 2.0;
//	est2->active = TRUE;
//	est2->no = FALSE;
//	*/
//	//printfList(a);
//	//DefineBeginning(&a, est1);
//	//PrintList(a);
//	//DefineBeginning(&a, est2);
//	//PrintList(a);
//	//DeleteValue(&a, "Name of the station");
//	//PrintfList(a);
//	/*
//	char op;
//	
//	printf("What's the name of the station? \n");
//	gets("^\n", est1->desig);
//	printf("How much? \n");
//	scanf("%f", est1->cost);
//	printf("Is it still working, yes or no? \n");
//	scanf("%c", &op);
//
//	if (op == 'S' || op == 's')
//		est1->active = TRUE;
//	else if (op == 'N' || op == 'n')
//		est1->active = FALSE;
//	else printf("Another one \n");
//
//	printf("Is it it a node, yes or no? \n");
//	scanf("%c", &op);
//
//	if (op == 'S' || op == 's')
//		est1->active = TRUE;
//	else if (op == 'N' || op == 'n')
//		est1->active = FALSE;
//	else printf("Another one \n");
//	*/
//
//	LIST a = NULL;
//	float cost;
//	int size;
//
//	ReadFile(&a, "Train.txt");
//	PrintList(a);
//	//SpecificPrice(&a);
//	DeleteValue(&a, "London");
//	PrintList(a);
//	//DeleteInactiveStations(&a);
//	//ChangePrice(a);
//	//NewStation(&a);
//	//SaveFile(a, "Train.txt"); // no need for the address since it does not modify the list itself
//	//ActivateStation(a, "", 1);
//	//ADStation(a, "", FALSE);
//	//DefineBeginning(&a, "Mirandela");
//	//DefineLastNumber(&a, "Paris");
//	//DeleteList(&a);
//	
//	//cost = TotalCost(a);
//	//printf("%.2f \n", cost);
//
//	//size = SizeOfList(a);
//	//printf("%d \n", size);
//}
//
//void PrintList(LIST list)
//{
//	if (list == NULL) {
//		printf("Empty list \n");
//		return;
//	}
//
//	while (list != NULL) {
//		printf("%s \n", ((STATION*)DATA(list))->desig);
//		list = NEXT(list);
//	}
//}
//
//STATUS DefineBeginning(LIST* list, void* value)
//{
//	NODE* newn = NULL;
//
//	if ((newn = (NODE*)malloc(sizeof(NODE))) != NULL) {
//		DATA(newn) = value;
//		NEXT(newn) = *list;
//		*list = newn;
//		return OK;
//	}
//	return ERROR;
//}
//
//STATUS DefineLast(LIST* list, void* value)
//{
//	NODE* newn = NULL;
//
//	if ((newn = (NODE*)malloc(sizeof(NODE))) != NULL) {
//		NODE* temp = *list;
//		DATA(newn) = value;
//		NEXT(newn) = NULL;
//
//		if (*list == NULL) {
//			*list = newn;
//			return OK;
//		}
//
//		while (NEXT(temp) != NULL) {
//			temp = NEXT(temp);
//		}
//
//		NEXT(temp) = newn;
//		return OK;
//	}
//	return ERROR;
//}
//
//void DeleteValue(LIST* list, char *name)
//{
//	NODE* prev = NULL;
//
//	NODE *temp = *list;
//
//	if (temp != NULL && !strcmp(((STATION*)DATA(temp)) -> desig, name)) {
//		*list = NEXT(temp);
//		free(DATA(temp));
//		free(temp);
//		return;
//	}
//
//	while (temp != NULL && strcmp(((STATION*)DATA(temp)) -> desig, name)) {
//		prev = temp;
//		temp = NEXT(temp);
//	}
//
//	if (temp == NULL)
//		return;
//
//	NEXT(prev) = NEXT(temp);
//	free(temp);
//	return;
//	///
//}
//
//void DeleteList(LIST* list)
//{
//	LIST temp = *list;
//	LIST nextt;
//
//	while (temp != NULL) {
//		nextt = NEXT(temp);
//		free(DATA(temp));
//		free(temp);
//		temp = nextt;
//	}
//
//	*list = NULL;
//}
//
//STATUS ReadFile(LIST* list, char* filename)
//{
//	FILE* fp;
//
//	STATION* ptr = NULL;
//	int active, node;
//
//	if ((fp = fopen(filename, "r")) != NULL) {
//		while (!feof(fp)) {
//			if (((ptr = (STATION*)malloc(sizeof(STATION))) != NULL) && DefineLast(list, ptr) == OK) {
//				ptr->active = ptr->node = FALSE;
//				fscanf(fp, "%[^;];%f;%d;%d; \n", ptr->desig, &(ptr->cost), &active, &node);
//				if (active)
//					ptr->active = TRUE;
//				if (node)
//					ptr->node = TRUE;
//			}
//			else {
//				DeleteList(list);
//				fclose(fp);
//				return ERROR;
//			}
//		}
//		fclose(fp);
//		return OK;
//	} 
//	return ERROR;
//}
//
//STATION* ReadStationData()
//{
//	STATION* ptr;
//	char op;
//
//	if ((ptr = (STATION*)malloc(sizeof(STATION))) != NULL) {
//		ptr->active = ptr->node = FALSE;
//
//		printf("Name of the station? \n");
//		gets(ptr->desig, MAX);
//
//		printf("How much? \n");
//		scanf("%f", &(ptr->cost));
//
//		printf("Is it still working, yes or no? \n");
//
//		while ((getchar()) != '\n');
//
//		scanf("%c", &op);
//
//		if (op == 'Y' || op == 'y')
//			ptr->active = TRUE;
//		else if (op == 'N' || op == 'n')
//			ptr->active = FALSE;
//		else printf("Another one \n");
//
//		printf("Is it it a node, yes or no? \n");
//
//		while ((getchar()) != '\n');
//
//		scanf("%c", &op);
//
//		if (op == 'Y' || op == 'y')
//			ptr->node = TRUE;
//		else if (op == 'N' || op == 'n')
//			ptr->node = FALSE;
//		else printf("Another one \n");
//	}
//	return ptr;
//}
//
//STATUS NewStation(LIST* list)
//{
//	STATION* Data = NULL;
//	int op;
//
//	if ((Data = ReadStationData()) == NULL) {
//		return ERROR;
//	}
//	do {
//		printf("1 - Insert in the beginning of the list \n");
//		printf("2 - Insert in the end of the list \n");
//		scanf("%d", &op);
//		switch (op) {
//		case 1: if (DefineBeginning(list, Data)) 
//			return OK; 
//			return ERROR; 
//			break;
//		case 2: if (DefineLast(list, Data)) 
//			return OK; 
//			return ERROR; 
//			break;
//		default: printf("Another one \n");
//		}
//	} while (op != 1 && op != 2);
//	return OK;
//}
//
//STATUS SaveFile(LIST list, char* filename)
//{
//	FILE* fp;
//
//	if ((fp = fopen(filename, "w")) != NULL) {
//
//		while (list != NULL) {
//			fprintf(fp, "%s;%.1f;", ((STATION*)DATA(list))->desig, ((STATION*)DATA(list))->cost);
//
//			if (((STATION*)DATA(list))->active) fprintf(fp, "1;");
//			else fprintf(fp, "0;");
//
//			if (((STATION*)DATA(list))->node) fprintf(fp, "1; \n");
//			else fprintf(fp, "0; \n");
//
//			list = NEXT(list);
//		}
//		fclose(fp);
//		return OK;
//	}
//	return ERROR;
//}
//
//BOOLEAN ActivateStation(LIST list, char* Name)
//{
//	while (list != NULL) {
//		if (!strcmp(((STATION*)DATA(list))->desig, Name)) {
//			((STATION*)DATA(list))->active = TRUE;
//			return TRUE;
//		}
//		list = NEXT(list);
//	}
//	return FALSE;
//}
//
//BOOLEAN ADStation(LIST list, char* Name, BOOLEAN ad)
//{
//	while (list != NULL) {
//		if (!strcmp(((STATION*)DATA(list))->desig, Name)) {
//			((STATION*)DATA(list))->active = ad;
//			return TRUE;
//		}
//		list = NEXT(list);
//	}
//	return FALSE;
//}
//
//float TotalCost(LIST list)
//{
//	float cost = 0.0;
//	char* first[MAX], last[MAX];
//
//	printf("First station? \n");
//	gets(first);
//
//	printf("Last station? \n");
//	gets(last);
//
//	while (list != NULL && strcmp(((STATION*)DATA(list))->desig, first)) {
//		list = NEXT(list);
//	}
//
//	if (list != NULL && !strcmp(((STATION*)DATA(list))->desig, first)) {
//		cost = ((STATION*)DATA(list))->cost;
//		do {
//			list = NEXT(list);
//			cost = cost + ((STATION*)DATA(list))->cost; 
//		} while (list != NULL && strcmp(((STATION*)DATA(list))->desig, last));
//	}
//
//	if (list == NULL) {
//		printf("Stations not found \n");
//		return;
//	}
//
//	return cost;
//}
//
//int SizeOfList(LIST list)
//{
//	int size = 0;
//
//	while (list != NULL) {
//		list = NEXT(list);
//		size++;
//	}
//
//	return size;
//}
//
//BOOLEAN ChangePrice(LIST list)
//{
//	char* name[MAX];
//
//	printf("What's the name of the station? \n");
//	gets(name);
//
//	while (list != NULL && strcmp(((STATION*)DATA(list))->desig, name)) {
//		list = NEXT(list);
//	}
//
//	if (list != NULL && !strcmp(((STATION*)DATA(list))->desig, name)) {
//		printf("What's the new price? \n");
//		scanf("%f", &((STATION*)DATA(list))->cost);
//		return TRUE;
//	} return FALSE;
//}
//
//STATUS SpecificPrice(LIST* list)
//{
//	float price = 0.0;
//
//	LIST listt = *list;
//	LIST prev = NULL;
//
//	printf("What's the only price? \n");
//	scanf("%f", &price);
//
//	if (list == NULL)
//		return FALSE;
//
//	if (!(prev = (NODE*)malloc(sizeof(NODE))))
//		return FALSE;
//
//	while (listt != NULL && (((STATION*)DATA(listt))->cost) != price) {
//		*list = NEXT(listt);
//		free(listt);
//		listt = *list;
//	}
//
//	while (listt != NULL) {
//		while (listt != NULL && (((STATION*)DATA(listt))->cost) == price) {
//			prev = listt;
//			listt = NEXT(listt);
//		}
//
//		if (listt == NULL)
//			return TRUE;
//
//		NEXT(prev) = NEXT(listt);
//
//		free(listt);
//		listt = NEXT(prev);
//	}
//	return TRUE;
//}
//
//void DeleteInactiveStations(LIST* list)
//{
//	LIST listt = *list;
//	LIST prev = NULL;
//
//	if (list == NULL)
//		return FALSE;
//
//	if (!(prev = (NODE*)malloc(sizeof(NODE))))
//		return FALSE;
//
//	while (listt != NULL && (((STATION*)DATA(listt))->active) == FALSE) {
//		*list = NEXT(listt);
//		free(listt);
//		listt = *list;
//	}
//
//	while (listt != NULL) {
//		while (listt != NULL && (((STATION*)DATA(listt))->active) != FALSE) {
//			prev = listt;
//			listt = NEXT(listt);
//		}
//
//		if (listt == NULL)
//			return TRUE;
//
//		NEXT(prev) = NEXT(listt);
//
//		free(listt);
//		listt = NEXT(prev);
//	}
//	return TRUE;
//}
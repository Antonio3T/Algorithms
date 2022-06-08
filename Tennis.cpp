






#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum STATUS { ERROR = 0, OK = 1 } STATUS;
//typedef enum {ERROR, OK} STATUS;

#define MAX 50

typedef struct TreeNode {
	void* Data;
	struct TreeNode* Left;
	struct TreeNode* Right;
}TreeNode;

typedef struct Player {
	char Name[MAX];
	int sets;
}PLAYER;

#define DATA(node) ((node)->Data)
#define LEFT(node) ((node)->Left)
#define RIGHT(node) ((node)->Right)

#define EMPTY NULL
#define NOLINK NULL

typedef TreeNode* TREE;

#define STAGES 15
typedef enum TREELOCATION { TREELEFT, TREERIGHT } TREELOCATION;

TREE CreateTree(void** v, int i, int size);
TREE NewTreeNode(void*); // allocates the node
STATUS CreateNewTreeNode(TREE*, void*); // takes a node and creates a data and initializes his "sons" with a null value
//void PrintTree(TREE);
STATUS EmptyTree(TREE);
STATUS IsLeaf(TREE);
TREE AddTreeNode(TREE upnode, TREE node, TREELOCATION where);
STATUS ReadPlayersFromFile(void** players, char* filename);
STATUS InsertInt(TREE*, void*);
int CountPlayers(TREE);
int TreeDeep(TREE);
int TreeSize(TREE);
int CountPlayerGames(TREE, char*);
void PrintPlayerGames(TREE, char*);
void PrintPlayers(TREE);
void PrintGame(TREE); // first game counting from the top
void PrintAllGames(TREE);
void PrintWinnerName(TREE);
void PrintWinnerGames(TREE);
int CountTotalSets(TREE);
int CountWinnerSets(TREE, void*);
TREE ChangeName(TREE, char*, char*);
TREE ReadPlayer();
char* MostSets(TREE, TREE);
void FreeTree(TREE);
TREE InitializeNode(void*, TREE, TREE);

void main()
{
	TREE tree;

	//EmptyTree(a);
	//IsLeaf(a);
	//CreateNewTreeNode(&a, "James");
	//PrintTree(a);

	//CountPlayers(a);

	void* players[STAGES];
	char filename[MAX] = "Players1.txt";
	char playername[MAX] = "Jogador1";
	
	//char filename[MAX];

	//printf("What's the name of the file? \n");
	//scanf("%s", filename);

	if (ReadPlayersFromFile(players, filename)) {
		//printf("%s read! \n", filename);
	}
	else { printf("ERROR \n"); }

	tree = CreateTree(players, 0, STAGES);

	//PrintPlayers(tree);
	//PrintGame(tree);
	//PrintWinnerName(tree);
	//PrintWinnerGames(tree);
	int c = CountPlayerGames(tree, playername);
	//printf("%d \n", c);
	//PrintPlayerGames(tree, playername);
	//printf("%d\n", CountWinnerSets(tree, DATA(tree)));
	//printf("%d\n", CountPlayers(tree));
	//ChangeName(tree);
	//PrintAllGames(tree);
	/*
	char PlayerName[MAX], newplayername[MAX];

	printf("What's the name of the player? \n");
	scanf("%s", PlayerName);

	printf("What's the new name? \n");
	scanf("%s", newplayername);

	ChangeName(tree, PlayerName, newplayername);
	PrintAllGames(tree);
	*/
	//ReadPlayer();
	//FreeTree(tree);
	//PrintAllGames(tree);
	char* Winner = MostSets(tree, tree);
	printf("%s", Winner);
}

TREE CreateTree(void** v, int i, int size)
{
	if (i >= size)
		return (NULL);
	else
		return (InitializeNode(*(v + i), CreateTree(v, 2 * i + 1, size), CreateTree(v, 2 * i + 2, size)));
}

TREE NewTreeNode(void* data)
{
	TREE ptr;

	if ((ptr = (TreeNode*)malloc(sizeof(TreeNode))) != NULL){

		DATA(ptr) = data;
		LEFT(ptr) = RIGHT(ptr) = NULL;
	}
	
	return ptr;
}

STATUS CreateNewTreeNode(TREE* newpointer, void* Data)
{
	TreeNode* ptemp;

	if ((ptemp = (TreeNode*)malloc(sizeof(TreeNode))) == NULL)
		return ERROR;

	*newpointer = ptemp;
	DATA(ptemp) = Data;
	LEFT(ptemp) = NULL;
	RIGHT(ptemp) = NULL;

	return OK;
}
/*
void PrintTree(TREE tree)
{
	if (EmptyTree(tree) == TRUE) return;

	PrintTree(LEFT(tree));

	printf("%d, ", *(int*)DATA(tree)); // * gets the value pointed by the pointer. Test for structurs (->), it might be on the test

	PrintTree(RIGHT(tree));


	return;
}
*/
STATUS EmptyTree(TREE tree)
{
	return (tree == NULL) ? OK : ERROR; // if, return true, else false
}

STATUS IsLeaf(TREE treepointer)
{
	return ((LEFT(treepointer) == NULL) && (RIGHT(treepointer) == NULL)) ? OK : ERROR;
}

TREE AddTreeNode(TREE upnode, TREE node, TREELOCATION where)
{
	TREE tmp = upnode;

	if (upnode == NULL || node == NULL)
		return NULL;

	if (where == TREELEFT) {
		if (LEFT(upnode) == NULL)
			upnode = node;
		else
			tmp = NULL;
	}

	if (where == TREERIGHT) {
		if (RIGHT(upnode) == NULL)
			upnode = node;
		else
			tmp = NULL;
	}

	return tmp;
}

STATUS ReadPlayersFromFile(void** players, char* filename)
{
	FILE* fp;

	int i = 0, j = 0;
	void* ptr;

	if (players == NULL || filename == NULL)
		return ERROR;

	if ((fp = fopen(filename, "r")) != NULL) {

		while (!feof(fp)) {

			if ((ptr = (PLAYER*)malloc(sizeof(PLAYER))) != NULL) {
				fscanf(fp, "%[^;];", ((PLAYER*)ptr)->Name);
				fscanf(fp, "%d\n", &((PLAYER*)ptr)->sets);

				players[i] = ptr;
				i++;
			}
			else {
				for (j = i; j >= 0; j--)
					free(players[j]);
				return ERROR;
			}
		}
		fclose(fp);
		return OK;
	}
	else return ERROR;
}

STATUS InsertInt(TREE* tree, void* Data)
{
	if (EmptyTree(*tree)) {
		TreeNode* newpointer;

		if (CreateNewTreeNode(&newpointer, Data) == ERROR)
			return ERROR;

		*tree = newpointer;
		return OK;
	}
	else {
		if (*(int*)(Data) < *(int*)(DATA(*tree))) {
			InsertInt(&LEFT(*tree), Data);
		}
		else {
			InsertInt(&RIGHT(*tree), Data);
			return OK;
		} // (int*) converts to an integer pointer and * gets the content of it
	}
}

int CountPlayers(TREE tree)
{
	int count = 0;

	if (tree == NULL)
		return count;

	if (IsLeaf(tree))
		count++;

	count += CountPlayers(LEFT(tree)) + CountPlayers(RIGHT(tree)); // LEFT(tree) will eventually be null and therefore return
}

// or
/*
int CountPlayers(TREE tree)
{
	if (IsLeaf(tree))
		return 1;
	return CountPlayers(LEFT(tree)) + CountPlayers(RIGHT(tree));
}
*/

int TreeDeep(TREE tree)
{
	if (tree == NULL)
		return 0;

	int leftDeep = TreeDeep(LEFT(tree));
	int rightDeep = TreeDeep(RIGHT(tree));

	if (leftDeep > rightDeep)
		return leftDeep + 1;
	else
		return rightDeep + 1;
}

int TreeSize(TREE tree)
{
	int count = 0;

	if (tree != NULL)
		count = 1 + TreeSize(LEFT(tree)) + TreeSize(RIGHT(tree));

	return count;
}

int CountPlayerGames(TREE tree, char* Name)
{
	int count = 0;

	if (tree != NULL) {

		if (!strcmp(((PLAYER*)DATA(tree))->Name, Name))
			count++;

		count += CountPlayerGames(LEFT(tree), Name) + CountPlayerGames(RIGHT(tree), Name);
	}

	return count;
}

void PrintPlayerGames(TREE tree, char* Name)
{
	if (tree != NULL) {

		if (!strcmp(((PLAYER*)DATA(tree))->Name, Name))
			printf("%s (%d) vs %s (%d)\n", ((PLAYER*)DATA(LEFT(tree)))->Name, ((PLAYER*)DATA(LEFT(tree)))->sets, ((PLAYER*)DATA(RIGHT(tree)))->Name, ((PLAYER*)DATA(RIGHT(tree)))->sets);

		PrintPlayerGames(LEFT(tree), Name);
		PrintPlayerGames(RIGHT(tree), Name);
		PrintPlayerGames(tree, Name);
	}
}

void PrintPlayers(TREE tree)
{
	if (tree == NULL)
		return;

	if (IsLeaf(tree))
		printf("\nName: %s\nSets: %i\n", ((PLAYER*)DATA(tree))->Name, ((PLAYER*)DATA(tree))->sets);

	if (LEFT(tree) != NULL)
		PrintPlayers(LEFT(tree));

	if (RIGHT(tree) != NULL)
		PrintPlayers(RIGHT(tree));
}

void PrintGame(TREE tree)
{
	if (tree != NULL && !IsLeaf(tree))
		printf("%s (%d) vs %s (%d)\n", ((PLAYER*)DATA(LEFT(tree)))->Name, ((PLAYER*)DATA(LEFT(tree)))->sets, ((PLAYER*)DATA(RIGHT(tree)))->Name, ((PLAYER*)DATA(RIGHT(tree)))->sets);
}

void PrintAllGames(TREE tree)
{
	if (tree != NULL && !IsLeaf(tree)) {
		PrintAllGames(LEFT(tree));
		PrintAllGames(RIGHT(tree));
		PrintGame(tree);
	}
}

void PrintWinnerName(TREE tree)
{
	printf("%s\n", ((PLAYER*)DATA(tree))->Name);
}

void PrintWinnerGames(TREE tree)
{
	if (tree != NULL && !IsLeaf(tree)) {
		PrintGame(tree);

		if (!strcmp(((PLAYER*)DATA(tree))->Name, ((PLAYER*)DATA(LEFT(tree)))->Name))
			PrintWinnerGames(LEFT(tree));
		else
			PrintWinnerGames(RIGHT(tree));
	}
}

int CountTotalSets(TREE tree)
{
	int count = 0;

	if (tree != NULL) {
		count = ((PLAYER*)DATA(tree))->sets + ((PLAYER*)DATA(LEFT(tree)))->sets + ((PLAYER*)DATA(RIGHT(tree)))->sets;
	}

	return count;
}

int CountWinnerSets(TREE tree, void* winner)
{
	int count = 0;

	if (tree != NULL) {
		if (!strcmp(((PLAYER*)DATA(tree))->Name, ((PLAYER*)winner)->Name))
			count += ((PLAYER*)DATA(tree))->sets;
		count += CountWinnerSets(LEFT(tree), winner) + CountWinnerSets(RIGHT(tree), winner);
	}

	return count;
}

TREE ChangeName(TREE tree, char* PlayerName, char* newplayername)
{

	if (tree != NULL) {
		if (!strcmp(((PLAYER*)DATA(tree))->Name, PlayerName)) {
		strcpy(((PLAYER*)DATA(tree))->Name, newplayername);
		}

		ChangeName(LEFT(tree), PlayerName, newplayername);
		ChangeName(RIGHT(tree), PlayerName, newplayername);
	}

	return tree;
}

TREE ReadPlayer()
{
	char PlayerName[MAX], op;
	int sets;
	void* ptr;

	printf("What's the name of the player? \n");
	gets_s(PlayerName, MAX);
	printf("How many sets did he win? \n");
	scanf("%d", &sets);

	if ((ptr = (PLAYER*)malloc(sizeof(PLAYER))) != NULL) {
		strcpy(((PLAYER*)ptr)->Name, PlayerName);
		((PLAYER*)ptr)->sets = sets;
	}

	return NewTreeNode(ptr);
}

char* MostSets(TREE tree, TREE temp)
{
	if (tree != NULL) {
		if (((PLAYER*)DATA(tree))->sets > ((PLAYER*)DATA(temp))->sets) {
			temp = tree;
		}

		MostSets(LEFT(tree), temp);
		MostSets(RIGHT(tree), temp);
	}

	return ((PLAYER*)DATA(temp))->Name;
}

TREE InitializeNode(void* data, TREE node1, TREE node2)
{
	TREE tmp = NULL;

	if (tmp = NewTreeNode(data)) {
		LEFT(tmp) = node1;
		RIGHT(tmp) = node2;
		return tmp;
	}
}

void FreeTree(TREE tree)
{
	if (tree != NULL) {
		FreeTree(LEFT(tree));
		FreeTree(RIGHT(tree));
		free(DATA(tree));
		free(tree);
	}
}
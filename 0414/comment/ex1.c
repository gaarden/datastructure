#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SEARCH 100
#define MALLOC(p, s)\
if(!((p)=malloc(s)))\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}
typedef struct node* treePointer;
typedef struct node
{
	int data;
	treePointer leftChild, rightChild;
};
treePointer bintree;
int search[MAX_SEARCH];

void read_data(char infile[]);
void insertNode(treePointer ptr, int n);
void check(treePointer ptr, int n);
void freeTree(treePointer ptr);

int num;
int value;
int depth;
int finish = 0;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	for (int i = 0; i < num; i++)
		check(bintree, search[i]);
	freeTree(bintree);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &num);
	fscanf(fp, "%d ", &value);

	MALLOC(bintree, sizeof(*bintree));
	bintree->data = value;
	bintree->leftChild = NULL;
	bintree->rightChild = NULL;

	for (int i = 0; i < num; i++)
	{
		fscanf(fp, "%d ", &value);
		insertNode(bintree, value);
	}
	
	int cnt = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &search[cnt]);
		cnt++;
	}

	fclose(fp);
}

void insertNode(treePointer ptr, int n)
{
	if (ptr->data >= n)
	{
		if (ptr->leftChild == NULL)
		{
			treePointer new;
			MALLOC(new, sizeof(*new));
			new->data = n;
			new->leftChild = NULL;
			new->rightChild = NULL;

			ptr->leftChild = new;
		}

		else
			insertNode(ptr->leftChild, n);
	}

	else
	{
		if (ptr->rightChild == NULL)
		{
			treePointer new;
			MALLOC(new, sizeof(*new));
			new->data = n;
			new->leftChild = NULL;
			new->rightChild = NULL;

			ptr->rightChild = new;
		}

		else
			insertNode(ptr->rightChild, n);
	}
}

void check(treePointer ptr, int n)
{
	depth++;

	if (ptr)
	{
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		if (ptr->data == n)
		{
			printf("%d yes %d", n, depth);
			finish = 1;
		}
	}

	else if (ptr == NULL && finish == 0)
	{
		printf("%d no 0", n);
	}

	depth--;
}

void freeTree(treePointer ptr)
{
	if (ptr)
	{
		freeTree(ptr->leftChild);
		freeTree(ptr->rightChild);
		free(ptr);
	}
}
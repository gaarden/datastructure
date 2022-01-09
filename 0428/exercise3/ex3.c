#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int key;
}element;

typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
};

treePointer bintree;
int index;
int c;
int max;
int min;

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
element* modifiedSearch(treePointer root, int key);
void insert(treePointer* node, int k);
void search(treePointer ptr, int b, int s);
void freeTree(treePointer ptr);

int value;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
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

	fscanf(fp, "%d ", &c);

	MALLOC(bintree, sizeof(*bintree));
	bintree->data.key = c;
	bintree->leftChild = NULL;
	bintree->rightChild = NULL;

	while (1)
	{
		fscanf(fp, "%d ", &value);

		if (value == -1)
			break;

		else
			insert(&bintree, value);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %d ", &min, &max);
		search(bintree, min, max);
	}

	fclose(fp);
}

element* modifiedSearch(treePointer root, int key)
{
	if (key == root->data.key)
		return NULL;

	if (key < root->data.key)
	{
		if (!(root->leftChild))
			return root;

		return modifiedSearch(root->leftChild, key);
	}

	if (key > root->data.key)
	{
		if (!(root->rightChild))
			return root;

		return modifiedSearch(root->rightChild, key);
	}
}

void insert(treePointer* node, int k)
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node))
	{
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->leftChild = NULL;
		ptr->rightChild = NULL;

		if (*node)
		{
			if (k < temp->data.key)
				temp->leftChild = ptr;

			else
				temp->rightChild = ptr;
		}

		else
			*node = ptr;
	}
}

void search(treePointer ptr, int b, int s)
{
	if (ptr)
	{
		search(ptr->rightChild, min, max);
		if ((ptr->data.key >= min) && (ptr->data.key <= max))
		{
			printf("%d ", ptr->data.key);
		}
		search(ptr->leftChild, min, max);
	}
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
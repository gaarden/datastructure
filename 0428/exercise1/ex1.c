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
int del;

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
element* modifiedSearch(treePointer root, int key);
void insert(treePointer* node, int k);
void delete(treePointer* ptr, int k);
void printTree(treePointer ptr);
void freeTree(treePointer ptr);

int value;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	if (bintree)
		printTree(bintree);
	else
		printf("-1");
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

	fscanf(fp, "%d ", &value);

	MALLOC(bintree, sizeof(*bintree));
	bintree->data.key = value;
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
		fscanf(fp, "%d ", &del);
		delete(&bintree, del);
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

void delete(treePointer* ptr, int k)
{
	treePointer target = NULL;
	treePointer targetParent = NULL;
	treePointer targetChild = NULL;
	treePointer replacement = NULL;

	target = *ptr;
	targetParent = NULL;
	
	while (target)
	{
		if (k < target->data.key)
		{
			targetParent = target;
			target = target->leftChild;
		}

		else if (k > target->data.key)
		{
			targetParent = target;
			target = target->rightChild;
		}

		else
			break;
	}

	if ((target->leftChild == NULL) && (target->rightChild == NULL))
	{
		if (targetParent == NULL)
			*ptr = NULL;

		else if (targetParent->leftChild == target)
			targetParent->leftChild = NULL;

		else
			targetParent->rightChild = NULL;

		free(target);
	}

	else if ((target->leftChild == NULL) || (target->rightChild == NULL))
	{
		if (target->leftChild)
			targetChild = target->leftChild;

		else
			targetChild = target->rightChild;

		if (targetParent)
		{
			if (target->data.key == targetParent->leftChild->data.key)
				targetParent->leftChild = targetChild;

			else
				targetParent->rightChild = targetChild;
		}

		else
			*ptr = targetChild;

		free(target);
	}

	else
	{
		replacement = target->rightChild;

		while (replacement->leftChild)
		{
			replacement = replacement->leftChild;
		}

		target->data.key = replacement->data.key;
		delete(&target->rightChild, replacement->data.key);
	}
}

/*
void deleteBSTNode(treePointer* node, int k)
{
	treePointer temp = *node;
	treePointer parent = NULL;

	while (temp)
	{
		if (k < temp->data.key)
		{
			parent = temp;
			temp = temp->leftChild;
		}

		else if (k > temp->data.key)
		{
			parent = temp;
			temp = temp->rightChild;
		}

		else
			break;
	}

	if ((temp->leftChild == NULL) && (temp->rightChild == NULL))
	{
		if (parent)
		{
			if (temp->data.key == parent->leftChild->data.key)
				parent->leftChild = NULL;

			else
				parent->rightChild = NULL;

			free(temp);
		}

		else
			free(temp);
	}

	else if ((temp->leftChild == NULL) || (temp->rightChild == NULL))
	{
		treePointer sub;

		if (temp->leftChild == NULL)
			sub = temp->rightChild;

		else
			sub = temp->leftChild;

		if (parent)
		{
			if (temp->data.key == parent->leftChild->data.key)
				parent->leftChild = sub;

			else
				parent->rightChild = sub;
		}

		else
			(*node) = sub;

		free(temp);
	}

	else
	{
		treePointer next;
		treePointer nextP = NULL;

		next = temp;
		nextP = next;
		next = temp->rightChild;

		while (next->leftChild)
		{
			nextP = next;
			next = next->leftChild;
		}
		
		temp->data.key = next->data.key;
		nextP->leftChild = next->rightChild;
		free(next);
	}
}
*/

void printTree(treePointer ptr)
{
	if (ptr)
	{
		printTree(ptr->leftChild);
		printf("%d ", ptr->data.key);
		printTree(ptr->rightChild);
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
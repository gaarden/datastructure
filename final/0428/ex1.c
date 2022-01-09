// 0428 1번

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if (!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct
{
	int key;
}element;

typedef struct node* treePointer;
typedef struct node
{
	element data;
	treePointer leftChild, rightChild;
};

void read_data(char infile[]);
void insert(treePointer* node, int k);
void delete(treePointer* ptr, int k);
element* modifiedSearch(treePointer root, int k);
void printBST(treePointer node);
void freeBST(treePointer node);

treePointer bin;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);

	if (bin)
	{
		printBST(bin);
		freeBST(bin);
	}
	else
		printf("-1");

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int k = 0;

	fscanf(fp, "%d ", &k);
	MALLOC(bin, sizeof(treePointer));
	bin->leftChild = NULL;
	bin->rightChild = NULL;
	bin->data.key = k;

	while (1)
	{
		fscanf(fp, "%d ", &k);

		if (k == -1)
			break;

		else
			insert(&bin, k);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &k);

		delete(&bin, k);
	}

	fclose(fp);
}

// BST insert 함수
void insert(treePointer* node, int k)
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node))
	{
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->leftChild = ptr->rightChild = NULL;

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
	
	if (targetParent)
	{
		if (k < targetParent->data.key)
			target = targetParent->leftChild;

		else
			target = targetParent->rightChild;
	}

	if (target->leftChild == NULL && target->rightChild == NULL)
	{
		if (targetParent == NULL)
			*ptr = NULL;

		else if (targetParent->leftChild == target)
			targetParent->leftChild = NULL;

		else
			targetParent->rightChild = NULL;

		free(target);
	}

	else if (target->leftChild == NULL || target->rightChild == NULL)
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
		replacement = target->leftChild;

		while (replacement->rightChild)
		{
			replacement = replacement->rightChild;
		}

		target->data.key = replacement->data.key;
		delete(&target->leftChild, replacement->data.key);
	}
}

// BST insert 함수에 사용되는 modifiedSearch 함수 (삽입해야하는 부분의 parent를 return 한다)
element* modifiedSearch(treePointer root, int k)
{
	treePointer pre = root;

	while (pre)
	{
		if (pre->data.key > k)
		{
			if (pre->leftChild)
				pre = pre->leftChild;

			else
				return pre;
		}

		else if (pre->data.key < k)
		{
			if (pre->rightChild)
				pre = pre->rightChild;

			else
				return pre;
		}

		else // temp->data.key == k
			return NULL;
	}
}

void printBST(treePointer node) // inorder 방식으로 탐색하며 출력
{
	if (node)
	{
		printBST(node->leftChild);
		printf("%d ", node->data.key);
		printBST(node->rightChild);
	}
}

void freeBST(treePointer node)
{
	if (node)
	{
		freeBST(node->leftChild);
		freeBST(node->rightChild);
		free(node);
	}
}
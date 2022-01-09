// 0426 2번

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
element* search(treePointer root, int k);
void insert(treePointer* node, int k);
element* modifiedSearch(treePointer root, int k);

treePointer bin;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	/*
	정수들을 입력받으며 binary search tree 형태로 저장
	찾고자하는 노드들을 탐색하며, 있으면 Y를, 없으면 N를 출력
	*/

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

		if (search(bin, k)) // search(bin, k) 하면 주소값이 나타남!
			printf("Y ");

		else
			printf("N ");
	}

	fclose(fp);
}

// BST search 함수(찾고자하는게 있으면 찾고자하는 것의 주소값 return, 없으면 NULL return)
element* search(treePointer root, int k)
{
	if (!root)
		return NULL;

	if (k == root->data.key)
		return &(root->data);

	if (k < root->data.key)
		return search(root->leftChild, k);

	return search(root->rightChild, k);
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
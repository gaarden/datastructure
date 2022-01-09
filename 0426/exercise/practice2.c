// 0426 2��

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
	�������� �Է¹����� binary search tree ���·� ����
	ã�����ϴ� ������ Ž���ϸ�, ������ Y��, ������ N�� ���
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

		if (search(bin, k)) // search(bin, k) �ϸ� �ּҰ��� ��Ÿ��!
			printf("Y ");

		else
			printf("N ");
	}

	fclose(fp);
}

// BST search �Լ�(ã�����ϴ°� ������ ã�����ϴ� ���� �ּҰ� return, ������ NULL return)
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

// BST insert �Լ�
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

// BST insert �Լ��� ���Ǵ� modifiedSearch �Լ� (�����ؾ��ϴ� �κ��� parent�� return �Ѵ�)
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
/*
• Task: 임의의 n 개의 정수를 입력 받아 binary tree 로 관리하
는 프로그램을 작성하라
• Input:
– 정수 리스트
• Output:
– binary tree 의 내용을 inorder 로 출력
– 단, 노드에 값이 없을 경우 출력하지 않음
• Specification
– Binary tree 의 표현은 linked representation 을 사용할 것
– 부모 노드 보다 left child 노드의 값이 작거나 같도록 유지할 것
– 입력이 모두 끝나면, inorder로 출력
– 메모리 해제
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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

void read_data(char infile[]);
void insertNode(treePointer ptr, int n);
void inorder(treePointer ptr);
void freeTree(treePointer ptr);

int value;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	inorder(bintree);
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
	bintree->data = value;
	bintree->leftChild = NULL;
	bintree->rightChild = NULL;

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &value);
		insertNode(bintree, value);
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

void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%d ", ptr->data);
		inorder(ptr->rightChild);
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
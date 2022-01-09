/*
• Task: Binary tree 에서 특정 값을 찾는 프로그램을 작성하라
• Input:
– 정수 리스트(첫 줄에는 정수 리스트의 크기, 둘째 줄에는 정수 리스트의 값)
– 셋째 줄: 찾을 값들의 리스트
• Output:
– 찾는 값이 tree 에 있는지 여부와 그 값이 위치한 depth (한 줄에 하나씩)
– 예) 3 이 tree 의 depth 2 에 있는 노드에 있으면 3 yes 2 출력
5 가 tree 에 없으면 5 no 0 출력
• Specification
– Binary tree 의 표현은 linked representation 을 사용할 것
– 파일로부터 정수 리스트를 입력 받아 Binary tree 생성
• 부모 노드 보다 left child 노드의 값이 작거나 같도록 유지할 것
– 반복문을 사용하여 두번째 리스트로부터 정수값을 입력받고 해당 값이 tree에 있는지
확인하여 출력
– Post-order traversal 기법을 사용할 것
– 작업 완료 후 모든 메모리 해제
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct node* treePointer;
typedef struct node
{
	int data;
	treePointer leftChild, rightChild;
};

treePointer first;
int size; // 정수 리스트(tree 구성하는 것)에 존재하는 수
int find[MAX_SIZE]; // 찾을 값들의 리스트
int cnt; // find 리스트에 값 넣을 때 위치 확인
int check;
int depth;

treePointer read_data(char infile[]);
void search(treePointer ptr, int n); // tree 만들 때 들어가는 위치 찾는 함수
void postorder(treePointer ptr, int n);
void freeTree(treePointer ptr);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	first = read_data(argv[1]);

	for (int i = 0; i < cnt; i++)
	{
		postorder(first, find[i]);
		check = 0;
	}

	freeTree(first);

	return EXIT_SUCCESS;
}

treePointer read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	treePointer root;

	MALLOC(root, sizeof(*root));
	root->leftChild = NULL;
	root->rightChild = NULL;

	int num = 0; // 입력받는 숫자

	fscanf(fp, "%d ", &size);

	fscanf(fp, "%d ", &num);
	root->data = num;

	for (int i = 0; i<size-1; i++)
	{
		fscanf(fp, "%d ", &num);
		search(root, num);
	}

	while (!(feof(fp)))
		fscanf(fp, "%d ", &find[cnt++]);

	fclose(fp);

	return root;
}

void search(treePointer ptr, int n)
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
			search(ptr->leftChild, n);
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
			search(ptr->rightChild, n);
	}
}

void postorder(treePointer ptr, int n)
{
	depth++;
	if (ptr)
	{
		postorder(ptr->leftChild, n);
		postorder(ptr->rightChild, n);

		if (ptr->data == n)
		{
			printf("%d yes %d\n", n, depth);
			check = 1;
		}

		else if ((ptr->data == first->data) && (ptr->data != n) && (check == 0))
			printf("%d no 0\n", n);
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
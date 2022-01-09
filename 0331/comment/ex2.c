/*
• Task: 두 개의 정렬된 리스트를 하나의 정렬된 리스트로 합치는 프로그램을
작성하라
• Input:
– 두 개의 정렬된 정수 리스트 (오름차순)
– 각 리스트의 마지막에는 -1이 있어 리스트의 끝을 나타낸다.
– 예) 2 4 5 7 13 -1
3 8 9 15 -1
• Output:
– 하나로 합쳐진 정수 리스트
– 예) 2 3 4 5 7 8 9 13 15
• Specification
– 파일에서 두 개의 정수 리스트를 읽어 두 개의 linked list 생성
– 정렬상태가 유지되도록 두 개의 리스트를 하나로 통합
– 통합된 결과를 오름차순으로 출력
– 작업 수행이 모두 끝난 후, 메모리 할당 해제
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
typedef struct listNode* listPointer;
typedef struct listNode
{
	int data;
	listPointer link;
};
listPointer first = NULL;

void read_data(char infile[]);

char how;
int what;
int check = 0;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printList();
	freeList();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%c %d ", &how, &what);

		if (how == 'i')
		{
			search(first, what);

			if (check == 1)
			{
				;
			}

			else
				insert(&first, , what);
		}

		else if (how == 'r')
		{
			for (int i = 0; i < what; i++)
				delete();
		}
	}


	fclose(fp);
}

void search(listPointer ptr, int value)
{
	int cnt = 0;

	for (;ptr;ptr = ptr->link)
	{
		if (ptr->data == value)
		{

		}
	}
}

void insert(listPointer *first, listPointer x, int value)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = value;
	temp->link = NULL;

	if (*first)
	{
		temp->link = x->link;
		x->link = temp;
	}

	else
	{
		temp->link = NULL;
		*first = temp;
	}
}

int delete(listPointer *first, listPointer trail, listPointer x)
{
	if (trail)
		trail->link = x->link;

	else
		(*first) = (*first)->link;

	free(x);
}

void printList()
{
	for (;first;first = first->link)
		printf("%d ", first->data);
}

void freeList()
{
	for (;first;first = first->link)
		free(first);
}
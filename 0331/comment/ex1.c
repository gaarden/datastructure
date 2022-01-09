/*
• Task: 명령어로 자료값을 입력받아 리스트로 관리하는 프로그램을 작성하라
• Input:
– (명령어, 정수)
• i 3 à 3을 리스트의 제일 뒤에 추가
• r 2 à 리스트에서 앞에서부터 두개의 노드 제거
• Output:
– 명령어 수행이 모두 끝난 후의 리스트에 남아있는 자료들을 공백으로 구분하여 출력
– 남아있는 자료가 없을 경우, 공백만 출력
• Specification
– Linked list 를 사용할 것
– r 명령에서 제거할 노드가 충분하지 않으면, 제거할 수 있는 데 까지 제거
• 예: r 2 에서 노드가 하나 밖에 없으면 하나만 제거
– 파일의 끝까지 명령수행을 마친 후 리스트의 내용을 FIFO 순서로 출력
– 작업이 모두 끝나면 반드시 할당 받은 메모리들을 모두 free 할 것
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
listPointer front = NULL;
listPointer rear = NULL;

void read_data(char infile[]);
void insert(int value);
int delete();
void printList();
void freeList();

char how;
int what;

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
			insert(what);

		else if (how == 'r')
		{
			for (int i = 0; i < what; i++)
				delete();
		}
	}


	fclose(fp);
}

void insert(int value)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = value;
	temp->link = NULL;

	if (front)
		rear->link = temp;

	else
		front = temp;
	rear = temp;
}

int delete()
{
	listPointer temp = front;
	int value = 0;

	if (!temp)
		;

	else
	{
		value = temp->data;
		front = temp->link;
		free(temp);
		return value;
	}
}

void printList()
{
	for (;front;front = front->link)
		printf("%d ", front->data);
}

void freeList()
{
	for (;front;front = front->link)
		free(front);
}
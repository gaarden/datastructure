/*
• Task: Queue 를 구현하여 바르게 작동함을 보여라
• Input:
– (명령어, 숫자)
• i 3 ! queue 에 원소 3 추가
• R 2 ! queue에서 두 개 원소 제거
• Output:
– 명령어 수행이 모두 끝난 후 Queue 의 내용
• Specification
– Queue 자료구조 선언 및 기본 operator 구현 : circular queue 사용
– 게시판에 게시된 파일에서 명령을 읽어 수행
– 파일의 끝까지 명령 수행을 마친 후 Queue 의 내용을 FIFO 순서로 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10001

#define MALLOC(p, s)\
if (!((p) = malloc(s)))\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}

#define REALLOC(p, s)\
if (!((p)=realloc(p, s)))\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct
{
	int key;
}element;

void read_data(char infile[]);
void addq(element item);
element deleteq();
void queueFull();
void queueEmpty();
void printQueue();

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;
char how;
int what;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printQueue();

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
			element data;
			data.key = what;
			addq(data);
		}

		else if (how == 'r')
		{
			for (int i = 0; i<what; i++)
				deleteq();
		}
	}


	fclose(fp);
}

void addq(element item)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}

element deleteq()
{
	element item;
	if (front == rear)
		queueEmpty();
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void queueFull()
{
	fprintf(stderr, "queue is full");
	exit(EXIT_FAILURE);
}

void queueEmpty()
{
	//fprintf(stderr, "queue is empty");
	exit(EXIT_FAILURE);
}

void printQueue()
{
	while (1)
	{
		printf("%d ", deleteq());
	}
}
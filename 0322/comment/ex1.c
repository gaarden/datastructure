/*
Task: Stack 을 구현하여 바르게 작동함을 보여라
• Input:
– (명령어, 숫자)
• i 3 ! stack에 3 추가
• r 2 ! stack에서 원소 두 번 제거
• Output:
– 명령어 수행이 모두 끝난 후 stack 의 내용
• Specification
– Stack 자료구조 선언 및 기본 operator 구현 : Dynamically allocated array
– 게시판에 게시된 파일에서 명령을 읽어 수행
– 파일의 끝까지 명령 수행을 마친 후 stack 의 내용을 LIFO 순서로 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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
void push(element item);
element pop();
void stackFull();
void stackEmpty();
void printStack();

element* stack;
int capacity = 1;
int top = -1;
char how;
int what;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printStack();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(stack, sizeof(*stack));
	element data;

	while (!feof(fp))
	{
		fscanf(fp, "%c %d ", &how, &what);

		if (how == 'i')
		{
			data.key = what;
			push(data);
		}

		else if (how == 'r')
		{
			for (int i = 0; i < what; i++)
				pop();
		}
	}


	fclose(fp);
}

void push(element item)
{
	if (top >= capacity - 1)
		stackFull();
	stack[++top] = item;
}

element pop()
{
	if (top == -1)
		stackEmpty();

	else
		return stack[top--];
}

void stackFull()
{
	REALLOC(stack, 2 * capacity * sizeof(*stack));
	capacity *= 2;
}

void stackEmpty()
{
	//fprintf(stderr, "Stack is empty, cannot pop element");
	exit(EXIT_FAILURE);
}

void printStack()
{
	while (1)
	{
		printf("%d ", pop());
	}
}
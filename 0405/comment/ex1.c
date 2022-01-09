/*
 Task: Stack 을 구현하여 바르게 작동함을 보여라
• Input:
– (명령어, 숫자)
• i 3 à 3 추가
• r 2 à 두 개 원소 제거
• Output:
– 명령어 수행이 모두 끝난 후 stack 의 내용을 출력
– Stack이 비었을 경우 공백 문자만 출력
• Specification
– Stack 자료구조 선언 및 기본 operator 구현 : Linked list
– 게시판에 게시된 파일에서 명령을 읽어 수행
– 파일의 끝까지 명령 수행을 마친 후 stack 의 내용을 LIFO 순서로 출력
– 작업을 마친 후 Stack 에 할당된 메모리 모두 해제
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
typedef struct
{
	int key;
}element;
typedef struct stack* stackPointer;
typedef struct stack
{
	element data;
	stackPointer link;
};
stackPointer top;

void read_data(char infile[]);
void push(element item);
element pop();
void printStack();

char how;
int what;
int check;

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

	while (!feof(fp))
	{
		fscanf(fp, "%c %d ", &how, &what);

		if (how == 'i')
		{
			element data;
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
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop()
{
	stackPointer temp = top;
	element item;
	if (!temp)
		check = 0;

	else
	{
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}

void printStack()
{
	check = 1;
	for (;top;)
	{
		if (check == 1)
			printf("%d ", pop());

		else
			exit(EXIT_FAILURE);
	}
}
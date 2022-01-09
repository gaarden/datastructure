/*
• Task: 파일에 사용된 괄호의 짝이 맞는지 확인하는 프로그램을 작성하
라
• Input:
– 임의의 텍스트 파일
• Output:
– 괄호의 짝이 모두 맞으면 ok 출력
– 괄호의 짝이 맞지 않으면 지금까지 읽은 괄호들을 모두 출력
• Specification
– Dynamic array 를 사용한 stack 을 이용할 것
– Stack 의 기본 오퍼레이션들 만을 사용할 것
– 검사 대상 괄호들은 ‘{‘ 와 ‘}’ , ‘(‘ 와 ‘)’, ‘[‘ 와 ‘]’
– 주석 (/* .. */) 으로 처리된 내용은 검사 대상에 포함하지 않음
• 단, // 로 시작하는 주석은 없다고 가정함
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
#define REALLOC(p, s)\
if (!((p)=realloc(p, s)))\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}
#define MAX_SIZE 1000

typedef struct
{
	char key;
}element;

void read_data(char infile[]);
void push(element item);
element pop();
void stackFull();
void printList();
void printResult();

element* stack;
int capacity = 1;
int top = -1;
char check;
char save[MAX_SIZE];
int out = 0; // true: 1, false: 0
int cnt = -1;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printResult();

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

	while (!feof(fp))
	{
		fscanf(fp, "%c ", &check);

		if (check == '/') // 주석 시작 예비
		{
			fscanf(fp, "%c ", &check);

			if (check == '*') // 주석 시작
			{
				out = 0;

				do
				{
					fscanf(fp, "%c ", &check);

					if (check == '*')
					{
						fscanf(fp, "%c ", &check);

						if (check == '/')
							out = 1;

						else
							out = 0;
					}

					else
						out = 0;

				} while (out == 0);
			}
		}

		if (check == '(' || check == '{' || check == '[')
		{
			save[++cnt] = check;
			element data;
			data.key = check;
			push(data);
		}

		else if (check == ')' || check == '}' || check == ']')
		{
			save[++cnt] = check;
			element data;
			data = pop();

			switch (check)
			{
			case ')':
				if (data.key == '(')
					;
				else
					printList();
				break;

			case '}':
				if (data.key == '{')
					;
				else
					printList();
				break;

			case ']':
				if (data.key == '[')
					;
				else
					printList();
				break;
			}
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
		printList();
	return stack[top--];
}

void stackFull()
{
	REALLOC(stack, 2 * capacity * sizeof(*stack));
	capacity *= 2;
}

void printList()
{
	for (int i = 0; i <= cnt; i++)
		printf("%c ", save[i]);

	exit(EXIT_FAILURE);
}

void printResult()
{
	if (top == -1)
		printf("ok");
	else
	{
		for (int i = 0; i <= cnt; i++)
			printf("%c ", save[i]);
	}
}
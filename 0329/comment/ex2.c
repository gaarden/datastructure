/*
• Task: infix 형태로 입력된 표현식을 평가하여 값을 계산하는
프로그램을 작성하라
• Input:
– Infix 형태의 사칙연산, 괄호를 포함한 표현식
– 예: (3+4)*5-9
• Output:
– Postfix로 변환한 표현식을 먼저 출력하고 다음 줄에 평가값을 출
력
– 예: 34+5*9-
26.00
• Specification:
– 소수점 둘째 자리에서 반올림
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char calculate[MAX_EXPR_SIZE];

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void read_data(char infile[]);
void postfix();
precedence get_token(char* symbol, int* n, char list[]);
void push(precedence item);
precedence pop();
void print_token(precedence item);
double eval();

int top = -1;
int cnt;
int count = -1;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	postfix();
	printf("%.2f", eval());

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
		fscanf(fp, "%c ", &expr[cnt++]);
	}

	fclose(fp);
}

void postfix()
{
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;

	for (token = get_token(&symbol, &n, expr); token != eos; token = get_token(&symbol, &n, expr))
	{
		if (token == operand)
		{
			printf("%c", symbol);
			calculate[++count] = symbol;
		}

		else if (token == rparen)
		{
			while (stack[top] != lparen)
				print_token(pop());
			pop();
		}

		else
		{
			while (isp[stack[top]] >= icp[token])
				print_token(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		print_token(token);
	printf("\n");
}

precedence get_token(char* symbol, int* n, char list[])
{
	*symbol = list[(*n)++];
	switch (*symbol)
	{
	case '(':return lparen;
	case ')':return rparen;
	case '+':return plus;
	case '-':return minus;
	case '/':return divide;
	case '*':return times;
	case '%':return mod;
	case '\0':return eos;
	default:return operand;
	}
}

void push(precedence item)
{
	if (top >= MAX_STACK_SIZE - 1)
		;
	stack[++top] = item;
}

precedence pop()
{
	if (top == -1)
		;
	return stack[top--];
}

void print_token(precedence item)
{
	switch (item)
	{
	case plus:
		printf("+");
		calculate[++count] = '+';
		break;

	case minus:
		printf("-");
		calculate[++count] = '-';
		break;

	case divide:
		printf("/");
		calculate[++count] = '/';
		break;

	case times:
		printf("*");
		calculate[++count] = '*';
	}
}

double eval()
{
	precedence token;
	char symbol;
	double op1, op2;
	int n = 0;
	double result = 0;
	top = -1;

	token = get_token(&symbol, &n, calculate);
	while (token != eos)
	{
		if (token == operand)
			push(symbol - '0');

		else
		{
			op2 = pop();
			op1 = pop();

			switch (token)
			{
			case plus: 
				result = op1 + op2;
				push(result);
				break;
			case minus: 
				result = op1 - op2;
				push(result);
				break;
			case times: 
				result = op1 * op2;
				push(result);
				break;
			case divide: 
				result = op1 / op2;
				push(result);
			}
		}
		token = get_token(&symbol, &n, calculate);
	}
	return result;
}
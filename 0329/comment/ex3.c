/*
• Task: infix 형태로 입력된 표현식을 postfix 형태로 변환하는
프로그램을 “&&”, “||”, “<<“, “>>” 연산자가 포함된 표현식도
변환할 수 있도록 수정하고 올바르게 작동함을 보여라
• Input:
– Infix 형태의 사칙연산, &&, ||, <<, >>, 괄호를 포함한 수식
– 예: (A&&B + C)*D
• Output:
– Postfix 형태로 변환된 수식
– 예: ABC+&&D*
• Specification:
– 각자 작성
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, and, or, left, right, eos, operand }precedence;
precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 5, 4, 11, 11, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 5, 4, 11, 11, 0 };

void read_data(char infile[]);
void postfix();
precedence get_token(char* symbol, int* n);
void push(precedence item);
precedence pop();
void print_token(precedence item);

int top = -1;
int cnt;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	postfix();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	char value = '/0';

	while (!feof(fp))
	{
		fscanf(fp, "%c ", &expr[cnt]);

		if (expr[cnt] == '&' || expr[cnt] == '|' || expr[cnt] == '<' || expr[cnt] == '>')
			fscanf(fp, "%c ", &value);
		cnt++;
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

	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
	{
		if (token == operand)
			printf("%c", symbol);

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

precedence get_token(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
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
	case '&':return and;
	case '|':return or ;
	case '<':return left;
	case '>':return right;
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
		break;

	case minus:
		printf("-");
		break;

	case divide:
		printf("/");
		break;

	case times:
		printf("*");
		break;

	case and:
		printf("&&");
		break;

	case or:
		printf("||");
		break;

	case left:
		printf("<<");
		break;

	case right:
		printf(">>");
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, left, right, and, or, eos, operand }precedence;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 10, 10, 8, 7, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 10, 10, 8, 7, 0 };
precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];

int top = -1;

void read_data(char infile[]);
void print_token(precedence n);
void push(precedence item);
precedence pop();
precedence get_token(char* symbol, int* n);
void postfix(void);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	postfix();

	return 0;
}

void read_data(char infile[])
{
	char c;

	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%c ", &c);

		if (c == '&' || c == '|' || c == '>' || c == '<')
			fscanf(fp, "%c ", &c);
		expr[i++] = c;
	}
	expr[i] = '\0';

	fclose(fp);
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
	case times:
		printf("*");
		break;
	case divide:
		printf("/");
		break;
	case mod:
		printf("%");
		break;
	case left:
		printf("<<");
		break;
	case right:
		printf(">>");
		break;
	case and:
		printf("&&");
		break;
	case or:
		printf("||");
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

precedence get_token(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '<': return left;
	case '>': return right;
	case '&': return and;
	case '|': return or;
	case '\0': return eos;
	default: return operand;
	}
}

void postfix(void)
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
	{
		print_token(token);
	}
	printf("\n");
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
precedence stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char post[MAX_EXPR_SIZE];

int top = -1;

void read_data(char infile[]);
char print_token(precedence n);
void push(precedence item);
precedence pop();
precedence get_token(char* symbol, int* n, char list[]);
void postfix(void);
double eval(void);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	postfix();
	printf("%.2f", eval());

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
		expr[i++] = c;
	}
	expr[i] = '\0';

	fclose(fp);
}

char print_token(precedence item)
{
	switch (item)
	{
	case plus:
		printf("+");
		return '+';
		break;
	case minus:
		printf("-");
		return '-';
		break;
	case times:
		printf("*");
		return '*';
		break;
	case divide:
		printf("/");
		return '/';
		break;
	case mod:
		printf("%");
		return '%';
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

precedence get_token(char* symbol, int* n, char list[])
{
	*symbol = list[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
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
	int i = 0;

	for (token = get_token(&symbol, &n, expr); token != eos; token = get_token(&symbol, &n, expr))
	{
		if (token == operand)
		{
			printf("%c", symbol);
			post[i++] = symbol;
		}
		else if (token == rparen)
		{
			while (stack[top] != lparen)
			{
				post[i++] = print_token(pop());
			}
			pop();
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
			{
				post[i++] = print_token(pop());
			}
			push(token);
		}
	}

	while ((token = pop()) != eos)
	{
		post[i++] = print_token(token);
	}
	printf("\n");
}

double eval(void)
{
	precedence token;
	char symbol;
	double op1, op2;
	double result;
	int n = 0;

	top = -1;
	token = get_token(&symbol, &n, post);
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
				break;
			}
		}
		token = get_token(&symbol, &n, post);
	}
	return result;
}
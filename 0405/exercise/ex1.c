#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACKS 10
typedef struct stack* stackPointer;
typedef struct stack
{
	int data;
	stackPointer link;
};
stackPointer top = NULL;

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
	fprintf(stderr, "insufficient memory");\
	exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
void push(int value);
int pop();
void printStack(stackPointer top);
void erase(stackPointer* ptr);


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printStack(top);
	erase(&top);

	return 0;
}

void read_data(char infile[])
{
	char how;
	int what;

	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while(!feof(fp))
	{
		fscanf(fp, "%c %d ", &how, &what);

		if (how == 'i')
			push(what);

		else if (how == 'r')
			for (int i = 0; i < what; i++)
			{
				if (top)
					pop();
			}
	}

	fclose(fp);
}

void push(int value)
{
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = value;
	temp->link = top;
	top = temp;
}

int pop()
{
	stackPointer temp = top;
	int data = 1;
	if (!(temp))
		exit(1);
	data = temp->data;
	top = temp->link;
	free(temp);
	return data;
}

void printStack(stackPointer top)
{
	if (top == NULL)
		printf(" ");

	while (top != NULL)
	{
		printf("%d ", pop());
	}

	// exit(EXIT_FAILURE);
}

void erase(stackPointer* ptr)
{
	stackPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}
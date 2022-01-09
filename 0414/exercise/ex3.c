#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct node* treePointer;
typedef struct node
{
	int data;
	float value;
	treePointer leftChildlink, rightChildlink;
};

typedef struct
{
	treePointer key;
} element;
element stack[MAX_SIZE];

treePointer expression;
treePointer node;
element tree1;
element tree2;

int check;
int top = -1;

treePointer read_data(char infile[]);
void push(element item);
element pop();
void inorder(treePointer ptr);
void freeTree(treePointer ptr);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	expression = read_data(argv[1]);
	inorder(expression);

	freeTree(expression);

	return EXIT_SUCCESS;
}

treePointer read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	element data;
	char member = '/0';
	char m = '/0';
	int n = 0;

	while (member != '\n')
	{
		MALLOC(node, sizeof(*node));
		node->leftChildlink = NULL;
		node->rightChildlink = NULL;

		fscanf(fp, "%c ", &member);

		if (member != '+' && member != '-' && member != '*' && member != '/') // 문자
		{
			node->data = member;
			data.key = node;

			push(data);
		}

		else // 연산 기호
		{
			tree1 = pop();
			tree2 = pop();

			node->data = member;
			node->rightChildlink = tree1.key;
			node->leftChildlink = tree2.key;

			data.key = node;

			push(data);
		}
	}

	while (!feof(fp))
	{
		fscanf(fp, "%c %d ", &m, &n);
	}

	fclose(fp);

	return node;
}

void push(element item)
{
	if (top >= MAX_SIZE - 1)
		;
	stack[++top] = item;
}

element pop()
{
	if (top == -1)
		;
	return stack[top--];
}

void search(treePointer ptr, int n)
{
	if (ptr->data >= n)
	{
		if (ptr->leftChildlink == NULL)
		{
			treePointer new;
			MALLOC(new, sizeof(*new));

			new->data = n;
			new->leftChildlink = NULL;
			new->rightChildlink = NULL;

			ptr->leftChildlink = new;
		}

		else
			search(ptr->leftChildlink, n);
	}

	else
	{
		if (ptr->rightChildlink == NULL)
		{
			treePointer new;
			MALLOC(new, sizeof(*new));

			new->data = n;
			new->leftChildlink = NULL;
			new->rightChildlink = NULL;

			ptr->rightChildlink = new;
		}

		else
			search(ptr->rightChildlink, n);
	}
}

void inorder(treePointer ptr)
{
	if (ptr)
	{
		if (ptr->leftChildlink != NULL && ptr->rightChildlink != NULL)
			printf("(");

		inorder(ptr->leftChildlink);
		printf("%c", ptr->data);
		inorder(ptr->rightChildlink);

		if (ptr->leftChildlink != NULL && ptr->rightChildlink != NULL)
			printf(")");
	}

	check = 0;
}

void freeTree(treePointer ptr)
{
	if (ptr)
	{
		freeTree(ptr->leftChildlink);
		free(ptr);
		freeTree(ptr->rightChildlink);
	}
}
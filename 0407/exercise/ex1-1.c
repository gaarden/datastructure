#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define COMPARE(x, y) (((x)<(y))?-1:((x)==(y))?0:1)
#define MALLOC(p, s)\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}
typedef struct poly* polyPointer;
typedef struct poly
{
	int coef;
	int expon;
	polyPointer link;
};
polyPointer start;
polyPointer avail;

void read_data(char infile[]);
void add(int coefficient, int exponent);
void delete(int coefficient, int exponent);
polyPointer cpadd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponenet, polyPointer* ptr);
polyPointer getNode(void);
void retNode(polyPointer node);
void cerase(polyPointer* ptr);
void printPoly();

char how;
int co;
int ex;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "E usage: [program][file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printPoly();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%c %d %d ", &how, &co, &ex);

		if (how == 'i')
		{
			add(co, ex);
		}

		else if (how == 'r')
		{
			delete(co, ex);
		}
	}
}

void add(int coefficient, int exponent)
{
	polyPointer temp;
	temp = getNode();
	temp->expon = -1;
	temp->link = NULL;

	temp->coef = coefficient;
	temp->expon = exponent;

	cpadd(start, temp);
}

void delete(int coefficient, int exponent)
{
	polyPointer temp;
	temp = getNode();
	temp->expon = -1;
	temp->link = NULL;

	temp->coef = coefficient*(-1);
	temp->expon = exponent;

	cpadd(start, temp);
}

polyPointer cpadd(polyPointer a, polyPointer b)
{
	polyPointer startA, c, lastC;
	int sum, done = FALSE;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1;
	lastC = c;
	do
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;

		case 0:
			if (startA == a)
				done = TRUE;
			else
			{
				sum = a->coef + b->coef;
				if (sum)
					attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
			break;

		case 1:
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}

void attach(int coefficient, int exponenet, polyPointer* ptr)
{
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponenet;
	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer getNode(void)
{
	polyPointer node;
	if (avail)
	{
		node = avail;
		avail = avail->link;
	}

	else
		MALLOC(node, sizeof(*node));

	return node;
}

void retNode(polyPointer node)
{
	node->link = avail;
	avail = node;
}

void cerase(polyPointer* ptr)
{
	polyPointer temp;
	if (*ptr)
	{
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}

void printPoly()
{
	polyPointer check;
	check = start;
	check = check->link;

	for (;check != start; check = check->link)
		printf("(%d %d) ", check->coef, check->expon);
}
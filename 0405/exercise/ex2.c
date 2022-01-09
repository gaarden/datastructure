#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)
typedef struct polyNode* polyPointer;
typedef struct polyNode
{
	int coef;
	int expon;
	polyPointer link;
};
polyPointer px, qx;
polyPointer avail = NULL;
polyPointer plus = NULL;

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
	fprintf(stderr, "insufficient memory");\
	exit(EXIT_FAILURE);\
}



void read_data(char infile[]);
void insertFront(polyPointer* last, polyPointer node);
void attach(int coefficient, int exponent, polyPointer* ptr);
polyPointer getNode();
polyPointer cpadd(polyPointer a, polyPointer b);
void printPoly(polyPointer sum);
void erase(polyPointer* ptr);


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}
	MALLOC(px, sizeof(*px));
	MALLOC(qx, sizeof(*qx));
	px->expon = -1;
	qx->expon = -1;
	px->link = NULL;
	qx->link = NULL;

	read_data(argv[1]);
	printPoly(px);
	//printPoly(qx);
	/*
	plus = cpadd(px, qx);
	
	printPoly(plus);
	erase(px);
	erase(qx);
	erase(plus);
	erase(avail);
	*/

	return 0;
}

void read_data(char infile[])
{
	int first, second;
	int coef, expon;

	polyPointer put = NULL;
	MALLOC(put, sizeof(*put));

	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &first);
	for (int i = 0; i < first; i++)
	{
		fscanf(fp, "%d %d ", &coef, &expon);
		attach(coef, expon, &px);
	}

	fscanf(fp, "%d ", &second);
	for (int i = 0; i < second; i++)
	{
		fscanf(fp, "%d %d ", &coef, &expon);
		attach(coef, expon, &qx);
	}

	fclose(fp);
}
/*
void insertFront(polyPointer* last, polyPointer node)
{
	if (!(*last)) //null
	{
		(*last)->link = node;
		node->link = node;
	}

	else //null พฦดิ
	{
		node->link = (*last)->link;
		(*last)->link = node;
	}
}
*/
void attach(int coefficient, int exponent, polyPointer* ptr)
{
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, rear, temp;
	int sum = 0;
	MALLOC(rear, sizeof(*rear));
	c = rear;

	while (a&&b)
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;

		case 0:
			sum = a->coef + b->coef;
			if (sum)
				attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;

		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}

	for (;a;a = a->link)
		attach(a->coef, a->expon, &rear);
	for (;b;b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	c = c->link;
	free(temp);
	return c;
}

void printPoly(polyPointer sum)
{
	for (; sum; sum->link)
		printf("(%d, %d)", sum->coef, sum->expon);
}

void erase(polyPointer* ptr)
{
	polyPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}
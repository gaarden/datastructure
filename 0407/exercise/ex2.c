#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode
{
	int key;
	listPointer link;
};

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
	fprintf(stderr, "insufficient memory");\
	exit(EXIT_FAILURE);\
}

int input_size = 0;
listPointer* myeqclass;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	FILE* fp;
	if (!(fp = fopen(argv[1], "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	input_size = read_data(fp, argv[1], &myeqclass);
	myeqclass = make1dArray(input_size);




	fclose(fp);

	return 0;
}

int read_data(FILE *fp, char infile[], listPointer *myeqclass)
{
	int n = 0;
	int read = 0;
	fscanf(fp, "%d ", &n);

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &read);
		//insert()
	}

	return n;
}

listPointer* make1dArray(int n)
{
	int n, * list;

	if (n < 1)
	{
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(list, n * sizeof(*list));

	return list;
}

void insert(listPointer* first, listPointer x, int value)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->key = value;
	temp->link = NULL;

	if (*first)
	{
		if (x != NULL)
		{
			temp->link = x->link;
			x->link = temp;
		}

		else
		{
			temp->link = *first;
			*first = temp;
		}
	}

	else
	{
		temp->link = NULL;
		*first = temp;
	}
}
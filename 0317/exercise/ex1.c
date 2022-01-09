#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
typedef struct {
	int col;
	int row;
	int value;
}term;

int n, m, element;
void read_data(char infile[], term a[]);
void transpose(term a[], term b[]);
void print_sparseMatrix(term a[]);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	term matrix[MAX_TERMS];
	term transMatrix[MAX_TERMS];

	read_data(argv[1], matrix);
	print_sparseMatrix(matrix);
	transpose(matrix, transMatrix);
	print_sparseMatrix(transMatrix);

	return 0;
}

void read_data(char infile[], term a[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d", &n, &m);
	a[0].row = n;
	a[0].col = m;
	
	int num = 1;
	int cnt = 0;

	while (!(feof(fp)))
	{
		fscanf(fp, "%d ", &element);

		if (element != 0)
		{
			a[num].row = cnt / m;
			a[num].col = cnt % m;
			a[num].value = element;

			num++;
			cnt++;
		}

		else
			cnt++;
	}

	a[0].value = num-1;

	fclose(fp);
}

void transpose(term a[], term b[])
{
	int rowTerms[MAX_TERMS], startingPos[MAX_TERMS];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i <= numCols; i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void print_sparseMatrix(term a[])
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	printf("\n");
}
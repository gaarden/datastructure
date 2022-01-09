#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)


typedef struct {
	int col;
	int row;
	int value;
}term;

void read_data(FILE* fp, char infile[], term a[]);
void matrix_sum(term a[], term b[], term d[]);
void print_sparseMatrix(term a[]);

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	term matrixA[MAX_TERMS];
	term matrixB[MAX_TERMS];
	term matrixSum[MAX_TERMS];

	FILE* fp;

	if (!(fp = fopen(argv[1], "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	read_data(fp, argv[1], matrixA);
	read_data(fp, argv[1], matrixB);
	matrix_sum(matrixA, matrixB, matrixSum);
	print_sparseMatrix(matrixSum);

	fclose(fp);
	return 0;
}

void read_data(FILE *fp, char infile[], term a[])
{	
	fscanf(fp, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);

	for (int i = 1; i <= a[0].value; i++)
		fscanf(fp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);

	a[a[0].value + 1].row = a[0].row;
	a[a[0].value + 1].col = a[0].col;

}

void matrix_sum(term a[], term b[], term d[])
{
	d[0].row = a[0].row;
	d[0].col = a[0].col;
	int num = 1;
	int i = 1, j = 1;


	while ((a[0].value+1 != i)||(b[0].value+1 != j))
	{
		if ((a[i].row == b[j].row) && (a[i].col == b[j].col))
		{
			if (a[i].value + b[j].value != 0)
			{
				d[num].row = a[i].row;
				d[num].col = a[i].col;
				d[num].value = a[i++].value + b[j++].value;
				num++;
			}
			
			else
			{
				i++;
				j++;
			}
		}

		else
		{
			if ((a[i].row < b[j].row))
			{
				d[num].row = a[i].row;
				d[num].col = a[i].col;
				d[num].value = a[i++].value;
				num++;
			}

			else if ((a[i].row > b[j].row))
			{
				d[num].row = b[j].row;
				d[num].col = b[j].col;
				d[num].value = b[j++].value;
				num++;
			}

			else
			{
				if ((a[i].col < b[j].col))
				{
					d[num].row = a[i].row;
					d[num].col = a[i].col;
					d[num].value = a[i++].value;
					num++;
				}

				else if ((a[i].col > b[j].col))
				{
					d[num].row = b[j].row;
					d[num].col = b[j].col;
					d[num].value = b[j++].value;
					num++;
				}
			}
		}
	}

	d[0].value = num-1;
}

void print_sparseMatrix(term a[])
{
	for (int i = 0; i <= a[0].value; i++)
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	printf("\n");
}
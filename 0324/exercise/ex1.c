#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 1000
typedef int bool;
#define true 1
#define false 0

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

typedef struct {
	short int vert;
	short int horiz;
}offsets;


void readData(char infile[]);
void push(element item);
element pop();
void path(int sR, int sC, int eR, int eC);


int maze[MAX_STACK_SIZE][MAX_STACK_SIZE] = { 0 };
int mark[MAX_STACK_SIZE][MAX_STACK_SIZE];

element stack[MAX_STACK_SIZE];
offsets move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

int startRow, startCol;
int exitRow, exitCol;
int rowSize, colSize;
int top;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	readData(argv[1]);
	path(startRow, startCol, exitRow, exitCol);

	return 0;
}

void readData(char infile[])
{
	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d", &startRow, &startCol);
	fscanf(fp, "%d %d", &exitRow, &exitCol);
	fscanf(fp, "%d %d", &rowSize, &colSize);
	
	for (int i = 0; i <= rowSize + 1; i++)
	{
		for (int j = 0; j <= colSize + 1; j++)
		{
				mark[i][j] = 1;
		}
	}

	for (int i = 1; i <= rowSize; i++)
		for (int j = 1; j <= colSize; j++)
			fscanf(fp, "%d", &maze[i][j]);

	for (int i = 1; i <= rowSize; i++)
		for (int j = 1; j <= colSize; j++)
			mark[i][j] = 0;

	

	fclose(fp);
}

void push(element item)
{
	if (top >= MAX_STACK_SIZE - 1)
		;
	stack[++top] = item;
}

element pop()
{
	if (top == -1)
		;
	return stack[top--];
}

void path(int sR, int sC, int eR, int eC)
{
	int i, row, col, nextRow, nextCol, dir;
	int found = false;
	element position;
	mark[sR][sC] = 1;
	top = 0;
	stack[0].row = sR; stack[0].col = sC; stack[0].dir = 0;

	while (top > -1 && !found)
	{
		position = pop();
		row = position.row;
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found)
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			if (nextRow == eR && nextCol == eC)
				found = true;

			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
			{
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}

			else
				++dir;
		}
	}

	if (found)
	{
		for (i = 0; i <= top; i++)
			printf("(%d %d) ", stack[i].row, stack[i].col);
		printf("(%d %d) ", row, col);
		printf("(%d %d)", eR, eC);
	}

	else
		printf("FAILURE");

}
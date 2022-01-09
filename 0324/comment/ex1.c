/*
• Task: 미로 탐색 프로그램을 완성하라
• Input:
– 미로의 입구,	출구의 좌표
– 미로의 크기 m,	n
– m*n 행렬
• Output:
– 탈출경로가 존재하면 입구로 부터 출구까지의 경로를 출력. 존재하지 않
으면 경로탐색 실패를 출력
– 출력 형식은 (행, 열) 을 공백 문자로 구별하여 한 줄에 나열
• 예: (1 1) (1 2) (1 3) (2 3) (3 3)
• Specification:
– Program 3.11, 3.12 를 참조하여 각자 작성
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10000
typedef struct
{
	short int vert;
	short int horiz;
}offsets;
typedef struct
{
	short int row;
	short int col;
	short int dir;
}element;

offsets move[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
element stack[MAX_STACK_SIZE];

void read_data(char infile[]);
void path(void);
void push(element item);
element pop();

int srow, scol;
int erow, ecol;
int m, n;
int top = -1;
int maze[MAX_STACK_SIZE][MAX_STACK_SIZE];
int mark[MAX_STACK_SIZE][MAX_STACK_SIZE];

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	path();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d ", &srow, &scol);
	fscanf(fp, "%d %d ", &erow, &ecol);
	fscanf(fp, "%d %d ", &m, &n);

	for (int i = 0; i <= m + 1; i++)
	{
		mark[i][0] = 1;
		mark[i][n+1] = 1;
	}

	for (int i = 0; i <= n + 1; i++)
	{
		mark[0][i] = 1;
		mark[m+1][i] = 1;
	}

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			fscanf(fp, "%d ", &maze[i][j]);
	}

	fclose(fp);
}

void path(void)
{
	int row, col, nextRow, nextCol, dir, found = 0;
	element position;
	mark[srow][scol] = 1; top = 0;
	stack[0].row = srow;
	stack[0].col = scol;
	stack[0].dir = 0;

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

			if (nextRow == erow && nextCol == ecol)
				found = 1;

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
		for (int i = 0; i <= top; i++)
			printf("(%d %d) ", stack[i].row, stack[i].col);
		printf("(%d %d) ", row, col);
		printf("(%d %d)", erow, ecol);
	}

	else
		printf("FAILURE");
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
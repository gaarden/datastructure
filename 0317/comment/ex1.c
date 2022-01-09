/*
Task: Sparse Matrix를 입력받아 FastTranspose 알고리즘을 사용하여Transposition 된 결과
를 출력하는 프로그램을 작성하라
• Input:
– 행의 수 n, 열의 수 m
– n*m 개의 행렬값
• Output:
– (row, col, value) 의 세 쌍으로 표현된 파일에서 읽은 행렬
– (row, col, value) 의 세 쌍으로 표현된 Transposition 된 행렬
• Specification:
– 파일 입력으로 n*m 행렬의 내용을 읽어 교재의 그림 2.5 와 같이
 (row, col, value) 세 쌍으로 표현하여 저장
– (row, col, value) 세 쌍으로 표현된 sparse matrix 를 출력하는 함수 print_sparseMatrix
를 작성하여 저장된 내용을 출력
– Matrix transposition 의 수행
– print_sparseMatrix 를 호출하여 transpose 된 matrix 내용을 출력

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
typedef struct
{
	int row;
	int col;
	int value;
}terms;

terms matrix[MAX_TERMS];
terms transMatrix[MAX_TERMS];

void read_data(char infile[]);
void fastTranspose(terms a[], terms b[]);
void print_sparseMatrix(terms a[]);

int n, m, key;
int cnt = 0;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	print_sparseMatrix(matrix);
	fastTranspose(matrix, transMatrix);
	print_sparseMatrix(transMatrix);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d ", &n, &m);
	matrix[0].row = n;
	matrix[0].col = m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fscanf(fp, "%d ", &key);

			if (key != 0)
			{
				matrix[++cnt].row = i;
				matrix[cnt].col = j;
				matrix[cnt].value = key;
			}
		}
	}
	matrix[0].value = cnt;

	fclose(fp);
}

void fastTranspose(terms a[], terms b[])
{
	int rowTerms[MAX_TERMS], startingPos[MAX_TERMS];
	int i, j, numCols = a[0].col, numTerms = a[0].value;
	b[0].row = numCols, b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
			rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++)
			rowTerms[a[i].col]++;
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)
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

void print_sparseMatrix(terms a[])
{
	for (int i = 0; i <= cnt; i++)
		printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
	printf("\n");
}
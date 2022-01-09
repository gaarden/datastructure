/*
• Task: mmult 함수를 활용하여 두 개의 sparse matrix 의 곱셈을 수행하
는 프로그램을 작성하라
• Input:
– A, B 행렬의 행, 열의 수, m, n, p : A(m*n), B(n*p)
– 두 행렬 A, B의 원소 값들
• Output:
– C = A*B 의 행렬 내용을 m*p 행렬의 형태로 출력
• Specification:
– 파일 입력으로 두 행렬 A, B의 원소값들을 읽고 sparse matrix 표현방식을 사용하여
저장
– B 의 Transposition 수행: fastTranspose 알고리즘 이용
– 계산 : 교재 81페이지 mmult 프로그램 이용
– 곱셈의 결과로 생성되는 행렬의 내용을 파일로 출력
• 출력 파일 이름은 matrix_mult.txt
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)
typedef struct
{
	int row;
	int col;
	int value;
}terms;

terms matrixa[MAX_TERMS];
terms matrixb[MAX_TERMS];
terms mult[MAX_TERMS];

void read_data(char infile[]);
void fastTranspose(terms a[], terms b[]);
void mmult(terms a[], terms b[], terms d[]);
void storeSum(terms d[], int* totalD, int row, int column, int* sum);
void printMult();

int m, n, p;
int key;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	mmult(matrixa, matrixb, mult);
	printMult();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}
	
	int cnt1 = 0;
	int cnt2 = 0;

	fscanf(fp, "%d %d %d ", &m, &n, &p);
	
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(fp, "%d ", &key);
			
			if (key != 0)
			{
				matrixa[++cnt1].row = i;
				matrixa[cnt1].col = j;
				matrixa[cnt1].value = key;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p; j++)
		{
			fscanf(fp, "%d ", &key);

			if (key != 0)
			{
				matrixb[++cnt2].row = i;
				matrixb[cnt2].col = j;
				matrixb[cnt2].value = key;
			}
		}
	}

	matrixa[0].row = m;
	matrixa[0].col = n;
	matrixa[0].value = cnt1;
	
	matrixb[0].row = n;
	matrixb[0].col = p;
	matrixb[0].value = cnt2;

	fclose(fp);
}

void fastTranspose(terms a[], terms b[])
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

void mmult(terms a[], terms b[], terms d[])
{
    int i, j, column, totalB = b[0].value, totalD = 0;
    int rowsA = a[0].row, colsA = a[0].col,
        totalA = a[0].value; int colsB = b[0].col;
    int rowBegin = 1, row = a[1].row, sum = 0;
    

    terms newB[MAX_TERMS];

    if (colsA != b[0].row)
    {
        fprintf(stderr, "Incompatible matrice\n");
        exit(EXIT_FAILURE);
    }

    fastTranspose(b, newB);

    a[totalA + 1].row = rowsA;
    a[totalA + 1].col = 0;
    a[totalA + 1].value = 0;
    newB[totalB + 1].row = colsB;
    newB[totalB + 1].col = 0;
    newB[totalB + 1].value = 0;

    for (i = 1; i <= totalA;)
    {
        column = newB[1].row;
        for (j = 1; j <= totalB + 1;)
        {
            if (a[i].row != row)
            {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                for (; newB[j].row == column; j++)
                    ;
                column = newB[j].row;
            }
            else if (newB[j].row != column)
            {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                column = newB[j].row;
            }
            else switch (COMPARE(a[i].col, newB[j].col))
            {
            case -1:
                i++;
                break;
            case 0:
                sum += (a[i++].value * newB[j++].value);
                break;
            case 1:
                j++;
            }
        }
        for (; a[i].row == row; i++)
            ;
        rowBegin = i; row = a[i].row;
    }
    d[0].row = rowsA;
    d[0].col = colsB;
    d[0].value = totalD;
}

void storeSum(terms d[], int* totalD, int row, int column, int* sum)
{
	if (*sum)
		if (*totalD < MAX_TERMS)
		{
			d[++ * totalD].row = row;
			d[*totalD].col = column;
			d[*totalD].value = *sum;
			*sum = 0;
		}
		else
		{
			fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
			exit(EXIT_FAILURE);
		}
}

void printMult()
{
	int cnt = 1;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			if (mult[cnt].row == i && mult[cnt].col == j)
				printf("%d ", mult[cnt++].value);

			else
				printf("0 ");
		}
		printf("\n");
	}
}
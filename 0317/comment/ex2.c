/*
Task: 두 개의 sparse matrix 의 덧셈을 수행하는 프로그램을 작성하라
• Input:
– (row, col, value) 형태로 표현된 sparse matrixA
– (row, col, value) 형태로 표현된 sparse matrixB
• Output:
– C = A+B 의 행렬 내용을 출력
• Specification:
– 파일 입력으로 두 행렬의 원소값들을 읽고 sparse matrix 표현방식을 사용하여 저장
– 두 행렬의 덧셈을 수행 : 세부내용은 각자 작성
– 덧셈의 결과로 생성되는 행렬의 내용을 (row, col, value) 형태로 출력
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

terms first[MAX_TERMS];
terms second[MAX_TERMS];
terms sum[MAX_TERMS];

void read_data(char infile[]);
void plus();
void print_sparseMatrix();

int cnt1, cnt2;
int cnt;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	plus();
	print_sparseMatrix(sum);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d %d ", &first[0].row, &first[0].col, &first[0].value);

	for (int i = 0; i < first[0].value; i++)
		fscanf(fp, "%d %d %d ", &first[++cnt1].row, &first[cnt1].col, &first[cnt1].value);

	fscanf(fp, "%d %d %d ", &second[0].row, &second[0].col, &second[0].value);

	for (int i = 0; i < second[0].value; i++)
		fscanf(fp, "%d %d %d ", &second[++cnt2].row, &second[cnt2].col, &second[cnt2].value);

	sum[0].row = first[0].row;
	sum[0].col = first[0].col;

	fclose(fp);
}

void plus()
{
	int i = 1;
	int j = 1;
	int count = 0;

	while (i <= cnt1 && j <= cnt2)
	{
		switch (COMPARE(first[i].row, second[j].row))
		{
		case -1:
			sum[++count] = first[i++];
			break;

		case 0:
			switch (COMPARE(first[i].col, second[j].col))
			{
			case -1:
				sum[++count] = first[i++];
				break;

			case 0:
				if (first[i].value + second[j].value)
				{
					sum[++count].row = first[i].row;
					sum[count].col = first[i].col;
					sum[count].value = first[i++].value + second[j++].value;
				}
				break;

			case 1:
				sum[++count] = second[j++];
			}
			break;

		case 1:
			sum[++count] = second[j++];
		}

	}

	if (i != cnt1)
	{
		for (; i <= cnt1;)
			sum[++count] = first[i++];
	}

	if (j != cnt2)
	{
		for (; j <= cnt2;)
			sum[++count] = second[j++];
	}

	sum[0].value = count;
}

void print_sparseMatrix()
{
	for (int i = 0; i <= sum[0].value; i++)
		printf("%d %d %d\n", sum[i].row, sum[i].col, sum[i].value);
	printf("\n");
}
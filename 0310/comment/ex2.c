/*
Task: 이차원 행렬의 모든 원소의 합을 구하는 프로그램을 작성하되, 동적할당을
이용하여 메모리 사용량을 최소화하여 작성하라
• Input:
– 행렬의 크기 m, n
– m*n 개의 정수형 원소
• Output:
– 읽은 행렬
– 행렬의 모든 원소의 합
• Specification:
– 파일 input.txt의 첫줄에 m, n 의 값, 둘째줄 부터 m*n 개의 원소값들이 있다
고 가정(파일 이름은 첫 번째 argument로 전달)
– m*n 배열을 동적할당으로 생성하고 파일로부터 원소들을 읽어 배열에 저장
– 배열의 내용을 출력하여 확인
– 마지막으로 배열의 모든 원소의 합을 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if(!((p)=malloc(s)))\
{\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

void read_data(FILE * fp, int rows, int cols);
int read_data2(FILE * fp, int** list);
void printArray(int** list);
int plus(int** list);
int** make2dArray(int rows, int cols);

int row, col;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	FILE* fp;

	if (!(fp = fopen(argv[1], "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int** lst;
	read_data(fp, row, col);
	lst = make2dArray(row, col);
	lst = read_data2(fp, lst);
	printArray(lst);
	printf("%d", plus(lst));

	fclose(fp);

	return EXIT_SUCCESS;
}

void read_data(FILE *fp, int rows, int cols)
{
	fscanf(fp, "%d %d ", &row, &col);
}

int read_data2(FILE* fp, int **list)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			fscanf(fp, "%d ", &list[i][j]);

	return list;
}

void printArray(int** list)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			printf("%d ", list[i][j]);
		printf("\n");
	}
}

int plus(int** list)
{
	int sum = 0;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			sum += list[i][j];

	return sum;
}

int** make2dArray(int rows, int cols)
{
	int** x, i;
	
	MALLOC(x, rows * sizeof(*x));

	for (i = 0; i < rows; i++)
		MALLOC(x[i], cols * sizeof(**x));

	return x;
}
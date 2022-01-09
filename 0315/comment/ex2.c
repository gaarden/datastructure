/*
Task: 다항식 와 주어진 값
에 대 ) 를 구하라
• Input:
– x 의 값
– 다항식 p(x) 에 대한 (계수, 지수) 리스트
• Output:
– )
• 요구사항
– 다항식의 (계수, 지수) 리스트는 파일에서 입력
– 계산 수행 횟수를 최소화 할 것
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TERMS 100
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)
typedef struct
{
	int coef;
	int expon;
}polynomial;

polynomial terms[MAX_TERMS];

void read_data(char infile[]);
int calculate(int num, int sum);

int cnt;
int num1, num2;
int sum1, sum2;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printf("%d", calculate(num1, sum1) + calculate(num2, sum2));

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d ", &num1, &num2);

	while (!feof(fp))
	{
		fscanf(fp, "%d %d ", &terms[cnt].coef, &terms[cnt].expon);
		cnt++;
	}

	fclose(fp);
}

int calculate(int num, int sum)
{
	for (int i = 0; i <= cnt; i++)
		sum += terms[i].coef * pow(num, terms[i].expon);

	return sum;
}
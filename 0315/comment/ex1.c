/*
Task: 다항식 와
의 덧셈을 수행하라
• Input:
– 다항식 p(x), q(x) 의 항 개수 n, m
– 다항식 p(x) 에 대한 (계수, 지수) 리스트
– 다항식 q(x) 에 대한 (계수, 지수) 리스트
• Output:
– 최대 n+m+1 개의 계수가 0이 아닌 항을 갖는 다항식
Ex) Standard output : p(x) = 3x^2+1x^1
 q(x) = 1x^2+5
 p(x) + q(x) = 4x^2+1x^1+5
• Specification:
– 파일에서 읽은 두 다항식을 와
의 형식으로 출력
– Program 2.6 을 사용하여 다항식 덧셈 수행
– 더해진 다항식을 의 형식으로 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)
typedef struct
{
	int coef;
	int expon;
}polynomial;

polynomial terms[MAX_TERMS];

void read_data(char infile[]);
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void attach(int coefficient, int exponent);
void printPoly(int* startD, int* finishD);

int avail = 0;
int starta, finisha, startb, finishb;
int px, qx;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	int startd = 0;
	int finishd = 0;

	read_data(argv[1]);
	padd(starta, finisha, startb, finishb, &startd, &finishd);
	printf("p(x) = ");
	printPoly(&starta, &finisha);
	printf("q(x) = ");
	printPoly(&startb, &finishb);
	printf("p(x) + q(x) = ");
	printPoly(&startd, &finishd);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d ", &px, &qx);

	starta = 0;
	finisha = px - 1;
	startb = px;
	finishb = px + qx - 1;
	avail = px + qx;

	for (int i = 0; i < px; i++)
		fscanf(fp, "%d %d ", &terms[i].coef, &terms[i].expon);

	for (int j = px; j < px+qx; j++)
		fscanf(fp, "%d %d ", &terms[j].coef, &terms[j].expon);

	fclose(fp);
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{
	int coefficient;
	*startD = avail;

	while (startA <= finishA && startB <= finishB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon))
		{
		case -1:
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
			break;

		case 0:
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;

		case 1:
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
		}

	for (;startA <= finishA;startA++)
		attach(terms[startA].coef, terms[startA].expon);

	for (;startB <= finishB;startB++)
		attach(terms[startB].coef, terms[startB].expon);

	*finishD = avail - 1;
}

void attach(int coefficient, int exponent)
{
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too many terms int the polynomial\n");
		exit(EXIT_FAILURE);
	}

	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void printPoly(int *startD, int *finishD)
{
	for (int i = *startD; i <= *finishD; i++)
	{
		if (terms[i].coef > 0)
		{
			if (i != *startD)
				printf("+");

			if (terms[i].expon == 0)
				printf("%d", terms[i].coef);

			else
				printf("%dx^%d", terms[i].coef, terms[i].expon);
		}

		else
		{
			if (terms[i].expon == 0)
				printf("%d", terms[i].coef);

			else
				printf("%dx^%d", terms[i].coef, terms[i].expon);
		}
	}
	printf("\n");
}
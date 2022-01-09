/*
Program 1.25 의 방식을 사용하여 Selection sort 알고리즘의
실행시간을 측정하는 프로그램을 작성하라.
• 단, 예제의 standard output은 파일 출력으로 변경하라. (파일명
은 output.txt)
• 단, 리스트 초기화 과정과 함께 selection sort는 1000번 반복하
라.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1001

void selection_sort(int list[], int n);

void main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	FILE* fp;

	if (!(fp = fopen("output.txt", "w")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;

	fprintf(fp, "	n	repetitions		time\n");
	for (n = 0; n <= 1000; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();

		do
		{
			repetitions++;

			for (i = 0; i < n;i++)
				a[i] = n - i;

			selection_sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		fprintf(fp, "%6d		%9d		%f\n", n, repetitions, duration);
		if (n == 100)
			step = 100;
	}

	fclose(fp);
}

void selection_sort(int list[], int n)
{
	int min, temp;

	for (int i = 0; i < n - 1; i++)
	{
		min = i;

		for (int j = i + 1; j < n; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		temp = list[min];
		list[min] = list[i];
		list[i] = temp;
	}
}
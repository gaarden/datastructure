/*
Binary Search 함수의 수행속도를 측정하라
1. Input:
• 정수 리스트의 크기 n
• n개의 정수 (각각 공백으로 구분됨)
• 검색하고자 하는 수의 리스트
2. Output:
• 각각의 검색하는 수에 대하여, 리스트에 존재하면 index 출력, 없으면 -1 출력 (standard output) Output은 공백으
로 구별하여 출력
EX) standard output : -1 2
• 수행속도 측정 결과는 파일 출력, 파일 이름 : 2번째 argument로 전달)
EX) 파일 출력 :
repetitions time
 11 0.093545
3. Specification
• 입력파일의 정수리스트를 배열에 저장
• 정렬 수행
• 입력파일로 부터 검색하고자 하는 수를 하나씩 읽으며 검색수행하고 결과 출력
• 시간 측정 결과 출력 시, 모든 검색하고자 하는 수를 1000번 탐색한 시간을 출력
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1000000

void read_data(char infile[], int list[], int search[]);
void selection_sort(int list[], int n);
int binsearch(int list[], int searchnum, int left, int right);
int num, size = 0, searchsize = 0;
int lst[MAX_SIZE];
int searchnum[MAX_SIZE];

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1], lst, searchnum);
	FILE* fp;

	if (!(fp = fopen(argv[2], "w")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	selection_sort(lst, size);

	fprintf(fp, "%s", "repetitions time\n");

	int step = 10;

	for (int n = 0; n <= 1000; n += step)
	{
		long repetition = 0;
		clock_t start = clock();

		do
		{
			repetition++;

			for (int i = 0; i < searchsize; i++)
				binsearch(lst, searchnum[i], 0, size - 1);

		} while (clock() - start < 1000);


		double duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetition;

		fprintf(fp, "%6d  %9d\n", repetition, duration);

		if (n == 100) step = 100;
	}
	fclose(fp);

	for (int i = 0; i < searchsize; i++)
		printf("%d ", binsearch(lst, searchnum[i], 0, size - 1));

	return 0;
}

void read_data(char infile[], int list1[], int list2[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &size);

	for (int i = 0; i < size; i++)
	{
		fscanf(fp, "%d ", &(list1[i]));

	}

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &(list2[searchsize]));
		searchsize++;
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

int binsearch(int list[], int searchnum, int left, int right)
{
	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (searchnum != list[middle])
		{
			if (searchnum < list[middle])
				right = middle - 1;

			else
				left = middle + 1;
		}

		else
			return middle;
	}

	return -1;
}
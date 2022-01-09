/*
Binary search algorithm 을 다음과 같은 구성으로 재구현하라
1. int read_data(char infile[], int list[]): infile 을 열어 파일에 있는 정수 리스
트를 list 배열에 순서대로 저장하고 리스트의 크기를 반환
2. selection_sort를 호출하여 배열을 오름차순으로 정렬한다
• 이때, 배열의 크기는 read_data 에서 반환된 정수값을 사용
3. void write_data(int list[], char outfile[], int size): list 에 있는 수들을
outfile 에 쓴다
4. int binsearch(int list[], int searchnum, int left, int right): list 에서
searchnum 을 찾아 있으면 해당 인덱스를, 없으면, -1 을 반환한다.
Input:
– 두 줄로 구성된 txt 파일 (첫 번째 줄 : 찾을 정수 값, 두 번째 줄 : 정수 리스트)
Ex) 5
4 7 1 3 5
Output:
– 정렬된 리스트가 저장된 파일(두 번째 argument로 저장할 파일의 이름 전달)
– 찾는 값이 있으면 인덱스를, 없으면 -1 을 표준출력
Ex) 3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001

int read_data(char infile[], int list[]);
void selection_sort(int list[], int n);
void write_data(int list[], char outfile[], int size);
int binsearch(int list[], int searchnum, int left, int right);

int cnt, num;

int main(int argc, char** argv)
{
	if (argc != 3) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	int lst[MAX_SIZE];

	cnt = read_data(argv[1], lst);
	selection_sort(lst, cnt);
	write_data(lst, argv[2], cnt);
	printf("%d", binsearch(lst, num, 0, cnt - 1));

	return EXIT_SUCCESS;
}

int read_data(char infile[], int list[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int n = 0;

	fscanf(fp, "%d ", &num);

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &list[n++]);
	}

	fclose(fp);

	return n;
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

void write_data(int list[], char outfile[], int size)
{
	int i = 0;
	FILE* fp;

	if (!(fp = fopen(outfile, "w")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%d ", list[i]);
	}
	fclose(fp);
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
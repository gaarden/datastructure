#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)

void read_data(char infile[]);
void merge(int initList[], int mergedList[], int i, int m, int n);
void mergePass(int initList[], int mergedList[], int n, int s);
int mergeSort(int a[], int n);
void makeUpList(int n, int a[]);
void compareList();

int size = 0; // 전체 문자열 길이
int size1 = 0; // 첫 문자열 길이
int size2 = 0; // 두번째 문자열 길이
int check = 0;
int lst[MAX_SIZE]; // 전체 문자열
int lst1[MAX_SIZE]; // 첫 문자열
int lst2[MAX_SIZE]; // 두번째 문자열
int extra[MAX_SIZE]; // 문자열 빈공간
int flag1 = 0;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	makeUpList(mergeSort(lst1, size1), lst1);
	makeUpList(mergeSort(lst2, size2), lst2);
	compareList();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	/*
	전체 문자열 길이, 전체 문자열, 첫 문자열 길이를 받음
	첫 문자열, 두번째 문자열 생성
	*/

	fscanf(fp, "%d ", &size);

	for (int cnt = 1; cnt <= size; )
		fscanf(fp, "%d ", &lst[cnt++]);

	fscanf(fp, "%d ", &size1);

	size2 = size - size1;

	int i, j;

	for (i = 1; i <= size1; i++)
		lst1[i] = lst[i];

	for (j = 1; j <= size2; j++)
		lst2[j] = lst[size1 + j];

	fclose(fp);
}

void merge(int initList[], int mergedList[], int i, int m, int n)
{
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n)
	{
		if (initList[i] <= initList[j])
			mergedList[k++] = initList[i++];

		else
			mergedList[k++] = initList[j++];
	}

	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];

	else
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
}

void mergePass(int initList[], int mergedList[], int n, int s)
{
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);

	if (i + s - 1 <= n)
		merge(initList, mergedList, i, i + s - 1, n);

	else
		for (j = i; j <= n; j++)
			initList[j] = mergedList[j];
}

int mergeSort(int a[], int n)
{
	int s = 1;

	while (s < n)
	{
		mergePass(a, extra, n, s);
		s *= 2;
		if (s >= n)
			return 1;
		mergePass(extra, a, n, s);
		s *= 2;
	}

	return 0;
}

void makeUpList(int n, int a[])
{
	/*
	오름차순 리스트를 만드는 과정
	*/

	if (n == 1)
	{
		for (int i = 1; i <= size1; i++)
		{
			a[i] = extra[i];
			extra[i] = 0; // extra 초기화
		}
	}

	else
		;
}

void compareList()
{
	int flag = 0;
	int i = 1, j = 1;

	while (i<=size1 && j<=size2)
	{
		switch (COMPARE(lst1[i], lst2[j]))
		{
		case -1: // lst1[i] < lst2[j]
			i++;
			break;

		case 0:
			printf("%d ", lst1[i]);
			i++;
			j++;
			flag = 1;
			break;

		case 1:
			j++;
			break;
		}
	}

	if (flag == 0)
		printf(" ");
}
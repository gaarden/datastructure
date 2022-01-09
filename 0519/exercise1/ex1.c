#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001

void read_data(char infile[]);
void setBoundary();
void merge(int initList[], int mergedList[], int i, int m, int n);
void mergePass(int initList[], int mergedList[], int n);
void mergeSort(int a[], int n);
void printList(int initList[], int mergedList[]);

int size = 0;
int check = 0;
int lst[MAX_SIZE];
int extra[MAX_SIZE];
int segment[MAX_SIZE];
int count; // lst를 print할지, extra를 print할지 결정하기 위해 세는 것
int cnt = 0;
int index = 1;
int mergeCnt = 0;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	setBoundary();
	mergeSort(lst, size);
	printList(lst, extra);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &size);

	for (int cnt = 1; cnt <= size; )
		fscanf(fp, "%d ", &lst[cnt++]);

	fclose(fp);
}

void setBoundary()
{
	int pre = 0;
	int temp = 0;

	for (int i = 1; i <= size; i++)
	{
		if (temp == 0)
		{
			temp = lst[i];
			cnt++;
		}

		else
		{
			pre = temp;
			temp = lst[i];

			if (pre <= temp)
				cnt++;

			else
			{
				segment[index] = cnt;
				index++;
				cnt = 1; // 다시 cnt 초기화
			}
		}
	}

	if (cnt != 0)
		segment[index] = cnt;
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

void mergePass(int initList[], int mergedList[], int n)
{
	int i, j;
	int save = 0;
	int recnt = 1;
	int preSum = 0;

	for (i = 1; segment[i + 1]; i += 2)
	{
		merge(initList, mergedList, save + 1, save + segment[i], save + segment[i] + segment[i + 1]);
		mergeCnt++;
		save += segment[i] + segment[i + 1];
		segment[i] = 0;
		segment[i + 1] = 0;
		preSum = 0;
		for (int j = 1; j <= recnt; j++)
			preSum += segment[j];
		segment[recnt++] = save - preSum;
	}

	
	if (segment[i] != 0)
	{
		for (int j = save + 1; j <= n; j++)
			mergedList[j] = initList[j];
		segment[recnt] = n - save;
		segment[i] = 0;
	}

	else
		;

	count++;
}

void mergeSort(int a[], int n)
{
	int i = 1;

	while (1)
	{
		mergePass(a, extra, n);
		i = i + 2;

		if (segment[i] == 0)
		{
			if (segment[1] == 0 || segment[1] == size)
				break;

			else
				i = 1;
		}

		mergePass(extra, a, n);
		i = i + 2;

		if (segment[i] == 0)
		{
			if (segment[1] == 0 || segment[1] == size)
				break;

			else
				i = 1;
		}
	}
}

void printList(int initList[], int mergedList[])
{
	if (count % 2 == 0)
	{
		for (int i = 1; i <= size; i++)
			printf("%d ", initList[i]);
		printf("%d\n", mergeCnt);
	}

	else
	{
		for (int i = 1; i <= size; i++)
			printf("%d ", mergedList[i]);
		printf("%d\n", mergeCnt);
	}
}
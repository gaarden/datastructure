#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001

void read_data(char infile[]);
void merge(int initList[], int mergedList[], int i, int m, int n);
void mergePass(int initList[], int mergedList[], int n, int s);
void mergeSort(int a[], int n);
void printList(int initList[], int mergedList[]);

int size = 0;
int check = 0;
int lst[MAX_SIZE];
int extra[MAX_SIZE];
int count; // lst를 print할지, extra를 print할지 결정하기 위해 세는 것

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
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

	fscanf(fp, "%d ", &check);

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
	count++;

	if (check == s)
	{
		printList(lst, extra);
	}
}

void mergeSort(int a[], int n)
{
	int s = 1;

	while (s < n)
	{
		mergePass(a, extra, n, s);
		s *= 2;
		if (s >= n)
			break;
		mergePass(extra, a, n, s);
		s *= 2;
	}
}

void printList(int initList[], int mergedList[])
{
	if (count % 2 == 0)
	{
		for (int i = 1; i <= size; i++)
			printf("%d ", initList[i]);
		printf("\n");
	}

	else
	{
		for (int i = 1; i <= size; i++)
			printf("%d ", mergedList[i]);
		printf("\n");
	}
}
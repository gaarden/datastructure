#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001

void read_data(char infile[]);
void merge(int initList[], int mergedList[], int i, int m, int n);
int rmergeSort(int a[], int link[], int left, int right);
int listMerge(int a[], int link[], int start1, int start2);
void printList(int a[]);

int size = 0;
int lst[MAX_SIZE];
int index[MAX_SIZE];
int start = 1;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	rmergeSort(lst, index, start, size);
	printList(index);

	for (int i = index[0]; i != 0; i = index[i])
		printf("%d ", lst[i]);

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

int rmergeSort(int a[], int link[], int left, int right)
{
	if (left >= right)
		return left;

	int mid = (left + right) / 2;

	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}

int listMerge(int a[], int link[], int start1, int start2)
{
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;)
	{
		if (a[last1] <= a[last2])
		{
			link[lastResult] = last1;
			lastResult = last1;
			last1 = link[last1];
		}

		else
		{
			link[lastResult] = last2;
			lastResult = last2;
			last2 = link[last2];
		}
	}

	if (last1 == 0)
		link[lastResult] = last2;

	else
		link[lastResult] = last1;
	
	return link[0];
}

void printList(int a[])
{
	for (int i = 0; i <= size; i++)
		printf("%d ", a[i]);
	printf("\n");
}
// 0519 2번

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001
typedef struct
{
	int key;
}element;

void read_data(char infile[]);
void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);
int compareList(element a[], element b[], int n, int m);
void printList(element a[], int n);

element list1[MAX_SIZE];
element list2[MAX_SIZE];
element same[MAX_SIZE];
int size;
int flag;
int check;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	check = compareList(list1, list2, flag, size - flag);

	if (check == -1)
		printf(" ");

	else
		printList(same, check);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int k = 0;

	fscanf(fp, "%d ", &size);

	for (int i = 1; i <= size;i++)
	{
		fscanf(fp, "%d ", &k);

		element new;
		new.key = k;

		list1[i] = new;
	}

	fscanf(fp, "%d ", &flag);

	for (int i = flag + 1, j = 1;i <= size; i++)
		list2[j++] = list1[i];

	mergeSort(list1, flag);
	mergeSort(list2, size - flag);

	fclose(fp);
}

void merge(element initList[], element mergedList[], int i, int m, int n)
{
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n)
	{
		if (initList[i].key <= initList[j].key)
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

void mergePass(element initList[], element mergedList[], int n, int s)
{
	int i, j;

	for (i = 1; i <= n - 2 * s + 1; i += 2 * s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);

	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);

	else if (i <= n)
		for (j = i; j <= size; j++)
			mergedList[j] = initList[j];
}

void mergeSort(element a[], int n)
{
	int s = 1;
	element extra[MAX_SIZE];

	while (s < n)
	{
		mergePass(a, extra, n, s);
		s *= 2;
		mergePass(extra, a, n, s);
		s *= 2;
	}
}

int compareList(element a[], element b[], int n, int m)
{
	// a: 배열1, b: 배열2, n: 배열1 끝인덱스, m: 배열2 끝인덱스
	int i = 1, j = 1, k = -1;

	while (i <= n && j <= m)
	{
		if (a[i].key > b[j].key)
			j++;

		else if (a[i].key < b[j].key)
			i++;

		else
		{
			k++;
			same[k] = a[i];
			i++;
			j++;
		}
	}

	return k;
}

void printList(element a[], int n)
{
	for (int i = 0; i <= n; i++)
		printf("%d ", a[i].key);
}
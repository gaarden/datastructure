// 0519 1¹ø

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
void printList(element a[]);

element list[MAX_SIZE];
int index[MAX_SIZE];
int cnt;
int size;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printList(list);
	printf("%d ", cnt);

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

		list[i] = new;
	}

	mergeSort(list, size);

	fclose(fp);
}

void merge(element initList[], element mergedList[], int i, int m, int n)
{
	cnt++;

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
		merge(initList, mergedList, index[i - 1] + 1, index[i + s - 1], index[i + 2 * s - 1]);

	if (i + s - 1 < n)
		merge(initList, mergedList, index[i - 1] + 1, index[i + s - 1], index[n]);

	else if (i <= n)
		for (j = index[i - 1] + 1; j <= size; j++)
			mergedList[j] = initList[j];
}

void mergeSort(element a[], int n)
{
	int s = 1, i = 2, k = 0; /* current segment size */
	element extra[MAX_SIZE];

	index[k++] = 0;
	while (i <= n)
	{
		if (a[i - 1].key > a[i].key)
			index[k++] = i - 1;
		i++;
	}
	index[k] = n;

	while (s < k)
	{
		mergePass(a, extra, k, s); s *= 2;
		mergePass(extra, a, k, s); s *= 2;
	}
}

void printList(element a[])
{
	for (int i = 1; i <= size; i++)
		printf("%d ", a[i].key);
}
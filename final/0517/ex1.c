// 0517 1¹ø

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
int cnt;
int check;
int size;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);

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

	fscanf(fp, "%d ", &check);

	mergeSort(list, size);

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

	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];

	if (s == check)
		printList(mergedList);
}

void mergeSort(element a[], int n)
{
	int s = 1;
	element extra[MAX_SIZE];

	while (s < n)
	{
		mergePass(a, extra, n, s);

		s *= 2;
		if (s > n)
		{
			printList(extra);
			break;
		}

		mergePass(extra, a, n, s);

		s *= 2;
		if (s > n)
		{
			printList(a);
			break;
		}
	}
}

void printList(element a[])
{
	for (int i = 1; i <= size; i++)
		printf("%d ", a[i].key);

	printf("\n");
}
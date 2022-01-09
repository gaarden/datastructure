// 0517 2¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001
typedef struct
{
	int key;
}element;

void read_data(char infile[]);
int rmergeSort(element a[], int link[], int left, int right);
int listMerge(element a[], int link[], int start1, int start2);

element list[MAX_SIZE];
int index[MAX_SIZE];
int size;
int start;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	rmergeSort(list, index, 1, size);
	start = index[0];

	for (int i = 0; i <= size; i++)
		printf("%d ", index[i]);
	printf("\n");

	for (int i = start; i; i = index[i])
		printf("%d ", list[i].key);

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

	fclose(fp);
}

int rmergeSort(element a[], int link[], int left, int right)
{
	if (left >= right)
		return left;

	int mid = (left + right) / 2;

	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}

int listMerge(element a[], int link[], int start1, int start2)
{
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2; )
	{
		if (a[last1].key <= a[last2].key)
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
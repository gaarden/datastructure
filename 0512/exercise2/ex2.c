#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001

int lst[MAX_SIZE] = { 0 };
int value = 0;
int cnt = 0;
int m = 0;

void read_data(char infile[]);
void quickSort(int a[], int left, int right);
void printList(int a[]);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	quickSort(lst, 1, cnt);
	printList(lst);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &value);

		if (value != -1)
			lst[++cnt] = value;

		else
			break;
	}

	fscanf(fp, "%d ", &m);

	fclose(fp);
}

void quickSort(int a[], int left, int right)
{
	int pivot, i, j;
	int temp;

	if (right - left == m)
	{
		for (int i = left; i <= right; i++)
			printf("%d ", a[i]);
		printf("\n");
	}

	if (left < right)
	{
		i = left;
		j = right + 1;
		pivot = a[left];

		do
		{
			do
			{
				i++;
			} while ((a[i] < pivot) && (i <= right));

			do
			{
				j--;
			} while ((a[j] > pivot) && (j >= left));

			if (i < j)
			{
				int save = a[i];
				a[i] = a[j];
				a[j] = save;
			}

		} while (i < j);

		int change = a[left];
		a[left] = a[j];
		a[j] = change;

		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

void printList(int a[])
{
	for (int i = 1; i <= cnt; i++)
		printf("%d ", a[i]);
	printf("\n");
}
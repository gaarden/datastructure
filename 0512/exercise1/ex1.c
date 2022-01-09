#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001

int lst[MAX_SIZE] = { 0 };
int value = 0;
int cnt = 0;
int m = 0;
int check = 0;

void read_data(char infile[]);
void insert(int e, int a[], int i);
void insertionSort(int a[], int n);
void printList(int a[]);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	insertionSort(lst, cnt);
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

void insert(int e, int a[], int i)
{
	a[0] = e;

	while (e < a[i])
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;

	check++;
}

void insertionSort(int a[], int n)
{
	int j;

	for (j = 2; j <= n; j++)
	{
		int temp = a[j];
		insert(temp, a, j - 1);

		if (check == m)
			printList(a);
	}
}

void printList(int a[])
{
	for (int i = 1; i <= cnt; i++)
		printf("%d ", a[i]);
	printf("\n");
}
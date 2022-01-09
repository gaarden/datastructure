// 0512 1¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001
typedef struct
{
	int key;
}element;

void read_data(char infile[]);
void insert(element e, element a[], int i);
void insertionSort(element a[], int n);
void printList(element a[]);

element list[MAX_SIZE];
int cnt;
int check;

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

	while (1)
	{
		fscanf(fp, "%d ", &k);

		if (k == -1)
			break;

		element new;
		new.key = k;

		cnt++;
		list[cnt] = new;
	}

	fscanf(fp, "%d ", &check);
	insertionSort(list, cnt);

	fclose(fp);
}

void insert(element e, element a[], int i)
{
	a[0] = e;

	while (e.key < a[i].key)
	{
		a[i + 1] = a[i];
		i--;
	}

	a[i + 1] = e;
}

void insertionSort(element a[], int n)
{
	int j;

	for (j = 2; j <= n; j++)
	{
		element temp = a[j];
		insert(temp, a, j - 1);

		if (j == check + 1)
			printList(a);
	}

	printList(a);
}

void printList(element a[])
{
	for (int i = 1; i <= cnt; i++)
		printf("%d ", a[i].key);

	printf("\n");
}
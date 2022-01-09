#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void read_data(char infile[]);
void adjust(int a[], int root, int n);
void heapSort(int a[], int n);
void printList(int a[]);

int size = 0;
int list[MAX_SIZE];
int checkP = 0;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	heapSort(list, size);
	printList(list);

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

	for (int i = 1; i <= size; i++)
		fscanf(fp, "%d ", &list[i]);

	fscanf(fp, "%d ", &checkP);

	fclose(fp);
}

void adjust(int a[], int root, int n)
{
	int child, rootkey;
	int temp;
	temp = a[root];
	rootkey = a[root];
	child = 2 * root;

	while (child <= n)
	{
		if ((child < n) && (a[child] < a[child + 1]))
			child++;

		if (rootkey > a[child])
			break;

		else
		{
			a[child / 2] = a[child];
			child *= 2;
		}
	}

	a[child / 2] = temp;
}

void heapSort(int a[], int n)
{
	int i, j;
	int temp;

	for (i = n / 2; i > 0; i--)
		adjust(a, i, n);

	for (i = n - 1; i > 0; i--)
	{
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);

		if (i == checkP)
			printList(list);
	}
}

void printList(int a[])
{
	for (int i = 1; i <= size; i++)
		printf("%d ", a[i]);
	printf("\n");
}
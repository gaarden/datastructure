//0524 1¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001
typedef struct
{
	int key;
}element;

void read_data(char infile[]);
void heapSort(element a[], int n);
void adjust(element a[], int root, int n);
void printList(element a[]);

element list[MAX_SIZE];
int size;
int check;

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

	fclose(fp);
}

void heapSort(element a[], int n)
{
	int i, j;
	element temp;

	for (i = n / 2; i > 0; i--)
		adjust(a, i, n);

	for (i = n - 1; i > 0; i--)
	{
		temp = a[1];
		a[1] = a[i + 1];
		a[i + 1] = temp;

		adjust(a, 1, i);

		if (i == check)
			printList(a);
	}
}

void adjust(element a[], int root, int n)
{
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n)
	{
		if ((child < n) && (a[child].key < a[child + 1].key))
			child++;

		if (rootkey > a[child].key)
			break;

		else
		{
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}

void printList(element a[])
{
	for (int i = 1; i <= size; i++)
		printf("%d ", a[i].key);

	printf("\n");
}
// 0524 2¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001
typedef struct
{
	int key;
}element;

void read_data(char infile[]);
int radixSort(element a[], int link[], int d, int r, int n);
int digit(element temp, int i, int r);
void printList(element a[], int link[], int n);

element list[MAX_SIZE];
int index[MAX_SIZE];
int front[MAX_SIZE], rear[MAX_SIZE];
int size;
int start;
int dig = 3;
int rad = 10;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	start = radixSort(list, index, dig, rad, size);
	printList(list, index, start);

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

	for (int i = 1; i <= size; i++)
	{
		fscanf(fp, "%d ", &k);

		element new;
		new.key = k;

		list[i] = new;
	}

	fclose(fp);
}

int radixSort(element a[], int link[], int d, int r, int n)
{
	int i, bin, current, first, last;

	first = 1;
	for (i = 1; i < n; i++)
		link[i] = i + 1;

	link[n] = 0;

	for (i = d - 1; i >= 0; i--)
	{
		for (bin = 0; bin < r; bin++)
			front[bin] = 0;

		for (current = first; current; current = link[current])
		{
			bin = digit(a[current], i, r);

			if (front[bin] == 0)
				front[bin] = current;

			else
				link[rear[bin]] = current;

			rear[bin] = current;
		}

		for (bin = 0; !front[bin]; bin++);

		first = front[bin];
		last = rear[bin];

		for (bin++; bin<r; bin++)
			if (front[bin])
			{
				link[last] = front[bin];
				last = rear[bin];
			}

		link[last] = 0;
	}

	return first;
}

int digit(element temp, int i, int r)
{
	int k = temp.key;

	for (int j = dig - 1; j > i; j--)
		k /= r;

	k %= r;

	return k;
}

void printList(element a[], int link[], int n)
{
	for (int i = n; i ; i = link[i])
		printf("%d ", a[i].key);

	printf("\n");
}
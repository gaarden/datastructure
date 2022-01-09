#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10001
#define MAX_QUEUE 11
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

void read_data(char infile[]);
int radixSort(int a[], int link[], int d, int r, int n);
int digit(int key, int n, int m);
void printList(int a[], int link[], int n);

int size = 0;
int list[MAX_SIZE];
int index[MAX_SIZE];
int front[MAX_QUEUE];
int rear[MAX_QUEUE];
int start = 0;
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

	fscanf(fp, "%d ", &size);

	for (int i = 1; i <= size; i++)
		fscanf(fp, "%d ", &list[i]);

	fclose(fp);
}

int radixSort(int a[], int link[], int d, int r, int n)
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

		//printList(a, link, first);
	}

	return first;
}

int digit(int key, int n, int m)
{
	int copy = key;

	for (int j = n + 1; j < dig; j++)
		copy = copy / m;

	copy = copy % m;

	return copy;
}

void printList(int a[], int link[], int n)
{
	for (int i = n; i; i = link[i])
		printf("%d ", a[i]);
	printf("\n");
}
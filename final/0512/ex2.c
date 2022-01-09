// 0512 2¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001
typedef struct
{
	int key;
}element;

void read_data(char infile[]);
void quickSort(element a[], int left, int right);
void printList(element a[], int left, int right);

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
	printList(list, 0, cnt);

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
		{
			cnt--;
			break;
		}

		element new;
		new.key = k;

		list[cnt] = new;
		cnt++;
	}

	fscanf(fp, "%d ", &check);

	quickSort(list, 0, cnt);

	fclose(fp);
}

void quickSort(element a[], int left, int right)
{
	int pivot, i, j;
	element temp;
	if (left < right)
	{
		if (right - left == check)
			printList(a, left, right);

		i = left;
		j = right + 1;
		pivot = a[left].key;

		do
		{
			do i++;
			while (a[i].key < pivot && i <= right);

			do j--;
			while (a[j].key > pivot && j >= left);

			if (i < j)
			{
				int temp = a[i].key;
				a[i].key = a[j].key;
				a[j].key = temp;
			}
		} while (i < j);

		int temp = a[left].key;
		a[left].key = a[j].key;
		a[j].key = temp;

		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

void printList(element a[], int left, int right)
{
	for (int i = left; i <= right; i++)
		printf("%d ", a[i].key);

	printf("\n");
}
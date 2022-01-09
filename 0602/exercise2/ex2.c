// 0602 2번

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10000

void read_data(char infile[]);
void sort(int list[MAX_SIZE][MAX_SIZE], int ind[]);
void sorting(int i1, int i2, int list1[], int list2[]);
void printList(int list[MAX_SIZE][MAX_SIZE]);

// lst 0번째 배열에다가 정렬한 것 저장할것임
// lst 1번째 배열부터 정보 저장

int size = 0;
int lst[MAX_SIZE][MAX_SIZE]; // 배열 정보 저장 공간
int index[MAX_SIZE]; // 배열 인덱스 크기 저장 공간
int newSort[MAX_SIZE];
int cnt = 0; // 배열 몇개인지 저장
int save = 0; // 정렬된 배열의 원소 개수

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	
	sort(lst, index);

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

	fscanf(fp, "%d ", &size);
	int n = 0;

	while (!feof(fp))
	{
		int count = 0;
		cnt++;

		while (1)
		{
			fscanf(fp, "%d ", &n);

			if (n != -1)
			{
				lst[cnt][count] = n;
				count++;
			}

			else
				break;
		}

		index[cnt] = count;
	}

	for (int i = 0; i < index[1]; i++)
		lst[0][i] = lst[1][i];

	index[0] = index[1];
	save = index[0];


	fclose(fp);
}

void sort(int list[MAX_SIZE][MAX_SIZE], int ind[])
{
	for (int i = 2; i <= cnt; i++)
	{
		int a = ind[0];
		int b = ind[i];

		sorting(a, b, list[0], list[i]);

		ind[0] += ind[i];
	}
}

void sorting(int i1, int i2, int list1[], int list2[])
{
	int j = 0, k = 0;
	int cc = 0;

	while (j < i1 && k < i2)
	{
		if (list1[j] < list2[k])
		{
			newSort[cc] = list1[j];
			j++;
			cc++;
		}

		else if (list1[j] > list2[k])
		{
			newSort[cc] = list2[k];
			k++;
			cc++;
		}

		else
		{
			newSort[cc] = list1[j];
			j++;
			cc++;
			newSort[cc] = list2[k];
			k++;
			cc++;
		}
	}

	for (; j < i1; j++)
		newSort[cc++] = list1[j];

	for (; k < i2; k++)
		newSort[cc++] = list2[k];

	for (int i = 0; i < cc; i++)
		lst[0][i] = newSort[i];

}

void printList(int list[MAX_SIZE][MAX_SIZE])
{
	for (int i = 0; i < index[0]; i++)
		printf("%d ", list[0][i]);
}
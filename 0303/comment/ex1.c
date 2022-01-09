/*
Selection sort 를 다음과 같은 구성으로 구현하라
1. 전역변수 int list[MAX_SIZE] 사용
2. 파일을 열어 파일에 있는 정수들을 읽고 순서대로 list에 저장
• 파일명은 argument로 전달
3. void selection_sort(): list 에 있는 수들을 오름차순으로 정렬
4. 정렬된 결과 표준 출력
Input:
- Text파일로 된 정수 리스트, 각 정수는 공백으로 구분
ex) 5 9 10 2 4
Output:
- 정렬된 리스트를 표준출력, 각 정수는 공백으로 구분
ex) 2 4 5 9 10
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001

int read_data(char infile[], int list[]);
void selection_sort(int list[], int n);
void print_list(int list[], int n);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	int lst[MAX_SIZE];
	int cnt;

	cnt = read_data(argv[1], lst);
	selection_sort(lst, cnt);
	print_list(lst, cnt);

	return EXIT_SUCCESS;
}

int read_data(char infile[], int list[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int n = 0;

	while (!feof(fp))
		fscanf(fp, "%d ", &(list[n++]));

	fclose(fp);

	return n;
}

void selection_sort(int list[], int n)
{
	int min, temp;

	for (int i = 0; i < n-1; i++)
	{
		min = i;

		for (int j = i+1; j < n; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		temp = list[min];
		list[min] = list[i];
		list[i] = temp;
	}
}

void print_list(int list[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}
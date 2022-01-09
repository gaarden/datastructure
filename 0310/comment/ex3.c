/*
• Selection sort 함수의 효율측정 프로그램을 dynamically allocated array 를 사용하여 재작성하라.
– Input: Sort 할 자료의 최대 크기 max_size Ex)300
– Output: 자료의 크기를 step 의 크기만큼씩 증가시켜서 측정한 수행속도 결과
Ex) Standard output : 1, 2, 3, 4, … 99, 100, 1, 2, 3, 4 … 199, 200, 1, 2, 3, 4, … 299, 300
파일 출력 : 파일 이름 “output.txt“
i=100 time : 0.00122s
i=200 time : 0.02142s
i=300 time : 0.12412s
– Specification: i=100.. max_size 까지 반복하며
• i개의 자료를 저장할 배열 생성(역순으로 초기화할것)
• Selection sort 함수 호출
• 배열의 메모리 할당 공간 비우기
• step = 100
– 프로그램 작성조건
• 전역변수를 사용하지 않음
• 배열의 크기를 미리 정하지 않음
• 배열의 주소를 sort 함수와 print 함수로 전달하여 처리
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MALLOC(p, s)\
if(!((p)=malloc(s)))\
{\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

int read_data(char infile[]);
int* make1dArray(int n);
void selection_sort(int* list, int n);
void print_list(int* list, int n);

void main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	FILE* fp;

	if (!(fp = fopen("output.txt", "w")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int step = 100;
	int* lst;
	int size;
	
	size = read_data(argv[1]);
	double duration;

	for (int n = 100; n <= size; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		lst = make1dArray(n);

		for (int i = 0; i < n;i++)
			lst[i] = n - i; // 역순 초기화

		selection_sort(lst, n);
		print_list(lst, n);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		fprintf(fp, "i=%d	time : %fs\n", n, duration);
	}

	fclose(fp);
}

int read_data(char infile[])
{
	FILE* f;

	if (!(f = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int num;

	fscanf(f, "%d ", &num);

	fclose(f);

	return num;
}

int* make1dArray(int n)
{
	int i, * list;

	if (n < 1)
	{
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(list, n * sizeof(int));

	return list;
}

void selection_sort(int* list, int n)
{
	int min, temp;

	for (int i = 0; i < n - 1; i++)
	{
		min = i;

		for (int j = i + 1; j < n; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		temp = list[min];
		list[min] = list[i];
		list[i] = temp;
	}
}

void print_list(int* list, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}
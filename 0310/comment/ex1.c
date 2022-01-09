/*
Selection sort 함수를 dynamically allocated array 를 사용하여 재작성하라.
• Input :
– Sort 할 자료의 최대 크기 n
– 정렬할 리스트
• Output :
– 정렬된 결과
Ex) 1 2 3 4 5 6 7 8 9 10
• Specification :
• n개의 자료를 저장할 배열 생성
• Selection sort 함수 호출하여 결과 출력
• 배열의 메모리 할당 공간 비우기
• 프로그램 작성조건
• 전역변수를 사용하지 않음
• 배열의 크기를 미리 정하지 않음
• 배열의 주소를 sort 함수와 print 함수로 전달하여 처리
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if(!((p)=malloc(s)))\
{\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

int read_data(FILE * fp, char infile[]);
void read_data2(FILE * fp, int* list);
int* make1dArray(int n);
void selection_sort(int* list, int n);
void print_list(int* list, int n);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	FILE* fp;

	if (!(fp = fopen(argv[1], "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	int listSize = 0;
	int *lst;

	listSize = read_data(fp, argv[1]);
	lst = make1dArray(listSize);
	read_data2(fp, lst);
	selection_sort(lst, listSize);
	print_list(lst, listSize);
	free(lst);

	fclose(fp);

	return EXIT_SUCCESS;
}

int read_data(FILE *fp, char infile[])
{
	int num = 0;

	fscanf(fp, "%d ", &num);

	return num;
}

void read_data2(FILE* fp, int *list)
{
	int i = 0;
	while (!feof(fp))
		fscanf(fp, "%d ", &list[i++]);
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

void selection_sort(int *list, int n)
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

void print_list(int *list, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
}
/*
C:\Users\LG\Desktop\KNU20211\DataStructure\0310\exercise\ex1.c
Exercise 1
• Selection sort 함수를 dynamically allocated array 를 사용하여 재작성하라.
• Input:
– Sort 할 자료의 최대 크기 n
– 정렬할 리스트
• Output:
– 정렬된 결과
Ex) 1 2 3 4 5 6 7 8 9 10
• Specification:
• n개의 자료를 저장할 배열 생성
• Selection sort 함수 호출하여 결과 출력
• 배열의 메모리 할당 공간 비우기
• 프로그램 작성조건
• 전역변수를 사용하지 않음
• 배열의 크기를 미리 정하지 않음
• 배열의 주소를 sort 함수와 print 함수로 전달하여 처
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MALLOC(p, s)\
if (!((p)=malloc(s)))\
{fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

int read_data1(FILE *fp, char infile[]);
int* make1dArray(int n);
void read_data2(FILE *fp, char infile[], int *list);
void selection_sort(int *list, int n);
void print(int *list, int n);


int main(int argc, char** argv)
{
    FILE* fp;
    fp = fopen(argv[1], "r");

    int* makeList;
    int input_size = 0;

    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    input_size = read_data1(fp, argv[1]);
    makeList = make1dArray(input_size);
    read_data2(fp, argv[1], makeList);
    selection_sort(makeList, input_size);
    print(makeList, input_size);
    fclose(fp);
    free(makeList);

    return 0;
}

int* make1dArray(int n)
{
    int * list;

    if (n < 1)
    {
        fprintf(stderr, "Improper value of n|n");
        exit(EXIT_FAILURE);
    }

    MALLOC(list, n * sizeof(int));
    return list;
}

int read_data1(FILE* fp, char infile[])
{
    int num = 0;

    fscanf(fp, "%d", &(num));

    return num;
}

void read_data2(FILE* fp, char infile[], int *list)
{
    int n = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%d ", &list[n]);
        n++;
    }

}

void selection_sort(int *list, int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        SWAP(list[i], list[min], temp);
    }
}

void print(int *list, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
}
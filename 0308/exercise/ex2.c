/*
C:\Users\LG\Desktop\KNU20211\DataStructure\0308\exercise\ex2.c
Exercise 2 • Binary Search 함수의 수행속도를 측정하라
1. Input:
• 정수 리스트의 크기 n
• n개의 정수 (각각 공백으로 구분됨)
• 검색하고자 하는 수의 리스트
2. Output:
• 각각의 검색하는 수에 대하여, 리스트에 존재하면 index 출력, 없으면 -1 출력 (standard output) Output은 공백으
로 구별하여 출력
EX) standard output : -1 2
• 수행속도 측정 결과는 파일 출력, 파일 이름 : 2번째 argument로 전달)
EX) 파일 출력 :
repetitions time
 11 0.093545
3. Specification
• 입력파일의 정수리스트를 배열에 저장
• 정렬 수행
• 입력파일로 부터 검색하고자 하는 수를 하나씩 읽으며 검색수행하고 결과 출력
• 시간 측정 결과 출력 시, 모든 검색하고자 하는 수를 1000번 탐색한 시간을 출
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX_SIZE 1000000
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void read_data(char infile[], int list[], int search[]);
void selection_sort(int list[], int n);
int binsearch(int list[], int searchnum, int left, int right);
int num, size = 0, searchsize = 0, step = 10;
double duration;
int input_data[MAX_SIZE];
int search_num[MAX_SIZE];

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    read_data(argv[1], input_data, search_num);
    FILE* fp;

    if (!(fp = fopen(argv[2], "w")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    selection_sort(input_data, size);

    fprintf(fp, "%s", "repetitions time\n");

    for (int n = 0; n <= 1000; n += step)
    {
        long repetition = 0;
        clock_t start = clock();

        do
        {
            repetition++;

            for (int i = 0; i < searchsize; i++)
                binsearch(input_data, search_num[i], 0, size - 1);

        } while (clock() - start < 1000);


        double duration_1 = ((double)(clock() - start));
        duration = duration_1 / CLOCKS_PER_SEC;
        duration /= repetition;

        fprintf(fp, "%6d  %9d\n", repetition, duration);

        if (n == 100) step = 100;
    }
    fclose(fp);

    for (int i = 0; i < searchsize; i++)
        printf("%d ", binsearch(input_data, search_num[i], 0, size - 1));

    return 0;
}

void read_data(char infile[], int list[], int search[])
{
    FILE* fp;

    if (!(fp = fopen(infile, "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d ", &size);

    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%d ", &(list[i]));

    }

    while (!feof(fp))
    {
        fscanf(fp, "%d ", &(search[searchsize]));
        searchsize++;
    }

    fclose(fp);
}

void selection_sort(int list[], int n)
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

int binsearch(int list[], int searchnum, int left, int right)
{
    int middle = (left + right) / 2;
    if (left <= right)
    {
        if (list[middle] > searchnum)
            return binsearch(list, searchnum, left, middle - 1);
        else if (list[middle] < searchnum)
            return binsearch(list, searchnum, middle + 1, right);
        else
            return middle;
    }
    else
        return -1;
}
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
#include <math.h>
#define MAX_SIZE 10000
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int read_data(char infile[], int list[]);
void selection_sort(int list[], int n);

int main1(int argc, char** argv)
{
    int input_data[MAX_SIZE];
    int input_size = 0;

    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    input_size = read_data(argv[1], input_data);

    selection_sort(input_data, input_size);

    for (int i = 0; i < input_size; i++)
        printf("%d ", input_data[i]);

    return 0;
}


int read_data(char infile[], int list[])
{
    FILE* fp;
    int size = 0;

    if (!(fp = fopen(infile, "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d ", &(list[size]));
        size++;
    }
    fclose(fp);

    return size;
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
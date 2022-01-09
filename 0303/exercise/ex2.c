/*
Binary search 를 다음과 같은 구성으로 구현하라
1. Exercise 1 에서 작성한 코드를 재사용하여 selection sort 수행
2. int binsearch(int searchnum, int left, int right): list 에서 searchnum 을
찾아 있으면 해당 인덱스를, 없으면, -1 을 반환
3. 찾을 정수 searchnum은 txt 파일에 정수 리스트와 함께 전달
4. Searchnum에 대한 binsearch 함수를 수행하고 결과를 표준출력
Input:
– 두 줄로 구성된 txt 파일
• 첫 번째 줄 : 찾을 정수 값
• 두 번째 줄 : 정수 리스트
Ex) 5
4 7 1 3 5
Output:
– 찾는 값이 있으면 인덱스를, 없으면 -1 을 표준출력
Ex) 3
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 10000
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int read_data(char infile[], int list[]);
void selection_sort(int list[], int n);
int binsearch(int searchnum, int left, int right);
int num;
int input_data[MAX_SIZE];
int input_size = 0;

int main2(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    input_size = read_data(argv[1], input_data);
    selection_sort(input_data, input_size);
    printf("%d", binsearch(num, 0, input_size - 1));

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

    fscanf(fp, "%d", &(num));
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

int binsearch(int searchnum, int left, int right)
{
    int temp;
    int middle = (left + right) / 2;

    temp = right;
    if (input_data[middle] != searchnum)
    {
        if (searchnum < input_data[middle])
            right = middle - 1;
        else
            left = middle + 1;

        binsearch(num, left, right);
    }
    else
        return middle;
}
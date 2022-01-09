/*
C:\Users\LG\Desktop\KNU20211\DataStructure\0310\exercise\ex2.c
Exercise 2
(2차원 동적할당 연습)
• Task: 이차원 행렬의 모든 원소의 합을 구하는 프로그램을 작성하되, 동적할당을
이용하여 메모리 사용량을 최소화하여 작성하라
• Input:
– 행렬의 크기 m, n
– m*n 개의 정수형 원소
• Output:
– 읽은 행렬
– 행렬의 모든 원소의 합
• Specification:
– 파일 input.txt의 첫줄에 m, n 의 값, 둘째줄 부터 m*n 개의 원소값들이 있다
고 가정(파일 이름은 첫 번째 argument로 전달)
– m*n 배열을 동적할당으로 생성하고 파일로부터 원소들을 읽어 배열에 저장
– 배열의 내용을 출력하여 확인
– 마지막으로 배열의 모든 원소의 합을 출력
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MALLOC(p, s)\
if (!((p)=malloc(s)))\
{fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

int read_data1_1(FILE* fp, char infile[]);
int read_data1_2(FILE * fp, char infile[]);
int** make2dArray(int rows, int cols);
void read_data2(FILE* fp, char infile[], int** x, int rows, int cols);
void print(int** x, int n, int m);


int main(int argc, char** argv)
{
    FILE* fp;
    fp = fopen(argv[1], "r");

    int** makeList;
    int row = 0;
    int col = 0;

    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    row = read_data1_1(fp, argv[1]);
    col = read_data1_2(fp, argv[1]);
    makeList = make2dArray(row, col);
    read_data2(fp, argv[1], makeList, row, col);
    print(makeList, row, col);
    fclose(fp);
    free(makeList);

    return 0;
}

int** make2dArray(int rows, int cols)
{
    int** x, i;

    MALLOC(x, rows*sizeof(*x));

    for (i = 0; i < rows; i++)
        MALLOC(x[i], cols * sizeof(**x));

    return x;
}

int read_data1_1(FILE* fp, char infile[])
{
    int num = 0;

    fscanf(fp, "%d", &(num));

    return num;
}

int read_data1_2(FILE* fp, char infile[])
{
    int num = 0;

    fscanf(fp, "%d", &(num));

    return num;
}

void read_data2(FILE* fp, char infile[], int** x, int rows, int cols)
{
    int n, m;

    while (!feof(fp))
    {
        for (n = 0; n < rows; n++)
            for (m = 0; m < cols; m++)
                fscanf(fp, "%d ", &x[n][m]);
    }
}

void print(int** list, int n, int m)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", list[i][j]);
            sum += list[i][j];
        }
        printf("\n");
    }

    printf("%d", sum);
}
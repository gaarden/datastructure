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

int read_data(FILE* fp, char infile[]);
int* make1dArray(int n);
void selection_sort(int* list, int n);
void print(int* list, int n);

int main(int argc, char** argv)
{
    FILE* fp;
    fp = fopen(argv[1], "r");

    int* makeList;
    int* speedList;
    int input_size = 0;
    int step = 100;

    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    input_size = read_data(fp, argv[1]);
    makeList = make1dArray(input_size);
    speedList = make1dArray(input_size);
    selection_sort(makeList, input_size);
    print(makeList, input_size);
    fclose(fp);
    free(makeList);

    return 0;
}

int read_data(FILE* fp, char infile[])
{
    int num = 0;

    fscanf(fp, "%d", &(num));

    return num;
}

int* make1dArray(int n)
{
    int* list;

    if (n < 1)
    {
        fprintf(stderr, "Improper value of n|n");
        exit(EXIT_FAILURE);
    }

    MALLOC(list, n * sizeof(int));
    return list;
}

void selection_sort(int* list, int n)
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

void write_data(int list[], char outfile[], int size, double speed[])
{
    int i = 0;
    FILE* f;

    if (!(f = fopen("output.txt", "w")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < size; i++)
    {
        fprintf(f, "i = %d time : %.5fs\n", list[i], speed[i]);
    }
    fclose(f);
}
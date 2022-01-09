#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)
typedef struct {
    int col;
    int row;
    int value;
}term;

int n, m, l, element;
void read_data(FILE* fp, term a[], term b[]);
void transpose(term a[], term b[]);
void storeSum(term d[], int* totalD, int row, int column, int* sum);
void mmult(term a[], term b[], term d[]);
void printMatrix(term a[]);

term a[MAX_TERMS];
term b[MAX_TERMS];
term d[MAX_TERMS];

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    FILE* fp;

    if (!(fp = fopen(argv[1], "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    read_data(fp, a, b);

    mmult(a, b, d);
    printMatrix(d);

    fclose(fp);
    return 0;
}

void read_data(FILE* fp, term a[], term b[])
{
    fscanf(fp, "%d %d %d", &n, &m, &l);

    a[0].row = n;
    a[0].col = m;
    b[0].row = m;
    b[0].col = l;

    int num = 1;
    int cnt = 0;
    int count = 0;


    while (count < n * m)
    {
        fscanf(fp, "%d ", &element);

        if (element != 0)
        {
            a[num].row = cnt / m;
            a[num].col = cnt % m;
            a[num].value = element;

            num++;
            cnt++;
        }

        else
            cnt++;

        count++;
    }
    a[0].value = num - 1;

    num = 1;
    cnt = 0;
    count = 0;

    while (count < m * l)
    {
        fscanf(fp, "%d ", &element);

        if (element != 0)
        {
            b[num].row = cnt / l;
            b[num].col = cnt % l;
            b[num].value = element;

            num++;
            cnt++;
        }

        else
            cnt++;

        count++;
    }
    b[0].value = num - 1;
}

void transpose(term a[], term b[])
{
    int rowTerms[MAX_TERMS], startingPos[MAX_TERMS];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0)
    {
        for (i = 0; i < numCols; i++)
            rowTerms[i] = 0;
        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;
        for (i = 1; i <= numCols; i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        for (i = 1; i <= numTerms; i++)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void storeSum(term d[], int* totalD, int row, int column, int* sum)
{
    if (*sum)
        if (*totalD < MAX_TERMS)
        {
            d[++ * totalD].row = row;
            d[*totalD].col = column;
            d[*totalD].value = *sum;
            *sum = 0;
        }
        else
        {
            fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
            exit(EXIT_FAILURE);
        }
}

void mmult(term a[], term b[], term d[])
{
    int i, j, column, totalB = b[0].value, totalD = 0;
    int rowsA = a[0].row, colsA = a[0].col,
        totalA = a[0].value; int colsB = b[0].col;
    int rowBegin = 1, row = a[1].row, sum = 0;

    term newB[MAX_TERMS];

    if (colsA != b[0].row)
    {
        fprintf(stderr, "Incompatible matrice\n");
        exit(EXIT_FAILURE);
    }

    transpose(b, newB);

    a[totalA + 1].row = rowsA;
    a[totalA + 1].col = 0;
    a[totalA + 1].value = 0;
    newB[totalB + 1].row = colsB;
    newB[totalB + 1].col = 0;
    newB[totalB + 1].value = 0;

    for (i = 1; i <= totalA;)
    {
        column = newB[1].row;
        for (j = 1; j <= totalB + 1;)
        {
            if (a[i].row != row)
            {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                for (; newB[j].row == column; j++)
                    ;
                column = newB[j].row;
            }
            else if (newB[j].row != column)
            {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                column = newB[j].row;
            }
            else switch (COMPARE(a[i].col, newB[j].col))
            {
            case -1:
                i++;
                break;
            case 0:
                sum += (a[i++].value * newB[j++].value);
                break;
            case 1:
                j++;
            }
        }
        for (; a[i].row == row; i++)
            ;
        rowBegin = i; row = a[i].row;
    }
    d[0].row = rowsA;
    d[0].col = colsB;
    d[0].value = totalD;
}

void printMatrix(term a[])
{
    int f = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < l; j++)
        {
            if ((a[f].row == i) && (a[f].col == j))
            {
                printf("%d ", a[f++].value);
            }
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
}

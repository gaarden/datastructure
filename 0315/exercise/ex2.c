#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

int n, m, a, b, result;
int sum1 = 0;
int sum2 = 0;
int length;
int avail = 0;

typedef struct {
    int coef;
    int expon;
}polynomial;
polynomial terms[MAX_TERMS];

int read_data(char infile[]);
void attach(int coefficient, int exponent);
int calculate(int size, int x, int sum);

int main(int argc, char** argv)
{
    length = read_data(argv[1]);
    a = calculate(length, n, sum1);
    b = calculate(length, m, sum2);
    result = a + b;
    printf("%d", result);

    return 0;
}

void attach(int coefficient, int exponent)
{
    if (avail >= MAX_TERMS)
    {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }

    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}


int read_data(char infile[])
{
    FILE* fp;

    if (!(fp = fopen(infile, "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &n, &m);

    int i = 0;

    while (!feof(fp))
    {
        fscanf(fp, "%d %d ", &terms[i].coef, &terms[i].expon);
        attach(terms[i].coef, terms[i].expon);
        i++;
    }

    fclose(fp);
    return i;
}

int calculate(int size, int x, int sum)
{
    for (int i = 0; i < size; i++)
        sum += terms[i].coef * pow(x,terms[i].expon);

    return sum;
}
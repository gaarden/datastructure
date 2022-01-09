#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)

typedef struct {
    int coef;
    int expon;
}polynomial;

polynomial terms[MAX_TERMS];

int n, m;
int avail = 0;
int startA, startB, finishA, finishB;
int* startD, * finishD;

int read_data(char infile[]);
void attach(int coefficient, int exponent);
void padd(int sA, int fA, int sB, int fB, int* sD, int* fD);

int main(int argc, char** argv)
{
    read_data(argv[1]);
    finishA = n-1;
    finishB = n + m-1;
    startA = 0;
    startB = finishA + 1;

    printf("p(x) = ");
    for (int i = 0; i <= finishA; i++)
    {
        if (terms[i].expon == 0)
        {
            printf("%d", terms[i].coef, terms[i].expon);
            if (i != finishA)
                if (terms[i+1].coef >= 0)
                    printf("+");
        }
        else
        {
            printf("%dx^%d", terms[i].coef, terms[i].expon);
            if (i != finishA)
                if (terms[i+1].coef >= 0)
                    printf("+");
        }
    }

    printf("\nq(x) = ");
    for (int i = startB; i <= finishB; i++)
    {
        if (terms[i].expon == 0)
        {
            printf("%d", terms[i].coef, terms[i].expon);
            if (i != finishB)
                if (terms[i+1].coef >= 0)
                    printf("+");
        }
        else
        {
            printf("%dx^%d", terms[i].coef, terms[i].expon);
            if (i != finishB)
                if (terms[i+1].coef >= 0)
                    printf("+");
        }
    }

    padd(startA, finishA, startB, finishB, &startD, &finishD);

    printf("\np(x) + q(x) = ");
    for (int i = startD; i <= finishD; i++)
    {
        if (terms[i].expon == 0)
        {
            printf("%d", terms[i].coef, terms[i].expon);
            if (i != finishD)
                if (terms[i+1].coef >= 0)
                    printf("+");
        }
        else
        {
            printf("%dx^%d", terms[i].coef, terms[i].expon);
            if (i != finishD)
                if (terms[i+1].coef >= 0)
                    printf("+");
        }
    }

    return 0;
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
    
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d %d ", &(terms[i].coef), &(terms[i].expon));
        attach(terms[i].coef, terms[i].expon);
    }

    for (int i = 0; i < m; i++)
    {
        fscanf(fp, "%d %d ", &(terms[n + i].coef), &(terms[n + i].expon));
        attach(terms[n + i].coef, terms[n + i].expon);
    }
    fclose(fp);
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

void padd(int sA, int fA, int sB, int fB, int* sD, int* fD)
{
    int coefficient;
    *sD = avail;
    while (sA<=fA&&sB<=fB)
        switch (COMPARE(terms[sA].expon, terms[sB].expon))
        {
        case -1:
            attach(terms[sB].coef, terms[sB].expon);
            sB++;
            break;

        case 0:
            coefficient = terms[sA].coef + terms[sB].coef;
            if (coefficient)
                attach(coefficient, terms[sA].expon);
            sA++;
            sB++;
            break;

        case 1:
            attach(terms[sA].coef, terms[sA].expon);
            sA++;
        }

    for (;sA <= fA;sA++)
        attach(terms[sA].coef, terms[sA].expon);
    for (;sB <= fB;sB++)
        attach(terms[sB].coef, terms[sB].expon);
    *fD = avail - 1;
}
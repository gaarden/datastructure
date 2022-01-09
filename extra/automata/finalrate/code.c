#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000
#define MALLOC(p,s) \
if(!(p=malloc(s))){\
   fprintf(stderr,"insufficient memory");\
   exit(EXIT_FAILURE);}
void readdata(char infile[])
{
    long long stnum;
    int score;
    int com, count = 0, i = 0, same = 0, fa = 0;
    FILE* f;
    if (!(f = fopen(infile, "r")))
    {
        fprintf(stderr, "file���� ����");
        exit(EXIT_FAILURE);
    }
    fscanf(f, "%d ", &com);
    while (!feof(f))
    {
        fscanf(f, "%d %d ", &stnum, &score);
        if (score > com)
            count++;
        else if (score == com)
        {
            count++;
            same++;
        }
        if (score >= 10)
            i++;
        else
            fa++;
    }
    float rate = (float)count / i * 100;
    count--;
    same--;
    printf("%d�� f���� ��%d�� f�� %d�� ������:%d ���� %f%%", count, i, fa, same, rate);
    fclose(f);
}
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "file�� ����");
        exit(EXIT_FAILURE);
    }
    readdata(argv[1]);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 90
#define MINRATE 0.35
#define FINRATE 0.4
typedef struct {
    float score;
    long long stnum;
}element;
element data[MAX];
float myscore = 0.0;
int readdata(char infile[])
{
    long long temp1;
    float temp2, temp3;
    int i = 0;
    FILE* f;
    if (!(f = fopen(infile, "r")))
    {
        fprintf(stderr, "file���� ����");
        exit(EXIT_FAILURE);
    }
    fscanf(f, "%f %f ", &temp3, &temp2);//
    myscore = MINRATE * temp3 + FINRATE * temp2;
    while (!feof(f))
    {
        fscanf(f, "%lld ", &data[i].stnum);
        if (data[i].stnum == 0)
            break;
        fscanf(f, "%f ", &data[i].score);
        data[i].score *= MINRATE;
        i++;
    }
    i = 0;
    while (!feof(f))
    {
        fscanf(f, "%lld %f", &temp1, &temp2);
        if (temp1 != data[i].stnum)
        {
            fprintf(stderr, "�й��� �ȸ»�~");
            exit(EXIT_FAILURE);
        }
        else
        {
            data[i].score += FINRATE * temp2;
        }
        i++;
    }
    fclose(f);
    return i;
}
void compare(int n)
{
    int count = 0, same = 0, fa = 0;
    for (int i = 0;i < n;i++)
    {
        if (myscore < data[i].score)
            count++;
        else if ((int)myscore == (int)data[i].score)
        {
            same++;
            count++;
        }
        if (data[i].score <= MINRATE * 10 + FINRATE * 10)
        {
            fa++;
        }
    }
    int total = n - fa;
    float rate = count / (float)total * 100;
    printf("##�뷫���� ����##\n��ü %d��(f����) �� %d���Դϴ�~ f�� %d���̱� �׷��� ����%f%%�Դϴ�.\n", total, count, fa, rate);
    printf("������ ������(�߰�,�⸻���) ���� ����� ������ %d���Դϴ�.", --same);
}
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "file�� ����");
        exit(EXIT_FAILURE);
    }
    int count;
    count = readdata(argv[1]);
    compare(count);
    return 0;
}
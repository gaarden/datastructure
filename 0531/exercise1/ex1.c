// 0531 1��

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define MAX_SLOT 101

typedef struct
{
	char english[MAX_SIZE];
	char korean[MAX_SIZE];
} element;

void read_data(char infile[]);
unsigned int stringToInt(char k[]);
void insert(char e[], char k[], int n);
void insertQ(char e[], char k[], int n);
int findNext(int n, int count);

element ht[MAX_SIZE][MAX_SLOT]; // l ���
element htQ[MAX_SIZE][MAX_SLOT]; // q ���
int b = 23;
int s = 2;
int cL = 0; // collision Ƚ��
int pL = 0; // probing Ƚ��
int cQ = 0;
int pQ = 0;
int cntQ = 0; // q ������� ó���� Ƚ��
int data = 0;
int current = 0;
int home = 0;
int num = 0;
char eng[MAX_SIZE];
char kor[MAX_SIZE];
int slotcheckL[MAX_SIZE]; // slot�� ��ŭ ���ֳ� Ȯ���ϱ� ���� �迭
int slotcheckQ[MAX_SIZE];

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printf("%d %d\n", cL, pL);
	printf("%d %d ", cQ, pQ);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &data);

	while (!feof(fp))
	{
		fscanf(fp, "%s ", &eng);
		fscanf(fp, "%s ", &kor);
		num = stringToInt(eng);
		home = num;
		insert(eng, kor, num);
		insertQ(eng, kor, num);
	}

	fclose(fp);
}

unsigned int stringToInt(char k[])
{
	int number = 0;
	int i = 0;

	while (k[i])
		number += k[i++];

	number = number % b;

	return number;
}

void insert(char e[], char k[], int n)
{
	element a; // �����Ϸ��� �ϴ� element �����
	strcpy(a.english, e);
	strcpy(a.korean, k);

	current = n; // ������

	if (slotcheckL[n] >= s) // ���밡���� s���� ũ�Ƿ� overflow -> linear probing
	{
		cL++;
		int next = (n + 1) % b;

		if (next == home)
		{
			pL++;
			printf("Overflow L\n");
		}

		else
		{
			pL++;
			insert(e, k, next);
		}
	}

	int colcheck = 0;

	for (int i = 0; slotcheckL[n] < s; i++)
	{
		if (ht[n][i].english[0] != '\0') // collision
			colcheck = 1;

		else // ����
		{
			ht[n][i] = a;
			slotcheckL[n]++;
			break;
		}
	}

	if (colcheck == 1)
		cL++;
}

void insertQ(char e[], char k[], int n)
{
	element q;
	strcpy(q.english, e);
	strcpy(q.korean, k);

	int next = n; // ������

	while (slotcheckQ[next] >= s && cntQ <= 11) // �ι�°�� 1<i<=(b-1)/2 ����
	{
		cQ++;
		pQ++;
		cntQ++;

		next = findNext(home, cntQ);
	}

	if (slotcheckQ[next] >= s)
	{
		printf("Overflow");
		exit(EXIT_FAILURE);
	}

	int colcheck = 0;

	for (int i = 0; slotcheckQ[next] < s; i++)
	{
		if (htQ[next][i].english[0] != '\0') // collision
			colcheck = 1;

		else // ����
		{
			htQ[next][i] = q;
			slotcheckQ[next]++;
			cntQ = 0;
			break;
		}
	}

	if (colcheck == 1)
		cQ++;
}

int findNext(int n, int count)
{
	int nextV = 0;

	for (int i = 1; i <= count; i = i + 2)
		nextV += i;
	
	if (!(count % 2))
	{
		nextV = nextV * (-1);
		nextV = (n + nextV) % b;

		if (nextV >= 0)
			;
		else
			nextV += b;
	}

	else
		nextV = (n + nextV) % b;

	return nextV;
}
// 0526 2��

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
int search(char k[], int n);
int searchD(char k[], int n);
int samecheck(char k[], char save[]);
void Dodelete(char k[], int n);
void insert(char e[], char k[], int n);
void delete(char k[], int n);

element ht[MAX_SIZE][MAX_SLOT];
int b = 0;
int s = 0;
int c = 0; // collision Ƚ��
int p = 0;
int num = 0;
int home = 0; // table full Ȯ�� ���� ��
int current = 0;
char how;
char eng[MAX_SIZE];
char kor[MAX_SIZE];
char what[MAX_SIZE]; // search�� delete �� �� �Է¹޴� ��
int slotcheck[MAX_SIZE]; // slot�� ��ŭ ���ֳ� Ȯ���ϱ� ���� �迭

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &b);
	fscanf(fp, "%d ", &s);

	while (!feof(fp))
	{
		fscanf(fp, "%c ", &how);

		switch (how)
		{
		case 's':
			fscanf(fp, "%s ", &what);
			num = stringToInt(what);
			search(what, num);
			printf("%d ", p);
			break;

		case 'i':
			fscanf(fp, "%s ", &eng);
			fscanf(fp, "%s ", &kor);
			num = stringToInt(eng);
			home = num;
			insert(eng, kor, num);
			printf("%d ", p);
			break;

		case 'd':
			fscanf(fp, "%s ", &what);
			num = stringToInt(what);
			home = num;
			delete(what, num);
			printf("%d ", p);
			break;
		}
	}


	fclose(fp);
}

unsigned int stringToInt(char k[])
{
	int number = 0;

	number = k[0];
	number = number % b;

	return number;
}

int search(char k[], int n)
{
	int i = 0;

	while (i < slotcheck[n])
	{
		if (samecheck(k, ht[n][i].english))
		{
			printf("%s ", ht[n][i].korean);
			return 1;
		}

		else
		{
			i++;
		}
	}

	int next = (n + 1) % b;

	if (next == home)
		;

	else
		search(k, next);

	return 0;
}

int searchD(char k[], int n)
{
	int i = 0;

	while (i < slotcheck[n])
	{
		int next = (n + 1) % b;

		if (next == home)
			;

		if (samecheck(k, ht[n][i].english))
		{
			return 1;
		}

		else
		{
			i++;
			searchD(k, next);
		}
	}

	return 0;
}

int samecheck(char k[], char save[])
{
	int j = 0;
	int check = 1;

	while (save[j] != '\0')
	{
		if (save[j] == k[j])
			j++;

		else
			return 0;
	}

	return 1;
}

void Dodelete(char k[], int n)
{
	element d;
	strcpy(d.english, "");
	strcpy(d.korean, "");

	int i = 0;

	while (1)
	{
		if (samecheck(k, ht[n][i].english))
		{
			ht[n][i] = d; // �� NULL�� �� �ִ� �� ��ü�� delete ���شٴ� �ǹ�
			slotcheck[n]--;
			break;
		}

		else
			i++;
	}

	return;
}

void insert(char e[], char k[], int n)
{
	element a; // �����Ϸ��� �ϴ� element �����
	strcpy(a.english, e);
	strcpy(a.korean, k);

	current = n;

	if (slotcheck[n] >= s) // ���밡���� s���� ũ�Ƿ� overflow -> linear probing
	{
		c += 1;
		int next = (n + 1) % b;

		if (next == home)
		{
			p++;
			printf("Overflow %d %d ", c, p);
			exit(EXIT_FAILURE);
		}

		else
		{
			p++;
			insert(e, k, next);
		}
	}

	int colcheck = 0;

	for (int i = 0; slotcheck[n] < s; i++)
	{
		if (ht[n][i].english[0] != '\0') // collision
			colcheck = 1;

		else // ����
		{
			ht[n][i] = a;
			slotcheck[n]++;
			break;
		}
	}

	if (colcheck == 1)
		c++;
}

void delete(char k[], int n)
{
	int flag = 0;

	flag = searchD(k, n);

	if (flag) // ������ ���� �ִ�.
		Dodelete(k, n);

	else // ������ ���� ����.
		;
}
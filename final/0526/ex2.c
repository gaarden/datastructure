#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void delete(char k[], int n);
void insert(char e[], char k[], int n);

element ht[MAX_SIZE][MAX_SLOT];
int b = 0;
int s = 0;
int c = 0; // collision 횟수
int p = 0; // probing 횟수
char how;
char eng[MAX_SIZE];
char kor[MAX_SIZE];
char what[MAX_SIZE]; // search나 delete 할 때 입력받는 것
int slotcheck[MAX_SIZE]; // slot이 얼만큼 차있나 확인하기 위한 배열

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

	int home = 0;

	fscanf(fp, "%d ", &b);
	fscanf(fp, "%d ", &s);

	while (!feof(fp))
	{
		fscanf(fp, "%c ", &how);

		switch (how)
		{
		case 's':
			fscanf(fp, "%s ", &what);
			home = stringToInt(what);
			search(what, home);
			break;

		case 'i':
			fscanf(fp, "%s ", &eng);
			fscanf(fp, "%s ", &kor);
			home = stringToInt(what);
			insert(eng, kor, home);
			break;

		case 'd':
			fscanf(fp, "%s ", &what);
			home = stringToInt(what);
			delete(what, home);
			break;
		}

		printf("%d ", p);
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
	int homeBucket, nextBucket, i = 0;
	homeBucket = stringToInt(k);

	while (i < slotcheck[n])
	{
		if (!strcmp(k, ht[n][i].english))
		{
			printf("%s ", ht[n][i].korean);
			return 1;
		}

		else
			i++;
	}

	nextBucket = (n + 1) % b;

	if (nextBucket == homeBucket)
		;

	else
		search(k, nextBucket);

	return 0;
}

void delete(char k[], int n)
{
	element d;
	strcpy(d.english, "");
	strcpy(d.korean, "");

	int homeBucket, i = 0;
	homeBucket = n;
	int flag = 0;

	while (i < slotcheck[n] && flag == 0)
	{
		if (!strcmp(k, ht[n][i].english))
		{
			ht[n][i] = d;
			slotcheck[n]--;
			flag = 1;
			break;
		}

		else
			i++;

		if (i == slotcheck[n])
		{
			n = (n + 1) % b;

			if (n == homeBucket)
			{
				printf("Overflow ");
				break;
			}
		}
	}
}

void insert(char e[], char k[], int n)
{
	element a; // 삽입하려고 하는 element 만들기
	strcpy(a.english, e);
	strcpy(a.korean, k);

	int homeBucket, nextBucket;
	homeBucket = stringToInt(e);

	if (slotcheck[n] >= s) // 수용가능한 s��다 크므로 overflow
	{
		c++;
		p++;

		nextBucket = (n + 1) % b;

		if (nextBucket == homeBucket)
		{
			printf("Overflow %d %d ", c, p);
			exit(EXIT_FAILURE);
		}

		insert(e, k, nextBucket);
	}

	int colcheck = 0;

	for (int i = 0; slotcheck[n] < s; i++)
	{
		if (strcmp(ht[n][i].english, "")) // collision
			colcheck = 1;

		else // 삽입
		{
			ht[n][i] = a;
			slotcheck[n]++;
			break;
		}
	}

	if (colcheck == 1)
		c++;
}
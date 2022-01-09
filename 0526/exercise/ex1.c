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
int search(char k[]);
int searchD(char k[]);
int samecheck(char k[], char save[]);
void Dodelete(char k[]);
void insert(char e[], char k[]);
void delete(char k[]);

element ht[MAX_SIZE][MAX_SLOT];
int b = 0;
int s = 0;
int c = 0; // collision 횟수
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

	printf("%d ", c);

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
			search(what);
			break;
			
		case 'i':
			fscanf(fp, "%s ", &eng);
			fscanf(fp, "%s ", &kor);
			insert(eng, kor);
			break;
			
		case 'd':
			fscanf(fp, "%s ", &what);
			delete(what);
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

int search(char k[])
{
	int homeBucket, i = 0;
	homeBucket = stringToInt(k);

	while (i < slotcheck[homeBucket])
	{
		if (samecheck(k, ht[homeBucket][i].english))
		{
			printf("%s ", ht[homeBucket][i].korean);
			return 1;
		}

		else
			i++;
	}

	printf("NF ");

	return 0;
}

int searchD(char k[])
{
	int homeBucket, i = 0;
	homeBucket = stringToInt(k);

	while (i < slotcheck[homeBucket])
	{
		if (samecheck(k, ht[homeBucket][i].english))
		{
			//printf("%s ", ht[homeBucket][i].korean);
			return 1;
		}

		else
			i++;
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

void Dodelete(char k[])
{
	element d;
	strcpy(d.english, "");
	strcpy(d.korean, "");
	
	int homeBucket, i = 0;
	homeBucket = stringToInt(k);

	while (1)
	{
		if (samecheck(k, ht[homeBucket][i].english))
		{
			ht[homeBucket][i] = d; // 다 NULL인 것 넣는 것 자체가 delete 해준다는 의미
			slotcheck[homeBucket]--;
			break;
		}

		else
			i++;
	}

	return;
}

void insert(char e[], char k[])
{
	element a; // 삽입하려고 하는 element 만들기
	strcpy(a.english, e);
	strcpy(a.korean, k);

	int homeBucket;
	homeBucket = stringToInt(e);

	if (slotcheck[homeBucket] >= s) // 수용가능한 s보다 크므로 overflow
	{
		c += 1;
		printf("Overflow %d ", c);
		exit(EXIT_FAILURE);
	}

	int colcheck = 0;

	for (int i = 0; slotcheck[homeBucket] < s; i++)
	{
		if (ht[homeBucket][i].english[0] != '\0') // collision
			colcheck = 1;

		else // 삽입
		{
			ht[homeBucket][i] = a;
			slotcheck[homeBucket]++;
			break;
		}
	}

	if (colcheck == 1)
		c++;
}

void delete(char k[])
{
	int flag = 0;

	flag = searchD(k);

	if (flag) // 삭제할 것이 있다.
		Dodelete(k);

	else // 삭제할 것이 없다.
		printf("NF ");
}
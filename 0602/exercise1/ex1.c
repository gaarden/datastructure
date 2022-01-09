// 0602 1번

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1001

typedef struct
{
	char stu[10];
	char name[10];
	char ch;
} element;

element lst[MAX_SIZE] = { 0 };
int value = 0;
int cnt = 0; // 자료 수
int check = 0; // 넣은 자료 수
char num[10]; // 학생 번호
char c[10]; // 학생 이름, 한글은 두칸 차지, 마지막 null 필요
char yn; // 접종 여부

void read_data(char infile[]);
void insert(element e, element a[], int i);
void insertionSort(element a[], int n);
void printList(element a[]);

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	
	insertionSort(lst, cnt);
	
	printList(lst);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &cnt);

	while (!feof(fp))
	{
		check++;

		//new 초기화
		element new;
		
		fscanf(fp, "%s ", num); // %s 쓸때는 & 붙이면 안됨
		fscanf(fp, "%s ", c);
		fscanf(fp, "%c ", &yn);

		strcpy(new.stu, num); // 마지막에 print할 때 001 이런식으로 출력되어야 해서 문자열로 저장
		strcpy(new.name, c);
		new.ch = yn;

		lst[check] = new;
	}
	
	fclose(fp);
}

void insert(element e, element a[], int i)
{
	a[0] = e;

	while (atoi(e.stu) < atoi(a[i].stu))
	{
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;

}

void insertionSort(element a[], int n)
{
	int j;

	for (j = 2; j <= n; j++)
	{
		element temp = a[j];
		insert(temp, a, j - 1);
	}
}

void printList(element a[])
{
	for (int i = 1; i <= cnt; i++)
	{
		if (a[i].ch == 'N')
			printf("%s %s %c ", a[i].stu, a[i].name, a[i].ch);
	}

	for (int i = 1; i <= cnt; i++)
	{
		if (a[i].ch == 'Y')
			printf("%s %s %c ", a[i].stu, a[i].name, a[i].ch);
	}
}
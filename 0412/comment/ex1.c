/*
• Task: 임의의 n 개의 정수를 입력 받아 binary tree 로 관리하는 프로
그램을 작성하라
• Input:
– 정수 리스트
• Output:
– binary tree 의 내용을 complete tree 의 노드 번호 순서대로 출력
– 단, 노드에 값이 없을 경우 출력하지 않음
• Specification
– Binary tree 의 표현은 배열을 이용할 것
• Array doubling 사용
– 입력파일로 부터 정수 리스트를 하나씩 차례로 읽어서 binary tree 에 저
장
– 부모 노드 보다 left child 노드의 값이 작거나 같도록 유지할 것
– 입력이 모두 끝나면, 배열의 내용을 순서대로 출력
– 할당된 배열공간 모두 해제
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if(!((p)=malloc(s)))\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}
#define REALLOC(p, s)\
if(!((p)=realloc(p, s)))\
{\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}
int capacity;
int value;
int* lst;

void read_data(char infile[]);
void insertNode(int n);
void arrayDoubling();
void printTree();

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printTree();

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(lst, sizeof(*lst));
	capacity = 1;
	arrayDoubling();
	lst[0] = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &value);
		insertNode(value);
	}

	fclose(fp);
}

void insertNode(int n)
{
	int index = 1;

	while (1)
	{
		if (lst[index] >= n) // 왼쪽 이동
		{
			index = 2 * index;

			if (index > capacity)
			{
				arrayDoubling();
				lst[index] = n;
				break;
			}

			else if (index <= capacity && lst[index] == 0)
			{
				lst[index] = n;
				break;
			}

			else
				;
		}

		else // 오른쪽 이동
		{
			index = 2 * index + 1;

			if (index > capacity)
			{
				arrayDoubling();
				lst[index] = n;
				break;
			}

			else if (index <= capacity && lst[index] == 0)
			{
				lst[index] = n;
				break;
			}

			else
				;
		}
	}

}

void arrayDoubling()
{
	REALLOC(lst, 2 * capacity * sizeof(*lst));

	for (int i = capacity; i < 2 * capacity; i++)
		lst[i] = 0;

	capacity *= 2;
}

void printTree()
{
	for (int i = 0; i < capacity; i++)
	{
		if (lst[i] != 0)
			printf("%d ", lst[i]);
	}

	free(lst);
}
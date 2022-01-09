#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define REALLOC(p, s)\
if(!((p)=realloc(p, s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}
#define MIN_SIZE 2

int read_data(char infile[]);
void search(int change, int n);
void arrayDoubling();
void printTree(int n);

int *lst;
int size = 1; // 현재 lst가 몇번째 index까지 존재하는지 (many-1)
int many = 2; // lst에 넣을 수 있는 배열 몇개인지 (size+1)

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	int large = read_data(argv[1]);
	printTree(large);

	return EXIT_SUCCESS;
}

int read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(lst, MIN_SIZE * sizeof(int));
	
	int root = 1; // lst[root]는 이 리스트의 root값 --> 건들면안됨
	int temp = 1; // search할 때 보조적인 역할
	int num = 0; // 입력받는 숫자
	lst[0] = 0;
	
	fscanf(fp, "%d ", &num);
	lst[root] = num;

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &num);
		search(temp, num);
		temp = root;
	}

	fclose(fp);

	return size;
}

void search(int change, int n)
{
	if (lst[change] >= n)
	{
		change = change * 2;
		if (change > size)
		{
			arrayDoubling();

			if (lst[change] != 0)
				search(change, n);
			else
				lst[change] = n;
		}
		else
		{
			if (lst[change] != 0)
				search(change, n);
			else
				lst[change] = n;
		}
	}

	else
	{
		change = 2 * change + 1;
		if (change > size)
		{
			arrayDoubling();

			if (lst[change] != 0)
				search(change, n);
			else
				lst[change] = n;
		}

		else
		{
			if (lst[change] != 0)
				search(change, n);
			else
				lst[change] = n;
		}
	}
}

void arrayDoubling()
{
	REALLOC(lst, many * sizeof(int) * 2);
	for (int i = many; i<2*many; i++)
		lst[i] = 0;

	many = 2 * many;
	size = many - 1;
}

void printTree(int n)
{
	for (int i = 0; i <= n; i++)
		if (lst[i] != 0)
			printf("%d ", lst[i]);

	free(lst);
}
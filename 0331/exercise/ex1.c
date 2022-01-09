#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct listNode* listPointer;
typedef struct listNode
{
	int data;
	listPointer link;
};

listPointer front = NULL;
listPointer rear = NULL;

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
	fprintf(stderr, "insufficient memory");\
	exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
void insert(int value);
void delete();
void printList(listPointer first);


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printList(front);

	return 0;
}

void read_data(char infile[])
{
	char how;
	int what;

	FILE* fp;
	if (!(fp = fopen(infile, "r")))
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%c %d ", &how, &what);

		if (how == 'i')
			insert(what);

		else
			for (int i = 0; i < what; i++)
				delete();
	}

	fclose(fp);
}

void insert(int value)
{
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = value;
	temp->link = NULL;

	if (front)
		rear->link = temp;

	else
		front = temp;

	rear = temp;
}

void delete()
{
	listPointer temp = front;
	int data;

	if (temp)
	{
		data = temp->data;
		front = temp->link;
	}
	
	free(temp);
}

void printList(listPointer first)
{
	for (;first;first = first->link)
		printf("%d ", first->data);
}
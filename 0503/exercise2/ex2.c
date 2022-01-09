// 0503 2¹ø

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 101
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTICES];

typedef struct node* nodePointer;
typedef struct node
{
	int vertex;
	nodePointer link;
};
nodePointer* graph;

typedef struct queue* queuePointer;
typedef struct queue
{
	int vertex;
	queuePointer link;
};
queuePointer front, rear;

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
void insert(int a, int b);
void bfs(int v);
void addq(int a);
int deleteq();

int size;
int v1, v2;
int start;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	bfs(start);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d ", &size);

	MALLOC(graph, (size + 1) * sizeof(*graph));

	for (int i = 0; i <= size; i++)
		graph[i] = NULL;

	while (1)
	{
		fscanf(fp, "%d %d ", &v1, &v2);

		if (v1 == -1)
			break;

		insert(v1, v2);
		insert(v2, v1);
	}

	start = v2;

	fclose(fp);
}

void insert(int a, int b)
{
	nodePointer temp;
	nodePointer copy;
	nodePointer pre;
	MALLOC(temp, sizeof(temp));
	temp->link = NULL;
	temp->vertex = b;

	copy = graph[a];
	pre = NULL;

	if (copy == NULL)
		;

	else
	{
		for (; copy;)
		{
			if (copy->vertex > b)
				break;

			else if (copy->vertex < b)
			{
				pre = copy;
				copy = copy->link;
			}
		}
	}

	if (graph[a] == NULL)
	{
		MALLOC(graph[a], sizeof(graph[a]));
		graph[a]->link = temp;
		graph[a] = graph[a]->link;
	}

	else
	{
		if (pre == NULL)
		{
			temp->link = graph[a];
			graph[a] = temp;
		}

		else
		{
			temp->link = pre->link;
			pre->link = temp;
		}
	}
}

void bfs(int v)
{
	nodePointer w;
	front = rear = NULL;
	printf("%d ", v);
	visited[v] = TRUE;
	addq(v);
	while (front)
	{
		v = deleteq();
		for (w = graph[v]; w; w = w->link)
			if (!visited[w->vertex])
			{
				printf("%d ", w->vertex);
				addq(w->vertex);
				visited[w->vertex] = TRUE;
			}
	}
}

void addq(int a)
{
	queuePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->vertex = a;
	temp->link = NULL;

	if (front)
		rear->link = temp;

	else
		front = temp;

	rear = temp;
}

int deleteq()
{
	queuePointer temp = front;
	int value;

	if (!temp)
		;

	else
	{
		value = temp->vertex;
		front = temp->link;
		free(temp);
	}

	return value;
}
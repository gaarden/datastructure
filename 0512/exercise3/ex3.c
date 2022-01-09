#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 101
#define TRUE 1
#define FALSE 0
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
int deleteq();
void addq(int a);
void colorCheck();
void printColor(int v);

char colorList[MAX_VERTICES] = { '\0' };
int keepG[MAX_VERTICES] = { 0 };

int size;
int v1, v2;
int start = 1;
int check;
int cnt;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);

	colorList[start] = 'r';
	bfs(start);
	colorCheck();

	if (check == 0)
		printColor(start);
	else
		printf("no");

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

	while (!feof(fp))
	{
		fscanf(fp, "%d %d ", &v1, &v2);

		insert(v1, v2);
		insert(v2, v1);
	}

	fclose(fp);
}

void insert(int a, int b)
{
	nodePointer temp;
	nodePointer copy;
	nodePointer pre;
	MALLOC(temp, sizeof(*temp));
	temp->link = NULL;
	temp->vertex = b;

	pre = NULL;

	if (graph[a] == NULL)
		;

	else
	{
		copy = graph[a];

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
		temp->link = NULL;
		graph[a] = temp;
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
	char color = '/0';
	front = rear = NULL;
	visited[v] = TRUE;
	addq(v);

	while (front)
	{
		v = deleteq();

		if (colorList[v] == 'r')
			color = 'g';

		else if (colorList[v] == 'g')
			color = 'r';

		for (w = graph[v]; w; w = w->link)
		{
			if (!visited[w->vertex])
			{
				colorList[w->vertex] = color;
				addq(w->vertex);
				visited[w->vertex] = TRUE;
			}
		}
	}
}

void colorCheck()
{
	check = 0;

	for (int i = 1; i <= size && check == 0; i++)
	{
		nodePointer w;
		char pre = '\0';
		char temp = '\0';

		for (w = graph[i]; w; w = w->link)
		{
			pre = temp;
			temp = colorList[w->vertex];

			if (pre != '\0')
			{
				if (pre == temp)
					check = 0;

				else
				{
					check = 1;
					return;
				}
			}
		}
	}
}

int deleteq()
{
	queuePointer temp = front;
	int value = 0;

	if (!temp)
		exit(EXIT_FAILURE);

	else
	{
		value = temp->vertex;
		front = temp->link;
		free(temp);
	}

	return value;
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

void printColor(int v)
{
	for (int i = 0; i <= size; i++)
	{
		visited[i] = FALSE;
	}

	nodePointer w;
	front = rear = NULL;

	if (colorList[v] == 'r')
		printf("%d ", v);
	else
		keepG[cnt++] = v;

	visited[v] = TRUE;
	addq(v);

	while (front)
	{
		v = deleteq();
		for (w = graph[v]; w; w = w->link)
			if (!visited[w->vertex])
			{
				if (colorList[w->vertex] == 'r')
					printf("%d ", w->vertex);

				else if (colorList[w->vertex] == 'g')
					keepG[cnt++] = w->vertex;

				addq(w->vertex);
				visited[w->vertex] = TRUE;
			}
	}

	printf("\n");

	for (int i = 0; i < cnt; i++)
		printf("%d ", keepG[i]);
}
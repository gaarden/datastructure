// 0505 1¹ø

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
	int weight;
	nodePointer link;
};

typedef struct
{
	int from;
	int to;
	int weight;
}element;

element* heap;
nodePointer* graph;

#define MALLOC(p, s)\
if(!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

#define REALLOC(p, s)\
if(!((p)=realloc(p, s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

void read_data(char infile[]);
void insert(int a, int b, int c);
void push(element item, int* n);
element pop(int* n);
void arrayDoubling();

int size;
int v1, v2, amount;
int n = 0;
int capacity = MAX_VERTICES;
int count;

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(heap, capacity * sizeof(*heap));
	for (int i = 0; i < capacity; i++)
	{
		element value;
		value.from = 0;
		value.to = 0;
		value.weight = 0;
		heap[i] = value;
	}

	read_data(argv[1]);

	while (1)
	{
		element del;
		del = pop(&count);

		int temp;
		
		if (del.from >= del.to)
		{
			temp = del.from;
			del.from = del.to;
			del.to = temp;
		}

		printf("(%d, %d, %d)\n", del.from, del.to, del.weight);
	}

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
		fscanf(fp, "%d %d %d ", &v1, &v2, &amount);

		insert(v1, v2, amount);
		insert(v2, v1, amount);

		element new;
		new.from = v1;
		new.to = v2;
		new.weight = amount;

		push(new, &count);
	}

	fclose(fp);
}

void insert(int a, int b, int c)
{
	nodePointer temp;
	nodePointer copy;
	nodePointer pre;
	MALLOC(temp, sizeof(temp));
	temp->link = NULL;
	temp->vertex = b;
	temp->weight = c;

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

void push(element item, int* n)
{
	int i = 0;

	if (count == capacity - 1)
		arrayDoubling();

	i = ++(*n);

	while ((i != 1) && (item.weight < heap[i / 2].weight))
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}

	heap[i] = item;
}

element pop(int* n)
{
	int parent, child;
	element item, temp;

	if (!(*n))
	{
		// fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while (child <= *n)
	{
		if ((child < *n) && (heap[child].weight > heap[child + 1].weight))
			child++;

		if (temp.weight <= heap[child].weight)
			break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}

	heap[parent] = temp;
	return item;
}

void arrayDoubling()
{
	REALLOC(heap, capacity * 2 * sizeof(*heap));
	for (int i = capacity; i < 2 * capacity; i++)
	{
		element value;
		value.from = 0;
		value.to = 0;
		value.weight = 0;
		heap[i] = value;
	}
	capacity *= 2;
}
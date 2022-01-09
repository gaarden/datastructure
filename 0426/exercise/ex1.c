#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 101
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int key;
}element;

element* heap;

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
void push(element item, int* n);
void arrayDoubling();
element pop(int* n);
void printTree();

int data;
int capacity = MAX_ELEMENTS;
int count; // ÇöÀç tree size

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	MALLOC(heap, capacity * sizeof(*heap));
	for (int i = 0; i<capacity; i++)
	{
		element value;
		value.key = 0;
		heap[i] = value;
	}

	read_data(argv[1]);
	printTree(count);
	free(heap);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d ", &data);

		if (data == -1)
			break;

		else
		{
			element value;
			value.key = data;

			push(value, &count);
		}
	}

	fclose(fp);
}

void push(element item, int* n)
{
	int i = 0;

	if (count == capacity -1)
	{
		arrayDoubling();
	}

	i = ++(*n);

	while ((i != 1) && (item.key > heap[i / 2].key))
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}

	heap[i] = item;
}

void arrayDoubling()
{
	REALLOC(heap, capacity * 2 * sizeof(*heap));
	for (int i = capacity; i < 2 * capacity; i++)
	{
		element value;
		value.key = 0;
		heap[i] = value;
	}
	capacity *= 2;
}

element pop(int* n)
{
	int parent, child;
	element item, temp;

	if (HEAP_EMPTY(*n))
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
		if ((child<*n)&&(heap[child].key<heap[child+1].key))
			child++;

		if (temp.key >= heap[child].key)
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}

	heap[parent] = temp;
	return item;
}

void printTree()
{
	while (1)
	{
		printf("%d ", pop(&count));
	}
}
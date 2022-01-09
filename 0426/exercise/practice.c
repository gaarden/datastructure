// 0426 1��

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if (!((p)=malloc(s))){\
fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}
#define REALLOC(p, s)\
if (!((p)=realloc(p, s))){\
fprintf(stderr, "insufficient memory");\
exit(EXIT_FAILURE);\
}
#define MAX_SIZE 101
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
}element;

void read_data(char infile[]);
void push(element item, int* n);
element pop(int* n);
void arrayDoubling();
void printHeap();

int capacity = MAX_SIZE;
element* heap;
int cnt = 0; // heap�� ����ִ� ���� ��

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, " E usage : [program] [file name]\n");
		exit(EXIT_FAILURE);
	}

	read_data(argv[1]);
	printHeap(cnt);

	return EXIT_SUCCESS;
}

void read_data(char infile[])
{
	FILE* fp;

	if (!(fp = fopen(infile, "r"))) {
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	/*
	heap ���� �迭 �����,
	���ҵ��� heap�� ����ִ� ����
	*/

	MALLOC(heap, MAX_SIZE * sizeof(element));

	int k = 0;

	while (1)
	{
		fscanf(fp, "%d ", &k);

		if (k == -1)
			break;

		else
		{
			element new;
			new.key = k;

			push(new, &cnt);
		}
	}

	fclose(fp);
}

// heap push �Լ�
void push(element item, int* n)
{
	int i;

	if ((*n) == capacity - 1)
		arrayDoubling();

	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key))
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}

	heap[i] = item;
}

// heap pop �Լ�
element pop(int* n)
{
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n))
	{
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while (child <= *n)
	{
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
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

// array doubling �Լ�(realloc �ʿ�)
void arrayDoubling()
{
	REALLOC(heap, 2 * capacity * sizeof(element));
	capacity *= 2;
}

// heap�� pop�ϸ� ��ҵ��� ����ϴ� �Լ�
void printHeap()
{
	while (cnt)
	{
		printf("%d ", pop(&cnt).key);
	}
}
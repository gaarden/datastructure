// 0426 1번

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
int cnt = 0; // heap에 들어있는 원소 수

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
	heap 동적 배열 만들고,
	원소들을 heap에 집어넣는 과정
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

// heap push 함수
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

// heap pop 함수
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

// array doubling 함수(realloc 필요)
void arrayDoubling()
{
	REALLOC(heap, 2 * capacity * sizeof(element));
	capacity *= 2;
}

// heap을 pop하며 요소들을 출력하는 함수
void printHeap()
{
	while (cnt)
	{
		printf("%d ", pop(&cnt).key);
	}
}
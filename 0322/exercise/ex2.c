#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 1000

typedef struct {
	int key;
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void read_data(char infile[]);
void addq(element item);
element deleteq();
void printQueue();

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }
    read_data(argv[1]);

    printQueue();

	return 0;
}

void read_data(char infile[])
{
    element data;
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
        fscanf(fp, "%c %d", &how, &what);
        

        if (how == 'i')
        {
            data.key = what;
            addq(data);
        }

        if (how == 'r')
        {
            for (int i = 0; i < what; i++)
                deleteq();
        }
    }

    fclose(fp);
}

void addq(element item)
{
    rear = (rear + 1) % MAX_QUEUE_SIZE;

    if (front == rear)
        printf("Full");

    queue[rear] = item;
}

element deleteq()
{
    element item;

    if (front == rear)
        printf("Empty");

    front = ((front + 1) % MAX_QUEUE_SIZE);
    return queue[front];
}

void printQueue()
{
    for (front + 1; front < rear;)
    {
        printf("%d ", queue[front + 1].key);
        deleteq();
    }
}
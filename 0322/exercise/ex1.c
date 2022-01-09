#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s)\
if (!((p)=malloc(s)))\
{fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}
#define REALLOC(p, s)\
if (!((p)=realloc(p, s)))\
{fprintf(stderr, "Insufficient memory");\
exit(EXIT_FAILURE);\
}

typedef struct
{
    int key;
} element;

void read_data(char infile[]);
void stackFull();
void push(element item);
element pop();
void printStack();

element* stack;
int capacity = 1;
int top = -1;
int how;
int what;

int main(int argc, char** argv)
{
    MALLOC(stack, sizeof(*stack));

    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }

    read_data(argv[1]);

    printStack();

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
            push(data);
        }

        if (how == 'r')
        {
            for (int i = 0; i < what; i++)
                pop();
        }
    }

    fclose(fp);
}

void stackFull()
{
    REALLOC(stack, 2 * capacity * sizeof(*stack));
    capacity *= 2;
}

void push(element item)
{
    if (top >= capacity - 1)
        stackFull();
    stack[++top] = item;
}

element pop()
{
    if (top < 0)
        printf("Empty");
    return stack[top--];
}

void printStack()
{
    for (top; top > -1;)
    {
        printf("%d ", stack[top].key);
        pop();
    }
}
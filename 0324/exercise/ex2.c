#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_DATA 1000
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
    char key;
} element;

element* stack;
int capacity = 1;
int top = -1;
int cnt = 0;

void read_data(char infile[]);
void stackFull();
void push(element item);
element pop();
void printArray(char a[]);

char read[MAX_DATA] = {'\0'};


int main(int argc, char** argv)
{
    MALLOC(stack, sizeof(*stack));

    if (argc != 2)
    {
        fprintf(stderr, " E usage : [program] [file name]\n");
        exit(EXIT_FAILURE);
    }
    read_data(argv[1]);
    printArray(read);
    free(stack);
    return 0;
}

void read_data(char infile[])
{
    element data;
    char new;

    FILE* fp;
    if (!(fp = fopen(infile, "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }


    while (!feof(fp))
    {
        fscanf(fp, "%c ", &new);

        if (new == '/')
        {
            fscanf(fp, "%c ", &new);
            if (new == '*')
            {
                do
                {
                    fscanf(fp, "%c ", &new);

                    if (new == '*')
                        fscanf(fp, "%c ", &new);

                } while (new != '/');
            }
        }

        if ((new == '{') || (new == '(') || (new == '['))
        {
            read[cnt++] = new;
            data.key = new;
            push(data);
        }

        switch (new)
        {
        case '}':
            read[cnt++] = new;
            if (stack[top].key == '{')
            {
                pop();
                break;
            }
            else
            {
                printArray(read);
                break;
            }
        case ')':
            read[cnt++] = new;
            if (stack[top].key == '(')
            {
                pop();
                break;
            }
            else
            {
                printArray(read);
                break;
            }
        case ']':
            read[cnt++] = new;
            if (stack[top].key == '[')
            {
                pop();
                break;
            }
            else
            {
                printArray(read);
                break;
            }
        default:
            break;

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
    if (top == -1)
        printArray(read);
    return stack[top--];
}

void printArray(char a[])
{
    if (top == -1)
        printf("ok");

    else
    {
        for (int i = 0; i <= cnt; i++)
            printf("%c ", a[i]);
    }
    exit(0);

}
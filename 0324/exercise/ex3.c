#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s)\
if (!((p) = malloc(s)))\
{\
   fprintf(stderr, "Insufficient memory");\
   exit(EXIT_FAILURE);\
    }

#define REALLOC(p,s)\
if(!((p) = realloc(p,s)))\
{\
    fprintf(stderr, "insufficient memory");\
    exit(EXIT_FAILURE);\
    }

typedef struct
{
    char key;
} element;

element* stack;
int capacity = 1;
int top = -1;
int num = 0;
char list[10000];

void read_data(char infile[]);
void push(element item);
element pop();
void stackFull();
void stackEmpty();
void printStack();

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

    free(stack);

}

void read_data(char infile[])
{
    FILE* fp;
    char c;
    element n;

    // 1. open file
    if (!(fp = fopen(infile, "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    // 2. read input data
    while (!feof(fp))
    {
        fscanf(fp, "%c ", &c);

        if (c == '/')
        {
            fscanf(fp, "%c ", &c);
            if (c == '*')
            {
                do
                {
                    fscanf(fp, "%c ", &c);

                    if (c == '*')
                        fscanf(fp, "%c ", &c);

                } while (c != '/');
            }
        }

        if ((c == '{') || (c == '(') || (c == '['))
        {
            list[num++] = c;
            n.key = c;
            push(n);
        }

        switch (c)
        {
        case '}':
            if (stack[top].key == '{')
            {
                list[num++] = c;
                pop();
                break;
            }
            else
            {
                list[num++] = c;
                printStack();
                break;
            }
        case ')':
            if (stack[top].key == '(')
            {
                list[num++] = c;
                pop();
                break;
            }
            else
            {
                list[num++] = c;
                printStack();
                break;
            }
        case ']':
            if (stack[top].key == '[')
            {
                list[num++] = c;
                pop();
                break;
            }
            else
            {
                list[num++] = c;
                printStack();
                break;
            }
        default:
            break;
        }
    }
    fclose(fp);
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
        stackEmpty();
    return stack[top--];
}
void stackFull()
{
    REALLOC(stack, 2 * capacity * sizeof(*stack));
    capacity *= 2;
}
void stackEmpty()
{
    fprintf(stderr, "Stack is empty.");
    exit(EXIT_FAILURE);
}
void printStack()
{
    if (top == -1)
    {
        printf("ok");
    }
    else
    {
        for (int i = 0; i <= num; i++)
            printf("%c ", list[i]);
    }
    exit(0);
}
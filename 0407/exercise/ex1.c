/*
• Task: 주어진 다항식에 명령에 따라 항을 추가 또는 삭제하는 프로그램을 작성하라
• Input:
– (명령어, 계수, 지수)
• i 2 3 : 2x^3 을 추가
• d 2 3 : 2x^3 을 삭제
• Output:
– 명령어 수행이 모두 끝난 뒤의 다항식
• Specification
– Circular Linked list 를 사용할 것
– 시작은 empty 다항식
– 입력파일로부터 명령어를 하나씩 읽어며 다항식의 항을 추가 또는 삭제
• 지수에 대한 내림차순 유지할 것
– 중복된 항이 추가될 경우 계수값들의 덧셈 수행
– 항의 삭제 시, 삭제된 노드를 available 리스트에 관리
– 항 추가 시, available 리스트에서 노드가 있으면 가져다가 사용
– 명령어 수행이 모두 끝나면 다항식을 출력
• 결과 다항식 �!�! + �!"#�!"# …을 (�!, n) (�!"#, n-1) … 과 같이 공백으로 구분된 (계수, 지수) 쌍의 리스트로
한 줄에 출력
• 예) 2x^3+ 4x^7 는 (2, 3) (4, 7)과 같이 한 줄에 출력
– 작업이 모두 끝나면 반드시 할당 받은 메모리들을 모두 free 할 것 (available list 포함)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t) = (x) , (x) = (y), (y) = (t))
#define COMPARE(x, y) ((x) < (y) ? -1 : ((x) == (y)) ? 0 : 1)
#define FALSE 0
#define TRUE 1
#define MALLOC(p,s)\
if(!((p) = malloc(s))){\
   fprintf(stderr, "insufficient memory");\
   exit(EXIT_FAILURE);\
}

#define REALLOC(p,s)\
if(!((p) = realloc(p, s))){\
   fprintf(stderr, "insufficient memory");\
   exit(EXIT_FAILURE);\
}

typedef struct {
    int key;
    /* other fields*/
} element;
typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
};

polyPointer a, avail;

void read_data(char infile[]);
void addp(int coef, int expon);
void deletep(polyPointer* a, int coef, int expon);
polyPointer cpadd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer* ptr);
polyPointer getNode(void);
void retNode(polyPointer node);
void cerase(polyPointer* ptr);
void erase(polyPointer* ptr);
void printp(polyPointer ptr);

void main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "fail to file open");
        exit(EXIT_FAILURE);
    }
    read_data(argv[1]);

    printp(a);

    cerase(&a);

    erase(&avail);

    return 0;

}
void read_data(char infile[])
{
    FILE* fp;
    polyPointer lastA;
    char op;
    int coef, expon;

    a = getNode();
    a->expon = -1;

    lastA = a;
    lastA->link = a;

    if (!(fp = fopen(infile, "r")))
    {
        fprintf(stderr, "failed to open file\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(fp))
    {
        fscanf(fp, "%c %d %d", &op, &coef, &expon);
        if (op == 'i')
        {
            addp(coef, expon);
        }
        else if (op == 'd')
        {
            deletep(&a, coef, expon);
        }
    }

    fclose(fp);
}

void addp(int coef, int expon)
{
    polyPointer temp, lastTemp;
    temp = getNode();
    temp->expon = -1;
    lastTemp = temp;

    attach(coef, expon, &lastTemp);
    lastTemp->link = temp;

    a = cpadd(a, temp);
}

void deletep(polyPointer* a, int coef, int expon)
{
    polyPointer temp = *a, pre, curr;
    pre = temp;
    temp = temp->link;
    curr = temp;
    for (; temp->expon != -1;)
    {
        if (temp->coef == coef && temp->expon == expon)
        {
            curr = temp;
            pre->link = temp->link;
            temp = temp->link;
            retNode(curr);
        }
        else
        {
            pre = temp;
            temp = temp->link;
        }
    }
}


polyPointer cpadd(polyPointer a, polyPointer b)
{
    polyPointer startA, c, lastC;
    int sum, done = FALSE;
    startA = a;         /* record start of a */
    a = a->link;         /* skip header node for a and b */
    b = b->link;
    c = getNode();      /* get a header node for sum */
    c->expon = -1;
    lastC = c;

    do
    {
        switch (COMPARE(a->expon, b->expon))
        {
        case -1: /* a->expon < b->expon */
            attach(b->coef, b->expon, &lastC);
            b = b->link;
            break;

        case 0: /* a->expon = b->expon */
            if (startA == a)
                done = TRUE;

            else
            {
                sum = a->coef + b->coef;

                if (sum)
                    attach(sum, a->expon, &lastC);

                a = a->link;
                b = b->link;
            }
            break;

        case 1: /* a->expon > b->expon */
            attach(a->coef, a->expon, &lastC);
            a = a->link;
        }
    } while (!done);

    lastC->link = c;

    return c;
}

void attach(int coefficient, int exponent, polyPointer* ptr)
{
    polyPointer temp;
    temp = getNode();
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

polyPointer getNode(void)
{/* provide a node for use */
    polyPointer node;
    if (avail)
    {
        node = avail;
        avail = avail->link;
    }

    else
        MALLOC(node, sizeof(*node));

    return node;

}

void retNode(polyPointer node)
{/* return a node to the available list */
    node->link = avail;
    avail = node;
}

void cerase(polyPointer* ptr)
{ /* erase the circular list pointed to by ptr */
    polyPointer temp;
    if (*ptr)
    {
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
}

void erase(polyPointer* ptr)
{/* erase the polynomial pointed to by ptr */
    polyPointer temp;
    while (*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}

void printp(polyPointer ptr)
{
    ptr = ptr->link;

    for (; ptr->expon != -1;)
    {
        printf("(%d, %d) ", ptr->coef, ptr->expon);
        ptr = ptr->link;
    }
}
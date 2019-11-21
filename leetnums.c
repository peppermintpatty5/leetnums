#include <stdio.h>
#include <stdlib.h>

#include "leetnums.h"

int main(int argc, char const *argv[])
{
    unsigned long x;

    if (argc > 1)
    {
        x = atol(argv[1]);
        printbt(calc(x));
        putchar('\n');
    }
    else
        fprintf(stderr, "Missing number argument\n");

    return EXIT_SUCCESS;
}

struct bintree *calc(unsigned long x)
{
    struct bintree *bt = malloc(sizeof(struct bintree));

    bt->x = x;

    if (x == 0 || x == 1)
    {
        bt->l = bt->r = NULL;
    }
    else
    {
        bt->l = calc(1);
        bt->r = calc(1);
        bt->op = XORQ;
    }

    return bt;
}

void printbt(struct bintree const *bt)
{
    putchar('(');
    if (bt->l && bt->r)
    {
        printbt(bt->l);
        switch (bt->op)
        {
        case SHLQ:
            printf(" << ");
            break;
        case XORQ:
            printf(" ^ ");
            break;
        }
        printbt(bt->r);
    }
    else
    {
        printf("%lu", bt->x);
    }
    putchar(')');
}

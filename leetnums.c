#include <stdio.h>
#include <stdlib.h>

#include "leetnums.h"

int main(int argc, char const *argv[])
{
    if (argc > 1)
        printbt(calc(atol(argv[1])));
    else
        fprintf(stderr, "Missing number argument\n");
    putchar('\n');

    return EXIT_SUCCESS;
}

struct bintree *calc(unsigned long const x)
{
    unsigned long n = 0;
    struct bintree *bt = malloc(sizeof(struct bintree));

    bt->x = x;

    if (x == 0 || x == 1) /* base cases */
        bt->l = bt->r = NULL;
    else
    {
        while (!nbit(x, n))
            n++;

        if (n) /* x is evenly divisible by 2^n */
        {
            bt->l = calc(x >> n);
            bt->r = calc(n);
            bt->op = SHLQ;
        }
        else /* find best way to cut x in half */
        {
            while (x >> n)
                n++;

            bt->l = calc(x & ~nmask(n >> 1));
            bt->r = calc(x & nmask(n >> 1));
            bt->op = XORQ;
        }
    }

    return bt;
}

void printbt(struct bintree const *bt)
{
    if (bt->l && bt->r)
    {
        putchar('(');
        printbt(bt->l);
        switch (bt->op)
        {
        case SHLQ:
            printf("<<");
            break;
        case XORQ:
            printf("^");
            break;
        }
        printbt(bt->r);
        putchar(')');
    }
    else
        printf("%s*\"\"", bt->x ? "!" : "");
}

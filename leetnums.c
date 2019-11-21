#include <stdio.h>
#include <stdlib.h>

#include "leetnums.h"

int main(int argc, char const *argv[])
{
    if (argc > 1)
        printbt(genbt(atoi(argv[1])));
    else
        fprintf(stderr, "Missing number argument");
    putchar('\n');

    return EXIT_SUCCESS;
}

struct bintree *genbt(unsigned const x)
{
    unsigned n = 0;
    struct bintree *bt = malloc(sizeof(struct bintree));

    if (x == 0)
        *bt = (struct bintree){NULL, NULL, ZERO};
    else if (x == 1)
        *bt = (struct bintree){NULL, NULL, ONE};
    else
    {
        while (!nbit(x, n))
            n++;

        if (n) /* x is evenly divisible by 2^n */
        {
            bt->l = genbt(x >> n);
            bt->r = genbt(n);
            bt->op = SHL;
        }
        else /* find best way to cut x in half */
        {
            n = sizeof(x) << 3;
            while (!nbit(x, n - 1))
                n--;

            bt->l = genbt(x & ~nmask(n >> 1));
            bt->r = genbt(x & nmask(n >> 1));
            bt->op = XOR;
        }
    }

    return bt;
}

void printbt(struct bintree const *bt)
{
    putchar('(');
    switch (bt->op)
    {
    case ZERO:
        printf("!!*\"\"");
        break;
    case ONE:
        printf("!*\"\"");
        break;
    case SHL:
        printbt(bt->l);
        printf("<<");
        printbt(bt->r);
        break;
    case XOR:
        printbt(bt->l);
        printf("^");
        printbt(bt->r);
        break;
    }
    putchar(')');
}

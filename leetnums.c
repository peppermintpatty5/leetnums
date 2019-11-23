#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "leetnums.h"

#define CACHE_SIZE 32

static char const *format = "%lu";
static size_t malloc_count = 0;
static struct bintree *CACHE[CACHE_SIZE];

int main(int argc, char const *argv[])
{
    unsigned long i, x = 0;
    unsigned int depth = UINT_MAX, stats = 0;
    struct bintree *bt;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && !atol(argv[i])) /* flag */
        {
            switch (argv[i][1])
            {
            case 'd':
                depth = atoi(&argv[i][2]);
                break;
            case 'f':
                format = &argv[i][2];
                break;
            case 's':
                stats = 1;
                break;
            default:
                fprintf(stderr, "Unrecognized flag: %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
        else
            x = atol(argv[i]);
    }

    bt = genbt(x);
    printbt(bt, depth);
    putchar('\n');

    if (stats)
    {
        printf("node count: %lu\n", nodecount(bt));
        printf("malloc count: %lu\n", malloc_count);
        printf("cache hits: ");
        for (i = 0; i < CACHE_SIZE; i++)
            if (CACHE[i])
                printf("%lu ", i);
        putchar('\n');
    }

    return EXIT_SUCCESS;
}

struct bintree *genbt(unsigned long x)
{
    unsigned long n = 0;
    struct bintree *bt;

    if (x < CACHE_SIZE && CACHE[x])
        bt = CACHE[x];
    else
    {
        bt = malloc(sizeof(struct bintree));
        malloc_count++;

        bt->val = x;
        if (x == 0 || x == 1)
        {
            bt->l = bt->r = NULL;
            bt->op = VAL;
        }
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

                bt->l = genbt(x & nmask(n >> 1));
                bt->r = genbt(x & ~nmask(n >> 1));
                bt->op = XOR;
            }
        }

        if (x < CACHE_SIZE)
            CACHE[x] = bt;
    }

    return bt;
}

void printbt(struct bintree const *bt, unsigned int depth)
{
    if (depth && bt->op) /* latter works like a boolean */
    {
        putchar('(');
        printbt(bt->l, depth - 1);
        printf(bt->op == SHL ? "<<" : "^");
        printbt(bt->r, depth - 1);
        putchar(')');
    }
    else
        printf(format, bt->val);
}

size_t nodecount(struct bintree const *bt)
{
    return bt ? 1 + nodecount(bt->l) + nodecount(bt->r) : 0;
}

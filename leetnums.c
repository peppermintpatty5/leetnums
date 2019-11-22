#include <stdio.h>
#include <stdlib.h>

#include "leetnums.h"

#define DEBUG_MODE 0
#define CACHE_SIZE 256

static size_t malloc_counter = 0;
static struct bintree *CACHE[CACHE_SIZE];

int main(int argc, char const *argv[])
{
#if DEBUG_MODE
    size_t i, j;

    /* long x = 18446744073709551616; */
    for (i = 0; i < 256; i++)
    {
        malloc_counter = 0;
        for (j = 0; j < CACHE_SIZE; j++)
            CACHE[j] = NULL;

        genbt(i << 8);
        printf("%lu\n", malloc_counter);
    }
#else
    size_t i;
    struct bintree *bt;

    if (argc > 0)
    {
        bt = genbt(0xFFFFFFFFFFFFFFFF);
        printbt(bt);
        putchar('\n');
    }
    else
        fprintf(stderr, "Missing number argument\n");

    for (i = 0; i < CACHE_SIZE; i++)
        if (CACHE[i])
            printf("%lu, ", i);
    putchar('\n');

    i = (((((((((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL)))) << ((1UL) << (((1UL) << (1UL)) ^ (1UL)))) ^ (((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))))) << ((1UL) << ((1UL) << ((1UL) << (1UL))))) ^ (((((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL)))) << ((1UL) << (((1UL) << (1UL)) ^ (1UL)))) ^ (((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL)))))) << ((1UL) << (((1UL) << ((1UL) << (1UL))) ^ (1UL)))) ^ (((((((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL)))) << ((1UL) << (((1UL) << (1UL)) ^ (1UL)))) ^ (((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))))) << ((1UL) << ((1UL) << ((1UL) << (1UL))))) ^ (((((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL)))) << ((1UL) << (((1UL) << (1UL)) ^ (1UL)))) ^ (((((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL))) << ((1UL) << ((1UL) << (1UL)))) ^ (((((1UL) << (1UL)) ^ (1UL)) << ((1UL) << (1UL))) ^ (((1UL) << (1UL)) ^ (1UL)))))));
    printf("i: %lu\n", i);
#endif

    return EXIT_SUCCESS;
}

struct bintree *genbt(unsigned long const x)
{
    unsigned long n = 0;
    struct bintree *bt;

    if (x < CACHE_SIZE && CACHE[x])
        bt = CACHE[x];
    else
    {
        bt = malloc(sizeof(struct bintree));
        malloc_counter++;

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

        if (x < CACHE_SIZE)
            CACHE[x] = bt;
    }

    return bt;
}

void printbt(struct bintree const *bt)
{
    putchar('(');
    switch (bt->op)
    {
    case ZERO:
        printf("0UL");
        break;
    case ONE:
        printf("1UL");
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

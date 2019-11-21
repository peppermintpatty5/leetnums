#ifndef LEETNUMS_H_
#define LEETNUMS_H_

/**
 * Extracts the nth bit of the integer x
 */
#define nbit(x, n) (((x) >> (n)) & 1)

/**
 * Enumerates the possible bintree operations
 */
enum ops
{
    SHLQ, /* shift left */
    XORQ  /* exclusive OR */
};

/**
 * Representation of a bitshift/xor expression
 */
struct bintree
{
    struct bintree *l; /* left hand side */
    struct bintree *r; /* right hand side */
    unsigned long x;   /* numeric value */
    enum ops op;       /* operation type */
};

/**
 * Recursively generates a bitshift/xor expression
 */
struct bintree *calc(unsigned long x);

/**
 * For debugging
 */
void printbt(struct bintree const *bt);

#endif

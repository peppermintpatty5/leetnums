#ifndef LEETNUMS_H_
#define LEETNUMS_H_

/**
 * Extracts the nth bit of the long integer x
 */
#define nbit(x, n) (((x) >> (n)) & 0x1UL)

/**
 * Produces a bit mask with lower n bits disabled
 */
#define nmask(n) (~0x0UL << (n))

/**
 * Enumerates the possible bintree operations
 */
enum ops
{
    VAL, /* numeric value */
    SHL, /* bitshift left */
    XOR  /* exclusive OR */
};

/**
 * Representation of a bitshift/xor expression
 */
struct bintree
{
    struct bintree *l; /* left hand side */
    struct bintree *r; /* right hand side */
    unsigned long val; /* numeric value */
    enum ops op;       /* operation type */
};

/**
 * Recursively generates a bitshift/xor expression
 */
struct bintree *genbt(unsigned long x);

/**
 * Prints the bitshift/xor expression to stdout
 */
void printbt(struct bintree const *bt, unsigned int depth);

/**
 * Recursiely counts the number of nodes in the tree
 */
unsigned int nodecount(struct bintree const *bt);

#endif

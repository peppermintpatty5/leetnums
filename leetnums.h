#ifndef LEETNUMS_H_
#define LEETNUMS_H_

/**
 * Extracts the nth bit of the integer x
 */
#define nbit(x, n) (((x) >> (n)) & 0x1)

/**
 * Create bit mask with lower n bits enabled
 */
#define nmask(n) (~((~0x0) << (n)))

/**
 * Enumerates the possible bintree operations
 */
enum ops
{
    ZERO, /* the number 0 */
    ONE,  /* the number 1 */
    SHL,  /* shift left */
    XOR   /* exclusive OR */
};

/**
 * Representation of a bitshift/xor expression
 */
struct bintree
{
    struct bintree *l; /* left hand side */
    struct bintree *r; /* right hand side */
    enum ops op;       /* operation type */
};

/**
 * Recursively generates a bitshift/xor expression
 */
struct bintree *genbt(const unsigned x);

/**
 * For debugging
 */
void printbt(struct bintree const *bt);

#endif

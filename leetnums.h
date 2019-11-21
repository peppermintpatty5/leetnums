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
struct bintree *calc(const unsigned long x);

/**
 * For debugging
 */
void printbt(struct bintree const *bt);

#endif

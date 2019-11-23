# leetnums
Very useless bitshift/xor expression generator

## Summary
Every positive integer has a unique binary representation, which can be transformed into an expression consisting solely of booleans `0` or `1`, bitwise XOR operators `^`, and bitwise left shift operators `<<`.

## Usage
This program loosely enforces the following command line argument syntax:
```sh
$ ./a.out [$num] # the number to convert (can be negative)
          [-d$depth] # depth used in printing expression tree
          [-f$format] # C-style printf format specifier
          [-s] # enables statistical output
```

As a sidenote, simply running `a.out` with no arguments is effectively the same as:
```sh
$ ./a.out 0 -d-1 -f%lu
```

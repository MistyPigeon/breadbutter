#include <stdio.h>
#include <stdlib.h>

int expr_main(int argc, char **argv) {
    if (argc < 4) return 1;
    long a = atol(argv[1]);
    long b = atol(argv[3]);
    char op = argv[2][0];
    if (op == '+') printf("%ld\n", a + b);
    else if (op == '-') printf("%ld\n", a - b);
    else if (op == '*') printf("%ld\n", a * b);
    else if (op == '/' && b != 0) printf("%ld\n", a / b);
    return 0;
}

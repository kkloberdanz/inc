#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    mpz_t n;
    unsigned long int i;

    for (i = 1; i < ULLONG_MAX; i++) {
        printf("%lu\n", i);
    }

    mpz_init(n);
    mpz_set_ui(n, i);
    for (;;) {
        mpz_out_str(stdout, 10, n);
        puts("");
        mpz_add_ui(n, n, 1);
    }
    mpz_clear(n);
    return 0;
}

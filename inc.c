#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gmp.h>

typedef const char *str;

struct opts {
    char *begin;
    char *end;
};

static void print_usage(void) {
    str msg = "inc:\n"
              "\t-b <int>\tnumber to begin with\n\n";
    fprintf(stderr, "%s", msg);
}

static int parse_opts(
    int argc, char *const *const argv, struct opts *opts /* out */
) {
    int c;
    while ((c = getopt(argc, argv, "b:he:")) != -1) {
        switch (c) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
        case 'b':
            opts->begin = strdup(optarg);
            break;
        case 'e':
            opts->end = strdup(optarg);
            break;
        default:
            return -1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    mpz_t n;
    mpz_t begin;
    mpz_t end;
    unsigned long long i = 1;
    int err = 0;

    struct opts opts = {
        .begin = NULL,
        .end = NULL,
    };

    err = parse_opts(argc, argv, &opts);
    if (err) {
        goto done;
    }

    if (!opts.begin && !opts.end) {
        for (i = 1; i < ULLONG_MAX; i++) {
            printf("%llu\n", i);
        }
    }

    mpz_init(n);
    mpz_init(end);
    mpz_init(begin);

    mpz_set_ui(n, i);

    if (opts.begin) {
        mpz_set_str(n, opts.begin, 10);
    }

    if (opts.end) {
        mpz_set_str(end, opts.end, 10);
    }

    for (;;) {
        if (opts.end && (mpz_cmp(n, end) > 0)) {
            break;
        }
        mpz_out_str(stdout, 10, n);
        puts("");
        mpz_add_ui(n, n, 1);
    }
done:
    mpz_clear(n);
    mpz_clear(begin);
    mpz_clear(end);
    free(opts.begin);
    free(opts.end);
    return err;
}

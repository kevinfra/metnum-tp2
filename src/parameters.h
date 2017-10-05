#ifndef METNUM_TP2_PARAMETERS_H
#define METNUM_TP2_PARAMETERS_H

struct parameters {
    u_char method;
    const char* test_file;
    const char* train_file;
    const char* out_file;
};

enum ParseResult { OK, MISSING_ARG, UNKNOWN_METHOD, UNKNOWN_ARG};

int parse(int argc, char const *argv[], parameters& p, const char **unknown);

#endif //METNUM_TP2_PARAMETERS_H

#include <iostream>
#include "parameters.h"
#include "machines/MachineFactory.h"

int parse(int argc, const char **argv, parameters &p, const char **unknown) {
    for (int i = 1; i < argc; ++i) {
        std::string opt(argv[i]);
        if(opt == "-m") {
            if(++i < argc) {
                char* ptr;
                long met = strtol(argv[i], &ptr, 10);
                if (*ptr || met >= MachineFactory::Implementation::IMPL_COUNT) {
                    *unknown = argv[i];
                    return UNKNOWN_METHOD;
                } else {
                    p.method = (MachineFactory::Implementation)met;
                }
            }
        } else if(opt == "-i") {
            if(++i < argc) {
                p.train_file = argv[i];
            }
        } else if(opt == "-q") {
            if(++i < argc) {
                p.test_file = argv[i];
            }
        } else if(opt == "-o") {
            if(++i < argc) {
                p.out_file = argv[i];
            }
        } else if(opt == "-alfa") {
            if(++i < argc) {
                p.alfa = atoi(argv[i]);
            }
        } else if(opt == "-k") {
            if(++i < argc) {
                p.k = atoi(argv[i]);
            }
        } else {
            *unknown = argv[i];
            return UNKNOWN_ARG;
        }
    }
    if(p.method == 255 || p.out_file == NULL || p.test_file == NULL || p.train_file == NULL) {
        return MISSING_ARG;
    }
    return OK;
}

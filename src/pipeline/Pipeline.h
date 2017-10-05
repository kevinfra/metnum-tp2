#ifndef METNUM_TP2_PIPELINE_H
#define METNUM_TP2_PIPELINE_H

#include "../matrix/Matrix.h"
#include "../io/IO.h"
#include "../parameters.h"

class Pipeline {
public:

    virtual void train() = 0;

    virtual void guess() = 0;

protected:

    Pipeline(const parameters& p) :
            train_file(p.train_file), test_file(p.test_file),
            out_file(p.out_file, std::ofstream::out | std::ofstream::trunc) {
        out_file << "ImageId,Label" << std::endl;
    }

    virtual ~Pipeline() {
        train_file.close();
        test_file.close();
        out_file.close();
    }

    void saveResult(u_int testCase, u_char digit) {
        out_file << testCase << ',' << +digit << std::endl;
    }

    std::ifstream train_file;
    std::ifstream test_file;
    std::ofstream out_file;
};


#endif //METNUM_TP2_PIPELINE_H

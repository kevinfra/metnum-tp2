#ifndef METNUM_TP2_MACHINE_H
#define METNUM_TP2_MACHINE_H

#include "../matrix/Matrix.h"
#include "../io/IO.h"

class Machine {
public:

    virtual void train(const TrainSet<Pixel> &trainSet) = 0;

    virtual vector<unsigned char> guess(const TestSet<Pixel> &testSet) = 0;

    virtual vector<unsigned char> guessK(const TestSet<Pixel> &testSet, unsigned int kp) = 0;
};


#endif //METNUM_TP2_MACHINE_H

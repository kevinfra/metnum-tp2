#ifndef METNUM_TP2_KNNMACHINE_H
#define METNUM_TP2_KNNMACHINE_H

#include <iostream>
#include "Machine.h"
#include "../io/MatrixIterator.h"
#include "../knn.h"

#define K 10

class KnnMachine : public Machine {
public:
    KnnMachine(const parameters& p) : Machine(p) {}

    virtual void train() {
        // data is already formatted, just load it
        std::cout << "Loading train set...        \r" << std::flush;
        trainSet = IO::loadTrainSet<unsigned char>(train_file);
    }

    virtual void guess() {
        std::cout << "Loading test set...        \r" << std::flush;
        //MatrixIterator<unsigned char> testCaseIt(test_file);
        vector<MatrixRef<unsigned char>> testSet = IO::loadTestSet<unsigned char>(test_file);
        uint i = 1;
        INIT_BENCH("bench-knn.csv");
        //for (; testCaseIt.hasNext(); ++testCaseIt) {
        for (auto testCaseIt = testSet.begin(); testCaseIt != testSet.end() ; testCaseIt++) {
            std::cout << "Guessing for case n° " << i << std::endl;
            //TrainSetIterator<unsigned char> trainSet(train_file);
            unsigned char res = kNN<unsigned char>(K, *testCaseIt, trainSet);
            saveResult(i, res);
            ++i;
        }
        std::cout << "All done!                   " << std::endl;
    }

private:
    vector<TrainCase<unsigned char>> trainSet;

};


#endif //METNUM_TP2_KNNMACHINE_H

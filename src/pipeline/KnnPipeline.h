#ifndef METNUM_TP2_KNNPIPELINE_H
#define METNUM_TP2_KNNPIPELINE_H

#include <iostream>
#include "Pipeline.h"
#include "../io/MatrixIterator.h"
#include "../knn.h"

#define K 10

class KnnPipeline : public Pipeline {
public:
    KnnPipeline(const parameters& p) : Pipeline(p) {}

    virtual void train() {
        // data is already formatted, do nothing
    }

    virtual void guess() {
        std::cout << "Loading train set...        \r" << std::flush;
        vector<TrainCase<unsigned char>> trainSet = IO::loadTrainSet<unsigned char>(train_file);
        std::cout << "Loading test set...        \r" << std::flush;
        //MatrixIterator<unsigned char> testCaseIt(test_file);
        vector<MatrixRef<unsigned char>> testSet = IO::loadTestSet<unsigned char>(test_file);
        uint i = 1;
        INIT_BENCH("bench-knn.csv")
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

};


#endif //METNUM_TP2_KNNPIPELINE_H

#include <gtest/gtest.h>
#include "../src/knn.h"

class knnTest : public ::testing::Test {
protected:

    virtual void SetUp() {
        m_h = 5;
        unknownMatrix = new FullMatrix<double>(5, 5, 0);
        for (int i = 0; i < 5; ++i) {
            if (i == 1 || i == 4) {
                (*unknownMatrix)[i][i] = 1;
            }
        }
    }

    virtual void TearDown() {
        delete unknownMatrix;
    }

    FullMatrix<double>* unknownMatrix;
    size_t m_h;
};

TEST_F(knnTest, findsNearest) {
    FullMatrix<double>* practiceMatrix1 = new FullMatrix<double>(5, 5, 0);
    for (int i = 0; i < 5; ++i) {
        (*practiceMatrix1)[i][i] = 1;
    }
    FullMatrix<double>* practiceMatrix2 = new FullMatrix<double>(5, 5, 0);
    for (int i = 0; i < 5; ++i) {
        if (i > 1 && i < 4) {
            (*practiceMatrix2)[i][i] = 1;
        }
    }

    row< FullMatrix<double> > knownMatrices = {
            *practiceMatrix1,
            *practiceMatrix2
    };

    row< FullMatrix<double> > * pointerToKnownMatrices = &knownMatrices;

    int knn_result = kNN(1, *unknownMatrix, (row< BaseMatrix<double> >*) pointerToKnownMatrices);
    ASSERT_EQ(1, knn_result);
}
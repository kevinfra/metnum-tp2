#include <gtest/gtest.h>
#include "../src/knn.h"

class knnTest : public ::testing::Test {
protected:

    virtual void SetUp() {
        m_h = 5;
        unknownMatrix = std::make_shared<FullMatrix<double>>(m_h, m_h, 0);
        for (int i = 0; i < 5; ++i) {
            if (i == 1 || i == 4) {
                (*unknownMatrix)[i][i] = 1;
            }
        }
    }

    MatrixRef<double> unknownMatrix;
    size_t m_h;
};

TEST_F(knnTest, findsNearest) {
    MatrixRef<double> practiceMatrix1 = std::make_shared<FullMatrix<double>>(5, 5, 0);
    for (int i = 0; i < 5; ++i) {
        (*practiceMatrix1)[i][i] = 1;
    }
    MatrixRef<double> practiceMatrix2 = std::make_shared<FullMatrix<double>>(5, 5, 0);
    for (int i = 0; i < 5; ++i) {
        if (i > 1 && i < 4) {
            (*practiceMatrix2)[i][i] = 1;
        }
    }
    vector< TrainCase<double> > knownMatrices = {
            {practiceMatrix1, 1},
            {practiceMatrix2, 2}
    };

    int knn_result = kNN(1, unknownMatrix, knownMatrices);

    ASSERT_EQ(1, knn_result);
}
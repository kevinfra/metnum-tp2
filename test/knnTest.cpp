#include <gtest/gtest.h>
#include "../src/knn.h"

class knnTest : public ::testing::Test {
public:
    knnTest() : m_h(5), unknownMatrix(m_h*m_h, 0) {}
protected:

    virtual void SetUp() {
        m_h = 5;
        for (int i = 0; i < 5; ++i) {
            if (i == 1 || i == 4) {
                unknownMatrix[i*6] = 1;
            }
        }
    }

    size_t m_h;
    vector<double> unknownMatrix;
};

TEST_F(knnTest, findsNearest) {
    vector<double> practiceMatrix1(25, 0);
    for (int i = 0; i < 5; ++i) {
        practiceMatrix1[i*6] = 1;
    }
    vector<double> practiceMatrix2(25, 0);
    for (int i = 2; i < 4; ++i) {
        practiceMatrix2[i*6] = 1;
    }
    vector< TrainCase<double> > knownMatrices = {
            {practiceMatrix1, 1},
            {practiceMatrix2, 2}
    };

    int knn_result = kNN(1, unknownMatrix, knownMatrices);

    ASSERT_EQ(1, knn_result);
}
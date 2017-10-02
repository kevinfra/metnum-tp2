

#include <gtest/gtest.h>
#include "../src/matrix/Matrix.h"
#include "../src/matrix/FullMatrix.h"
#include "../src/matrix/SparseMatrix.h"

class MatrixText : public ::testing::Test {
protected:

    virtual void SetUp() {
        m_h = 5;
    }

    virtual void TearDown() {
        delete m;
    }

    Matrix<int>* m;
    size_t m_h;
};

TEST_F(MatrixText, fullIdentity) {
    m = new FullMatrix<int>(m_h, m_h, 0);
    for (size_t i = 0; i < m_h; ++i) {
        (*m)[i][i] = 1;
    }
    for (size_t i = 0; i < m_h; ++i) {
        for (size_t j = 0; j < m_h; ++j) {
            if(i != j) {
                ASSERT_EQ((*m)[i][j], 0);
            } else {
                ASSERT_EQ((*m)[i][j], 1);
            }
        }
    }
}

TEST_F(MatrixText, sparseIdentity) {
    m = new SparseMatrix<int>(m_h, m_h, 0);
    for (size_t i = 0; i < m_h; ++i) {
        (*m)[i][i] = 1;
    }
    for (size_t i = 0; i < m_h; ++i) {
        for (size_t j = 0; j < m_h; ++j) {
            if(i != j) {
                ASSERT_EQ((*m)[i][j], 0);
            } else {
                ASSERT_EQ((*m)[i][j], 1);
            }
        }
    }
}
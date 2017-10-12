#include <gtest/gtest.h>
#include "../src/matrix/Matrix.h"
#include "../src/matrix/FullMatrix.h"
#include "../src/matrix/SparseMatrix.h"

class MatrixTest : public ::testing::Test {
protected:

    virtual void SetUp() {
        m_h = 5;
    }

    MatrixRef<int> m;
    size_t m_h;
};

TEST_F(MatrixTest, fullIdentity) {
    m = FullMatrix<int>::create(m_h, m_h, 0);
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

TEST_F(MatrixTest, sparseIdentity) {
    m = SparseMatrix<int>::create(m_h, m_h, 0);
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

TEST_F(MatrixTest, square_array) {
    int value = 1;
    int** arr = new int*[m_h];
    for (size_t i = 0; i < m_h; ++i) {
        arr[i] = new int[m_h];
        for (size_t j = 0; j < m_h; ++j) {
            arr[i][j] = value;
        }
    }
    m = FullMatrix<int>::create(arr, m_h, m_h);
    ASSERT_EQ(m->height(), m_h);
    for (size_t i = 0; i < m->height(); ++i) {
        ASSERT_EQ((*m)[i].size(), m_h);
        for (size_t j = 0; j < m->width(); ++j) {
            ASSERT_EQ((*m)[i][j], value);
        }
    }

    for (size_t i = 0; i < m_h; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, dotProduct) {
    FullMatrix<int> a = {
            {2, 0, 1},
            {3, 0, 0},
            {5, 1, 1}
    };

    
    FullMatrix<int> b= {
            {1, 0, 1},
            {1, 2, 1},
            {1, 1, 0}
    };

    FullMatrix<int> expected = {
            {3, 1, 2},
            {3, 0, 3},
            {7, 3, 6}
    };

    MatrixRef<int> result = a.dotProduct(b);

    ASSERT_EQ(*result, expected);

    FullMatrix<int> i3 = FullMatrix<int>::identity(3);

    ASSERT_EQ(*a.dotProduct(i3), a);
    ASSERT_EQ(*b.dotProduct(i3), b);
    ASSERT_EQ(*i3.dotProduct(a), a);
    ASSERT_EQ(*i3.dotProduct(b), b);

    FullMatrix<int> c = {
            {2, 5, 1},
            {4, 3, 1}
    };

    FullMatrix<int> d = {
            {1, 0, 0},
            {0, 2, 0},
            {2, 3, 1}
    };

    FullMatrix<int> ex2 = {
            {4, 13, 1},
            {6,  9, 1}
    };

    ASSERT_EQ(*c.dotProduct(d), ex2);
}

TEST_F(MatrixTest, sum) {
    FullMatrix<int> a = {
            {2, 0, 1},
            {3, 0, 0},
            {5, 1, 1}
    };

    FullMatrix<int> b = {
            {1, 0, 1},
            {1, 2, 1},
            {1, 1, 0}
    };

    FullMatrix<int> expected = {
            {3, 0, 2},
            {4, 2, 1},
            {6, 2, 1}
    };

    MatrixRef<int> result = a + b;

    ASSERT_EQ(*result, expected);
}

TEST_F(MatrixTest, norm) {
    int value = 1;
    m = FullMatrix<int>::create(m_h, m_h, value);
    ASSERT_EQ(m->infinityNorm(), 1);
    ASSERT_EQ(m->twoNorm(), 5);
    ASSERT_EQ(m->singleNorm(), 25);
}

TEST_F(MatrixTest, traspose){
    int value = 1;
    int** arr = new int*[m_h];
    for (size_t i = 0; i < m_h; ++i) {
        arr[i] = new int[m_h];
        for (size_t j = 0; j < m_h; ++j) {
            arr[i][j] = value;
            value++;
        }
    }
    m = FullMatrix<int>::create(arr, m_h, m_h);
    MatrixRef<int> transposedM = m->transpose();
    MatrixRef<int> transposed_transposedM = transposedM->transpose();
    
    ASSERT_EQ(*m, *transposed_transposedM);

    int sizeN = 5;
    int sizeM = 6;
    int anotherValue = 1;
    int** notSquared_arr = new int*[sizeM];
    for (int i = 0; i < sizeM; ++i) {
        notSquared_arr[i] = new int[sizeN];
        for (int j = 0; j < sizeN; ++j) {
            notSquared_arr[i][j] = anotherValue;
            anotherValue++;
        }
    }
    FullMatrix<int> notSquared_m(notSquared_arr, sizeM, sizeN);
    MatrixRef<int> notSquared_transposedM = notSquared_m.transpose();
    MatrixRef<int> notSquared_transposed_transposedM = notSquared_transposedM->transpose();

    ASSERT_EQ(notSquared_m, *notSquared_transposed_transposedM);

    for (size_t i = 0; i < m_h; ++i) {
        delete[] arr[i];
    }
    for (int i = 0; i < sizeM; ++i) {
        delete[] notSquared_arr[i];
    }
    delete[] arr;
    delete[] notSquared_arr;
}

TEST_F(MatrixTest, inplaceTranspose) {
    m = FullMatrix<int>::create(m_h, m_h);

    int value = 1;
    for (size_t i = 0; i < m_h; ++i) {
        for (size_t j = 0; j < m_h; ++j) {
            (*m)[i][j] = value;
            value++;
        }
    }

    auto m_t = m->transpose();
    m->inplaceTranspose();
    ASSERT_EQ(*m, *m_t);
}

TEST_F(MatrixTest, isLowerTriangular) {
    int value = 1;
    int** arr = new int*[m_h];
    for (size_t i = 0; i < m_h; ++i) {
        arr[i] = new int[m_h];
        for (size_t j = 0; j < m_h; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    m = FullMatrix<int>::create(arr, m_h, m_h);
    ASSERT_TRUE(m->isLowerTriangular());

    for (size_t i = 0; i < m_h; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, isUpperTriangular) {
    int value = 1;
    int** arr = new int*[m_h];
    for (size_t i = 0; i < m_h; ++i) {
        arr[i] = new int[m_h];
        for (size_t j = 0; j < m_h; ++j) {
            if (j >= i) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    m = FullMatrix<int>::create(arr, m_h, m_h);
    ASSERT_TRUE(m->isUpperTriangular());

    for (size_t i = 0; i < m_h; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, trasposeProduct) {
    int value = 1;
    int** arr = new int*[m_h];
    for (size_t i = 0; i < m_h; ++i) {
        arr[i] = new int[m_h];
        for (size_t j = 0; j < m_h; ++j) {
            arr[i][j] = value;
            value++;
        }
    }
    m = FullMatrix<int>::create(arr, m_h, m_h);
    ASSERT_EQ(*m->dotProduct(*m->transpose()), *m->transposedProduct());

    for (size_t i = 0; i < m_h; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, solveLowerTriangularSquaredSystem) {
    int size = 5;
    double value = 1;
    double** arr = new double*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    FullMatrix<double> A(arr, size, size);
    vector<double> b = {15,25,35,45,55};
    double expected0 = 15;
    double expected1 = (25 - (expected0*2))/3;
    double expected2 = (35 - (expected0*4) - (expected1*5))/6;
    double expected3 = (45 - (expected0*7) - (expected1*8) - (expected2*9))/10;
    double expected4 = (55 - (expected0*11) - (expected1*12) - (expected2*13) - (expected3*14))/15;

    vector<double> expected = { expected0, expected1, expected2, expected3,  expected4 };
    vector<double> result = Matrix<double>::solveLowerTriangularSquaredSystem(A, b);
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_NEAR(expected[i], result[i], 0.0000001) << "i=" << i;
    }

    FullMatrix<int> C = FullMatrix<int>::identity(5);
    vector<int> d = { 13, 15, 17, 18, 19};
    vector<int> expected_2 = d;
    vector<int> result_2 = Matrix<int>::solveLowerTriangularSquaredSystem(C, d);
    for (size_t i = 0; i < expected_2.size(); ++i) {
        ASSERT_EQ(expected_2[i], result_2[i]) << "i=" << i;
    }

    for (int i = 0; i < size; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, solveUpperTriangularSquaredSystem) {
    int size = 5;
    double value = 1;
    double** arr = new double*[size];
    for (int i = size-1; i >= 0; --i) {
        arr[i] = new double[size];
        for (int j = size-1; j >= 0; --j) {
            if ( j >= i) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    FullMatrix<double> A(arr, size, size);
    vector<double> b = { 55, 45, 35, 25, 15 };
    double expected0 = 15;
    double expected1 = (25 - (expected0*2))/3;
    double expected2 = (35 - (expected0*4) - (expected1*5))/6;
    double expected3 = (45 - (expected0*7) - (expected1*8) - (expected2*9))/10;
    double expected4 = (55 - (expected0*11) - (expected1*12) - (expected2*13) - (expected3*14))/15;

    vector<double> expected = { expected4, expected3, expected2, expected1,  expected0 };
    vector<double> result = Matrix<double>::solveUpperTriangularSquaredSystem(A, b);
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_NEAR(expected[i], result[i], 0.0000001) << "i=" << i;
    }

    FullMatrix<int> C = FullMatrix<int>::identity(5);
    vector<int> d = { 19, 18, 17, 15, 13 };
    vector<int> expected_2 = d;
    vector<int> result_2 = Matrix<int>::solveUpperTriangularSquaredSystem(C, d);
    for (size_t i = 0; i < expected_2.size(); ++i) {
        ASSERT_EQ(expected_2[i], result_2[i]) << "i=" << i;
    }

    for (int i = 0; i < size; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, solveLUSystem){
    int size = 5;
    double value = 1;

    double** arr = new double*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    FullMatrix<double> L(arr, size, size);

    double** arr2 = new double*[size];
    for (int i = size-1; i >= 0; --i) {
        arr2[i] = new double[size];
        for (int j = size-1; j >= 0; --j) {
            if ( j >= i) {
                arr2[i][j] = value;
                value++;
            } else {
                arr2[i][j] = 0;
            }
        }
    }
    FullMatrix<double> U(arr2, size, size);

    vector<double> b = { 100, 200, 300, 400, 500 };
    vector<double> expected = { 3.34677, 0.77131, 0.00408, -0.10576, -0.77037 };

    vector<double> result = Matrix<double>::solveLUSystem(L,U,b);

    for (int k = 0; k < 5; ++k) {
        ASSERT_NEAR(expected[k], result[k], 0.1);
    }

    for (int i = 0; i < size; ++i) {
        delete[] arr[i];
        delete[] arr2[i];
    }
    delete[] arr;
    delete[] arr2;
}

TEST_F(MatrixTest, solvePLUSystem) {
    int** arr = new int*[3];
    arr[0] = new int[3]{0,1,2};
    arr[1] = new int[3]{1,0,0};
    arr[2] = new int[3]{0,1,0};

    FullMatrix<int> m(arr, 3, 3);
    FullMatrix<int> u = {{1,0,0},{0,1,2},{0,0,-2}};
    FullMatrix<int> l = {{1,0,0},{0,1,0},{0,1,1}};
    FullMatrix<int> p = {{0,1,0},{1,0,0},{0,0,1}};

    vector<int> b = {1,2,3};
    vector<int> expected_x = {2,3,-1};

    ASSERT_EQ(Matrix<int>::solvePLUSystem(p,l,u,b), expected_x);

    for (int i = 0; i < 3; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

TEST_F(MatrixTest, solveCholeskySystem){
    int size = 5;
    double value = 1;

    double** arr = new double*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            if (j < i+1) {
                arr[i][j] = value;
                value++;
            } else {
                arr[i][j] = 0;
            }
        }
    }
    FullMatrix<double> L(arr, size, size);

    vector<double> b = { 1, 2, 4, 6, 105 };

    vector<double> result = Matrix<double>::solveCholeskySystem(L,b);

    MatrixRef<double> trasposedL = L.transpose();

    vector<double> result_with_trasposed = Matrix<double>::solveLUSystem(L, *trasposedL, b);
    ASSERT_EQ(result_with_trasposed, result);

    for (int i = 0; i < size; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}
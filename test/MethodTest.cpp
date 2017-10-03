#include <gtest/gtest.h>
#include "../src/matrix/Matrix.h"
#include "../src/matrix/FullMatrix.h"
#include "../src/Methods.h"

class MethodTest : public ::testing::Test {
protected:

    virtual void TearDown() {
        if(m != nullptr) {
            delete m;
            m = nullptr;
        }
    }

    Matrix<double>* m = nullptr;
};

TEST_F(MethodTest, int_eigenvalue) {
    m = new FullMatrix<double>({{3,0},{2,-1}});
    double evalue = 3;
    vector<double> evector = {2,1};
    double evectorNorm = Vectors::twoNorm(evector);

    vector<double> v(m->height(), 0);
    double delta = 0.001;
    unsigned long iterations = 10;
    ASSERT_NEAR(evalue, Methods::power_method(*m, v, delta, iterations), delta);
    double vNorm = Vectors::twoNorm(v);

    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_NEAR(evector[i]/evectorNorm, v[i]/vNorm, delta);
    }
}
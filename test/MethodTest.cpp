#include <gtest/gtest.h>
#include "../src/matrix/Matrix.h"
#include "../src/matrix/FullMatrix.h"
#include "../src/Methods.h"

class MethodTest : public ::testing::Test {
protected:

    MatrixRef<double> m;
};

TEST_F(MethodTest, int_eigenvalue) {
    std::initializer_list<std::vector<double>> m_base{{3,0},{2,-1}};
    m = std::make_shared<FullMatrix<double>>(m_base);
    double evalue = 3;
    vector<double> evector = {2,1};
    double evectorNorm = Vectors::twoNorm(evector);

    vector<double> v(m->height(), 0);
    double delta = 0.001;
    unsigned long iterations = 10;
    ASSERT_NEAR(evalue, Methods::power_method(m, v, delta, iterations), delta);
    double vNorm = Vectors::twoNorm(v);

    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_NEAR(evector[i]/evectorNorm, v[i]/vNorm, delta);
    }
}
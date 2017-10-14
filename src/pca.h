#ifndef METNUM_TP2_PCA_H
#define METNUM_TP2_PCA_H

#include <vector>

vector<double> get_mean(const Matrix<double> &X);

MatrixRef<double> substract_mean(const Matrix<double>& X, vector<double> &mean);

vector<vector<double>> get_eigenvectors(MatrixRef<double> M_x, unsigned int alfa);

/*
 * 1 <= alfa <= filas(X)
 */
MatrixRef<double> pca(const MatrixRef<double> X, unsigned int alfa = 100);

#endif //METNUM_TP2_PCA_H

#ifndef METNUM_TP2_PCA_H
#define METNUM_TP2_PCA_H

#include <vector>
#include <limits>
#include "power.h"

vector<double> get_mean(const Matrix<double> &X) {
    vector<double> mean;
    for (size_t j = 0; j < X.width(); j++) {
        double sum = 0;
        for (size_t i = 0; i < X.height(); i++)
            sum += X[i][j];
        mean.push_back(sum / X.height());
    }
    return mean;
}

MatrixRef<double> substract_mean(const Matrix<double>& X, vector<double> &mean) {
    MatrixRef<double> result = X.makeNew();
    for (size_t i = 0; i < X.height(); i++) {
        for (size_t j = 0; j < X.width(); j++) {
            (*result)[i][j] = X[i][j] - mean[j];
        }
    }
    return result;
}

vector<vector<double>> get_autovectors(MatrixRef<double> M_x, unsigned int alfa) {
    vector<vector<double>> autovectors;
    for (unsigned int i = 0; i < alfa; i++) {
        vector<double> autovector;
        double autovalue = power_method(M_x, autovector, 0.001, 30);
        autovectors.push_back(autovector);
        M_x = deflate(M_x, autovector, autovalue);
    }
    return autovectors;
}

/*
 * 1 <= alfa <= filas(X)
 */
MatrixRef<double> pca(const MatrixRef<double> X, unsigned int alfa) {
    // Calcular X - mean
    vector<double> mean = get_mean(*X);
    MatrixRef<double> X_sub_mean = substract_mean(*X, mean);

    // Calcular M_x
    X_sub_mean->inplaceTranspose();
    MatrixRef<double> M_x = X_sub_mean->transposedProduct()->dotProduct(1.0/ (X_sub_mean->width() - 1));

    // Calcular autovalores y autovectores
    vector<vector<double>> autovectors = get_autovectors(M_x, std::min(alfa, (unsigned int) X_sub_mean->width()));

    // Construir V ortogonal con los autovectores de M_x dispuestos como
    // columnas. Alfa es la cantidad de autovectores que se toman; se
    // descartan el resto de los autovectores, tomando de esta manera
    // solo los principales.
    // Como solo usamos V^t, la creamos con los autovectores como filas
    return FullMatrix<double>::create(autovectors);
}

#endif //METNUM_TP2_PCA_H

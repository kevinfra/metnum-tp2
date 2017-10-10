#ifndef METNUM_TP2_PCA_H
#define METNUM_TP2_PCA_H

#include <vector>
#include <limits>
#include "matrix/FullMatrix.h"
#include "Methods.h"

vector<double> get_mean(const MatrixRef<double> &X) {
    vector<double> mean;
    for (int j = 0; j < X->width(); j++) {
        double sum = 0;
        for (int i = 0; i < X->height(); i++)
            sum += (*X)[i][j];
        mean.push_back(sum / X->height());
    }
    return mean;
}

MatrixRef<double> substract_mean(const MatrixRef<double> X, vector<double> &mean) {
    MatrixRef<double> result = X;
    for (int i = 0; i < X->height(); i++) {
        for (int j = 0; j < X->width(); j++) {
            (*X)[i][j] = (*X)[i][j] - mean[j];
        }
    }
    return result;
}

MatrixRef<double> transposedProduct(vector<double> v) {
    MatrixRef<double> mat = std::make_shared<FullMatrix<double>>(v.size(), v.size());
    for (int i = 0; i < v.size(); i++)
        for (int j = 0; j < v.size(); j++)
            (*mat)[i][j] = (*mat)[i][j] + v[i] * v[j];
    return mat;
}

vector<vector<double>> get_autovectors(MatrixRef<double> M_x, const int alfa) {
    vector<vector<double>> autovectors;
    for (int i = 0; i < alfa; i++) {
        // esto te va a traer un solo autovector, estas corriendo sobre la misma matriz
        vector<double> autovector;
        double autovalue = Methods::power_method(M_x, autovector, 0.001, 30);
        autovectors.push_back(autovector);
        M_x = (*M_x) - *transposedProduct(autovector)->dotProduct(autovalue);
    }
    return autovectors;
}

MatrixRef<double> build_matrix(vector<vector<double>> vectors) {
    int width = vectors.size();
    int height = vectors[0].size();
    MatrixRef<double> mat = std::make_shared<FullMatrix<double>>(height, width);
    for (int j = 0; j < width; j++)
        for (int i = 0; i < height; i++)
            (*mat)[i][j] = vectors[j][i];
    return mat;
}

/*
 * 1 <= alfa <= filas(X)
 */
MatrixRef<double> pca(size_t k, const MatrixRef<double> &X, const int alfa) {
    // Calcular X - mean
    vector<double> mean = get_mean(X);
    MatrixRef<double> X_sub_mean = substract_mean(X, mean);

    // Calcular M_x
    MatrixRef<double> M_x = X->transpose()->transposedProduct()->dotProduct(1.0/X->height());

    // Calcular autovalores y autovectores
    vector<vector<double>> autovectors = get_autovectors(M_x, alfa);

    // Construir V ortogonal con los autovectores de M_x dispuestos como
    // columnas. Alfa es la cantidad de autovectores que se toman; se
    // descartan el resto de los autovectores, tomando de esta manera
    // solo los principales.
    MatrixRef<double> V = build_matrix(autovectors);

    // Cambio de base haciendo V^t * X
    // Cuanto mas recortado este V, mas dimensiones de X se tiran
    return V->transpose()->dotProduct(*X);
}

#endif //METNUM_TP2_PCA_H

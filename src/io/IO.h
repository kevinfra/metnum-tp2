#ifndef METNUM_TP2_IO_H
#define METNUM_TP2_IO_H

#include <fstream>
#include "../matrix/Matrix.h"
#include "../matrix/FullMatrix.h"

template < typename T>
struct TrainCase {
    MatrixRef<T> img;
    unsigned char digit;
};

namespace IO {

    template < typename T >
    MatrixRef<T> splitAndParse(const std::string& s, char delimiter) {
        size_t prev = 0;
        size_t next = 0;
        std::string token;
        MatrixRef<T> m = std::make_shared<FullMatrix<T>>(28, 28);
        for (size_t i = 0; i < 28; ++i) {
            for (size_t j = 0; j < 28; ++j) {
                next = s.find(delimiter, prev);
                token = s.substr(prev, next - prev);
                (*m)[i][j] = T(std::stoi(token));
                prev = next + 1;
            }
        }
        return m;
    }

    template < typename T >
    vector<TrainCase<T>> loadTrainSet(std::ifstream& file) {
        vector<TrainCase<T>> set;
        std::string line;
        std::getline(file, line);
        while(std::getline(file, line)) {
            size_t digitEnd = line.find(',');
            unsigned char digit = std::stoi(line.substr(0, digitEnd));
            line.erase(0, digitEnd + 1);
            set.push_back({IO::splitAndParse<T>(line, ','), digit});
        }
        return set;
    }

    template < typename T >
    vector<MatrixRef<T>> loadTestSet(std::ifstream& file) {
        vector<MatrixRef<T>> set;
        std::string line;
        std::getline(file, line);
        while(std::getline(file, line)) {
            set.push_back(IO::splitAndParse<T>(line, ','));
        }
        return set;
    }

    void clearFile(const std::string& fn);
}


#endif //METNUM_TP2_IO_H
